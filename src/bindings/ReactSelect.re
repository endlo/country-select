type selectOption('a) = {
  label: string,
  value: 'a,
};

[@mel.module "react-select"] [@react.component]
external make:
  (
    ~defaultValue: 'a=?,
    ~onChange: 'a => unit,
    ~options: array(selectOption('a))
  ) =>
  React.element =
  "default";
