module Styles = {
    open Css;
    
    let item = style([
      display(`flex),
      padding2(~v=px(10), ~h=px(5)),
      borderBottom(px(1), `solid, `hex("EEE")),
      cursor(`pointer),
      hover([
          backgroundColor(`hex("EEE"))
      ])
    ]);

    let word = style([
      width(pct(100.)),
    ]);

    let kana = style([
      fontSize(em(0.85)),
    ]);

    let kanji = style([
      marginRight(px(10)),
    ]);

    let transitivity = style([
      width(px(75)),
      textAlign(`center),
    ]);

    let struct_ = style([
      width(px(75)),
      textAlign(`center),
    ]);
};

let component = ReasonReact.statelessComponent("Nippon.VerbsListItem");

let make = (~verb, _children) => {
    ...component,
    render: _ => {
      <li className=Styles.item>
        <div className=Styles.word>
          <span className=Styles.kanji>{ReasonReact.string(verb##in_kanji)}</span>
          <span className=Styles.kana>{ReasonReact.string(verb##in_kana)}</span>
        </div>
        <div className=Styles.transitivity>
          {ReasonReact.string(verb##transitivity_type)}
        </div>
        <div className=Styles.struct_>
          {ReasonReact.string(verb##struct_type)}
        </div>
      </li>
    },
  };