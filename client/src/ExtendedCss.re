include Css;

let string_of_scrollBehavior =
    fun
    | `auto => "auto"
    | `smooth => "smooth";

/*
    @see https://developer.mozilla.org/en-US/docs/Web/CSS/scroll-behavior
*/
let scrollBehavior = x => `declaration("scrollBehavior", string_of_scrollBehavior(x))