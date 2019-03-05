module Styles = {
    open ExtendedCss;

    let flick = Css.(keyframes([
        (50, [backgroundColor(`hex("f2ff8f")),]),
        (100, [backgroundColor(`hex("FFF")),])
    ]));

    let card = style([
        display(`flex),
        justifyContent(`spaceBetween),
        alignItems(`flexStart),
        padding3(~top=px(15), ~h=px(15), ~bottom=px(30)),
        borderBottom(px(1), `solid, `hex("EEE")),
        backgroundColor(`hex("FFF")),
    ]);

    let highlite = style([
        animationName(flick),
        animationDuration(2000),
    ]);

    let head = style([
        marginBottom(px(10)),
    ]);

    let definitions = style([
        margin(px(0)),
        padding2(~v=px(0), ~h=px(30)),
        listStyleType(`none),
        `declaration("counter-reset", "defs"),
    ]);

    let definition = style([
        marginBottom(px(10)),
        lineHeight(`abs(1.5)),
        `declaration("counter-increment", "defs"),

        before([
            display(`inlineBlock),
            width(px(16)),
            height(px(16)),
            marginRight(px(6)),
            marginLeft(px(-24)),
            contentRule("defs"),
            borderRadius(pct(50.)),
            border(px(1), `solid, `hex("BBB")),
            fontSize(rem(0.7)),
            textAlign(`center),
            lineHeight(px(16)),
            color(`hex("555")),
        ]),
    ]);

    let examples = style([
        padding2(~h=px(30), ~v=px(0)),
    ]);

    let struct_ = style([
        maxWidth(px(170)),
        minWidth(px(170)),    
        padding(px(15)),
        backgroundColor(`hex("EEE")),
        borderRadius(px(10)),
        boxShadow(~y=px(1), ~blur=px(2), `hex("BBB")),
        textAlign(`center),
    ]);

    let structList = style([
        margin(px(0)),
        marginTop(px(10)),
        padding(px(0)),
        listStyleType(`none),
        whiteSpace(`nowrap),
    ]);

    let structListItem = style([
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

    let structAbbr = style([
        textDecoration(`none),
        borderBottom(px(1), `dotted, `hex("888")),
    ]);
}

module Sentence = {
    module Style = {
        open Css;
        let example = style([
            marginBottom(px(10)),
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

module Definition = {
    let component = ReasonReact.statelessComponent("Nippon.VerbCard.Definition");
    let make = (~definition, _children) => {
        ...component,
        render: _self => {
            <div className=Styles.definition>
                { definition->ReasonReact.string }
            </div>
        }
    } 
}

module Definitions = {
    let component = ReasonReact.statelessComponent("Nippon.VerbCard.Definitions");
    let make = (~definitions, _children) => {
        ...component,
        render: _self => {
            <ol className=Styles.definitions>
                ...{ definitions|>Js.Array.map(v => <li className=Styles.definition>v->ReasonReact.string</li>) }
            </ol>
        }
    } 
}

let structDescription = type_ => switch (type_) {
    | "VV" => {j|оба глагола основные|j}
    | "Vs" => {j|основной + вспомогательный|j}
    | "pV" => {j|глагол модификатор + основной|j}
    | "V" => {j|глаголы воспринимаются как единый глагол с новым смыслом|j}
    | _ => ""
}

let component = ReasonReact.statelessComponent("Nippon.VerbCard");

let make = (~verb, ~highlite=false, _children) => {
    ...component,
    render: _ => {
      <article className={Styles.card ++ (highlite ? " " ++ Styles.highlite : "")}>
        <div>
            <header className=Styles.head>
                <b className=Styles.kanji>{verb##in_kanji->ReasonReact.string}</b>
                <small className=Styles.kana>{verb##in_kana->ReasonReact.string}</small>
                <small className=Styles.romaji>{Hepburn.romajiOfKana(verb##in_kana)->Js.String.toLowerCase->ReasonReact.string}</small>
            </header>
            {
                <Definitions definitions=verb##definitions />
            }
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
        <div className=Styles.struct_>
            {ReasonReact.string({j|тип |j})} <abbr className=Styles.structAbbr title=structDescription(verb##struct_type)>{ReasonReact.string(verb##struct_type)}</abbr>
            <ul className=Styles.structList>
            ...{
                verb##struct_parts
                |> Js.Array.map(part => <li className=Styles.structListItem>part->ReasonReact.string</li>)
            }
            </ul>
        </div>
      </article>
    },
  };