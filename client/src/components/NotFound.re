module Styles = {
    open Css;
   
    let container = style([
        position(`fixed),
        top(pct(50.)),
        left(pct(50.)),
        width(px(500)),
        padding(px(30)),
        transform(`translate(pct(-50.), pct(-50.))),
        fontSize(rem(1.8)),
        textAlign(`center),
    ]);
};

let component = ReasonReact.statelessComponent("Nippon.NotFound");

let make = _ => {
    ...component,
    render: _ =>
    <div className=Styles.container>
        {{j|Страница не найдена ¯\\_(ツ)\\_/¯|j}->ReasonReact.string}
    </div>
}