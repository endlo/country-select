module Styles = {
  open StyleUtils;

  let container =
    make(
      ~alignItems="center",
      ~display="flex",
      ~flexDirection="column",
      ~fontFamily="Arial",
      (),
    );
};

[@react.component]
let make = () => <main style=Styles.container> <CountrySelect /> </main>;
