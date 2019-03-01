module Styles = {
    open Css;

    let pagination = style([
        position(`absolute),
        left(px(0)),
        bottom(px(0)),
        right(px(0)),
        height(px(40)),
        margin(px(0)),
        padding(px(0)),
        listStyleType(`none),
        backgroundColor(`hex("d4d1d1")),
        lineHeight(px(28)),
        textAlign(`center),
        userSelect(`none),
    ]);

    let item = style([
        display(`inlineBlock),
        padding2(~v=px(0), ~h=px(8)),
        cursor(`pointer),
    ]);

    let active = style([
        fontWeight(`bold),
        backgroundColor(`hex("CCC")),
        borderRadius(px(10)),
    ]);

    let input = style([
      width(px(40)),
      textAlign(`center),
      fontSize(rem(1.)),
    ]);

    let pageTotal = style([
      position(`relative),
      top(px(2)),
      fontSize(rem(0.8)),
    ]);

    let arrow = style([
      fontSize(rem(2.)),
      fontWeight(`bold),
    ]);
    let activeArrow = style([
      color(`hex("205dbf")),
      cursor(`pointer),
    ]);
}

let component = ReasonReact.statelessComponent("Nippon.ListPaginator");

let make = (~currentPage, ~totalCount, ~perPage, ~onPageClick, _children) => {
  ...component,
  render: _self => {
    let pageCount = (totalCount /. perPage)->ceil->int_of_float;
    <nav className=Styles.pagination>
      {
        currentPage == 1
        ? <span className=Styles.arrow>{ReasonReact.string({j|←|j})}</span>
        : <span className=(Styles.arrow ++ " " ++ Styles.activeArrow) onClick={_evt => onPageClick(currentPage - 1)}>{ReasonReact.string({j|←|j})}</span>
      }
      <input
        type_="text"
        className=Styles.input
        value=string_of_int(currentPage)
        onInput={event => {
          let page = try (ReactEvent.Form.target(event)##value->int_of_string) {
          | _ => 1
          };
          onPageClick(max(1, min(page, pageCount)))
        }} />
      <span className=Styles.pageTotal>{(" / " ++ string_of_int(pageCount))->ReasonReact.string}</span>
      {
        currentPage == pageCount
        ? <span className=Styles.arrow>{ReasonReact.string({j|→|j})}</span>
        : <span className=(Styles.arrow ++ " " ++ Styles.activeArrow) onClick={_evt => onPageClick(currentPage + 1)}>{ReasonReact.string({j|→|j})}</span>
      }
    </nav>
  },
};