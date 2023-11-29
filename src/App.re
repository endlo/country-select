module Styles = {
  open Utils.Style;

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
