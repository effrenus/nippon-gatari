module Styles = {
    open Css;

    let panel = style([
      display(`flex),
      justifyContent(`spaceAround),
      alignItems(`stretch),
      height(vh(80.)),
      padding(px(30)),
      boxSizing(`borderBox)
    ]);

    let search = style([
        width(`calc(`sub, pct(100.), px(60))),
        margin2(~v=px(0), ~h=px(30)),
        padding(px(10)),
        boxSizing(`borderBox),
        lineHeight(px(30)),
        fontSize(rem(1.2)),
    ]);

    let listWrap = style([
        position(`relative),
        maxWidth(px(500)),
        width(pct(30.)),
        marginRight(px(30)),
    ]);
    
    let list = style([
      position(`absolute),
      left(px(0)),
      top(px(0)),
      right(px(0)),
      bottom(px(30)),
      margin(px(0)),
      padding(px(0)),
      overflow(`auto),
      listStyleType(`none),
      backgroundColor(`hex("FFF")),
      boxShadow(~y=px(1), ~blur=px(20), `hex("a1c4fd")),
    ]);

    let cards = style([
      width(pct(70.)),
      overflow(`auto),
      backgroundColor(`hex("FFF")),
      boxShadow(~y=px(1), ~blur=px(20), `hex("a1c4fd")),
    ]);
};

type action = 
  | UpdatePage(int)
  | FilterName(string)
  | NoOp;

type state = {
    page: int,
    filterText: option(string),
};

let component = ReasonReact.reducerComponent("Nippon.VerbPanel");

let make = (~verbs, _children) => {
    ...component,
    reducer: (action, state) => switch (action) {
    | UpdatePage(page) => ReasonReact.Update({ ...state, page: page })
    | FilterName(word) => ReasonReact.Update({ ...state, filterText: (word == "" ? None : Some(word)) })
    | NoOp => ReasonReact.NoUpdate
    },
    initialState: () => {
        page: 1, filterText: None
    },
    render: ({ state, send }) => {
        let page = state.page - 1;
        let perPage = 15;
        let allVerbs = switch (state.filterText) {
        | None => verbs
        | Some(text) => verbs|>Js.Array.filter(verb => Js.String.includes(text, verb##in_kana))
        };
        let filteredVerbs = allVerbs->Belt.Array.slice(~offset=page*perPage, ~len=perPage);
        <div>
            <input
                className=Styles.search
                onInput={event => ReactEvent.Form.target(event)##value->Hepburn.hiraganaOfRomaji->FilterName->send}
                placeholder={j|Поиск|j}
                type_="text"
            />
            <section className=Styles.panel>
                <div className=Styles.listWrap>
                    <ul className=Styles.list>
                        ...{filteredVerbs-> Belt.Array.map(verb => <VerbsListItem verb=verb />)}
                    </ul>
                    <ListPaginator 
                        currentPage=state.page
                        totalCount=float_of_int(Belt.Array.length(allVerbs))
                        perPage=float_of_int(perPage)
                        onPageClick=(page => send(UpdatePage(page))) />
                </div>

                <div className=Styles.cards>
                    ...{filteredVerbs-> Belt.Array.map(verb => <VerbCard verb=verb />)}
                </div>
            </section>
        </div>
    }
}