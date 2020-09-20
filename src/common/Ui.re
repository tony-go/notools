module TextInput = {
  [@bs.module "grommet"][@react.component]
  external make: (~placeholder: string, ~value: string, ~onChange: ((ReactEvent.Form.t) => unit), ~autoFocus: bool=?) => React.element = "TextInput";
}

module Button = {
  [@bs.module "grommet"][@react.component]
  external make: (~label: string, ~onClick: (ReactEvent.Mouse.t) => unit) => React.element = "Button";
}

module Box = {
  [@bs.module "grommet"][@react.component]
  external make: (~gap: string, ~direction: string, ~children: option('children)=?) => React.element = "Box";
}

module CheckBox = {
  [@bs.module "grommet"][@react.component]
  external make: (~checked: bool, ~label: string, ~onChange: (ReactEvent.Form.t) => unit) => React.element = "CheckBox";
}

