module Styles = {
    open Css;

    let card = style([
        display(`flex),
        justifyContent(`spaceBetween),
        padding3(~top=px(15), ~h=px(15), ~bottom=px(30)),
        borderBottom(px(1), `solid, `hex("EEE")),
    ]);

    let head = style([
        marginBottom(px(10)),
    ]);

    let definition = style([
        marginBottom(px(20)),
        padding2(~h=px(30), ~v=px(0)),
    ]);

    let examples = style([
        padding2(~h=px(30), ~v=px(0)),
    ]);

    let verbStruct = style([
        width(px(200)),
        padding(px(15)),
        backgroundColor(`hex("EEE")),
        borderRadius(px(10)),
        boxShadow(~y=px(1), ~blur=px(2), `hex("BBB")),
        textAlign(`center),
    ]);

    let verbStructList = style([
        margin(px(0)),
        marginTop(px(10)),
        padding(px(0)),
        listStyleType(`none),
    ]);

    let verbStructListItem = style([
        display(`inlineBlock),
        padding(px(10)),
        border(px(3), `solid, `hex("AAA")),
        borderRadius(px(5)),
        backgroundColor(`hex("FFF")),
        firstChild([
            marginRight(px(10)),
        ]),
    ]);

    let kanji = style([
        marginRight(px(10)),
    ]);
    let kana = style([
        marginRight(px(10)),
    ]);
    let romaji = style([
        fontSize(em(1.)),
    ]);
}

module Sentence = {
    module Style = {
        open Css;
        let example = style([
            color(`hex("111")),
        ]);

        let translation = style([
            display(`block),
            marginTop(px(5)),
            fontSize(rem(0.9)),
        ])
    }
    let component = ReasonReact.statelessComponent("Nippon.VerbCard.Sentence");
    let make = (~kanji, ~kana, ~translation, _children) => {
        ...component,
        render: _self => {
            <div className=Style.example>
                <span title=kana>{kanji->ReasonReact.string}</span> 
                <span className=Style.translation>{translation->ReasonReact.string}</span>
            </div>
        }
    }    
}

let component = ReasonReact.statelessComponent("Nippon.VerbCard");

let make = (~verb, _children) => {
    ...component,
    render: _ => {
      <article className=Styles.card>
        <div>
            <header className=Styles.head>
                <b className=Styles.kanji>{verb##in_kanji->ReasonReact.string}</b>
                <small className=Styles.kana>{verb##in_kana->ReasonReact.string}</small>
                <small className=Styles.romaji>{Hepburn.romajiOfKana(verb##in_kana)->Js.String.toLowerCase->ReasonReact.string}</small>
            </header>
            <div className=Styles.definition>
                ...{ verb##definitions |> Js.Array.map(v => v->ReasonReact.string) }
            </div>
            {
                switch (verb##examples) {
                | None => ReasonReact.null
                | Some(examples) => 
                <div className=Styles.examples>
                ...{
                    examples |> Js.Array.map(v => <Sentence kanji=v##in_kanji kana=v##in_kana translation=v##translation />)
                }
                </div>
                };
            }
        </div>
        <div className=Styles.verbStruct>
            {ReasonReact.string({j|тип |j} ++ verb##struct_type)}
            <ul className=Styles.verbStructList>
            ...{
                verb##struct_parts
                |> Js.Array.map(part => <li className=Styles.verbStructListItem>part->ReasonReact.string</li>)
            }
            </ul>
        </div>
      </article>
    },
  };