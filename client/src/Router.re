module Link = {
  let component = ReasonReact.statelessComponent("Link");

  let make = (~href, ~id=?, ~className=?, ~title=?, ~role=?, children) => {
    ...component,
    render: self =>
      <a
        ?id
        ?className
        ?title
        ?role
        href
        onClick=(
          self.handle((event, _self) =>
            if (!event->ReactEvent.Mouse.ctrlKey
                && event->ReactEvent.Mouse.button != 1) {
              event->ReactEvent.Mouse.preventDefault;
              ReasonReact.Router.push(href);
            }
          )
        )>
        ...children
      </a>,
  };
};

type route =
  | CompoundVerbs
  | Redirect(string)
  | CompoundVerbDetail(string)
  | NotFound;

[@bs.send]
external pushState:
  (Dom.history, [@bs.as {json|null|json}] _, [@bs.as ""] _, ~href: string) =>
  unit =
  "";

let pushSilentUnsafe = path =>
  switch ([%external history], [%external window]) {
  | (None, _)
  | (_, None) => ()
  | (Some((history: Dom.history)), Some(_)) =>
    pushState(history, ~href=path)
  };

let getSearchParams = (url: ReasonReact.Router.url) =>
  url.search
  |> Js.String.split("&")
  |> Js.Array.map (v => {
      let pair = v|>Js.String.split("=");
      Js.Array.length(pair) > 1
        ? (pair[0], Some(pair[1]->Js.Global.decodeURIComponent))
        : (pair[0], None)
  })
  |> Belt.List.fromArray

let makeUrl = path => ReasonReact.Router.{
  path: path |> Js.String.split("/") |> Array.to_list,
  hash: "",
  search: ""
};

let string_of_url = (url: ReasonReact.Router.url) => {
  let join = (arr, delim) => arr->Belt.List.reduce("", (acc, v) => acc ++ v ++ delim);

  "/" ++ (url.path->join("/")) ++ "?" ++ url.search
};

let urlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => Redirect("/compverbs/")
  | ["index.html"] => Redirect("/compverbs/")
  | ["compverbs"] => CompoundVerbs
  | ["compverbs", name] => CompoundVerbDetail(name)
  | _ => NotFound
  }