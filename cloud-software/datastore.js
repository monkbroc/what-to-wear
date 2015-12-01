var fs = require("fs");
var thenify = require('thenify').withCallback;

var Datastore = {
  file: "data.json",

  load: function () {
    try {
      var data = fs.readFileSync(this.file);
      this.store = JSON.parse(data);
    } catch (error) { }
  },

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
