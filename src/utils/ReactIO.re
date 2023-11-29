// Tweak the default React useState hook to do two things:
// - Simplify the interface to remove access to the previous value (assume always overrite)
// - Wrap the set function in an IO
let useState = intitalState => {
  let (state, set) = React.useState(intitalState);
  let set =
    React.useCallback0(newState => IO.suspend(() => set(_ => newState)));

  (state, set);
};

// Add a new version of the React useState hook that allows mapping of the previous value and
// wraps the set function in an IO.
let useMappableState = intitalState => {
  let (state, set) = React.useState(intitalState);
  let set =
    React.useCallback0(newStateFn => IO.suspend(() => set(newStateFn)));

  (state, set);
};
