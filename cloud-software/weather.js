const got = require('got');

function forecastUrl({ apiKey, lat, lon }) {
	return `https://api.openweathermap.org/data/2.5/onecall?lat=${lat}&lon=${lon}&appid=${apiKey}&exclude=minutely,hourly&units=metric`;
}

async function getForecast({ url, _got = got }) {
	const { body } = await _got(url);
	return JSON.parse(body);
}

function clothesForWeather({ forecast }) {
	// transforms weather data from https://openweathermap.org/api/one-call-api
	// into clock predictions
	const daily = forecast.daily[0];
	const summary = daily.weather[0].main;
	const temperature = forecast.current.feels_like;
	if (summary === 'Thunderstorm' || summary === 'Drizzle' || summary === 'Rain') {
		return 'umbrella';
	} else if (summary === 'Snow') {
		return 'shovel';
	} else if (temperature < 2) {
		return 'hat';
	} else if (temperature < 12) {
		return 'jacket';
	} else if (temperature < 20) {
		return 'sweater';
	} else {
		return 'tshirt';
	}
}

module.exports = {
	forecastUrl,
	getForecast,
	clothesForWeather
};
