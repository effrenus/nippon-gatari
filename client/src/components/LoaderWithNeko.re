module Styles = {
    open Css;
  
    let neko = style([
      position(`fixed),
      left(pct(50.)),
      top(pct(50.)),
      textAlign(`center),
      fontSize(rem(1.3)),
      transform(`translate(pct(-50.), pct(-50.))),
  
      before([
        display(`block),
        contentRule(""),
        width(px(100)),
        height(px(100)),
        marginBottom(px(10)),
        backgroundImage(`url("/assets/maneki-neko.svg")),
        backgroundSize(`contain),
        backgroundRepeat(`noRepeat),
        backgroundPosition(pct(50.), pct(50.))
      ])
    ]);
}

let component = ReasonReact.statelessComponent("Nippon.LoaderWithNeko");

let make = _children => {
    ...component,
    render: _ => <div className=Styles.neko> {ReasonReact.string({j|Загрузка…|j})} </div>,
  };