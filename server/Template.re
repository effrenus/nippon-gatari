/* TODO Use PUG */
let head = helmet => {
  let title = helmet##title##toString();
  let meta = helmet##meta##toString();

  {j|
    <head>
        <meta charset="UTF-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0" />
        <meta http-equiv="X-UA-Compatible" content="ie=edge" />
        $title
        $meta
        <link rel="shortcut icon" href="/assets/favicon.png" />
    </head>  
  |j}
}

let page = (~helmet, ~body) => {
    let head' = head(helmet);
    {j|<!DOCTYPE html>
        <html lang="ru" prefix="og: http://ogp.me/ns#">
          $head'
          <body>
            $body
          </body>
        </html>    
    |j}
}

let render = (html, ~apolloState, ~helmet) => page(
    ~helmet,
    ~body={j|
        <div id="app">$html</div>
        <script>
        window.__APOLLO_STATE__ = $apolloState;
        </script>
        <script src="/assets/Index.js"></script>
    |j}
)

let renderErrorPage = errorMsg => 
    {j|<!DOCTYPE html>
      <html lang="ru">
        <head>
            <meta charset="UTF-8" />
            <meta name="viewport" content="width=device-width, initial-scale=1.0" />
            <meta http-equiv="X-UA-Compatible" content="ie=edge" />
            <title>Ошибка</title>
            <link rel="shortcut icon" href="/assets/favicon.png" />
        </head>  
        <body>
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
        </body>
      </html>
    |j}