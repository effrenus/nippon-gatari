module Styles = VerbPanel__Styles;

module Filter = {
    type t = {
        word: option(string),
    };

    let apply = (verbs, filterParams) => {
        let filterByWord = verbs => 
                filterParams.word
                ->Belt.Option.mapWithDefault(verbs, word => verbs|>Js.Array.filter(verb => Js.String.includes(word, verb##in_kana)));

        verbs
        |> filterByWord
    };
}

type action = 
  | UpdatePage(int)
  | UpdateFilterWord(string)
  | HighliteVerb(int);

type state = {
    page: int,
    filter: Filter.t,
    highliteVerbIndex: option(int),
};

let onSearchInput = (event, {ReasonReact.send}) =>
    Js.Re.fromStringWithFlags("[a-z0-9]", ~flags="i")
    |> Js.Re.test(ReactEvent.Form.target(event)##value->Hepburn.hiraganaOfRomaji)
    ? ()
    : ReactEvent.Form.target(event)##value->Hepburn.hiraganaOfRomaji->UpdateFilterWord->send

let component = ReasonReact.reducerComponent("Nippon.VerbPanel");

let make = (~verbs, _children) => {
    ...component,
    reducer: (action, state) => switch (action) {
    | UpdatePage(page) => ReasonReact.Update({ ...state, page: page, highliteVerbIndex: None })
    | UpdateFilterWord(word) => ReasonReact.Update({ 
            page: 1,
            highliteVerbIndex: None,
            filter: { word: (word == "" ? None : Some(word)) }
        })
    | HighliteVerb(index) => ReasonReact.Update({ ...state, highliteVerbIndex: Some(index) })
    },
    initialState: () => {
        page: 1, filter: { word: None }, highliteVerbIndex: None,
    },
    render: ({ state, send, handle }) => {
        let page = state.page - 1;
        let perPage = 15;
        let filteredVerbs = Filter.apply(verbs, state.filter);
        let visibleVerbs = filteredVerbs->Belt.Array.slice(~offset=page*perPage, ~len=perPage);

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
                            placeholder={j|Поиск|j}
                            type_="text"
                        />
                    </div>
                    
                    <ul className=Styles.list>
                        ...{visibleVerbs
                            ->Belt.Array.mapWithIndex((i, verb) => <VerbsListItem onClick=(_event => send(HighliteVerb(i))) verb=verb />)}
                    </ul>
                    <ListPaginator 
                        currentPage=state.page
                        totalCount=float_of_int(Belt.Array.length(filteredVerbs))
                        perPage=float_of_int(perPage)
                        onPageClick=(page => send(UpdatePage(page))) />
                </div>

                <Cards verbs=visibleVerbs highliteVerbIndex=state.highliteVerbIndex />
            </section>
        </section>
    }
}