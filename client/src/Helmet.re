
[@bs.module "react-helmet"] [@bs.scope "Helmet"]
external renderStatic : unit => Js.t({..}) = "";

[@bs.module "react-helmet"]
external helmet : ReasonReact.reactClass = "Helmet";

let make = children => ReasonReact.wrapJsForReason(
    ~reactClass=helmet,
    ~props=Js.Obj.empty(),
    children
  )