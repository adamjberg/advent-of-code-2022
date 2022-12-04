const fs = require("fs");
const day3 = () => {
  const data = fs.readFileSync("./input.txt", "utf-8");
  const array = data.split("\n");
  const alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const duplicateArray = [];
  let score = 0;
  for (let i = 0; i < array.length; i++) {
    const element = array[i];
    const middle = Math.floor(element.length / 2);
    const firstHalf = element.substring(0, middle);
    const secondHalf = element.substring(middle);
    for (let j = 0; j < firstHalf.length; j++) {
      const element = firstHalf[j];
      const regex = new RegExp(element);
      const matchedValue = secondHalf.match(regex);
      if (matchedValue !== null) {
        duplicateArray.push(matchedValue[0]);
        j = firstHalf.length;
      }
    }
  }
  for (let i = 0; i < duplicateArray.length; i++) {
    const element = duplicateArray[i];
    const matchedValue = alphabet.indexOf(element);
    score += matchedValue + 1;
  }
  console.log(score);
};
day3();

const day3Part2 = () => {
  const data = fs.readFileSync("./input.txt", "utf-8");
  const alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const array = data.split("\n");
  const badges = [];
  let score = 0;
  for (let i = 0; i < array.length; i += 3) {
    const element1 = array[i];
    const element2 = array[i + 1];
    const element3 = array[i + 2];
    for (let j = 0; j < element1.length; j++) {
      const element = element1[j];
      const regex = new RegExp(element);
      const firstMatch = element2.match(regex);
      const secondMatch = element3.match(regex);
      if (firstMatch !== null && secondMatch !== null) {
        badges.push(element);
        j = element1.length;
      }
    }
  }
  for (let i = 0; i < badges.length; i++) {
    const element = badges[i];
    const matchedValue = alphabet.indexOf(element);
    score += matchedValue + 1;
  }
  console.log(score);
};

// day3Part2();