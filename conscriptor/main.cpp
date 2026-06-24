#include <iostream>
#include <fstream>

int main(int argc, char **argv){
	if(argc < 2){
		return EXIT_SUCCESS;
	}
	
	std::string land_levies = std::string(argv[1]) + ".txt";
	std::string land_levies_l = std::string(argv[1]) + "_loc.txt";
	std::string land_levies_m = std::string(argv[1]) + "_mods.txt";
	std::string land_levies_ml = std::string(argv[1]) + "_modloc.txt";
	
	std::ofstream _landf;
	std::ofstream _landfl;
	std::ofstream _landfm;
	std::ofstream _landfpm;
	std::ofstream _landfml;
	_landf.open(land_levies.c_str());
	_landfl.open(land_levies_l.c_str());
	_landfm.open(land_levies_m.c_str());
	_landfml.open(land_levies_ml.c_str());
	
	constexpr int r = 128;
	constexpr double g_step = 2.55; 
	
	constexpr float unrest_modifier = 0.5f / 50.0f;
	constexpr float purist_manpower_recovery = 0.5f / 50.0f;
	constexpr float war_exhaustion_cost_impact = 0.01f;
	
	if(_landf){
		for(int i = 0; i <= 50; i++){
			_landf <<"acr_change_levies_"<<i<<" = {\n"<<
					"	major = no\n"<<
					"	\n"<<
					"	color = { "<<r<<" "<<((int)(255.0 - (double)i * g_step))<<" 0 }\n"<<
					"	\n"<<
					"	potential = {\n"<<
					"		is_variable_equal = {\n"<<
					"			which = country_levy_pcnt_int\n"<<
					"			value = "<<i<<"\n"<<
					"		}\n"<<
					"		has_country_flag = acr_setup_national_levies\n"<<
					"	}\n"<<
					"	\n"<<
					"	allow = {}\n"<<
					"	\n"<<
					"	effect = {\n"<<
					"		if = {\n"<<
					"			limit = {\n"<<
					"				ai = yes\n"<<
					"			}\n"<<
					"			acr_ai_adjust_country_levy_pcnt = yes\n"<<
					"		}\n"<<
					"		update_levies_pcnt_acr_effect = { levy_pcnt = country_levy_pcnt new_pcnt = levies_increase_factor }\n"<<
					"	}\n"<<
					"	\n"<<
					"	ai_will_do = {\n"<<
					"		factor = 1\n"<<
					"		modifier = {\n"<<
					"			factor = 0\n"<<
					"			ai_doesnt_adjust_levies_at_war = yes\n"<<
					"		}\n"<<
					"		modifier = {\n"<<
					"			factor = 0\n"<<
					"			ai_doesnt_adjust_levies_at_peace = yes\n"<<
					"		}\n"<<
					"	}\n"<<
					"	\n"<<
					"	ai_importance = 400\n"<<
					"}\n";
			_landfl <<" acr_change_levies_"<<i<<"_title:0 \"£icon_manpower£ §YCountry levies: "<<i<<"%§! £icon_sailors£\"\n";
			_landfl <<" acr_change_levies_"<<i<<"_desc:0 \"Click this decision to change monthly levies percentage\"\n";
			_landfm << "levies_level_" << i << " = {\n";
			_landfm << '\t' << "war_exhaustion_cost = " << war_exhaustion_cost_impact * i << '\n';
			_landfm << '\t' << "global_unrest = " << unrest_modifier * i << '\n';
			_landfm << "}\n";
			_landfm << "purist_levies_level_" << i << " = {\n";
			_landfm << '\t' << "sailors_recovery_speed = " << purist_manpower_recovery * i << '\n';
			_landfm << '\t' << "manpower_recovery_speed = " << purist_manpower_recovery * i << '\n';
			_landfm << '\t' << "war_exhaustion_cost = " << war_exhaustion_cost_impact * i << '\n';
			_landfm << '\t' << "global_unrest = " << (unrest_modifier * i * 2) << '\n';
			_landfm << "}\n";
			_landfml <<" levies_level_" << i << ":0 \"£icon_manpower£ Country levies: "<<i<<"% £icon_sailors£\"\n";
			_landfml <<" desc_levies_level_" << i << ":0 \"\"\n";
			_landfml <<" purist_levies_level_" << i << ":0 \"£icon_manpower£ Country levies: "<<i<<"% £icon_sailors£\"\n";
			_landfml <<" desc_purist_levies_level_" << i << ":0 \"\"\n";
		}
	}
	
	return EXIT_SUCCESS;
}