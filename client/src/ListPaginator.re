module Styles = {
    open Css;

    let pagination = style([
        position(`absolute),
        left(px(0)),
        bottom(px(0)),
        right(px(0)),
        height(px(30)),
        margin(px(0)),
        padding(px(0)),
        listStyleType(`none),
        backgroundColor(`hex("EEE")),
        lineHeight(px(30)),
        textAlign(`center),
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
}

let component = ReasonReact.statelessComponent("Nippon.ListPaginator");

let make = (~currentPage, ~totalCount, ~perPage, ~onPageClick, _children) => {
  ...component,
  render: _self =>
    <nav>
      <ul className=Styles.pagination>
        {(totalCount /. perPage |> ceil |> int_of_float)
         ->(Belt.List.makeBy(i => i + 1))
         ->(
             Belt.List.mapU((. page) => {
               let key = page |> string_of_int;
               <li
                 key
                 className={
                   Styles.item ++ (page === currentPage ? (" " ++ Styles.active) : "")
                 }
                 onClick={event => {
                   event->ReactEvent.Mouse.preventDefault;
                   onPageClick(page);
                 }}>
                 {key |> ReasonReact.string}
               </li>;
             })
           )
         |> Belt.List.toArray
         |> ReasonReact.array}
      </ul>
    </nav>,
};