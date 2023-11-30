include Css;

module Colors = {
  module Background = {
    type t =
      | Box
      | Selected
      | Focused;
  };

  module Border = {
    type t =
      | ControlAlpha
      | LineAlpha;
  };

  module Text = {
    type t =
      | Primary
      | Secondary
      | Tertiary
      | Error;
  };

  module Light = {
    type t =
      | Background(Background.t)
      | Border(Border.t)
      | Text(Text.t);

    let toColor =
      fun
      | Background(Box) => hex("FFFFFF")
      | Background(Selected) => hex("FFDBB3")
      | Background(Focused) => rgba(255, 219, 179, 0.25)
      | Border(ControlAlpha) => rgba(0, 0, 0, 0.2)
      | Border(LineAlpha) => rgba(0, 0, 0, 0.08)
      | Text(Primary) => hex("333333")
      | Text(Secondary) => rgba(0, 0, 0, 0.52)
      | Text(Tertiary) => rgba(0, 0, 0, 0.32)
      | Text(Error) => red;
  };

  type t =
    | CurrentColor
    | Light(Light.t)
    | Transparent;

  let toColor =
    fun
    | CurrentColor => currentColor
    | Light(light) => light |> Light.toColor
    | Transparent => transparent;
};

module Typography = {
  module Size = {
    type t =
      | XSmall
      | Medium;
  };

  type t =
    | Text(Size.t);

  let toStyle =
    fun
    | Text(XSmall) =>
      style([
        fontFamily(`custom("Arial")),
        fontSize(rem(0.75)),
        fontWeight(normal),
        lineHeight(rem(0.875)),
      ])
    | Text(Medium) =>
      style([
        fontFamily(`custom("Arial")),
        fontSize(rem(0.875)),
        fontWeight(normal),
        lineHeight(rem(1.125)),
      ]);
};

module Utils = {
  let extendBaseStyle = (baseStyle, extendedStyle) =>
    [Some(baseStyle), extendedStyle] |> List.catOptions |> Css.merge;
};

// Override the functions that come from the Css libray to enforce design system types.
let backgroundColor = Colors.toColor >> backgroundColor;
let borderBottom = (length, style, color) =>
  borderBottom(length, style, color |> Colors.toColor);
let borderBottomColor = Colors.toColor >> borderBottomColor;
let border = (length, style, color) =>
  border(length, style, color |> Colors.toColor);
let borderColor = Colors.toColor >> borderColor;
let borderLeft = (length, style, color) =>
  borderLeft(length, style, color |> Colors.toColor);
let borderLeftColor = Colors.toColor >> borderLeftColor;
let borderRight = (length, style, color) =>
  borderRight(length, style, color |> Colors.toColor);
let borderRightColor = Colors.toColor >> borderRightColor;
let borderTop = (length, style, color) =>
  borderTop(length, style, color |> Colors.toColor);
let borderTopColor = Colors.toColor >> borderTopColor;
let color = Colors.toColor >> color;
let outline = (length, style, color) =>
  outline(length, style, color |> Colors.toColor);
let textDecorationColor = Colors.toColor >> textDecorationColor;

let typography = Typography.toStyle;
