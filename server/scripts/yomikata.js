const got = require("got");
const {URL} = require("url");
const fs = require("fs");
const path = require("path");
const cheerio = require('cheerio');

const sleep = (time = 1000) => new Promise((resolve, _reject) => setTimeout(resolve, time));

const verb_dict = JSON.parse(fs.readFileSync(path.resolve(__dirname, "../verb_dict.json")));

(async function main() {
    for (let verb of verb_dict) {
        for (let example of verb.examples) {
            try {
                const {body} = await got(new URL(`https://yomikatawa.com/kanji/${example.in_kanji}?search=1`).href);
                const $ = cheerio.load(body);
                example.in_kana = $("h1+.ad_in_content+p").text().trim();
            } catch (_err) {
                console.log(example.in_kanji);
            }
            await sleep(1000);
        }
    }

    fs.writeFileSync(path.resolve(__dirname, "../verb_dict_new.json"), JSON.stringify(verb_dict));
})();