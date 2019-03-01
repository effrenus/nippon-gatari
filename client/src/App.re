Css.(
  global("body", [
    minHeight(vh(100.)),
    margin(px(0)),
    backgroundImage(
      linearGradient(deg(0), [(0, `hex("cfd9df")), (100, `hex("e2ebf0"))])
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
