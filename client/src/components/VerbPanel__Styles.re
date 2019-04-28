open Css;

let head = style([
    marginBottom(px(20)),
]);

let header = style([
    marginTop(px(0)),
    marginBottom(px(0)),
]);

let editor = style([
    display(`block),
    marginTop(px(15)),
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
    paddingRight(px(40)),
    boxSizing(`borderBox),
    lineHeight(px(45)),
    fontSize(rem(1.)),
    borderWidth(px(0)),
    borderBottomWidth(px(3)),
    borderRadius(px(5)),
]);

let filter = style([
    position(`relative),

    before([
        contentRule(""),
        position(`absolute),
        right(px(15)),
        top(px(11)),
        width(px(20)),
        height(px(20)),
        backgroundImage(`url("data:image/svg+xml;base64,PHN2ZyB4bWxucz0naHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmcnIHZpZXdCb3g9JzAgMCA1MTIgNTEyJz48cGF0aCBkPSdNNDk1IDQ2Ni4yTDM3Ny4yIDM0OC40YTIwNi42IDIwNi42IDAgMSAwLTI4LjkgMjguOUw0NjYuMSA0OTVhMjAuNCAyMC40IDAgMCAwIDI4LjktMjguOHptLTI3Ny41LTgzLjNDMTI2LjIgMzgyLjkgNTIgMzA4LjcgNTIgMjE3LjVTMTI2LjIgNTIgMjE3LjUgNTJDMzA4LjcgNTIgMzgzIDEyNi4zIDM4MyAyMTcuNXMtNzQuMyAxNjUuNC0xNjUuNSAxNjUuNHonLz48L3N2Zz4=")),
        backgroundRepeat(`noRepeat),
        backgroundSize(`cover),
        opacity(0.6),
    ]),
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