Css.(
  global("body", [
    minHeight(vh(100.)),
    margin(px(0)),
    backgroundImage(
      linearGradient(deg(120), [(0, `hex("a1c4fd")), (100, `hex("c2e9fb"))])
    ),
    fontFamily("Arial, sans-serif")
  ])
);

let component = ReasonReact.statelessComponent("Nippon.App");

let make = _children => {
  ...component,
  render: _self =>
  <ReasonApollo.Provider client=GqlClient.instance>
    <VerbsList />
  </ReasonApollo.Provider>,
};
