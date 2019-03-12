module StrCyr : sig
  val to_lower : string -> string
  val to_upper : string -> string
  val capitalize : string -> string
end = struct
  (* Manipulations with cyrillic chars *)

  let iterate tr a =
    let rec loop d buf index = match Uutf.decode d with
    | `End -> Buffer.contents buf
    | `Uchar u ->
      Uutf.Buffer.add_utf_8 buf (tr index u);
      loop d buf (index + 1)
    | _ -> failwith (Printf.sprintf "Error on input string: %s\n Incorrect arguments." a)
    in

    loop (Uutf.decoder (`String a)) (Buffer.create 512) 0

  let to_lower_char u =
    match Uchar.to_int u with
    | code when code >= 1040 && code <= 1071 -> Uchar.of_int (code + 32)
    | _ -> u

  let to_upper_char u =
    match Uchar.to_int u with
    | code when code >= 1072 && code <= 1103 -> Uchar.of_int (code - 32)
    | _ -> u

  let to_lower = iterate (fun _ c -> to_lower_char c)
  let to_upper = iterate (fun _ c -> to_upper_char c) 
  let capitalize = iterate (fun i c -> match i with 0 -> to_upper_char c | _ -> c)

end

let honbun = Honbun.load ~path:"../dumps/honbun.json" ()

let parse_examples row =
  [
    List.nth_opt row 7;
    List.nth_opt row 8;
    List.nth_opt row 9;
    List.nth_opt row 10;
  ]
  |> List.filter (fun v -> (Base.Option.is_some v) && (Base.Option.value_exn v |> String.split_on_char '|' |> List.length) > 2)
  |> List.map (fun v -> Base.Option.value_exn v)
  |> List.map (fun cell ->
    let p = String.split_on_char '|' cell in
    try (match List.length p with
    3 ->
      {Compverb.
        definition = None;
        in_kanji = List.nth p 0;
        in_kana = List.nth p 1;
        translation = List.nth p 2 |> String.trim |> StrCyr.capitalize;
      }
    | 4 ->
      {Compverb.
        definition = Some (List.nth p 0 |> String.trim |> int_of_string);
        in_kanji = List.nth p 1;
        in_kana = List.nth p 2;
        translation = List.nth p 3 |> String.trim |> StrCyr.capitalize;
      }
    | _ -> failwith "Invalid example") with err -> print_endline cell; raise err
  )

let parse_csv_row acc row =
  match List.hd row with
  | "" -> acc
  | _ ->
    {Compverb.
      in_kanji = List.nth row 0;
      in_kana = List.nth row 1;
      definitions = List.nth row 2 |> String.split_on_char '|' |> List.map (fun x -> String.trim @@ StrCyr.to_lower x);
      synonyms = None;
      struct_type = (Honbun.struct_by_kanji_exn honbun (List.nth row 0) |> Compverb.struct_type_of_string);
      transitivity_type = Compverb.transitivity_type_of_string (List.nth row 6);
      struct_parts = [List.nth row 3; List.nth row 4];
      examples = match (parse_examples row) with [] -> None | v -> Some(v);
    } :: acc

let combine_edited_dict () =
  let edited_verbs = 
    Csv.load "../dumps/verbs_edited.csv"
    |> List.fold_left parse_csv_row []
  in
  edited_verbs
  |> List.rev
  |> Compverb.Json.encode
  |> Yojson.Basic.to_string
  |> print_endline

let () =
  combine_edited_dict ()
  (* Yomikata.fetch [
    "https://yomikatawa.com/kanji/%E7%A7%81%E3%81%AF%E8%B2%AF%E9%87%91%E3%82%92%E9%8A%80%E8%A1%8C%E3%81%AB%E9%A0%90%E3%81%91%E5%85%A5%E3%82%8C%E3%81%9F?search=1";
    "https://yomikatawa.com/kanji/%E3%81%93%E3%81%AE%E3%83%AF%E3%83%BC%E3%83%89%E3%81%AF%E3%80%81%E6%AD%A3%E3%81%97%E3%81%8F%E3%81%AA%E3%81%84%E5%8F%AF%E8%83%BD%E6%80%A7%E3%81%8C%E3%81%82%E3%82%8A%E3%81%BE%E3%81%99?search=1"
  ]
  |> Lwt_main.run *)