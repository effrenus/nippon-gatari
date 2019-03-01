module Styles = {
    open Css;

    let wrap = style([
        maxWidth(px(1500)),
        margin(`auto),
        padding4(~top=px(15), ~right=px(30), ~left=px(30), ~bottom=px(30)),
    ]);

    let head = style([
        marginBottom(px(20)),
    ]);

    let header = style([
        marginTop(px(0)),
        marginBottom(px(0)),
    ]);

    let subheader = style([
        fontSize(rem(0.9)),
    ]);

    let panel = style([
        display(`flex),
        justifyContent(`spaceAround),
        alignItems(`stretch),
        height(px(580)),
        boxSizing(`borderBox)
    ]);

    let search = style([
        width(pct(100.)),
        height(px(45)),
        marginBottom(px(0)),
        padding2(~v=px(0), ~h=px(10)),
        boxSizing(`borderBox),
        lineHeight(px(45)),
        fontSize(rem(1.)),
        borderWidth(px(0)),
        borderBottomWidth(px(3)),
        borderRadius(px(5)),
    ]);

    let listWrap = style([
        position(`relative),
        maxWidth(px(500)),
        width(pct(30.)),
        marginRight(px(30)),
        borderRadius(px(5)),
        backgroundColor(`hex("FFF")),
        boxShadow(~y=px(1), ~blur=px(10), `hex("999")),
    ]);
    
    let list = style([
        position(`absolute),
        left(px(0)),
        top(px(45)),
        right(px(0)),
        bottom(px(30)),
        margin(px(0)),
        padding(px(0)),
        overflow(`auto),
        listStyleType(`none),
    ]);
};

type action = 
  | UpdatePage(int)
  | FilterName(string)
  | HighliteVerb(int)
  | NoOp;

type state = {
    page: int,
    filterText: option(string),
    highliteVerbIndex: option(int),
};

let component = ReasonReact.reducerComponent("Nippon.VerbPanel");

let make = (~verbs, _children) => {
    ...component,
    reducer: (action, state) => switch (action) {
    | UpdatePage(page) => ReasonReact.Update({ ...state, page: page, highliteVerbIndex: None })
    | FilterName(word) => ReasonReact.Update({ ...state, page: 1, highliteVerbIndex: None, filterText: (word == "" ? None : Some(word)) })
    | HighliteVerb(index) => ReasonReact.Update({ ...state, highliteVerbIndex: Some(index) })
    | NoOp => ReasonReact.NoUpdate
    },
    initialState: () => {
        page: 1, filterText: None, highliteVerbIndex: None,
    },
    render: ({ state, send }) => {
        let page = state.page - 1;
        let perPage = 15;
        let allVerbs = switch (state.filterText) {
        | None => verbs
        | Some(text) => verbs|>Js.Array.filter(verb => Js.String.includes(text, verb##in_kana))
        };
        let filteredVerbs = allVerbs->Belt.Array.slice(~offset=page*perPage, ~len=perPage);
        <section className=Styles.wrap>
            <header className=Styles.head>
                <h1 className=Styles.header>{{j|Словарь составных глаголов|j}->ReasonReact.string}</h1>
                <span className=Styles.subheader>{{j|под редакцией |j}->ReasonReact.string} <a href="http://www.nippon-gatari.info/" target="_blank">{{j|Олеси Гончар|j}->ReasonReact.string}</a></span>
            </header>
            <section className=Styles.panel>
                <div className=Styles.listWrap>
                    <input
                        className=Styles.search
                        onInput={event => 
                                Js.Re.fromStringWithFlags("[a-z0-9]", ~flags="i")
                                |> Js.Re.test(ReactEvent.Form.target(event)##value->Hepburn.hiraganaOfRomaji)
                                ? ()
                                : ReactEvent.Form.target(event)##value->Hepburn.hiraganaOfRomaji->FilterName->send}
                        placeholder={j|Поиск|j}
                        type_="text"
                    />
                    
                    <ul className=Styles.list>
                        ...{filteredVerbs-> Belt.Array.mapWithIndex((i, verb) => <VerbsListItem onClick=(_event => send(HighliteVerb(i))) verb=verb />)}
                    </ul>
                    <ListPaginator 
                        currentPage=state.page
                        totalCount=float_of_int(Belt.Array.length(allVerbs))
                        perPage=float_of_int(perPage)
                        onPageClick=(page => send(UpdatePage(page))) />
                </div>

                <Cards verbs=filteredVerbs highliteVerbIndex=state.highliteVerbIndex />
            </section>
        </section>
    }
}