var env = require("./env");
var datastore = require("./datastore");
var res = require("./res");

var whatToWear = require("./hook/what-to-wear.js");

datastore.load();

var hook = {
  datastore: datastore,
  env: env,
  res: res
};

hook.params = {};


whatToWear(hook);
