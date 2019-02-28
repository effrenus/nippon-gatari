/**
 * Bindings to `hepburn` npm package
 * @see https://github.com/lovell/hepburn
 */

type katakana = string;
type romaji = string;
type hiragana = string;
type kana = string;

[@bs.module "hepburn" ]
external romajiOfKana : kana => romaji = "fromKana"; 

[@bs.module "hepburn" ]
external hiraganaOfRomaji : romaji => hiragana = "toHiragana";

[@bs.module "hepburn" ]
external katakanaOfRomaji : romaji => katakana = "toKatakana";

[@bs.module "hepburn" ]
external cleanRomaji : romaji => romaji = "cleanRomaji";

[@bs.module "hepburn" ]
external containsHiragana : string => bool = "containsHiragana";

[@bs.module "hepburn" ]
external containsKatakana : string => bool = "containsKatakana";

[@bs.module "hepburn" ]
external containsKana : string => bool = "containsKana";

[@bs.module "hepburn" ]
external containsKanji : string => bool = "containsKanji";