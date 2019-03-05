module Styles = {
    open Css;
   
    let transitivity_tr = style([
        padding2(~v=px(5), ~h=px(3)),
        borderRadius(px(4)),
        backgroundColor(`hex("f7c5c5")),
        fontSize(rem(0.9)),
    ]);

    let transitivity_intr = style([
        padding2(~v=px(5), ~h=px(3)),
        borderRadius(px(4)),
        backgroundColor(`hex("d5e6ff")),
        fontSize(rem(0.9)),
    ]);
};

module TransitiveLabel = {
  let component = ReasonReact.statelessComponent("Nippon.TransitiveLabel");
  let make = _ => {
    ...component,
    render: _ => <span title={j|переходный глагол|j} className=Styles.transitivity_tr>{j|他|j}->ReasonReact.string</span>
  }
}

module IntransitiveLabel = {
  let component = ReasonReact.statelessComponent("Nippon.IntransitiveLabel");
  let make = _ => {
    ...component,
    render: _ => <span title={j|непереходный глагол|j} className=Styles.transitivity_intr>{j|自|j}->ReasonReact.string</span>
  }
}