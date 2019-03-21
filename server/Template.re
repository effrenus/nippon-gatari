/* TODO Use PUG */
let head = title => {j|
    <head>
        <meta charset="UTF-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0" />
        <meta http-equiv="X-UA-Compatible" content="ie=edge" />
        <title>$title</title>
        <link
          rel="shortcut icon"
          href="data:image/png;base64,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"
        />
    </head>  
    |j}

let page = (~title, ~body) => {
    let head' = head(title);
    {j|
        <!DOCTYPE html>
        <html lang="ru">
          $head'
          <body>
            $body
          </body>
        </html>    
    |j}
}

let render = (html, apolloState) => page(
    ~title={j|Словарь составных глаголов|j},
    ~body={j|
        <div id="app">$html</div>
        <script>
        window.__APOLLO_STATE__ = $apolloState;
        </script>
        <script src="/assets/Index.js"></script>
    |j}
)

let renderErrorPage = errorMsg => page(
    ~title={j|Произошла ошибка|j},
    ~body={j|
        <section class="errorbox">
            <h1>Ошибка сервера</h1>
            $errorMsg
        </section>
        <style>
        .errorbox {
            width: 600px;
            border: 3px solid #ff5722;
            margin: 30px auto 0;
            padding: 30px;
        }
        </style>
    |j}
)