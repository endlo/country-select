module Styles = {
  open Css;

  let container =
    style([alignItems(center), display(flexBox), flexDirection(column)]);
};

[@react.component]
let make = () => {
  let (country, setCountry) = ReactIO.useState(() => None);

  <main className=Styles.container>
    <CountrySelect country onChange={Option.pure >> setCountry} />
  </main>;
};
