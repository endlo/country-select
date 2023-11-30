[@mel.module "react-visibility-sensor"] [@react.component]
external make:
  (~children: React.element, ~onChange: bool => unit) => React.element =
  "default";

let makeProps = (~onChange: bool => IO.t(unit, unit)) =>
  makeProps(~onChange=onChange >> IOUtils.unsafeRunHandledAsync);
