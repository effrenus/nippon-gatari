(* open Yojson *)
open Lwt
open Cohttp_lwt_unix

type cell = {
  _1: string [@key "1"];
  _2: string [@key "2"];
  _3: string [@key "3"];
  kanji: string [@key "4"];
  kana: string [@key "5"];
  _6: string [@key "6"];
  part_1_kanji: string [@key "7"];
  part_1_romaji: string [@key "8"];
  _9: string [@key "9"];
  part_2_kanji: string [@key "10"];
  part_2_romaji: string [@key "11"];
  struct_: string [@key "12"];
  _13: string [@key "13"];
  _14: string option [@key "14"];
  _15: string option [@key "15"];
  _16: string [@key "16"];
  _17: string [@key "17"];
  _18: string [@key "18"];
  _19: string [@key "19"];
  _20: string [@key "20"];
  _21: string option [@key "21"];
  _22: string option [@key "22"];
  _23: string option [@key "23"];
  _24: string option [@key "24"];
  _25: string option [@key "25"];
  _26: string option [@key "26"];
} [@@deriving yojson]

type row = {
  id: int;
  cell: cell;
} [@@deriving yojson]

type data = {
  page: string;
  total: int;
  records: string;
  rows: row list;
} [@@deriving yojson]

(* let () =
  let d = Safe.from_file "./dumps/honbun.json" in
  let s = data_of_yojson d in
  match s with
  | Ok(v) -> List.iter (fun r -> print_endline r.cell.kana) v.rows
  | Error(err) -> print_endline err *)

let rec fetch = function
  hd :: tl -> Client.get (Uri.of_string hd) >>= fun (_resp, body) ->
    body |> Cohttp_lwt.Body.to_string >>= fun _body ->
    print_endline "OK";
    Lwt_unix.sleep 5. >>= fun () -> fetch tl
  | [] -> Lwt.return ()

let () =
  fetch [
    "https://yomikatawa.com/kanji/%E7%A7%81%E3%81%AF%E8%B2%AF%E9%87%91%E3%82%92%E9%8A%80%E8%A1%8C%E3%81%AB%E9%A0%90%E3%81%91%E5%85%A5%E3%82%8C%E3%81%9F?search=1";
    "https://yomikatawa.com/kanji/%E3%81%93%E3%81%AE%E3%83%AF%E3%83%BC%E3%83%89%E3%81%AF%E3%80%81%E6%AD%A3%E3%81%97%E3%81%8F%E3%81%AA%E3%81%84%E5%8F%AF%E8%83%BD%E6%80%A7%E3%81%8C%E3%81%82%E3%82%8A%E3%81%BE%E3%81%99?search=1"
  ]
  |> Lwt_main.run