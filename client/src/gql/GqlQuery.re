module GetAllVerbsGql = [%graphql
  {|
  query getAllVerbs {
    verbs {
        in_kanji
        in_kana
        struct_type
        definitions
        struct_parts
        transitivity_type
        examples {
          in_kanji
          in_kana
          translation
        }
    }
  }
|}];

module GetAllVerbsComponent = ReasonApollo.CreateQuery(GetAllVerbsGql);