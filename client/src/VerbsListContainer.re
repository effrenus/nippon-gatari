open GqlQuery;

let component = ReasonReact.statelessComponent("Nippon.VerbsList");

let make = _children => {
    ...component,
    render: _ => {
      <GetAllVerbsComponent>
        ...{
             ({result}) =>
               switch (result) {
               | Loading => <LoaderWithNeko />
               | Error(error) =>
                  <div> {ReasonReact.string(error##message)} </div>
               | Data(response) =>
                  <VerbPanel verbs=response##verbs />
               }
           }
      </GetAllVerbsComponent>;
    },
  };