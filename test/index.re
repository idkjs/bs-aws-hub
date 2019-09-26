open Hub;

Hub.listen(`auth, (response:hubCallback) => Js.log2("callback", response));

open HubDecco;

HubDecco.listen(`auth, (response: hubCapsule) =>
      Js.log2("hubCapsule", response)
    );