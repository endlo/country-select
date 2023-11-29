[@react.component]
let make = (~className=?, ~country: option(Country.t), ~onChange) =>
  <ReactSelect
    backspaceRemovesValue=false
    ?className
    controlShouldRenderValue=false
    components=[
      (DropdownIndicator, Some(_ => <div> "HAI"->React.string </div>)),
      (IndicatorSeparator, None),
    ]
    onChange
    options=[||]
    placeholder="Select Country..."
    tabSelectsValue=false
    value=?country
  />;
