Css.(
  global("body", [
    minHeight(vh(100.)),
    margin(px(0)),
    backgroundImage(
      linearGradient(deg(-20), [(0, `hex("616161")), (100, `hex("9bc5c3"))])
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
