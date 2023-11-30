module Horizontal = {
  module Styles = {
    open Css;

    let container = (~size) => style([flexShrink(0.0), width(px(size))]);
  };

  [@react.component]
  let make = (~size: int) => <div className={Styles.container(~size)} />;
};

module Vertical = {
  module Styles = {
    open Css;

    let container = (~size) => style([flexShrink(0.0), height(px(size))]);
  };

  [@react.component]
  let make = (~size: int) => <div className={Styles.container(~size)} />;
};
