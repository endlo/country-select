module Styles = {
  open Css;

  let select = style([minWidth(rem(15.0))]);
};

let countriesSourceUrl = "https://gist.githubusercontent.com/rusty-key/659db3f4566df459bd59c8a53dc9f71f/raw/4127f9550ef063121c564025f6d27dceeb279623/counties.json";

let fetchCountries =
  IOUtils.Promise.lazyPromiseToReludeIO(() =>
    Fetch.fetch(countriesSourceUrl) |> Js.Promise.then_(Fetch.Response.json)
  )
  |> IO.map(
       Js.Json.decodeArray
       >> Option.fold([||], Array.mapOption(Country.decode)),
     )
  |> IO.mapError(ignore);

[@react.component]
let make = (~className=?, ~country: option(string), ~onChange) => {
  let (isOpen, setIsOpen) = ReactIO.useState(() => false);
  let (countries, setCountries) = ReactIO.useState(() => AsyncResult.init);

  // On mount, fetch the list of countries
  React.useEffect0(() => {
    setCountries(AsyncResult.loading)
    |> IO.flatMap(() => fetchCountries)
    |> IO.flatMap(AsyncResult.pure >> setCountries)
    |> IOUtils.unsafeRunHandledAsync;
    None;
  });

  let selectedCountry =
    (countries |> AsyncResult.getOk, country)
    |> Option.mapTuple2((countries, selectedCountry) =>
         countries
         |> Array.find(({label: _, value}: Country.t) =>
              value |> Country.Value.toString |> String.eq(selectedCountry)
            )
       )
    |> Option.flatten;

  <Dropdown
    isOpen
    onClose={setIsOpen(false)}
    target={
      <button onClick={_ => setIsOpen(true) |> IOUtils.unsafeRunHandledAsync}>
        {country |> Option.getOrElse("Select Country...") |> React.string}
      </button>
    }>
    <ReactSelect
      autoFocus=true
      backspaceRemovesValue=false
      className={className |> StyleUtils.extendBaseStyle(Styles.select)}
      controlShouldRenderValue=false
      components=[(DropdownIndicator, None), (IndicatorSeparator, None)]
      menuIsOpen=true
      onChange={({label: _, value}: Country.t) =>
        value
        |> Country.Value.toString
        |> onChange
        |> IO.flatMap(() => setIsOpen(false))
      }
      options={countries |> AsyncResult.getOk |> Option.getOrElse([||])}
      placeholder="Search..."
      tabSelectsValue=false
      value=?selectedCountry
    />
  </Dropdown>;
};
