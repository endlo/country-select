module Styles = {
  open Css;

  let main =
    style([
      alignItems(center),
      display(flexBox),
      flexDirection(column),
      padding2(~h=rem(1.0), ~v=rem(10.0)),
    ]);
};

[@react.component]
let make = () => {
  let (country, setCountry) = ReactIO.useState(() => None);

  <main className=Styles.main>
    <CountrySelect country onChange={Option.pure >> setCountry} />
  </main>;
};
