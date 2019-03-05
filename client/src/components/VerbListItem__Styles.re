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
    paddingLeft(px(6)),
    lineHeight(px(25)),
]);

let kana = style([
    fontSize(em(0.75)),
]);

let kanji = style([
    marginRight(px(10)),
]);

let transitivity = style([
    width(px(75)),
    textAlign(`center),
    lineHeight(px(25)),
]);

let struct_ = style([
    width(px(75)),
    textAlign(`center),
    lineHeight(px(25)),
]);