type struct_type = [
    | `VV
    | `Vs
    | `pV
    | `V
    | `BackForm
    | `Unknown]

type transitivity_type =
    | Transitive
    | Intransitive

type example = {
    in_kanji: string;
    in_kana: string;
    translation: string;
}

type verb = {
    in_kanji: string;
    in_kana: string;
    definitions: string list;
    similars: string list option;
    struct_type: struct_type;
    transitivity_type: transitivity_type;
    struct_parts: string list;
    examples: example list option;
}

let string_of_transitivity_type = function
    Transitive -> "tr."
    | Intransitive -> "intr."

let string_of_struct_type = function
    `VV -> "VV"
    | `Vs -> "Vs"
    | `pV -> "pV"
    | `V -> "V"
    | `BackForm -> "back-form"
    | `Unknown -> ""

module Parse = struct
    open Yojson.Basic.Util
    let parse_example json = {
        in_kanji = json |> member "in_kanji" |> to_string;
        in_kana = json |> member "in_kana" |> to_string;
        translation = json |> member "translation" |> to_string;
    }
    let parse_verb json = {
        in_kanji = (json |> member "in_kanji" |> to_string);
        in_kana = (json |> member "in_kana" |> to_string);
        similars = None;
        transitivity_type = (match (json |> member "transitivity_type" |> to_string) with | "tr" -> Transitive | "intr" | _ -> Intransitive);
        struct_type = (match (json |> member "struct_type" |> to_string) with
            | "VV" -> `VV
            | "Vs" -> `Vs
            | "pV" -> `pV
            | "V" -> `V
            | "back-form" -> `BackForm
            | _ -> `Unknown);
        definitions = (json |> member "definitions" |> to_list |> List.map to_string);
        struct_parts = (json |> member "struct_parts" |> to_list |> List.map to_string);
        examples = (json |> member "examples" |> to_option (fun j -> j |> to_list |> Base.List.map ~f:parse_example));
    }
    let parse json = json |> to_list |> List.map parse_verb
end