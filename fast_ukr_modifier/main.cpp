#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string save_path;
string save_path_loc;
string save_path_eff;
string save_path_effm;

int range;
int range_negative;
int range_positive;
float discipline_factor = 0.05;
float legitimacy_factor = 2;
float rival_border_fort_maintenance_factor = 0.33;
float trade_efficiency_factor = 0.33;
float build_time_factor = 0.25;
float inflation_action_cost_factor = 0.33;

void save_effect_mod(int i)
{
	fstream _effs;
	_effs.open(save_path_effm.c_str(), fstream::app);
	_effs << "set_centralization_modifier_by_val_acr_effect = { val = "<<i<<" }\n";
	_effs.close();
}

void save_effect(int i)
{
	fstream _effs;
	_effs.open(save_path_eff.c_str(), fstream::app);
	_effs << "remove_country_modifier = ukr_centralization_"+to_string(i)+"\n";
	_effs.close();
}

void save_loc(int i)
{
	fstream _locs;
	_locs.open(save_path_loc.c_str(), fstream::app);
	_locs << " ukr_centralization_"+to_string(i)+":0 "+'"'+"Centralization-Decentralization bonus"+'"'+"\n";
	_locs << " desc_ukr_centralization_"+to_string(i)+":0 "+'"'+'"'+"\n";
	_locs.close();
}

void create_modifiers(int i)
{
	int reverse_i = -i;
	fstream _modifiers;
	_modifiers.open(save_path.c_str(), fstream::app);
	_modifiers << "ukr_centralization_"+to_string(i)+" = {\n";
	_modifiers << "	discipline = "+to_string(i*discipline_factor)+"\n";
	_modifiers << "	legitimacy = "+to_string(i*legitimacy_factor)+"\n";
	_modifiers << "	rival_border_fort_maintenance = "+to_string(reverse_i*rival_border_fort_maintenance_factor)+"\n";
	_modifiers << "	trade_efficiency = "+to_string(reverse_i*trade_efficiency_factor)+"\n";
	_modifiers << "	build_time = "+to_string(i*build_time_factor)+"\n";
	_modifiers << "	inflation_action_cost = "+to_string(i*inflation_action_cost_factor)+"\n";
	_modifiers << "}\n";
	_modifiers.close();
}

int main()
{
	cout<<"Save path: ";
	getline(cin, save_path);
	cout<<"Localization save path: ";
	getline(cin, save_path_loc);
	cout<<"Effects save path: ";
	getline(cin, save_path_eff);
	cout<<"Effects (modifiers) save path: ";
	getline(cin, save_path_effm);
	
	cout<<"Range: ";
	cin>>range;
	
	range_negative = (range/2)*(-1);
	range_positive = (range/2);
	
	discipline_factor /= (float)range_positive;
	legitimacy_factor /= (float)range_positive;
	rival_border_fort_maintenance_factor /= (float)range_positive;
	trade_efficiency_factor /= (float)range_positive;
	build_time_factor /= (float)range_positive;
	inflation_action_cost_factor /= (float)range_positive;
	
	for(int i=range_negative; i<range_positive+1; i++){
		create_modifiers(i);
	}
	for(int i=range_negative; i<range_positive+1; i++){
		save_loc(i);
	}
	for(int i=range_negative; i<range_positive+1; i++){
		save_effect(i);
		save_effect_mod(i);
	}
}
