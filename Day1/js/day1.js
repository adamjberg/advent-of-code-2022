// Adapted from https://www.reddit.com/r/adventofcode/comments/z9ezjb/comment/iyh1ocu/?utm_source=share&utm_medium=web2x&context=3
const fs = require('fs');

const start = process.hrtime.bigint();

const data = fs.readFileSync('input.txt');

let [first, second, third] = String(data).replace(/(.*)(\r\n|\n|\r)/gm, '$1,').split(',,').map(elf => {
  return elf.split(',').reduce((prev, next) => prev + Number(next), 0)
}).sort((a,b) => b -a);

const end = process.hrtime.bigint();

// 571958n
console.log(end - start);

console.log(first + second + third);