module Styles = {
  open Css;

  let screen =
    style([alignItems(center), display(flexBox), flexDirection(column)]);

  let container = style([width(pct(35.0))]);
};

[@react.component]
let make = () => {
  let (country, setCountry) = ReactIO.useState(() => None);

  <main className=Styles.screen>
    <div className=Styles.container>
      <CountrySelect country onChange={Option.pure >> setCountry} />
    </div>
  </main>;
};
