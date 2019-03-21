open Lwt
open Cohttp_lwt_unix

let rec fetch = function
  hd :: tl -> Client.get (Uri.of_string hd) >>= fun (_resp, body) ->
    body |> Cohttp_lwt.Body.to_string >>= fun body ->
    let s = 
      Soup.parse body
      |> Soup.select_one("h1+.ad_in_content+p")
      |> Base.Option.bind ~f:Soup.leaf_text
    in
    Base.Option.iter s ~f:print_endline;
    Lwt_unix.sleep 5. >>= fun () -> fetch tl
  | [] -> Lwt.return ()