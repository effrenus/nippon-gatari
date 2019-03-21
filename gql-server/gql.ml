open Graphql_lwt

type ctx = {
  verbs: Compverb.verb list;
}

let example = Schema.(obj "example"
~fields:(fun _ -> [
  field "definition"
    ~args:Arg.[]
    ~typ:int
    ~resolve:(fun _ (p: Compverb.example) -> p.definition)
  ;
  field "in_kanji"
    ~args:Arg.[]
    ~typ:(non_null string)
    ~resolve:(fun _ (p: Compverb.example) -> p.in_kanji)
  ;
  field "in_kana"
    ~args:Arg.[]
    ~typ:(non_null string)
    ~resolve:(fun _ (p: Compverb.example) -> p.in_kana)
  ;
  field "translation"
    ~args:Arg.[]
    ~typ:(non_null string)
    ~resolve:(fun _ (p: Compverb.example) -> p.translation)
  ;])
)

let verb = Schema.(obj "verb"
  ~fields:(fun _verb -> [
    field "in_kanji"
      ~args:Arg.[]
      ~doc:"Kanji form of the verb"
      ~typ:(non_null string)
      ~resolve:(fun _ p -> p.Compverb.in_kanji)
    ;
    field "in_kana"
      ~args:Arg.[]
      ~doc:"Kana form of the verb"
      ~typ:(non_null string)
      ~resolve:(fun _ p -> p.Compverb.in_kana)
    ;
    field "definitions"
      ~args:Arg.[]
      ~doc:"Verb definitions in russian"
      ~typ:(non_null (list (non_null string)))
      ~resolve:(fun _ p -> p.Compverb.definitions)
    ;
    field "synonyms"
      ~args:Arg.[]
      ~doc:"Synonyms"
      ~typ:(list (non_null string))
      ~resolve:(fun _ p -> p.Compverb.synonyms)
    ;
    field "struct_parts"
      ~args:Arg.[]
      ~doc:"Verb simple parts of which it consists"
      ~typ:(non_null (list (non_null string)))
      ~resolve:(fun _ p -> p.Compverb.struct_parts)
    ;
    field "struct_type"
      ~args:Arg.[]
      ~typ:(non_null string)
      ~resolve:(fun _ p -> Compverb.string_of_struct_type p.Compverb.struct_type)
    ;
    field "transitivity_type"
      ~args:Arg.[]
      ~doc:"Transitivity type (`tr.`, `intr.`)"
      ~typ:(non_null string)
      ~resolve:(fun _ p -> Compverb.string_of_transitivity_type p.Compverb.transitivity_type)
    ;
    field "examples"
      ~args:Arg.[]
      ~typ:(list (non_null example))
      ~resolve:(fun _ p -> p.Compverb.examples)
  ])
)

let schema = Schema.(schema [
    io_field "verbs"
      ~args:Arg.[]
      ~typ:(non_null (list (non_null verb)))
      ~resolve:(fun info () -> Lwt_result.return info.ctx.verbs)
    ;
    io_field "getVerbByName"
      ~args:Arg.[
        arg "name" ~typ:(non_null string)
      ]
      ~typ:verb
      ~resolve:(fun info () name ->
        let decoded_name = Uri.pct_decode name in
        info.ctx.verbs
        |> Base.List.find ~f:(fun v -> Base.String.(=) v.Compverb.in_kana decoded_name)
        |> Lwt_result.return)
    ;
  ]
)