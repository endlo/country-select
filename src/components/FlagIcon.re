[%%mel.raw {|import "/node_modules/flag-icons/css/flag-icons.min.css";|}];

module Styles = {
  open DesignSystem;

  let inline = "fi";

  let flagIcon = ({value, _}: Country.t) =>
    "fi-" ++ (value |> Country.Value.toString);

  let container = (~country) =>
    merge([
      inline,
      country |> flagIcon,
      style([height(rem(0.875)), maxWidth(rem(0.875))]),
    ]);
};

[@react.component]
let make = (~country) => <span className={Styles.container(~country)} />;
