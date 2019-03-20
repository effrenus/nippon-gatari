type t;

type rinfo = {.
    address: string,
    family: string,
    port: int,
    size: int
};

[@bs.module "dgram"]
external createSocket : ([@bs.string][ `udp4 | `udp6 ]) => t = "";

[@bs.send]
external on : (t, ([@bs.string] [ `message((Node.Buffer.t, Js.t(rinfo)) => unit)])) => unit = "";

[@bs.send]
external bind : t => (~port: int, ~address: string=?, ~cb: unit => unit=?, unit) => unit = "";

[@bs.send]
external send : t => (~msg: string, ~port: int, ~address: string=?) => unit = "";

[@bs.send]
external close : t => unit => unit = "";