module Emotion = {
    [@bs.module "emotion-server"]
    external renderStylesToString : string => string = "";
}

module Express = {
    [@bs.module]
    external compression : unit => Express.Middleware.t = "compression";
}