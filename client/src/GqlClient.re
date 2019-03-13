let fetch = [%raw {|require("isomorphic-unfetch")|}];

[@bs.module "react-apollo"]
external getDataFromTree : ReasonReact.reactElement => Js.Promise.t(unit) = "";

let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

let httpLink =
  ApolloLinks.createHttpLink(~uri="http://localhost:8080/graphql", ~fetch, ());

let instance =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());