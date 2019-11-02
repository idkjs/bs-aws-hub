# Bucklescript bindings for [aws-amplify's hub](https://github.com/aws/aws-amplify#readme)

## Example

```reason
type userData = {
  isLoggedIn: bool,
  username: string,
  id: int,
  email: string,
};
type user =
  | Anonymous
  | LoggedIn(userData);
type userAction =
  | UserLoggedIn(userData)
  | UserLoggedOut;

type state = {user};
let reducer = (_, action) =>
  switch (action) {
  | UserLoggedIn(authData) => {user: LoggedIn(authData)}
  | UserLoggedOut => {user: Anonymous}
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, {user: Anonymous});

  open Hub;

  let listener =
    data => {
      Js.log( "listening for auth events...");
      let message = data->payloadGet->messageGet;
      let userJs = data->payloadGet->dataGet;

      let event = data->payloadGet->eventGet->eventFromString;

      switch (event) {
      | SignIn =>
         Js.log2("SignIn Messsage: ", message);

        let userData: userData = {
          isLoggedIn: true,
          username: userJs->usernameGet,
          id: userJs->attributesGet->subGet,
          email: userJs->attributesGet->emailGet,
        };
        dispatch(UserLoggedIn(userData));
      | SignUp => Js.log2("SignUp Messsage: ", message)

      | SignOut => Js.log2("SignOut Messsage: ", message);
        dispatch(UserLoggedOut);
      | SignIn_failure =>  Js.log2("SignIn_failure Messsage: ", message)

      | Configured => Js.log2("Configured Messsage: ", message)

      | _ => Js.log2("unknown error", data)
      };
    };
  React.useEffect1(
    () => {
      Hub.listen(Auth, listener);
      Some(() => Hub.remove(Auth, listener));
    },
    [||],
  );
  <UserContext.Provider value=(state.user, dispatch)>
    <Home />
  </UserContext.Provider>;
};
```

## Todo

 [ ] bind to `dispatch`.

