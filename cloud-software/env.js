var fs = require("fs");
var dotenv = require("dotenv");

var env = {};
try {
  var buf = fs.readFileSync(".env");
  env = dotenv.parse(buf);
} catch (error) {
  console.warn("Error loading .env: " + error);
}

module.exports = env;
