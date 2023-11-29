let extendBaseStyle = (baseStyle, extendedStyle) =>
  [Some(baseStyle), extendedStyle] |> List.catOptions |> Css.merge;
