const fs = require("fs");
const path = require("path");

const honbun = JSON.parse(fs.readFileSync(path.resolve(__dirname, "../dumps/honbun.json")));
const verb_dict = JSON.parse(fs.readFileSync(path.resolve(__dirname, "../verb_dict.json")));

for (let verb of verb_dict) {
    const honbun_def = honbun.rows.find(elm => elm.cell["4"] === verb.in_kana);
    if (!honbun_def) continue;
    
    verb.struct_type = honbun_def.cell["12"];
}

console.log(JSON.stringify(verb_dict));