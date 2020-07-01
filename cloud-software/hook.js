function forecastUrl(apiKey, location) {
  var apiUrl = "https://api.forecast.io/forecast";
  var excludeFields = "exclude=minutely,hourly";
  return apiUrl + "/" + apiKey + "/" + location + "?" + excludeFields;
}

function getForecast(url) {
  var got = require("got");
  return got(url)
  .then(function (response) {
    return JSON.parse(response.body);
  });
}

function forecastMapper(weather) {
  return {
    // Word weather summary for next 24 hours
    summary: weather.daily.data[0].summary,
    // Current temperature
    temperature: weather.currently.apparentTemperature
  };
}

function clothesForWeather(weather) {
  var s = weather.summary;
  if(s.match(/rain/i)) {
    return "umbrella";
  } else if(s.match(/snow/i)) {
    return "shovel";
  }
  
  var t = weather.temperature;
  if(t < 33) {
    return "hat";
  } else if(t < 55) {
    return "jacket";
  } else if(t < 70) {
    return "sweater";
  } else {
    return "tshirt";
  }
}

function outputMessage(hook, clothes, message) {
  if(hook.params.coreid) {
    console.log(message);
    hook.res.end(clothes);
  } else {
    hook.res.end(message + "\n");
  }
}

module['exports'] = function whatToWear (hook) {
  var location = hook.params.location || hook.env.DEFAULT_LOCATION;
  var url = forecastUrl(hook.env.FORECAST_IO_API_KEY, location);
  
  getForecast(url)
  .then(function (weather) {
    var simpleWeather = forecastMapper(weather);
    var clothes = clothesForWeather(simpleWeather);
    var message = "Wear " + clothes + " for forecast " + JSON.stringify(simpleWeather);
    outputMessage(hook, clothes, message);
  })
  .catch(function (error) {
    console.error("Error getting forecast: " + error);
    hook.res.end("error");
  });
};
