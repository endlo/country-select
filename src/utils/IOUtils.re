// Allow running the side effects suspended in an IO. We use the IO pattern heavily at Qwick to push
// side effects to the furthest edges of our applications. This allows us to easily add additional effects to
// the IO chain, gracefully handle errors and prevent additional actions from firing if something in the chain
// fails, and greatly improves our control over exactly when those side effects happen.
let unsafeRunHandledAsync = IO.unsafeRunAsync(Result.fold(id, id));

module Promise = {
  external unsafePromiseToExn: Js.Promise.error => Js.Exn.t = "%identity";

  // Lazy helper function to convert promises to Relude IOs that can be chained with other effects
  let lazyPromiseToReludeIO: (unit => Js.Promise.t('a)) => IO.t('a, Js.Exn.t) =
    lazyPromise =>
      lazyPromise |> RJs.Promise.toIOLazy |> IO.mapError(unsafePromiseToExn);
};
