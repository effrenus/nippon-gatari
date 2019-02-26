open GqlQuery;

let component = ReasonReact.statelessComponent("Nippon.VerbsList");

let make = _children => {
    ...component,
    render: _ => {
      <GetAllVerbsComponent>
        ...{
             ({result}) =>
               switch (result) {
               | Loading => <div> {ReasonReact.string("Loading")} </div>
               | Error(error) =>
                  <div> {ReasonReact.string(error##message)} </div>
               | Data(response) =>
                  <VerbPanel verbs=response##verbs />
               }
           }
      </GetAllVerbsComponent>;
    },
  };