open GqlQuery;

module Styles = {
  open Css;

  let neko = style([
    position(`fixed),
    left(pct(50.)),
    top(pct(50.)),
    textAlign(`center),
    fontSize(rem(1.5)),
    transform(`translate(pct(-50.), pct(-50.))),

    before([
      display(`block),
      contentRule(""),
      width(px(100)),
      height(px(100)),
      marginBottom(px(20)),
      backgroundImage(`url("/maneki-neko.svg")),
      backgroundSize(`contain),
      backgroundRepeat(`noRepeat),
      backgroundPosition(pct(50.), pct(50.))
    ])
  ]);
}

let component = ReasonReact.statelessComponent("Nippon.VerbsList");

let make = _children => {
    ...component,
    render: _ => {
      <GetAllVerbsComponent>
        ...{
             ({result}) =>
               switch (result) {
               | Loading => <div className=Styles.neko> {ReasonReact.string({j|Загрузка…|j})} </div>
               | Error(error) =>
                  <div> {ReasonReact.string(error##message)} </div>
               | Data(response) =>
                  <VerbPanel verbs=response##verbs />
               }
           }
      </GetAllVerbsComponent>;
    },
  };