open Express;

module Client = NipponGatariClient;

let app = App.make ();

[@bs.module "emotion-server"]
external renderStylesToString : string => string = "";

App.get(app, ~path="/assets/*") @@
Static.asMiddleware @@
Static.make("./", Static.defaultOptions());

App.get(app, ~path="/*") @@
PromiseMiddleware.from((_next, req, res) => {
  let apolloClient = ReasonApollo.createApolloClient(~link=Client.GqlClient.httpLink, ~cache=ApolloInMemoryCache.createInMemoryCache(), ());
  let clientApp = <Client.App apolloClient=apolloClient getInitUrl={() => Client.Router.makeUrl(req->Request.originalUrl)} />;

    Js.Promise.(
      Client.GqlClient.getDataFromTree(clientApp)
      |> then_(() => {
          res
          |> Response.sendString(
              Template.render(
                renderStylesToString(clientApp->ReactDOMServerRe.renderToString),
                ~apolloState=apolloClient->Client.GqlClient.extract->Js.Json.stringifyAny,
                ~helmet=Client.Helmet.renderStatic()
              )
          )
          |> resolve
        })
      |> catch(err => err -> Template.renderErrorPage -> Response.sendString(res) -> resolve)
    )
})

app->App.listen(~port=8100, ());