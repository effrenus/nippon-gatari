open Yojson

type cell = {
  _1: string [@key "1"];
  _2: string [@key "2"];
  kanji: string [@key "3"];
  _4: string [@key "4"];
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

type t = {
  page: string;
  total: int;
  records: string;
  rows: row list;
} [@@deriving yojson]

let struct_by_kanji_exn r k =
  r.rows
  |> List.find_opt (fun v -> String.equal v.cell.kanji k)
  |> Base.Option.value_map ~default:"?" ~f:(fun v -> v.cell.struct_)

let load ~path () =
  let d = Safe.from_file path in
  let s = of_yojson d in
  match s with
  | Ok(v) -> v
  | Error(err) -> failwith err