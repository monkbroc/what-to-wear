var fs = require("fs");
var thenify = require('thenify').withCallback;

var Datastore = {
  file: "data.json",

  load: thenify(function (callback) {
    fs.readFile(this.file, function (err, data) {
      if(!err) {
        this.store = JSON.parse(data);
      }
      callback(null);
    }.bind(this));
  }),

  save: thenify(function (callback) {
    var data = JSON.stringify(this.store);
    console.log(data);
    fs.writeFile(this.file, data, function (err) {
      callback();
    });
  }),

  get: thenify(function (name, callback) {
    callback(null, this.store[name]);
  }),

  set: thenify(function (name, value, callback) {
    this.store[name] = value;
    this.save(callback);
  })
};

Datastore.store = {};

module.exports = Datastore;
