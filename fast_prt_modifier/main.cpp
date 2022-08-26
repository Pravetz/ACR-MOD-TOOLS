#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string save_path;
string save_path_loc;
string save_path_eff;

int range;
int range_negative;
int range_positive;

void save_effect(int i)
{
	fstream _effs;
	_effs.open(save_path_eff.c_str(), fstream::app);
	_effs << "remove_country_modifier = prt_militarization_"+to_string(i)+"\n";
	_effs.close();
}

void save_loc(int i)
{
	fstream _locs;
	_locs.open(save_path_loc.c_str(), fstream::app);
	_locs << " prt_militarization_"+to_string(i)+":0 "+'"'+"Militarization-Demilitarization bonus"+'"'+"\n";
	_locs << " desc_prt_militarization_"+to_string(i)+":0 "+'"'+'"'+"\n";
	_locs.close();
}

void create_modifiers(int i)
{
	int reverse_i;
	reverse_i = i*(-1);
	fstream _modifiers;
	_modifiers.open(save_path.c_str(), fstream::app);
	_modifiers << "prt_militarization_"+to_string(i)+" = {\n";
	_modifiers << "	discipline = "+to_string(i*0.002)+"\n";
	_modifiers << "	land_maintenance_modifier = "+to_string(reverse_i*0.01)+"\n";
	_modifiers << "	fort_maintenance_modifier = "+to_string(reverse_i*0.01)+"\n";
	_modifiers << "	trade_efficiency = "+to_string(reverse_i*0.01)+"\n";
	_modifiers << "	development_cost = "+to_string(i*0.01)+"\n";
	_modifiers << "	build_time = "+to_string(i*0.01)+"\n";
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
	
	cout<<"Range: ";
	cin>>range;
	
	range_negative = (range/2)*(-1);
	range_positive = (range/2);
	
	for(int i=range_negative; i<range_positive+1; i++){
		create_modifiers(i);
	}
	for(int i=range_negative; i<range_positive+1; i++){
		save_loc(i);
	}
	for(int i=range_negative; i<range_positive+1; i++){
		save_effect(i);
	}
}
