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
    let clientApp = <Client.App getInitUrl={() => Client.Router.makeUrl(req->Request.originalUrl)} />;

    Js.Promise.(
      Client.GqlClient.getDataFromTree(clientApp)
      |> then_(() => {
          res 
          |> Response.sendString(
              Template.render(
                renderStylesToString(clientApp->ReactDOMServerRe.renderToString),
                ~apolloState=Client.GqlClient.instance->Client.GqlClient.extract->Js.Json.stringifyAny,
                ~helmet=Client.Helmet.renderStatic()
              )
          )
          |> resolve
        })
      |> catch(err => err -> Template.renderErrorPage -> Response.sendString(res) -> resolve)
    )
})

app->App.listen(~port=8100, ());