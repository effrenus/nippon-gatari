module Styles = {
    open Css;

    let wrap = style([
        maxWidth(px(1500)),
        margin(`auto),
        padding4(~top=px(15), ~right=px(30), ~left=px(30), ~bottom=px(30)),
    ]);

    let card = style([
        display(`flex),
        justifyContent(`spaceBetween),
        alignItems(`flexStart),
        marginTop(px(15)),
        padding3(~top=px(15), ~h=px(15), ~bottom=px(30)),
        borderBottom(px(1), `solid, `hex("EEE")),
        backgroundColor(`hex("FFF")),
        boxShadow(~blur=px(3), ~spread=px(1),  `hex("ccc")),
    ]);

    let head = style([
        width(px(170)),
        maxWidth(px(170)),
    ]);

    let body = style([
        flexGrow(2.),
        paddingTop(px(12)),
    ]);

    let definitions = style([
        margin(px(0)),
        padding2(~v=px(0), ~h=px(30)),
        listStyleType(`none),
        `declaration("counter-reset", "defs"),
    ]);

    let definition = style([
        marginBottom(px(30)),
        lineHeight(`abs(1.4)),
        `declaration("counter-increment", "defs"),
        lastOfType([
            marginBottom(px(0))
        ]),

        before([
            display(`inlineBlock),
            width(px(16)),
            height(px(16)),
            marginRight(px(6)),
            marginLeft(px(-24)),
            `declaration("content", "counter(defs, decimal)"),
            borderRadius(pct(50.)),
            border(px(1), `solid, `hex("BBB")),
            fontSize(rem(0.7)),
            textAlign(`center),
            lineHeight(px(16)),
            fontWeight(`bold),
            color(`hex("444")),
        ]),
    ]);

    let definitionText = style([
        display(`inlineBlock),
        marginBottom(px(5)),
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

    let title = style([
        marginTop(px(0)),
        marginBottom(px(10)),
        fontWeight(`normal),
        fontSize(rem(1.7)),
    ]);
    let kana = style([
        display(`block),
        marginBottom(px(10)),
    ]);
    let romaji = style([]);

    let structAbbr = style([
        textDecoration(`none),
        borderBottom(px(1), `dotted, `hex("888")),
    ]);

    let detailLink = style([
        color(`hex("000")),
        textDecoration(`none),

        hover([
            textDecoration(`underline),
        ])
    ]);

    let backLink = style([
        textDecoration(`none),
        borderBottom(px(1), `solid, `hex("b5c5f7")),
        color(`hex("314a9c")),

        before([
            contentRule({j|←|j}),
            fontSize(rem(1.8)),
        ])
    ])
}

module Sentence = {
    module Style = {
        open Css;
        let example = style([
            marginTop(px(10)),
            color(`hex("333")),
        ]);

        let kanji = style([
            display(`block),
            marginBottom(px(5)),
        ]);

        let translation = style([
            display(`block),
            marginTop(px(0)),
        ])
    }
    let component = ReasonReact.statelessComponent("Nippon.VerbCard.Sentence");
    let make = (~kanji, ~kana, ~translation, _children) => {
        ...component,
        render: _self => {
            <div className=Style.example>
                <span className=Style.kanji title=kana>{kanji->ReasonReact.string}</span> 
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
    let getDefExamples = (examples, defIndex) =>
        switch (examples) {
        | None => ReasonReact.null
        | Some(exs) => 
            exs
            -> Belt.Array.keep(ex => switch (ex##definition) { | None => false | Some(v) => v === defIndex + 1 })
            -> Belt.Array.map(ex => <Sentence kanji=ex##in_kanji kana=ex##in_kana translation=ex##translation />)
            -> ReasonReact.array
        }
    let component = ReasonReact.statelessComponent("Nippon.VerbCard.Definitions");
    let make = (~definitions, ~examples, _children) => {
        ...component,
        render: _self => {
            <ol className=Styles.definitions>
                ...{ definitions |> Js.Array.mapi((v, i) => 
                    <li className=Styles.definition>
                        <span className=Styles.definitionText>{v->ReasonReact.string}</span>
                        {getDefExamples(examples, i)}
                    </li>) }
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

let component = ReasonReact.statelessComponent("Nippon.VerbCardDetail");

let make = (~verb, _children) => {
    ...component,
    render: _ => {
      <div className=Styles.wrap>
        <Router.Link className=Styles.backLink href="/compverbs/">{{j|к общему списку|j}->ReasonReact.string}</Router.Link>
        <article className=Styles.card>
            {
                let kanji = verb##in_kanji;
                let kana = verb##in_kana;
                let defs = verb##definitions|>Js.Array.joinWith("; ");
                <Helmet>
                    <title>{j|$kanji・$kana — значение слова, примеры. Словарь составных глаголов|j}->ReasonReact.string</title>
                    <meta property="description" content={j|$kanji・$kana — $defs. Примеры|j} />
                    <meta property="keywords" content={j|значение слова, $kanji, $kana, примеры, словарь, составные глаголы, 複合動詞, обучение, японский язык, ниппонгатари|j} />
                    <meta property="og:locale" content="ru" />
                    <meta property="og:type" content="article" />
                    <meta property="og:url" content={j|/compverbs/$kana/|j} />
                    <meta property="og:title" content={j|$kanji・$kana — значение слова, примеры. Словарь составных глаголов|j} />
                    <meta property="og:description" content={j|$kanji・$kana — $defs. Примеры.|j} />
                    <meta name="author" content={j|Олеся Гончар|j} />
                </Helmet>
            }
            <header className=Styles.head>
                <h1 className=Styles.title>{verb##in_kanji->ReasonReact.string}</h1>
                <span className=Styles.kana>{verb##in_kana->ReasonReact.string}</span>
                <span className=Styles.romaji>{Hepburn.romajiOfKana(verb##in_kana)->Js.String.toLowerCase->ReasonReact.string}</span>
            </header>
            <div className=Styles.body>
                <Definitions definitions=verb##definitions examples=verb##examples />
            {
                switch (verb##examples) {
                | None => ReasonReact.null
                | Some(examples) => 
                <div className=Styles.examples>
                ...{
                    examples
                    -> Belt.Array.keep(ex => switch (ex##definition) { | None => true | Some(_) => false })
                    |> Js.Array.map(v => <Sentence kanji=v##in_kanji kana=v##in_kana translation=v##translation />)
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
      </div>
    },
  };