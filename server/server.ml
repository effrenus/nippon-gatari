let serve_static path =
  match Server_assets.read path with
  | Some body -> body
  | None -> ""

let on_exn = function
  | Unix.Unix_error (error, func, arg) ->
    Logs.warn (fun m ->
      m  "Client connection error %s: %s(%S)"
        (Unix.error_message error) func arg
    )
  | exn -> Logs.err (fun m -> m "Unhandled exception: %a" Fmt.exn exn)

module Graphql_cohttp_lwt = Graphql_cohttp.Make (Graphql_lwt.Schema) (Cohttp_lwt_unix.IO) (Cohttp_lwt.Body)

let on_request gql_cb conn req body =
  let req_path = Cohttp.Request.uri req |> Uri.path in
  let path_parts = Str.(split (regexp "/") req_path) in
  match req.meth, path_parts with
    `GET,  ["graphql"]
  | `GET,  ["graphql"; _]
  | `POST, ["graphql"] -> gql_cb conn req body
  | _, _ ->
    `Response (Cohttp.Response.make ~status:`OK (), Cohttp_lwt.Body.of_string (serve_static "index.html")) 
    |> Cohttp_lwt_unix.IO.return

let () =
  let verbs = Yojson.Basic.from_file "./verb_dict.json" |> Compverb.Parse.parse in
  let callback = Graphql_cohttp_lwt.make_callback (fun _ : Gql.ctx -> { verbs }) Gql.schema in
  let server = Cohttp_lwt_unix.Server.make_response_action ~callback:(on_request callback) () in
  let mode = `TCP (`Port 8080) in

  Cohttp_lwt_unix.Server.create ~on_exn ~mode server
  |> Lwt_main.run