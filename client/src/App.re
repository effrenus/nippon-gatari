Css.(
  global("body", [
      minHeight(vh(100.)),
      margin(px(0)),
      backgroundImage(
          linearGradient(deg(0), [(0, `hex("cfd9df")), (100, `hex("e2ebf0"))])
      ),
      fontFamily("Arial, sans-serif"),

      `selector("a", [
        hover([
          textDecoration(`none)
        ])
      ])
  ])
);

module Styles = {
  open Css;

  let wrap = style([
      maxWidth(px(1500)),
      margin(`auto),
      padding4(~top=px(15), ~right=px(30), ~left=px(30), ~bottom=px(30)),
  ]);

  let head = style([
      marginBottom(px(20)),
  ]);

  let header = style([
      display(`inlineBlock),
      marginTop(px(0)),
      marginBottom(px(0)),
      marginRight(px(20)),
  ]);

  let navLink = style([
    display(`inlineBlock),
    marginRight(px(15)),
    padding2(~v=px(7), ~h=px(13)),
    borderRadius(px(15)),
    backgroundColor(`hex("FFF")),
  ]);

}

type action =
  | ChangeRoute(Router.route);

type state = {
  route: Router.route
};

let routeToComponent = (route : Router.route) => switch (route) {
  | CompoundVerbs(url) => <VerbsListContainer url />
  | CompoundVerbDetail(name) => <VerbDetailContainer name />
  | CompoundVerbAbout => <VerbAbout />
  | Redirect(path) => <Redirect r=path />
  | NotFound => <NotFound />
  }

let component = ReasonReact.reducerComponent("Nippon.App");

let make = (~getInitUrl=?, _children) => {
  ...component,
  initialState: () => { route: Router.urlToRoute(switch (getInitUrl) { | None => ReasonReact.Router.dangerouslyGetInitialUrl() | Some(f) => f() }) },
  reducer: (action, _state) => 
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({ route: route })
  },
  didMount: self => {
    let watchId = ReasonReact.Router.watchUrl(url => { 
      Router.urlToRoute(url)
      -> ChangeRoute
      |> self.send
    });
    self.onUnmount(() => watchId->ReasonReact.Router.unwatchUrl)
  },
  render: self => {
    let comp = routeToComponent(self.state.route);
    <section className=Styles.wrap>
      <header className=Styles.head>
        <h1 className=Styles.header>{j|Словарь составных глаголов|j}->ReasonReact.string</h1>
        <Router.Link className=Styles.navLink href="/compverbs/">{{j|Список глаголов|j}->ReasonReact.string}</Router.Link>
        <Router.Link className=Styles.navLink href="/compverbs/about/">{{j|О словаре|j}->ReasonReact.string}</Router.Link>
      </header>
        
      <ReasonApollo.Provider client=GqlClient.instance>
        comp
      </ReasonApollo.Provider>
    </section>
  }
};
