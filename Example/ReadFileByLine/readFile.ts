const fs = require('fs');
const readline = require('readline');

const rl = readline.createInterface({
    input: fs.createReadStream('test.env'),
    output: process.stdout,
    terminal: false
});

console.log("hello, world")
let ret = []
rl.on('line', (line: string) => {
    let splitLines = line.split('=')
    ret.push(splitLines[0])
})

rl.on('close', () => {
    console.log(ret.join(','))
})
