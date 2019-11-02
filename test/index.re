open Hub;
let listener = data => {
  Js.log("listening for auth events...");
  let message = data->payloadGet->messageGet;

  let event = data->payloadGet->eventGet->eventFromString;

  switch (event) {
  | SignIn => Js.log2("SignIn Messsage: ", message)

  /* Do something here like:

     let userData: AuthTypes.userData = {
       isLoggedIn: true,
       username: userJs->usernameGet,
       id: userJs->attributesGet->subGet,
       email: userJs->attributesGet->emailGet,
     };
     dispatch(UserLoggedIn(userData));
      */
  | SignUp => Js.log2("SignUp Messsage: ", message)

  | SignOut => Js.log2("SignOut Messsage: ", message)
  /* do something here like: `dispatch(UserLoggedOut);` */
  | SignIn_failure => Js.log2("SignIn_failure Messsage: ", message)

  | Configured => Js.log2("Configured Messsage: ", message)

  | _ => Js.log2("unknown error", data)
  };
};

Hub.listen(Auth, listener);