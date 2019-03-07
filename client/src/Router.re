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

let makeUrl = path => ReasonReact.Router.{
  path: path |> Js.String.split("/") |> Array.to_list,
  hash: "",
  search: ""
};

let urlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => Redirect("/compverbs/")
  | ["index.html"] => Redirect("/compverbs/")
  | ["compverbs"] => CompoundVerbs
  | ["compverbs", name] => CompoundVerbDetail(name)
  | _ => NotFound
  }