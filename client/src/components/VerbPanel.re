module Styles = VerbPanel__Styles;

module Filter = {
    type t = {
        word: option(string),
        page: int,
    };

    type action = UpdateWord(string) | UpdatePage(int);

    let empty = {
        word: None,
        page: 1,
    };

    let apply = (verbs, filterParams) => {
        let filterByWord = verbs => {
            let word = filterParams.word->Belt.Option.map(w => w->Hepburn.hiraganaOfRomaji);
            let filter = (word, verb) => Js.String.includes(word, Hepburn.containsKanji(word) ? verb##in_kanji : verb##in_kana);

            word
            ->Belt.Option.mapWithDefault(verbs, word => verbs |> Js.Array.filter(filter(word)));
        }

        verbs
        |> filterByWord
    };

    let update = (filter, action) => switch (action) {
    | UpdateWord(word) => { page: 1, word: (word == "" ? None : Some(word)) }
    | UpdatePage(num) =>  { ...filter, page: num }
    }

    let toJson = filter => {
        let dict = Js.Dict.empty ();
        dict -> Js.Dict.set("word", filter.word->Belt.Option.mapWithDefault(Js.Json.null, Js.Json.string));
        dict -> Js.Dict.set("page", filter.page->float_of_int->Js.Json.number);

        Js.Json.object_(dict)
    }

    let fromJson = val_ => {
        open Belt.Option;

        let p = Js.Json.parseExn(val_);

        Js.Json.decodeObject(p)
        -> map(dict => {
            word: dict->Js.Dict.get("word")->flatMap(Js.Json.decodeString),
            page: dict->Js.Dict.get("page")->flatMap(Js.Json.decodeNumber)->map(int_of_float)->getWithDefault(1)
           })
    }

    let save = filter => {
        let url = ReasonReact.Router.dangerouslyGetInitialUrl();
        let params =
            url
            -> Router.getSearchParams
            -> Belt.List.keep(p => !Belt.List.has(["word", "page"], p, (a, (k, _)) => k == a))
            -> Belt.List.concat([
                ("page", Some(filter.page->string_of_int)),
                ("word", filter.word)
               ])
            -> Belt.List.reduce("", (acc, (k, v)) => acc ++ "&" ++ (switch v {  | None => "" | Some(d) => k ++ "=" ++ d }))
            -> Js.String.substr(~from=1);

        Router.string_of_url({...url, search: params})
        -> Router.pushSilentUnsafe
    }

    let restore = () => {
        open Belt;
        let searchParams =
            ReasonReact.Router.dangerouslyGetInitialUrl()
            |> Router.getSearchParams;
        let kCmp = (a, b) => a == b;

        {
            word: List.getAssoc(searchParams, "word", kCmp)->Option.flatMap(x => x),
            page: List.getAssoc(searchParams, "page", kCmp)
            -> Option.flatMap(x => x->Option.map(x => try (int_of_string(x)) { | _ => 1 }))
            -> Option.getWithDefault(1)
        }
    }
}

type action =
  | UpdateFilter(Filter.action)
  | HighliteVerb(int);

type state = {
    filter: Filter.t,
    highliteVerbIndex: option(int),
};

let onSearchInput = (event, {ReasonReact.send}) =>
    ReactEvent.Form.target(event)##value->Filter.UpdateWord->UpdateFilter->send

let component = ReasonReact.reducerComponent("Nippon.VerbPanel");

let make = (~verbs, _children) => {
    ...component,
    reducer: (action, state) => switch (action) {
    | UpdateFilter(action') => {
        let filter = Filter.update(state.filter, action');
        ReasonReact.UpdateWithSideEffects({ highliteVerbIndex: None, filter }, _ => filter->Filter.save)
    }
    | HighliteVerb(index) => ReasonReact.Update({ ...state, highliteVerbIndex: Some(index) })
    },
    initialState: () => {
        filter: Filter.restore(), highliteVerbIndex: None,
    },
    willReceiveProps: self => {...self.state, filter: Filter.restore()},
    render: ({ state, send, handle }) => {
        let perPage = 15;
        let filteredVerbs = Filter.apply(verbs, state.filter);
        let page = max(1, min((state.filter.page), (Js.Array.length(filteredVerbs)->float_of_int /. perPage->float_of_int)->ceil->int_of_float));
        let visibleVerbs = filteredVerbs->Belt.Array.slice(~offset=(page-1)*perPage, ~len=perPage);

        <section className=Styles.wrap>
            <header className=Styles.head>
                <h1 className=Styles.header>{j|Словарь составных глаголов|j}->ReasonReact.string</h1>
                <span className=Styles.subheader>{j|под редакцией |j}->ReasonReact.string <a href="http://www.nippon-gatari.info/" target="_blank">{j|Олеси Гончар|j}->ReasonReact.string</a></span>
            </header>
            <section className=Styles.panel>
                <div className=Styles.listWrap>
                    <div className=Styles.filter>
                        <input
                            className=Styles.search
                            onInput={handle(onSearchInput)}
                            value=?state.filter.word
                            placeholder={j|Поиск|j}
                            type_="text"
                        />
                    </div>

                    <ul className=Styles.list>
                        ...{visibleVerbs
                            -> Belt.Array.mapWithIndex((i, verb) => <VerbsListItem onClick=(_event => send(HighliteVerb(i))) verb=verb />)}
                    </ul>
                    <ListPaginator
                        currentPage=page
                        totalCount=float_of_int(Belt.Array.length(filteredVerbs))
                        perPage=float_of_int(perPage)
                        onPageClick=(page => page->Filter.UpdatePage->UpdateFilter->send) />
                </div>

                <Cards verbs=visibleVerbs highliteVerbIndex=state.highliteVerbIndex />
            </section>
        </section>
    }
}