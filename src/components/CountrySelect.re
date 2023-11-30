module CommonStyles = {
  open Css;

  let typography =
    style([
      fontFamily(`custom("Arial")),
      fontSize(px(14)),
      fontWeight(normal),
      lineHeight(px(18)),
    ]);
};

module Button = {
  module Styles = {
    open Css;

    let button =
      merge([
        CommonStyles.typography,
        style([
          backgroundColor(white),
          border(rem(0.0625), solid, gray),
          borderRadius(px(4)),
          padding2(~h=rem(0.5), ~v=rem(0.25)),
          textAlign(`left),
        ]),
      ]);
  };

  [@react.component]
  let make = (~selectedCountry, ~setIsOpen) =>
    <button
      className=Styles.button
      onClick={_ => setIsOpen(true) |> IOUtils.unsafeRunHandledAsync}>
      {selectedCountry
       |> Option.fold(
            "Select Country...", ({count: _, label, value: _}: Country.t) =>
            label |> Country.Label.toString
          )
       |> React.string}
    </button>;
};

module CountryOption = {
  module Styles = {
    open Css;

    type interactionState =
      | Selected
      | Focused
      | Blurred;

    let getInteractionState = (~isFocused, ~isSelected) =>
      isSelected ? Selected : isFocused ? Focused : Blurred;

    let container = (~isFocused, ~isSelected) =>
      style([
        backgroundColor(
          switch (getInteractionState(~isFocused, ~isSelected)) {
          | Selected => rgba(255, 219, 179, 1.0)
          | Focused => rgba(255, 219, 179, 0.25)
          | Blurred => white
          },
        ),
        display(flexBox),
        flexDirection(row),
        flexWrap(nowrap),
        padding(rem(0.25)),
      ]);

    let text = style([flex(`num(1.0)), padding2(~h=rem(0.25), ~v=zero)]);

    let count = style([color(rgba(0, 0, 0, 0.52))]);
  };

  [@react.component]
  let make =
    React.forwardRef(
      (
        ~data as {count, label, _}: Country.t,
        ~innerProps,
        ~isFocused,
        ~isSelected,
        ref_,
      ) =>
      React.cloneElement(
        <div
          className={Styles.container(~isFocused, ~isSelected)}
          ref=?{
            ref_ |> Js.Nullable.toOption |> Option.map(ReactDOM.Ref.domRef)
          }>
          <div> "Poop"->React.string </div>
          <div className=Styles.text>
            {label |> Country.Label.toString |> React.string}
          </div>
          <div className=Styles.count>
            {count |> Int.toString |> React.string}
          </div>
        </div>,
        innerProps,
      )
    );
};

module Styles = {
  open Css;

  let select =
    merge([CommonStyles.typography, style([minWidth(rem(15.0))])]);
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
         |> Array.find(({value, _}: Country.t) =>
              value |> Country.Value.toString |> String.eq(selectedCountry)
            )
       )
    |> Option.flatten;

  <Dropdown
    isOpen
    onClose={setIsOpen(false)}
    target={<Button selectedCountry setIsOpen />}>
    <ReactSelect
      autoFocus=true
      backspaceRemovesValue=false
      className={className |> StyleUtils.extendBaseStyle(Styles.select)}
      controlShouldRenderValue=false
      components=[
        DropdownIndicator(None),
        IndicatorSeparator(None),
        Option(
          Some(
            (
              {data, innerProps, innerRef, isFocused, isSelected, _}:
                ReactSelect.Components.optionProps(Country.t),
            ) =>
              <CountryOption
                data
                innerProps
                isFocused
                isSelected
                ref=innerRef
              />,
          ),
        ),
      ]
      menuIsOpen=true
      onChange={({value, _}: Country.t) =>
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
