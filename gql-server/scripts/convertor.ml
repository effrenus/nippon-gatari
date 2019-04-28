module StrCyr : sig
  val to_lower : string -> string
  val to_upper : string -> string
  val capitalize : string -> string
  val contains : Uchar.t -> string -> bool
  val split_by : Uchar.t -> string -> string list
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

  let satisfy p s =
    let rec loop d = match Uutf.decode d with
    | `End -> false
    | `Uchar u ->
      if p u then 
        true 
      else 
        loop d
    | _ -> failwith (Printf.sprintf "Error on input string: %s\n Incorrect arguments." s)
    in

    loop (Uutf.decoder (`String s))

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
  let contains ch = satisfy (fun c -> Uchar.equal c ch)
  let split_by ch str =
    let chars = ref [] in
    let _ = iterate (fun _ c ->
      chars := c :: !chars;
      c
    ) str in
    
    List.rev !chars
    |> List.fold_left (fun (acc, buf) c -> 
      if Uchar.equal c ch then
        ((Buffer.contents buf) :: acc, Buffer.create 512)
      else begin
        Uutf.Buffer.add_utf_8 buf c;
        (acc, buf)
      end
    ) ([], Buffer.create 512)
    |> fun (acc, buf) -> (Buffer.contents buf) :: acc
    |> List.map String.trim
end

let honbun = Honbun.load ~path:"./honbun.json" ()

let parse_examples row =
  [
    List.nth_opt row 7;
    List.nth_opt row 8;
    List.nth_opt row 9;
    List.nth_opt row 10;
    List.nth_opt row 11;
    List.nth_opt row 12;
    List.nth_opt row 13;
  ]
  |> List.filter (fun v -> (Base.Option.is_some v) && (Base.Option.value_exn v |> String.split_on_char '|' |> List.length) > 2)
  |> List.map (fun v -> Base.Option.value_exn v)
  |> List.map (fun cell ->
    let p = String.split_on_char '|' cell |> List.map String.trim in
    try (match List.length p with
    3 ->
      {Compverb.
        definition = None;
        in_kanji = List.nth p 0;
        in_kana = List.nth p 1;
        translation = List.nth p 2 |> StrCyr.capitalize;
      }
    | 4 ->
      {Compverb.
        definition = Some (List.nth p 0 |> int_of_string);
        in_kanji = List.nth p 1;
        in_kana = List.nth p 2;
        translation = List.nth p 3 |> StrCyr.capitalize;
      }
    | _ -> failwith "Invalid example") with err -> print_endline cell; raise err
  )

let parse_csv_row rows =
  let synonyms = ref [] in
  let u_rarrow = Uchar.of_int 8594 in

  let parse acc row =
      let row' = List.map String.trim row in
      match List.hd row' with
      | "" -> acc
      | hd when StrCyr.contains u_rarrow hd ->
        let parts = try StrCyr.split_by u_rarrow hd with | _ -> print_endline hd; [""; ""] in
        let syn = List.nth parts 1 in
        let syn_of = List.nth parts 0 in
        synonyms := (syn_of, Compverb.{
            in_kanji = syn;
            in_kana = List.nth row' 1;
          }) :: !synonyms;
        acc
      | _ ->
        {Compverb.
          in_kanji = List.nth row' 0;
          in_kana = List.nth row' 1;
          definitions = List.nth row' 2 |> String.split_on_char '|' |> List.map (fun x -> String.trim @@ StrCyr.to_lower x);
          synonyms = None;
          struct_type = (Honbun.struct_by_kanji_exn honbun (List.nth row' 0) |> (fun type_ -> if String.equal type_ "?" then List.nth row' 5 else type_ ) |> Compverb.struct_type_of_string);
          transitivity_type = Compverb.transitivity_type_of_string (List.nth row' 6);
          struct_parts = [List.nth row' 3; List.nth row' 4];
          examples = match (parse_examples row') with [] -> None | v -> Some(v);
        } :: acc;
  in
  
  let verbs = List.fold_left parse [] rows in

  verbs
  |> List.map (fun verb ->
    let syns = !synonyms |> List.filter (fun (syn, _) -> String.equal syn verb.Compverb.in_kanji) |> List.map (fun (_, def) -> def) in
    {
      verb with synonyms = if List.length syns == 0 then None else Some syns
    }
  )

let combine_edited_dict () =
  let edited_verbs = 
    Csv.load "../dumps/verbs_edited.csv"
    |> parse_csv_row
  in
  edited_verbs
  |> List.rev
  |> Compverb.Json.encode
  |> Yojson.Basic.to_string
  |> print_endline

let () =
  combine_edited_dict ()
