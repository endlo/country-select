[@react.component]
let make = () =>
  <main>
    <div> "Test"->React.string </div>
    <Bindings.ReactSelect onChange={_ => ()} options=[||] />
  </main>;
