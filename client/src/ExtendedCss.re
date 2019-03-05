include Css;

let string_of_scrollBehavior =
    fun
    | `auto => "auto"
    | `smooth => "smooth";

/*
    @see https://developer.mozilla.org/en-US/docs/Web/CSS/scroll-behavior
*/
let scrollBehavior = x => `declaration("scrollBehavior", string_of_scrollBehavior(x))

let string_of_contentRule = x =>
    switch (x) {
    | x when x == "defs" => "counter(defs)"
    | _ => {j|"$x"|j};
    }

let contentRule = x => `declaration("content", string_of_contentRule(x));