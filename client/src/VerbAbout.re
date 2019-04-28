module Styles = {
    open Css;
  
    let article = style([
        padding(px(15)),
        backgroundColor(`hex("FFF")),
        boxShadow(~blur=px(3), ~spread=px(1),  `hex("ccc")),
        lineHeight(`abs(1.5)),
    ]);  
}

let component = ReasonReact.statelessComponent("Nippon.VerbAbout");

let make = _children => {
    ...component,
    render: _ => {
      <>
      <Helmet>
          <title>{j|О словаре|j}->ReasonReact.string</title>
          <meta name="description" content={j|Словарь по составным (сложным) глаголам японского языка. 複合動詞 (ふくごうどうし）|j} />
          <meta name="keywords" content={j|словарь, составные глаголы, 複合動詞, японский язык, примеры, значение глаголов, ниппон гатари|j} />
          <meta property="og:locale" content="ru" />
          <meta property="og:title" content={j|О словаре|j} />
          <meta property="og:url" content="/compverbs//about/" />
          <meta property="og:description" content={j|Словарь по составным (сложным) глаголам японского языка. 複合動詞 (ふくごうどうし）|j} />
          <meta property="og:type" content="website" />
      </Helmet>
            
      <article className=Styles.article>
        <p>{j|Составные глаголы японского языка или 複合動詞 (ふくごうどうし) – особый вид глаголов, который часто состоит как правило из слияния двух глаголов, и имеет смысл одного из них (нередко оттенок задает второй глагол). Тем, кто изучал немецкий язык всегда легко свыкнуться с существованием подобного явления, т.к. в немецком языке не редкость слияния разных частей речи (хотя в японском сливаются не только глаголы, но и прилагательные), однако другим учащимся это бывает не так просто. Но если практиковаться в изучении данного вида глаголов и “расписывать его по полочкам”, т.е. на составные части, жизнь сразу упрощается.|j}->ReasonReact.string</p>
        <p>{j|Как отмечалось выше, нередко задает погоду второй из глаголов. Так, если вы хорошо уяснили на четвертом уровне, что 込みます это “втюхивать”, “впихивать”, и часто употребляется выражение 込んでいる – т.е. “забито”, то вы уже начали уяснять нюанс составной части и в дальнейшем Вам будет проще понять такие глаголы, как 殴り込む – 殴る (бить) и 込む (втискивать, проталкивать, набивать, быть переполненным) – составной глагол означает вбивать, нападать, совершать нападки. Т.е. не просто 1 раз стукнуть и забыть, а по оттенку 込む налететь на человека со всей дури и чуть ли не собой его закрыть.|j}->ReasonReact.string</p>
        <p>{j|В свете вышесказанного весь справочник составных глаголов будет разбит на следующие части:|j}->ReasonReact.string</p>
        <ul>
            <li>{j|Составной глагол и его значение.|j}->ReasonReact.string</li>
            <li>{j|Переходность (他動詞, 他） и непереходность (自動詞, 自) глагола. Это важно, потому что нужно помнить на кого и от кого идет действие.|j}->ReasonReact.string</li>
            <li>{j|Перевод глагола – без этого никуда.|j}->ReasonReact.string</li>
            <li>{j|Составные части с переводом – это ускорит мнемонику запоминания глагола.|j}->ReasonReact.string</li>
            <li>{j|По возможности пример с каждым из глаголов.|j}->ReasonReact.string</li>
        </ul>
        <p>{j|Советую обращать внимание на употребление частиц в примерах, т.к. они стандартизированы и часто употребляются именно с этими глаголами.|j}->ReasonReact.string</p>
        <p>{j|При составлении словаря использовались материалы из книг/сайтов:|j}->ReasonReact.string</p>

        <ul>
            <li><a href="http://www.nippon-gatari.info/" target="_blank"><strong>"nippon-gatari.info"->ReasonReact.string</strong></a></li>
            <li><a href="https://tokado.ru/jp/ja26.php?tracking=58aea9d11050c" target="_blank" rel="nofollow">{j|徹底ドリル|j}->ReasonReact.string</a>", "->ReasonReact.string <a href="https://tokado.ru/jp/ja19.php?tracking=58aea9d11050c" target="_blank" rel="nofollow">{j|合格できる|j}->ReasonReact.string</a>{j|, 新完全マスター, 日本語総まとめ, kotobank, weblio|j}->ReasonReact.string</li>
            <li><a href="https://db4.ninjal.ac.jp/vvlexicon/db/" target="_blank" rel="nofollow">"db4.ninjal.ac.jp"->ReasonReact.string</a></li>
            <li><a href="https://english.cheerup.jp" target="_blank" rel="nofollow">"english.cheerup.jp"->ReasonReact.string</a></li>
            <li><a href="https://dictionary.goo.ne.jp/" target="_blank" rel="nofollow">"dictionary.goo.ne.jp"->ReasonReact.string</a></li>
            <li><a href="https://ncode.syosetu.com/" target="_blank" rel="nofollow">"ncode.syosetu.com"->ReasonReact.string</a></li>
            <li><a href="https://eow.alc.co.jp" target="_blank" rel="nofollow">"eow.alc.co.jp"->ReasonReact.string</a></li>
            <li><a href="https://eitopi.com" target="_blank" rel="nofollow">"eitopi.com"->ReasonReact.string</a></li>
            <li><a href="https://kotonoha-jiten.com/blog/yarisugosu/" target="_blank" rel="nofollow">"kotonoha-jiten.com"->ReasonReact.string</a></li>
            <li><a href="https://english.cheerup.jp" target="_blank" rel="nofollow">"english.cheerup.jp"->ReasonReact.string</a></li>
            <li><a href="https://mayonez.jp/" target="_blank" rel="nofollow">"mayonez.jp"->ReasonReact.string</a></li>
        </ul>
      </article>
      </>;
    },
  };