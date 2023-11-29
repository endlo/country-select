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
let make = () => {
  let (country, setSelectedCountry) = ReactIO.useState(() => None);

  <main style=Styles.container>
    <CountrySelect country onChange={Option.pure >> setSelectedCountry} />
  </main>;
};
