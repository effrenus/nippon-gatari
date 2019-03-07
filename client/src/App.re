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

type action =
  | ChangeRoute(Router.route);

type state = {
  route: Router.route
};

let component = ReasonReact.reducerComponent("Nippon.App");

let make = _children => {
  ...component,
  initialState: () => { route: ReasonReact.Router.dangerouslyGetInitialUrl()->Router.urlToRoute },
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
  render: self =>
  <ReasonApollo.Provider client=GqlClient.instance>
  {
    switch (self.state.route) {
    | CompoundVerbs => <VerbsListContainer />
    | CompoundVerbDetail(name) => <VerbDetailContainer name />
    | Redirect(path) => <Redirect r=path />
    | NotFound => <NotFound />
    }
  }
  </ReasonApollo.Provider>
};
