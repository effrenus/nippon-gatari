open NipponGatariClient;

let server = Udp.createSocket(`udp4);

server->Udp.on(`message((_buf, info) => 
    GqlClient.getDataFromTree(<ReasonApollo.Provider client=GqlClient.instance><VerbDetailContainer name="%E3%81%82%E3%81%8C%E3%82%8A%E3%81%93%E3%82%80" /></ReasonApollo.Provider>)
    |> Js.Promise.then_(() => {
    server
    -> Udp.send(
        ~msg=ReactDOMServerRe.renderToString(<ReasonApollo.Provider client=GqlClient.instance><VerbDetailContainer name="%E3%81%82%E3%81%8C%E3%82%8A%E3%81%93%E3%82%80" /></ReasonApollo.Provider>),
        ~port=info##port,
        ~address=info##address
    )
    |> Js.Promise.resolve
    })
    |> ignore
));

server->Udp.bind(~port=8200, ());