open Lwt.Infix

let on_exn = function
  | Unix.Unix_error (error, func, arg) ->
    Logs.warn (fun m ->
      m  "Client connection error %s: %s(%S)"
        (Unix.error_message error) func arg
    )
  | exn -> Logs.err (fun m -> m "Unhandled exception: %a" Fmt.exn exn)

module Graphql_cohttp_lwt = Graphql_cohttp.Make (Graphql_lwt.Schema) (Cohttp_lwt_unix.IO) (Cohttp_lwt.Body)

let make_response_compressed ~headers body =
  let body' = Ezgzip.compress body in
  let len = Bytes.length (Bytes.of_string body') in
  let headers' = Cohttp.Header.add_list headers [
    "Content-Length", string_of_int(len);
    "Access-Control-Allow-Origin", "*";
    "Content-Encoding", "gzip"
  ] in
  
  `Expert (Cohttp.Response.make ~status:`OK ~headers:headers' (), fun _in oc -> body' |> Lwt_io.write oc >>= fun () ->  Lwt_io.flush oc)

let verbs = Yojson.Basic.from_file "./verb_dict.json" |> Compverb.Json.decode

let cors_headers () =
  Cohttp.Header.add_list 
    (Cohttp.Header.init ())
    [
    "Access-Control-Allow-Origin", "*";
    "Access-Control-Allow-Methods", "GET, PUT, POST, DELETE, HEAD, OPTIONS";
    "Access-Control-Allow-Headers", "content-type";
    "Content-Length", "0"
    ]

let on_request conn req body =
  let req_path = Cohttp.Request.uri req |> Uri.path in
  let path_parts = Str.(split (regexp "/") req_path) in

  match req.meth, path_parts with
  | `OPTIONS, ["graphql"] -> 
    Cohttp_lwt_unix.IO.return 
      (`Response (Cohttp.Response.make ~status:`OK ~headers:(cors_headers ()) (), Cohttp_lwt.Body.of_string ""))
  
  | `POST, ["graphql"] -> Graphql_cohttp_lwt.execute_request Gql.schema { verbs } req body >>=
                            (fun resp -> match resp with
                            | `Response(_, b) ->
                                Cohttp_lwt.Body.to_string b >>= 
                                (fun d -> Cohttp_lwt_unix.IO.return (make_response_compressed ~headers:(Cohttp.Header.init ()) d))
                            | `Expert(_) as a -> Cohttp_lwt_unix.IO.return a)
  
  | _,  _ -> (Graphql_cohttp_lwt.make_callback (fun _ : Gql.ctx -> { verbs }) Gql.schema) conn req body

let () =
  let server = Cohttp_lwt_unix.Server.make_response_action ~callback:on_request () in
  let port = try int_of_string (Sys.getenv "PORT") with Not_found -> 8080 in
  let mode = `TCP (`Port port) in

  Cohttp_lwt_unix.Server.create ~on_exn ~mode server
  |> Lwt_main.run