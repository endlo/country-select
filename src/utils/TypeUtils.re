// A subset of opaque type constructors that we built at Qwick to lean even more on the type system instead
// of passing around basic data types. This was a boon to our velocity and comfortability in making deep
// architechtural changes to a very large code base with very low effort.

module type OpaqueString = {
  type t;
  let fromString: string => option(t);
  let toString: t => string;
  let compare: (t, t) => Bastet.Interface.ordering;
  let eq: (t, t) => bool;

  module Ord: Bastet.Interface.ORD with type t = t;
  module Set: Set.SET with type value = t;
  module Map: Map.MAP with type key = t;
};

module type OpaqueFromString = {
  type t;
  let fromString: string => option(t);
  let toString: t => string;
};

module MakeCustomOpaqueStringType = (O: OpaqueFromString) : OpaqueString => {
  type t = O.t;
  let fromString = O.fromString;
  let toString = O.toString;
  let compare = String.compareWithConversion(toString);
  let eq = String.eqWithConversion(toString);

  module Ord = {
    type nonrec t = t;
    let compare = compare;
    let eq = eq;
  };
  module Set = Set.WithOrd(Ord);
  module Map = Map.WithOrd(Ord);
};

module MakeOpaqueStringType = () : OpaqueString =>
  MakeCustomOpaqueStringType({
    type t = string;
    let fromString = id >> Option.pure;
    let toString = id;
  });
