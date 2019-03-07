let component = ReasonReact.statelessComponent("Nippon.Redirect");

let make = (~r, _) => {
    ...component,
    didMount: _ => Js.Global.setTimeout(() => ReasonReact.Router.push(r), 10) |> ignore,
    render: _ => ReasonReact.null
}