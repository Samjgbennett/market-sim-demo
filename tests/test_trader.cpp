#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "file_handling.h"
#include "Trader.h"
#include <vector>
#include <filesystem>

void test()
{
	/////////////////////////////////////////////
	/// write the asset history to file
	/////////////////////////////////////////////
	const std::filesystem::path test_file = getRootDir() + "/tests/test_io/Market_test.csv";
	std::filesystem::create_directories(test_file.parent_path());

	std::vector<double> mu({ 0.0, 0.0, 0.0});
	std::vector<double> sigma({ 1e-3, 1e-2, 1e-1 });

	unsigned int number_of_timesteps = 1000;
	unsigned int number_of_assets = mu.size();
	std::vector<std::string> asset_names;

	// give names to all the assets
	asset_names.resize(number_of_assets);
	std::stringstream header;
	for (unsigned int i = 0; i < asset_names.size(); ++i)
	{
		header.str(std::string());
		header.clear();
		header << "Asset " << i;
		asset_names[i] = header.str();
	}

	AssetHistory::generate_log_price_history(test_file.string(), asset_names, mu.data(), sigma.data(), number_of_timesteps);

	/////////////////////////////////////////////
	/// reading from file
	/////////////////////////////////////////////

	std::vector<std::vector<double>> data;

	data.resize(number_of_timesteps);

	for (auto& step : data)
		step.resize(mu.size());

	unsigned int m_max = data[0].size();
	unsigned int n_max = data.size();

	std::vector<double*> data_ptrs(data.size());

	// set each element of data_ptrs to point at each array (timestep)
	// in data
	std::transform(data.begin(), data.end(), data_ptrs.begin(),
		[](auto& val)
		{
			return val.data();
		});

	// empty the asset names before retrieving from file
	asset_names.resize(0);

	AssetHistory::read_price_history(test_file.string(), asset_names, data_ptrs.data(), m_max, n_max);

	std::vector<std::vector<double>> transposed_data;

	// need to transpose the data so each row represent the time-history of each asset
	util::transpose_data_matrix(data, transposed_data);

	// since log-price was generated, calculate exponent of all values
	util::exp_matrix(transposed_data);

	Market sim(asset_names, transposed_data);

	double initial_currency = 1000.0;
	unsigned int number_of_history = 50;

	// The trader which will trade in the market
	Trader trader(initial_currency, asset_names, number_of_history, sim);

	// number of times to print the output as the simulation runs
	unsigned int split = 10;
	unsigned int steps = number_of_timesteps / split;

	std::cout << "Starting cash " << initial_currency << std::endl;

	// run 10 simulations
	for (unsigned int i = 0; i < split; ++i)
	{
		// put the trader in the market simulation 
		// running for 10000 steps
		// the trader interacts (buys/sells) with market every 50 steps
		sim.run(steps, trader, 50);
	}
	REQUIRE(trader.liquidated_total(sim) > 0.0);
	REQUIRE(trader.liquidated_profits(sim) < trader.liquidated_total(sim));
}

TEST_CASE("Test asset history")
{
	test();
}