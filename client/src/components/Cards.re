module Styles = {
    open ExtendedCss;

    let cards = style([
      width(pct(70.)),
      overflow(`auto),
      backgroundColor(`hex("FFF")),
      boxShadow(~y=px(1), ~blur=px(10), `hex("999")),
      scrollBehavior(`smooth),
    ]);
};

type action = NoOp;

type state = {
    ref_: ref(option(Dom.element)),
}

let setRef = (ref_, {ReasonReact.state}) => 
    state.ref_ := Js.Nullable.toOption(ref_);

let component = ReasonReact.reducerComponent("Nippon.VerbCards");

let make = (~verbs, ~highliteVerbIndex, _children) => {
    ...component,
    initialState: () => {ref_: ref(None)},
    willReceiveProps: ({ state }) => {
        switch ((state.ref_^, highliteVerbIndex)) {
        | (Some(domRef), Some(index)) => {
            let elm = domRef
                |> Webapi.Dom.Element.children
                |> Webapi.Dom.HtmlCollection.item(index);
            elm 
            -> Belt.Option.map((elm => elm |> Webapi.Dom.Element.scrollIntoView))
            |> ignore;
        }
        | (_, _) => ()
        }
        state
    },
    reducer: (action, _) => switch (action) {
    | NoOp => ReasonReact.NoUpdate
    },
    render: self => {
        let highliteIndex = switch (highliteVerbIndex) {
        | Some(index) => index
        | None => -1
        };
        <div className=Styles.cards ref={self.handle(setRef)}>
            ...{verbs-> Belt.Array.mapWithIndex((i, verb) => <VerbCard highlite={i == highliteIndex ? true : false} verb=verb />)}
        </div>
    }
}