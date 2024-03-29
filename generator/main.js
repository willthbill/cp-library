const clipboardy = require('clipboardy');
const readline = require('readline');
const fs = require('fs');

function getDirectory(){
    return __dirname;
    const temp1 = process.argv0; // calling path
    let idx = temp1.lastIndexOf("/");
    if(idx == -1) idx = temp1.length;
    const temp2 = temp1.substring(0, idx);
    const directory = `${process.cwd()}/${temp2}`;
    return directory;
}

const directory = getDirectory();

const outputColors = {
    green : "\x1b[32m",
    red : "\x1b[31m",
    reset : "\x1b[0m"
};

function copy(str){
    clipboardy.writeSync(str);
}

function getFolders(rootFolder){
    return new Promise((resolve, _) =>
        fs.readdir(rootFolder, { withFileTypes: true }, (_, files) => {
            resolve(files
                .filter(file => file.isDirectory())
                .filter(dir => dir.name[0] != '.')
                .map(dir => dir.name)
            );
        })
    );
}

function getReader(completions){
    return readline.createInterface({
        input: process.stdin,
        output: process.stdout,
        completer : (line) => {
            const hits = completions.filter(c => c.indexOf(line) == 0);
            return [hits.length ? hits : completions, line];
        }
    });
}

function getInput(reader, completions, question){
    return new Promise((resolve, _) =>
        reader.question(question, input => {
            reader.close();
            if(completions.indexOf(input) == -1){
                console.log(`${outputColors.red}Invalid input`);
                console.log(`${outputColors.reset}`);
                process.exit(0);
            }
            resolve(input);
        })
    );
}

const matchString = /%\s*include<\s*(\S*)s*>\s*%/g;

/*function _test(){
    let test = `
    %include<hello>%
    sdfsdf
    eegargserg
    sergesrg
    %include<hej>  %
    eegargserg
    sergesrg
    % include<  hello> %
    `;
    const matches = test.matchAll(matchString);
    console.log(matches);
    for(const match of matches){
        console.log(match);
        const idx = test.indexOf(match);
        console.log(idx);
        console.log("|", test, "|");
        test = test.replace(match, "from another file");
    }
    console.log(test);
}
_test();*/

function removeBlankLines(file) {
    lines = file.split("\n").filter(line => line.replace(/\s/g, '').length > 0)
    return lines.join("\n")
}

function setFileMetaData(file, pathname, withmessage = false) {
    if(withmessage) {
        return `// BEGIN code block of: ${pathname}
// Standard message: The following is code from https://github.com/williamMBDK/cp-library but was copied from a local copy of the repository. Changes to the original source may have been done here.
${file}
// END code block of: ${pathname}`;
    } else {
        return `// BEGIN code block of: ${pathname}
${file}
// END code block of: ${pathname}`;
    }
}

function processFile(pathname){
    let file = fs.readFileSync(
        `${directory}/../src/${pathname}/main.cpp`,
        {encoding:'utf8', flag:'r'}
    );
    const matches = file.matchAll(matchString);
    for(const match of matches){
        const newPath = match[1];
        const dependency = processFile(newPath) + "\n";
        file = file.replace(match[0], setFileMetaData(dependency, newPath));
    }
    return removeBlankLines(file);
}

function printFile(file) {
    console.log("============================ content ============================");
    console.log(file);
    console.log("=================================================================");
}

async function run(){
    let category, concept;
    try{
        const categories = await getFolders(`${directory}/../src`);
        const category_reader = getReader(categories);
        category = await getInput(
            category_reader,
            categories,
            "Input category: "
        );
        const concepts = await getFolders(`${directory}/../src/${category}`);
        const concept_reader = getReader(concepts);
        concept = await getInput(
            concept_reader,
            concepts,
            "Input concept: "
        );
        let file = processFile(`${category}/${concept}`);
        file = setFileMetaData(file, `${category}/${concept}`, true);
        console.log(`${outputColors.green}Generated content for ${category}/${concept}`);
        copy(file);
        console.log(`${outputColors.green}Content copied to clipboard`);
        console.log(`${outputColors.reset}`);
        printFile(file);
    } catch(e){
        console.log(`${outputColors.red}The following error occured\n`);
        console.log(`${outputColors.reset}${e}`);
        process.exit(0);
    }
}

if(process.argv.length == 4){ // silent
    const category = process.argv[2];
    const concept = process.argv[3];
    let file = setFileMetaData(processFile(`${category}/${concept}`), `${category}/${concept}`, true);
    console.log(file)
}else{
    run();
}
