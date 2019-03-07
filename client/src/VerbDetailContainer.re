open GqlQuery;

module Styles = {
  open Css;

  let wrap = style([
      maxWidth(px(1500)),
      margin(`auto),
      padding4(~top=px(15), ~right=px(30), ~left=px(30), ~bottom=px(30)),
  ]);

  let backLink = style([
    display(`inlineBlock),
    marginBottom(px(15)),
    fontWeight(`bold),
    color(`hex("000")),
    textDecoration(`none),
    verticalAlign(`top),

    before([
      contentRule({j|←|j}),
      fontSize(rem(1.8)),
    ])
  ])
}

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
                ->Belt.Option.mapWithDefault(ReasonReact.null, verb => 
                  <section className=Styles.wrap>
                    <Router.Link className=Styles.backLink href="/compverbs/">{{j|назад|j}->ReasonReact.string}</Router.Link>
                    <VerbCard verb />
                  </section>)
               }
           }
      </GetVerbComponent>;
    },
  };