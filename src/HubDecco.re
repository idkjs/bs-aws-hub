/* https://github.com/aws-amplify/amplify-js/blob/master/packages/core/src/Hub.ts
   hub export `export default Hub;`
   node_modules/@aws-amplify/core/src/Hub.t */
type t;
[@bs.module "aws-amplify"] external hub: t = "Hub";

[@decco] type channel = string;
[@decco] type hubPayload = {
  event: string,
  data: option(Js.Json.t),
  message: option(string),
};

[@decco] type hubCapsule = {
  channel,
  payload: hubPayload,
  source: string,
  patternInfo: option(array(string)),
};
// type hubCallback = {capsule: hubCapsule};
// [@decco] type hubCallback = {capsule: hubCapsule};
/*
 Define a function which calls Hub's `listen` function. It takes our `t` type hub a string for the name of the channel we want to listen to and a callback. Here is typed to the types in `Hub.ts` but it works with a simpler version as well(for future reference):
 ```
 [@bs.send]
 external listen: (t, string, Js.Json.t => unit) => unit = "listen";
 ```

 We also use `[@bs.string]` to limit the string input to channels defined in the js. We can add other channels. This list defines the protected channels in the source.
 */
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
    (Js.Json.t) => unit
  ) =>
  unit =
  "listen";

/* use currying to pass `hub` in here and `string` and `hubCallback` at the call site. */
[@decco] type hubCallback = {capsule: hubCapsule};
let listen = (channel, cb) => {listen(hub, channel, result =>
        hubCapsule_decode(result)
        |> Belt.Result.getExn
        |> cb
    );
};