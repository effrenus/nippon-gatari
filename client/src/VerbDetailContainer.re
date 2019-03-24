open GqlQuery;

let component = ReasonReact.statelessComponent("Nippon.Verb.Detail");

let make = (~name, _children) => {
    ...component,
    render: _ => {
      let getVerbQuery = GetVerbGql.make(~name, ());
      <GetVerbComponent variables=getVerbQuery##variables>
        ...{
             ({result}) =>
               switch (result) {
               | Loading => <LoaderWithNeko />
               | Error(error) =>
                  <div> {ReasonReact.string(error##message)} </div>
               | Data(response) =>
                response##verb
                ->Belt.Option.mapWithDefault(ReasonReact.null, verb => <VerbCardDetail verb />)
               }
           }
      </GetVerbComponent>;
    },
  };