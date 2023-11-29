[@react.component]
let make = () => {
  let (selectedCountry, setSelectedCountry) = React.useState(() => None);

  // Each new country selection should override the previous, so lets shadow the set function
  // and make it a little easier to use.
  let setSelectedCountry = country => setSelectedCountry(_ => country);

  <Bindings.ReactSelect
    backspaceRemovesValue=false
    controlShouldRenderValue=false
    components=[
      {
        key: DropdownIndicator,
        value: Some(_ => <div> "HAI"->React.string </div>),
      },
      {key: IndicatorSeparator, value: None},
    ]
    onChange={country => Some(country) |> setSelectedCountry}
    options=[||]
    placeholder="Select Country..."
    tabSelectsValue=false
    value=?selectedCountry
  />;
};
