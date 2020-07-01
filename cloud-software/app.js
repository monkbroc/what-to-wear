const express = require('express');
const weather = require('./weather');

const app = express();

app.get('/', async (req, res) => {
	let forecast;
	try {
		const apiKey = process.env.OPENWEATHER_API_KEY;
		const [lat, lon] = (process.env.LOCATION || '').split(',');

		const url = weather.forecastUrl({ apiKey, lat, lon });
		forecast = await weather.getForecast({ url });
		const clothes = weather.clothesForWeather({ forecast });

		console.log(`Wear ${clothes} for weather`);
		console.dir(forecast, { depth: null });
		res.end(clothes);
	} catch (err) {
		console.log('Error fetching weather', err);
		console.dir(forecast, { depth: null });

		res.status(500).end();
	}
});

module.exports = app;
