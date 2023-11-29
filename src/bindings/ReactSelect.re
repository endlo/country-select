module Components = {
  type props;

  type t =
    | ClearIndicator
    | Control
    | DropdownIndicator
    | DownChevron
    | CrossIcon
    | Group
    | GroupHeading
    | IndicatorsContainer
    | IndicatorSeparator
    | Input
    | LoadingIndicator
    | Menu
    | MenuList
    | MenuPortal
    | LoadingMessage
    | NoOptionsMessage
    | MultiValue
    | MultiValueContainer
    | MultiValueLabel
    | MultiValueRemove
    | Option
    | Placeholder
    | SelectContainer
    | SingleValue
    | ValueContainer;

  let toString =
    fun
    | ClearIndicator => "ClearIndicator"
    | Control => "Control"
    | DropdownIndicator => "DropdownIndicator"
    | DownChevron => "DownChevron"
    | CrossIcon => "CrossIcon"
    | Group => "Group"
    | GroupHeading => "GroupHeading"
    | IndicatorsContainer => "IndicatorsContainer"
    | IndicatorSeparator => "IndicatorSeparator"
    | Input => "Input"
    | LoadingIndicator => "LoadingIndicator"
    | Menu => "Menu"
    | MenuList => "MenuList"
    | MenuPortal => "MenuPortal"
    | LoadingMessage => "LoadingMessage"
    | NoOptionsMessage => "NoOptionsMessage"
    | MultiValue => "MultiValue"
    | MultiValueContainer => "MultiValueContainer"
    | MultiValueLabel => "MultiValueLabel"
    | MultiValueRemove => "MultiValueRemove"
    | Option => "Option"
    | Placeholder => "Placeholder"
    | SelectContainer => "SelectContainer"
    | SingleValue => "SingleValue"
    | ValueContainer => "ValueContainer";
};

type selectOption('a) = {
  label: string,
  value: 'a,
};

[@mel.module "react-select"] [@react.component]
external make:
  (
    ~autoFocus: bool=?,
    ~backspaceRemovesValue: bool=?,
    ~className: string=?,
    ~classNamePrefix: string=?,
    ~components: Js.Dict.t(Js.Nullable.t(Components.props => React.element))
                   =?,
    ~controlShouldRenderValue: bool=?,
    ~defaultValue: 'a=?,
    ~hideSelectedOptions: bool=?,
    ~isClearable: bool=?,
    ~isDisabled: bool=?,
    ~isSearchable: bool=?,
    ~menuIsOpen: bool=?,
    ~onChange: 'a => unit,
    ~options: array(selectOption('a)),
    ~placeholder: string=?,
    ~tabSelectsValue: bool=?,
    ~value: 'a=?
  ) =>
  React.element =
  "default";

// Shadow the external make to add some additional type safety as well as wrap the onChange event in an IO.
let makeProps =
    (
      ~components:
         option(
           list((Components.t, option(Components.props => React.element))),
         )=?,
      ~onChange: 'a => IO.t(unit, unit),
    ) =>
  makeProps(
    ~components=?
      components
      |> Option.map(
           List.map(((key, value)) =>
             (key |> Components.toString, value |> Js.Nullable.fromOption)
           )
           >> Js.Dict.fromList,
         ),
    ~onChange=onChange >> IOUtils.unsafeRunHandledAsync,
  );
