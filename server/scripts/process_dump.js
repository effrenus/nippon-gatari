const fs = require("fs");

const data = (JSON.parse(fs.readFileSync("./verb_dict.json"))).map(v => {
    const newV = {
        in_kanji: v.in_kanji,
        in_kana: v.in_kana,
        definitions: v.definitions.join("|"),
        part_1: v.struct_parts[0],
        part_2: v.struct_parts[1],
        struct_type: v.struct_type,
        transitivity_type: v.transitivity_type
    };
    v.examples.forEach((e, i) => newV["example_"+(i+1)] = `${e.in_kanji}|${e.in_kana}|${e.translation}`)
    !newV.example_2 && (newV.example_2 = "");
    !newV.example_3 && (newV.example_3 = "");
    !newV.example_4 && (newV.example_4 = "");
    return newV;
});

console.log(JSON.stringify(data));