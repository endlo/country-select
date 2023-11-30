module ClassNames = {
  type state;

  type t = {menu: state => string};
};

module Components = {
  type props;

  type genericProps = {innerRef: Js.Nullable.t(ReactDOM.domRef)};
  type genericComponent = option(genericProps => React.element);

  type controlProps = {
    children: React.element,
    innerProps: Js.t({.}),
  };
  type controlComponent = option(controlProps => React.element);

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
  type optionComponent('data) = option(optionProps('data) => React.element);

  type t('data) =
    | ClearIndicator(genericComponent)
    | Control(controlComponent)
    | DropdownIndicator(genericComponent)
    | DownChevron(genericComponent)
    | CrossIcon(genericComponent)
    | Group(genericComponent)
    | GroupHeading(genericComponent)
    | IndicatorsContainer(genericComponent)
    | IndicatorSeparator(genericComponent)
    | Input(genericComponent)
    | LoadingIndicator(genericComponent)
    | Menu(genericComponent)
    | MenuList(genericComponent)
    | MenuPortal(genericComponent)
    | LoadingMessage(genericComponent)
    | NoOptionsMessage(genericComponent)
    | MultiValue(genericComponent)
    | MultiValueContainer(genericComponent)
    | MultiValueLabel(genericComponent)
    | MultiValueRemove(genericComponent)
    | Option(optionComponent('data))
    | Placeholder(genericComponent)
    | SelectContainer(genericComponent)
    | SingleValue(genericComponent)
    | ValueContainer(genericComponent);

  let toKey =
    fun
    | ClearIndicator(_) => "ClearIndicator"
    | Control(_) => "Control"
    | DropdownIndicator(_) => "DropdownIndicator"
    | DownChevron(_) => "DownChevron"
    | CrossIcon(_) => "CrossIcon"
    | Group(_) => "Group"
    | GroupHeading(_) => "GroupHeading"
    | IndicatorsContainer(_) => "IndicatorsContainer"
    | IndicatorSeparator(_) => "IndicatorSeparator"
    | Input(_) => "Input"
    | LoadingIndicator(_) => "LoadingIndicator"
    | Menu(_) => "Menu"
    | MenuList(_) => "MenuList"
    | MenuPortal(_) => "MenuPortal"
    | LoadingMessage(_) => "LoadingMessage"
    | NoOptionsMessage(_) => "NoOptionsMessage"
    | MultiValue(_) => "MultiValue"
    | MultiValueContainer(_) => "MultiValueContainer"
    | MultiValueLabel(_) => "MultiValueLabel"
    | MultiValueRemove(_) => "MultiValueRemove"
    | Option(_) => "Option"
    | Placeholder(_) => "Placeholder"
    | SelectContainer(_) => "SelectContainer"
    | SingleValue(_) => "SingleValue"
    | ValueContainer(_) => "ValueContainer";

  let toValue: t('data) => Js.Nullable.t(props => React.element) =
    fun
    | Option(optionComponent) =>
      optionComponent |> Js.Nullable.fromOption |> Relude.Unsafe.coerce
    | Control(controlComponent) =>
      controlComponent |> Js.Nullable.fromOption |> Relude.Unsafe.coerce
    | ClearIndicator(genericComponent)
    | DropdownIndicator(genericComponent)
    | DownChevron(genericComponent)
    | CrossIcon(genericComponent)
    | Group(genericComponent)
    | GroupHeading(genericComponent)
    | IndicatorsContainer(genericComponent)
    | IndicatorSeparator(genericComponent)
    | Input(genericComponent)
    | LoadingIndicator(genericComponent)
    | Menu(genericComponent)
    | MenuList(genericComponent)
    | MenuPortal(genericComponent)
    | LoadingMessage(genericComponent)
    | NoOptionsMessage(genericComponent)
    | MultiValue(genericComponent)
    | MultiValueContainer(genericComponent)
    | MultiValueLabel(genericComponent)
    | MultiValueRemove(genericComponent)
    | Placeholder(genericComponent)
    | SelectContainer(genericComponent)
    | SingleValue(genericComponent)
    | ValueContainer(genericComponent) =>
      genericComponent |> Js.Nullable.fromOption |> Relude.Unsafe.coerce;
};

[@mel.module "react-select"] [@react.component]
external make:
  (
    ~autoFocus: bool=?,
    ~backspaceRemovesValue: bool=?,
    ~className: string=?,
    ~classNamePrefix: string=?,
    ~classNames: ClassNames.t=?,
    ~components: Js.Dict.t(Js.Nullable.t(Components.props => React.element))
                   =?,
    ~controlShouldRenderValue: bool=?,
    ~defaultValue: string=?,
    ~hideSelectedOptions: bool=?,
    ~isClearable: bool=?,
    ~isDisabled: bool=?,
    ~isSearchable: bool=?,
    ~menuIsOpen: bool=?,
    ~onChange: 'a => unit,
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
      ~components: option(list(Components.t('a)))=?,
      ~onChange: 'a => IO.t(unit, unit),
    ) =>
  makeProps(
    ~components=?
      components
      |> Option.map(
           List.map(component =>
             (component |> Components.toKey, component |> Components.toValue)
           )
           >> Js.Dict.fromList,
         ),
    ~onChange=onChange >> IOUtils.unsafeRunHandledAsync,
  );
