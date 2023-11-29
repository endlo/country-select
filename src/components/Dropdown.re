module Blanket = {
  module Styles = {
    open Css;

    let container =
      style([
        bottom(zero),
        left(zero),
        position(fixed),
        right(zero),
        top(zero),
        zIndex(1),
      ]);
  };

  [@react.component]
  let make = (~onClose) =>
    <div
      className=Styles.container
      onClick={_ => onClose |> IOUtils.unsafeRunHandledAsync}
    />;
};

module Menu = {
  module Styles = {
    open Css;

    let container =
      style([
        backgroundColor(white),
        borderRadius(px(4)),
        boxShadow(
          Shadow.box(
            ~x=zero,
            ~y=zero,
            ~blur=rem(0.5),
            rgba(8, 35, 48, 0.24),
          ),
        ),
        marginTop(rem(0.5)),
        padding(rem(0.5)),
        position(absolute),
        zIndex(2),
      ]);
  };

  [@react.component]
  let make = (~children) => <div className=Styles.container> children </div>;
};

module Styles = {
  open Css;

  let container = style([position(relative)]);
};

[@react.component]
let make = (~children, ~isOpen, ~onClose, ~target) =>
  <div className=Styles.container>
    target
    {isOpen ? <Menu> children </Menu> : React.null}
    {isOpen ? <Blanket onClose /> : React.null}
  </div>;
