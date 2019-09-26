/* does same exact thing using `gentype` */

type channel = string;
module HubPayload = {
  [@genType.import ("@aws-amplify/core/Hub", "HubPayload")]
  type t = {
    event: string,
    data: option(Js.t({.})),
    message: option(string),
  };
};
module HubCapsule = {
  [@genType.import ("@aws-amplify/core/Hub", "HubCapsule")]
  type t = {
    channel,
    payload: HubPayload.t,
    source: string,
    patternInfo: option(array(string)),
  };
};
module HubCallback = {
  [@genType.import ("@aws-amplify/core/Hub", "HubCallback")];

  type t = {capsule: HubCapsule.t};
};
type callback = option(HubCallback.t);
type t;
[@bs.module "aws-amplify"] external hub: t = "Hub";
[@bs.send]
external listen:
  (
    t,
    [@bs.string] [
      | `core
      | `auth
      | `api
      | `analytics
      | `interactions
      | `pubsub
      | `storage
      | `xr
    ],
    HubCallback.t => unit
  ) =>
  unit =
  "listen";

/* use currying to pass `hub` in here and `string` and `hubCallback` at the call site. */

let listen = (channel, hubCallback) => listen(hub, channel, hubCallback);