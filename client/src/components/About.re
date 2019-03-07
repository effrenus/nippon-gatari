let component = ReasonReact.statelessComponent("Nippon.About");

let make = _children => {
    ...component,
    render: _ => {
      <article>
      "about"->ReasonReact.string
      </article>
    },
  };