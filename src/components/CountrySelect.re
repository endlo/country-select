module CommonStyles = {
  open Css;

  // Ideally this would be set at a global level for the application, but given that this is the
  // primary component of the assignment, I wanted to make sure this component could be lifted into
  // another application and keep the text styles.
  let typography =
    style([
      color(rgba(51, 51, 51, 1.0)),
      fontFamily(`custom("Arial")),
      fontSize(rem(0.875)),
      fontWeight(normal),
      lineHeight(rem(1.125)),
    ]);
};

module Button = {
  module Styles = {
    open Css;

    let button =
      merge([
        CommonStyles.typography,
        style([
          alignItems(center),
          backgroundColor(white),
          border(rem(0.0625), solid, rgba(0, 0, 0, 0.2)),
          borderRadius(rem(0.1875)),
          display(flexBox),
          flexDirection(row),
          flexWrap(nowrap),
          padding2(~h=rem(0.625), ~v=rem(0.25)),
          textAlign(`left),
        ]),
      ]);

    let title = (~selectedCountry) =>
      style([
        color(
          selectedCountry |> Option.isSome
            ? currentColor : rgba(0, 0, 0, 0.32),
        ),
      ]);
  };

  [@react.component]
  let make = (~selectedCountry, ~setIsOpen) =>
    <button
      className=Styles.button
      onClick={_ => setIsOpen(true) |> IOUtils.unsafeRunHandledAsync}
      tabIndex=0
      type_="button">
      {selectedCountry
       |> Option.fold(React.null, country =>
            <> <FlagIcon country /> <Spacer.Horizontal size=8 /> </>
          )}
      <div className={Styles.title(~selectedCountry)}>
        {selectedCountry
         |> Option.fold(
              "Select Country", ({count: _, label, value: _}: Country.t) =>
              label |> Country.Label.toString
            )
         |> React.string}
      </div>
      <Spacer.Horizontal size=6 />
      <Icon.DropdownArrow />
    </button>;
};

module SearchBar = {
  module Styles = {
    open Css;

    let container =
      style([
        alignItems(center),
        display(flexBox),
        flexDirection(row),
        flexWrap(nowrap),
        padding2(~h=rem(0.625), ~v=rem(0.5)),
      ]);

    let searchIcon =
      style([flexShrink(0.0), height(rem(0.875)), width(rem(0.875))]);
  };

  [@react.component]
  let make =
      (
        ~controlProps as
          {children, innerProps}: ReactSelect.Components.controlProps,
      ) =>
    React.cloneElement(
      <div className=Styles.container>
        <div className=Styles.searchIcon> <Icon.Search /> </div>
        <Spacer.Horizontal size=8 />
        children
      </div>,
      innerProps,
    );
};

module CountryOption = {
  module EmptyFlag = {
    module Styles = {
      open Css;

      let container =
        style([flexShrink(0.0), height(rem(0.875)), width(rem(0.875))]);
    };

