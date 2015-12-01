// var hook = require("./hook/what-to-wear.js");

var datastore = require("./datastore");

datastore.load()
.then(function () {
  return datastore.get("foo");
})
.then(function (data) {
  console.log("get");
  return console.log(data);
})
.then(function () {
  console.log("set");
  return datastore.set("foo", "quux");
})
.then(function () {
  return console.log("Done!");
})
.catch(function (err) {
  console.error("Error");
  return console.error(err);
});

