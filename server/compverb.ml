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
    definition: int option;
    in_kanji: string;
    in_kana: string;
    translation: string;
}

type verb = {
    in_kanji: string;
    in_kana: string;
    definitions: string list;
    synonyms: string list option;
    struct_type: struct_type;
    transitivity_type: transitivity_type;
    struct_parts: string list;
    examples: example list option;
}

let string_of_transitivity_type = function
    Transitive -> "tr."
    | Intransitive -> "intr."

let transitivity_type_of_string = function
    "tr" -> Transitive
    | "intr" -> Intransitive
    | _ -> Intransitive

let string_of_struct_type = function
    `VV -> "VV"
    | `Vs -> "Vs"
    | `pV -> "pV"
    | `V -> "V"
    | `BackForm -> "back-form"
    | `Unknown -> ""

let struct_type_of_string = function
    "VV" -> `VV
    | "Vs" -> `Vs
    | "pV" -> `pV
    | "V" -> `V
    | "V (一語化)" -> `V
    | "back-form" -> `BackForm
    | _ -> `Unknown

module Json = struct
    open Yojson.Basic.Util
    
    let decode_example json = {
        definition = json |> member "definition" |> to_option (fun v -> v |> to_int );
        in_kanji = json |> member "in_kanji" |> to_string;
        in_kana = json |> member "in_kana" |> to_string;
        translation = json |> member "translation" |> to_string;
    }
    
    let decode_verb json = {
        in_kanji = (json |> member "in_kanji" |> to_string);
        in_kana = (json |> member "in_kana" |> to_string);
        synonyms = None;
        transitivity_type = (match (json |> member "transitivity_type" |> to_string) with | "tr" -> Transitive | "intr" | _ -> Intransitive);
        struct_type = json |> member "struct_type" |> to_string |> struct_type_of_string;
        definitions = (json |> member "definitions" |> to_list |> List.map to_string);
        struct_parts = (json |> member "struct_parts" |> to_list |> List.map to_string);
        examples = (json |> member "examples" |> to_option (fun j -> j |> to_list |> Base.List.map ~f:decode_example));
    }
    
    let decode json = json |> to_list |> List.map decode_verb

    let encode_example example =
        `Assoc [
            "definition", example.definition |> Base.Option.value_map ~default:`Null ~f:(fun v -> `Int v);
            "in_kanji", `String example.in_kanji;
            "in_kana", `String example.in_kana;
            "translation", `String (example.translation |> String.trim);
        ]

    let encode_verb verb =
        `Assoc [
            "in_kanji", `String verb.in_kanji;
            "in_kana", `String verb.in_kana;
            "definitions", `List (List.map (fun v -> `String (v|>String.trim)) verb.definitions);
            "synonyms", `Null;
            "struct_type", `String (string_of_struct_type verb.struct_type);
            "struct_parts", `List [`String (List.nth verb.struct_parts 0); `String (List.nth verb.struct_parts 1)];
            "transitivity_type", `String (match verb.transitivity_type with Transitive -> "tr" | Intransitive -> "intr");
            "examples", match verb.examples with None -> `Null | Some v -> `List (List.map encode_example v)
        ]

    let encode verbs = 
        `List (verbs |> List.map encode_verb)
end