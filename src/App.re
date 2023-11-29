module Styles = {
  open Css;

  let container =
    style([
      alignItems(center),
      display(flexBox),
      flexDirection(column),
      fontFamily(`custom("Arial")),
    ]);
};

[@react.component]
let make = () => {
  let (country, setSelectedCountry) = ReactIO.useState(() => None);

  <main className=Styles.container>
    <CountrySelect country onChange={Option.pure >> setSelectedCountry} />
  </main>;
};
