const got = require('got');

function forecastUrl({ apiKey, lat, lon }) {
	return `https://api.openweathermap.org/data/2.5/onecall?lat=${lat}&lon=${lon}&appid=${apiKey}&exclude=current,minutely,hourly`;
}

module.exports = {
	forecastUrl
};
