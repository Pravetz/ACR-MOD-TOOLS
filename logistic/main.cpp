#include <iostream>
#include <fstream>

int main(int argc, char **argv){
	if(argc < 2){
		return EXIT_SUCCESS;
	}
	
	std::string base_name = std::string(argv[1]);
	std::string land_armdef = base_name + "_land_ad.txt";
	std::string land_mundef = base_name + "_land_md.txt";
	std::string naval_armdef = base_name + "_naval_ad.txt";
	std::string naval_mundef = base_name + "_naval_md.txt";
	std::string locs = base_name + "_loc.txt";
	
	std::ofstream _lad;
	std::ofstream _lmd;
	std::ofstream _nad;
	std::ofstream _nmd;
	std::ofstream _locfile;
	
	_lad.open(land_armdef.c_str());
	_lmd.open(land_mundef.c_str());
	_nad.open(naval_armdef.c_str());
	_nmd.open(naval_mundef.c_str());
	_locfile.open(locs.c_str());
	
	constexpr float ship_durability = -1.0f / 100.0f;
	constexpr float engagement_cost_modifier = 1.0f / 100.0f;
	constexpr float shock_damage = -1.0f / 100.0f;
	constexpr float fire_damage = -1.0f / 100.0f;
	constexpr float artillery_level_modifier = -10.0f / 100.0f;
	constexpr float backrow_artillery_damage = -1.0f / 100.0f;
	constexpr float blockade_efficiency = -1.0f / 100.0f;
	constexpr float siege_blockade_progress = -1.0f / 100.0f;
	constexpr float naval_morale_damage = -1.0f / 100.0f;
	constexpr float siege_ability = -1.0f / 100.0f;
	constexpr float morale_damage_received = 0.25 / 100.0f;
	constexpr float naval_morale_damage_received = 0.25 / 100.0f;
	
	if(_lad && _lmd && _nad && _nmd){
		for(int i = 1; i <= 100; i++){
			_lad << "land_armament_deficit_" << i << " = {\n";
			_lad << "	shock_damage = " << ((float)i * shock_damage) << "\n";
			_lad << "	morale_damage_received = " << ((float)i * morale_damage_received) << "\n";
			_lad << "	siege_ability = " << ((float)i * siege_ability) << "\n";
			_lad << "}\n";
			_lmd << "land_munitions_deficit_" << i << " = {\n";
			_lmd << "	fire_damage = " << ((float)i * fire_damage) << "\n";
			_lmd << "	morale_damage_received = " << ((float)i * morale_damage_received) << "\n";
			_lmd << "	artillery_level_modifier = " << ((float)i * artillery_level_modifier) << "\n";
			_lmd << "	siege_ability = " << ((float)i * siege_ability) << "\n";
			_lmd << "	backrow_artillery_damage = " << ((float)i * backrow_artillery_damage) << "\n";
			_lmd << "}\n";
			_nad << "naval_armament_deficit_" << i << " = {\n";
			_nad << "	ship_durability = " << ((float)i * ship_durability) << "\n";
			_nad << "	naval_morale_damage_received = " << ((float)i * naval_morale_damage_received) << "\n";
			_nad << "	engagement_cost_modifier = " << ((float)i * engagement_cost_modifier) << "\n";
			_nad << "}\n";
			_nmd << "naval_munitions_deficit_" << i << " = {\n";
			_nmd << "	blockade_efficiency = " << ((float)i * blockade_efficiency) << "\n";
			_nmd << "	siege_blockade_progress = " << ((float)i * siege_blockade_progress) << "\n";
			_nmd << "	naval_morale_damage_received = " << ((float)i * naval_morale_damage_received) << "\n";
			_nmd << "	naval_morale_damage = " << ((float)i * naval_morale_damage) << "\n";
			_nmd << "}\n";
			_locfile << " land_armament_deficit_" << i << ":0 \"Land units " << i << "% armament deficit\"\n";
			_locfile << " land_munitions_deficit_" << i << ":0 \"Land units " << i << "% munitions deficit\"\n";
			_locfile << " naval_armament_deficit_" << i << ":0 \"Naval units " << i << "% armament deficit\"\n";
			_locfile << " naval_munitions_deficit_" << i << ":0 \"Naval units " << i << "% munitions deficit\"\n";
		}
		
		_lad.close();
		_lmd.close();
		_nad.close();
		_nmd.close();
		_locfile.close();
	}
	
	return EXIT_SUCCESS;
}