    [@react.component]
    let make = () => <div className=Styles.container />;
  };

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
        alignItems(center),
        backgroundColor(
          switch (getInteractionState(~isFocused, ~isSelected)) {
          | Selected => rgba(255, 219, 179, 1.0)
          | Focused => rgba(255, 219, 179, 0.25)
          | Blurred => transparent
          },
        ),
        display(flexBox),
        flexDirection(row),
        flexWrap(nowrap),
        padding2(~h=rem(0.625), ~v=rem(0.25)),
      ]);

    let text = style([flex(`num(1.0))]);

    let count = style([color(rgba(0, 0, 0, 0.52))]);
  };

  [@react.component]
  let make =
      (
        ~optionProps as
          {
            data: {count, label, _} as country,
            innerProps,
            innerRef,
            isFocused,
            isSelected,
            _,
          }:
            ReactSelect.Components.optionProps(Country.t),
      ) => {
    // To improve performance of the menu due to loading all of the flag SVGs at once upon first
    // menu open, we're going to keep track of the first time the component appears in the viewport
    // to actually trigger the flag icon to load. We're only going to do this once as the flag will
    // be cached and can be called up at any point the user scrolls through the list.
    let (hasAppearedInViewport, setHasAppearedInViewport) =
      ReactIO.useMappableState(() => false);
    let setHasAppearedInViewport = newValue =>
      setHasAppearedInViewport(oldValue => oldValue || newValue);

    <ReactVisibilitySensor intervalDelay=50 onChange=setHasAppearedInViewport>
      {React.cloneElement(
         <div
           className={Styles.container(~isFocused, ~isSelected)}
           ref=?{innerRef |> Js.Nullable.toOption}>
           {hasAppearedInViewport ? <FlagIcon country /> : <EmptyFlag />}
           <Spacer.Horizontal size=8 />
           <div className=Styles.text>
             {label |> Country.Label.toString |> React.string}
           </div>
           <Spacer.Horizontal size=8 />
           <div className=Styles.count>
             {count |> Int.toString |> React.string}
           </div>
         </div>,
         innerProps,
       )}
    </ReactVisibilitySensor>;
  };
};

module Styles = {
  open Css;

  let select =
    merge([
      CommonStyles.typography,
      style([
        width(rem(14.375)),
        selector(
          ".country-select__placeholder",
          [color(rgba(0, 0, 0, 0.32))],
        ),
      ]),
    ]);

  let menu =
    style([
      borderTop(rem(0.0625), solid, rgba(0, 0, 0, 0.08)),
      important(position(inherit_)),
      paddingTop(rem(0.25)),
    ]);
};

let countriesSourceUrl = "https://gist.githubusercontent.com/rusty-key/659db3f4566df459bd59c8a53dc9f71f/raw/4127f9550ef063121c564025f6d27dceeb279623/counties.json";

let fetchCountries =
  IOUtils.Promise.lazyPromiseToReludeIO(() =>
    Fetch.fetch(countriesSourceUrl) |> Js.Promise.then_(Fetch.Response.json)
  )
  |> IO.map(
       Js.Json.decodeArray
       >> Option.fold([||], Array.mapOption(Country.decode))
       >> Array.sortBy(
            (
              {count: aCount, label: aLabel, _}: Country.t,
              {count: bCount, label: bLabel, _},
            )
            // Let's do our sorting here so we can plop a nicely sorted array into state to use in our UI
            =>
              switch (Int.compare(bCount, aCount)) {
              | `equal_to => Country.Label.compare(aLabel, bLabel)
              | other => other
              }
            ),
     )
  |> IO.mapError(ignore);

[@react.component]
let make = (~className=?, ~country: option(string), ~onChange) => {
  let (countries, setCountries) = ReactIO.useState(() => AsyncResult.init);

  let (isOpen, setIsOpen) = ReactIO.useState(() => false);

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
      classNamePrefix="country-select"
      classNames={menu: _state => Styles.menu}
      controlShouldRenderValue=false
      components={ReactSelect.Components.make(
        ~control=Some(controlProps => <SearchBar controlProps />),
        ~dropdownIndicator=None,
        ~indicatorSeparator=None,
        ~option=Some(optionProps => <CountryOption optionProps />),
      )}
      menuIsOpen=true
      onChange={({value, _}: Country.t) =>
        value
        |> Country.Value.toString
        |> onChange
        |> IO.flatMap(() => setIsOpen(false))
      }
      onKeyDown={
        ReactEvent.Keyboard.key
        >> (
          fun
          | "Escape" => setIsOpen(false)
          | _ => IO.pure()
        )
      }
      options={countries |> AsyncResult.getOk |> Option.getOrElse([||])}
      placeholder="Search"
      tabSelectsValue=false
      unstyled=true
      value=?selectedCountry
    />
  </Dropdown>;
};
