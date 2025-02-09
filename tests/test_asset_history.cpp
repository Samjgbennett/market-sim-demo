#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "AssetHistory.h"
#include "file_handling.h"
#include <sstream>
#include <filesystem>

void test()
{
	/////////////////////////////////////////////
	/// writing to file
	/////////////////////////////////////////////
	const std::filesystem::path test_file = getRootDir() + "/tests/test_io/Market_test.csv";
	std::filesystem::create_directories(test_file.parent_path());

	std::vector<double> mu({ 0.0, -1.0, 1.0 });
	std::vector<double> sigma({ 1.0, 1.5, 2.0});

	unsigned int number_of_timesteps = 100;
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

	REQUIRE(asset_names.size() == number_of_assets);
	REQUIRE(data.size() == number_of_timesteps);
	REQUIRE(data[0].size() == number_of_assets);
}

TEST_CASE("Asset history read and write consistent", "[asset_history]") {
	test();
}
