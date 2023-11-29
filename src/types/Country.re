module Label = TypeUtils.MakeOpaqueStringType();

module Value = {
  let%private testRegex = [%re "/^([a-z]{2})$/"];

  include TypeUtils.MakeCustomOpaqueStringType({
    type t = string;
    let fromString =
      fun
      | str when str |> Js.Re.test_(testRegex) => Some(str)
      | _ => None;
    let toString = id;
  });
};

type t = {
  label: Label.t,
  value: Value.t,
};

let decode =
  Js.Json.decodeObject
  >> Option.flatMap(countryDict =>
       (
         Js.Dict.get(countryDict, "label")
         |> Option.flatMap(Js.Json.decodeString)
         |> Option.flatMap(Label.fromString),
         Js.Dict.get(countryDict, "value")
         |> Option.flatMap(Js.Json.decodeString)
         |> Option.flatMap(Value.fromString),
       )
       |> Option.mapTuple2((label, value) => {label, value})
     );
