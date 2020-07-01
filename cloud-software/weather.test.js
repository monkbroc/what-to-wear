const { expect } = require('chai');

const weather = require('./weather');

describe('weather', () => {
	describe('forecastUrl', () => {
		it('returns a formatted url', () => {
			const url = weather.forecastUrl({ apiKey: 'abc123', lat: 42, lon: -83 });
			expect(url).to.eql('https://api.openweathermap.org/data/2.5/onecall?lat=42&lon=-83&appid=abc123&exclude=minutely,hourly&units=metric');
		});
	});

	describe('getForecast', () => {
		it('returns payload', async () => {
			const expectedUrl = 'https://weather';
			const body = '{ "weather": "clear" }';
			const got = async function(url) {
				expect(url).to.eql(expectedUrl);
				return { body };
			};

			const result = await weather.getForecast({ url: expectedUrl, _got: got });
			expect(result).to.eql({ weather: 'clear' });
		});
	});

	describe('clothesForWeather', () => {
		it('maps thunderstorm to umbrella', () => {
			const forecast = {
				current: {
					feels_like: 0
				},
				daily: [{
					weather: [{
						main: 'Thunderstorm'
					}]
				}]
			};
			expect(weather.clothesForWeather({ forecast })).to.eql('umbrella');
		});
		it('maps drizzle to umbrella', () => {
			const forecast = {
				current: {
					feels_like: 0
				},
				daily: [{
					weather: [{
						main: 'Drizzle'
					}]
				}]
			};
			expect(weather.clothesForWeather({ forecast })).to.eql('umbrella');
		});
		it('maps rain to umbrella', () => {
			const forecast = {
				current: {
					feels_like: 0
				},
				daily: [{
					weather: [{
						main: 'Rain'
					}]
				}]
			};
			expect(weather.clothesForWeather({ forecast })).to.eql('umbrella');
		});
		it('maps snow to shovel', () => {
			const forecast = {
				current: {
					feels_like: 0
				},
				daily: [{
					weather: [{
						main: 'Snow'
					}]
				}]
			};
			expect(weather.clothesForWeather({ forecast })).to.eql('shovel');
		});
		it('maps freezing to hat', () => {
			const forecast = {
				current: {
					feels_like: 0
				},
				daily: [{
					weather: [{
						main: 'Clear'
					}]
				}]
			};
			expect(weather.clothesForWeather({ forecast })).to.eql('hat');
		});
		it('maps cold to jacket', () => {
			const forecast = {
				current: {
					feels_like: 6
				},
				daily: [{
					weather: [{
						main: 'Clear'
					}]
				}]
			};
			expect(weather.clothesForWeather({ forecast })).to.eql('jacket');
		});
		it('maps warm to sweater', () => {
			const forecast = {
				current: {
					feels_like: 14
				},
				daily: [{
					weather: [{
						main: 'Clear'
					}]
				}]
			};
			expect(weather.clothesForWeather({ forecast })).to.eql('sweater');
		});
		it('maps hot to tshirt', () => {
			const forecast = {
				current: {
					feels_like: 30
				},
				daily: [{
					weather: [{
						main: 'Clear'
					}]
				}]
			};
			expect(weather.clothesForWeather({ forecast })).to.eql('tshirt');
		});
	});
});
