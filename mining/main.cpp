#include <iostream>
#include <fstream>
#include <unordered_map>

struct MineModifier{
	double trade_goods;
	double inflation;
};

std::unordered_map<std::string, MineModifier> minegoods = {
	{ "iron", MineModifier{ 0.33f, -0.0005 } },
	{ "copper", MineModifier{ 0.41f, -0.001 } },
	{ "salt", MineModifier{ 0.55f, 0.0 } },
	{ "coal", MineModifier{ 0.65f, 0.0 } }
};

std::unordered_map<std::string, std::string> minelocs = {
	{ "iron", "Iron" },
	{ "copper", "Copper" },
	{ "salt", "Salt" },
	{ "coal", "Coal" }
};

int main(int argc, char **argv){
	if(argc < 2){
		return EXIT_SUCCESS;
	}
	
	std::string modsf = argv[1] + std::string(".txt");
	std::string locsf = argv[1] + std::string("_locs.txt");
	std::ofstream _mods;
	std::ofstream _locs;
	_mods.open(modsf.c_str());
	_locs.open(locsf.c_str());
	
	if(_mods){
		for(const auto &mine : minegoods){
			for(int i = 1; i <= 20; i++){
				_mods << mine.first << "_mine_level_" << i << " = {\n";
				_mods << "\ttrade_goods_size = " << mine.second.trade_goods * (double)i << '\n';
				_mods << "\tinflation_reduction = " << mine.second.inflation * (double)i << '\n';
				_mods << "}\n";
				_locs << ' ' << mine.first << "_mine_level_" << i << ":0 \"" << minelocs.at(mine.first) << " mine level " << i << "\"\n";
			}
		}
		_mods.close();
		_locs.close();
	}
	
	return EXIT_SUCCESS;
}