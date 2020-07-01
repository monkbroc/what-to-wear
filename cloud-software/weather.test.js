const { expect } = require('chai');

const weather = require('./weather');

describe('weather', () => {
	describe('forecastUrl', () => {
		it('returns a formatted url', () => {
			const url = weather.forecastUrl({ apiKey: 'abc123', lat: 42, lon: -83 });
			expect(url).to.eql('http');
		});
	});
});
