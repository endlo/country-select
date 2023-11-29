open Relude.Globals;

[@react.component]
let make = () => {
  let (selectedCountry, setSelectedCountry) = ReactIO.useState(() => None);

  <ReactSelect
    backspaceRemovesValue=false
    controlShouldRenderValue=false
    components=[
      (DropdownIndicator, Some(_ => <div> "HAI"->React.string </div>)),
      (IndicatorSeparator, None),
    ]
    onChange={Option.pure >> setSelectedCountry}
    options=[||]
    placeholder="Select Country..."
    tabSelectsValue=false
    value=?selectedCountry
  />;
};
