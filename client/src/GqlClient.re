let fetch = [%raw {|require("isomorphic-unfetch")|}];

/* TODO Move to Apollo.re? */
[@bs.module "react-apollo"]
external getDataFromTree : ReasonReact.reactElement => Js.Promise.t(unit) = "";

[@bs.send]
external extract : ApolloClient.generatedApolloClient => Js.t({..}) = "";

[@bs.val]
external apolloState: ApolloInMemoryCache.inMemoryCacheRestoreData = "window.__APOLLO_STATE__";

let rehydrate = cache => switch ([%external window]) {
  | None => cache
  | Some(_) => cache |> ApolloInMemoryCache.restore(apolloState)
  };

let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

let httpLink = {
  /* We need different URIs for isomorphic render. */
  let uri = [%raw "process.env.GQL_URI"];
  ApolloLinks.createHttpLink(~uri, ~fetch, ())
}

let instance =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=rehydrate(inMemoryCache), ());