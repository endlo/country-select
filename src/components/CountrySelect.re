module Styles = {
  open Css;

  let select = style([minWidth(rem(15.0))]);
};

[@react.component]
let make = (~className=?, ~country: option(string), ~onChange) =>
  <ReactSelect
    backspaceRemovesValue=false
    className={className |> StyleUtils.extendBaseStyle(Styles.select)}
    controlShouldRenderValue=false
    components=[(DropdownIndicator, None), (IndicatorSeparator, None)]
    onChange
    options=[||]
    placeholder="Select Country..."
    tabSelectsValue=false
    value=?country
  />;
