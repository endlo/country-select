module ClassNames = {
  // https://react-select.com/styles#the-classnames-prop

  type state;

  type t = {menu: state => string};
};

module Components = {
  // https://react-select.com/components

  type genericProps = {innerRef: Js.Nullable.t(ReactDOM.domRef)};

  type controlProps = {
    children: React.element,
    innerProps: Js.t({.}),
  };

  type optionProps('data) = {
    children: React.element,
    data: 'data,
    innerProps: Js.t({.}),
    innerRef: Js.Nullable.t(ReactDOM.domRef),
    isDisabled: bool,
    isFocused: bool,
    isSelected: bool,
    label: string,
  };

  type t('data) = {
    [@mel.as "Control"]
    control: Js.Nullable.t(controlProps => React.element),
    [@mel.as "DropdownIndicator"]
    dropdownIndicator: Js.Nullable.t(genericProps => React.element),
    [@mel.as "IndicatorSeparator"]
    indicatorSeparator: Js.Nullable.t(genericProps => React.element),
    [@mel.as "Option"]
    option: Js.Nullable.t(optionProps('data) => React.element),
  };

  // Add a make function as a better interface to replace those pesky Js.Nullables with options.
  let make = (~control, ~dropdownIndicator, ~indicatorSeparator, ~option) => {
    control: control |> Js.Nullable.fromOption,
    dropdownIndicator: dropdownIndicator |> Js.Nullable.fromOption,
    indicatorSeparator: indicatorSeparator |> Js.Nullable.fromOption,
    option: option |> Js.Nullable.fromOption,
  };
};

[@mel.module "react-select"] [@react.component]
external make:
  (
    ~autoFocus: bool=?,
    ~backspaceRemovesValue: bool=?,
    ~className: string=?,
    ~classNamePrefix: string=?,
    ~classNames: ClassNames.t=?,
    ~components: Components.t('a)=?,
    ~controlShouldRenderValue: bool=?,
    ~defaultValue: string=?,
    ~hideSelectedOptions: bool=?,
    ~isClearable: bool=?,
    ~isDisabled: bool=?,
    ~isSearchable: bool=?,
    ~menuIsOpen: bool=?,
    ~onChange: 'a => unit,
    ~onKeyDown: ReactEvent.Keyboard.t => unit=?,
    ~options: array('a),
    ~placeholder: string=?,
    ~tabSelectsValue: bool=?,
    ~unstyled: bool=?,
    ~value: 'a=?
  ) =>
  React.element =
  "default";

// Shadow the external make to add some additional type safety as well as wrap the onChange event in an IO.
let makeProps =
    (
      ~onChange: 'a => IO.t(unit, unit),
      ~onKeyDown: option(ReactEvent.Keyboard.t => IO.t(unit, unit))=?,
    ) =>
  makeProps(
    ~onChange=onChange >> IOUtils.unsafeRunHandledAsync,
    ~onKeyDown=?
      onKeyDown |> Option.map(fn => fn >> IOUtils.unsafeRunHandledAsync),
  );
