module Blanket = {
  module Styles = {
    open DesignSystem;

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
    open DesignSystem;

    let container =
      style([
        backgroundColor(Light(Background(Box))),
        borderRadius(rem(0.125)),
        boxShadows([
          Shadow.box(
            ~x=zero,
            ~y=rem(0.1875),
            ~blur=rem(1.125),
            ~spread=zero,
            rgba(0, 0, 0, 0.15),
          ),
          Shadow.box(
            ~x=zero,
            ~y=zero,
            ~blur=zero,
            ~spread=rem(0.0625),
            rgba(0, 0, 0, 0.08),
          ),
        ]),
        marginTop(rem(0.1875)),
        position(absolute),
        zIndex(2),
      ]);
  };

  [@react.component]
  let make = (~children) => <div className=Styles.container> children </div>;
};

module Styles = {
  open DesignSystem;

  let container = style([position(relative)]);
};

[@react.component]
let make = (~children, ~isOpen, ~onClose, ~target) =>
  <div className=Styles.container>
    target
    {isOpen ? <Menu> children </Menu> : React.null}
    {isOpen ? <Blanket onClose /> : React.null}
  </div>;
