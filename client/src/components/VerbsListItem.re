module Styles = VerbListItem__Styles;

let component = ReasonReact.statelessComponent("Nippon.VerbsListItem");

let make = (~verb, ~onClick, _children) => {
    ...component,
    render: _ => {
      <li className=Styles.item onClick=onClick>
        <div className=Styles.word>
          <span className=Styles.kanji>{ReasonReact.string(verb##in_kanji)}</span>
          <span className=Styles.kana>{ReasonReact.string(verb##in_kana)}</span>
        </div>
        <div className=Styles.transitivity>
          {
            switch (verb##transitivity_type) {
            | "tr." => <TransitivityLabels.TransitiveLabel/>
            | "intr." => <TransitivityLabels.IntransitiveLabel/>
            | "dual" => <TransitivityLabels.DualLabel/>
            | _ => "?"->ReasonReact.string
            }
          }
        </div>
        <div className=Styles.struct_>
          {ReasonReact.string(verb##struct_type)}
        </div>
      </li>
    },
  };