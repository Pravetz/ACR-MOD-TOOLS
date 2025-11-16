#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string save_path;
string save_path_loc;

int range;
float trade_goods_size_modifier_factor = 0.0025;
float local_culture_conversion_cost_factor = 0.005;


void save_loc(int i)
{
	fstream _locs;
	_locs.open(save_path_loc.c_str(), fstream::app);
	_locs << " from_urbanization_"+to_string(i)+":0 "+'"'+"From urbanization"+'"'+"\n";
	_locs << " desc_from_urbanization_"+to_string(i)+":0 "+'"'+'"'+"\n";
	_locs.close();
}

void create_modifiers(int i)
{
	int reverse_i = -i;
	fstream _modifiers;
	_modifiers.open(save_path.c_str(), fstream::app);
	_modifiers << "from_urbanization_"+to_string(i)+" = {\n";
	_modifiers << "	trade_goods_size_modifier = "+to_string((double)i * trade_goods_size_modifier_factor)+"\n";
	_modifiers << "	local_culture_conversion_cost = "+to_string(-(double)i * local_culture_conversion_cost_factor)+"\n";
	_modifiers << "}\n";
	_modifiers.close();
}

int main()
{
	cout<<"Localization save path: ";
	getline(cin, save_path_loc);
	cout<<"Modifiers save path: ";
	getline(cin, save_path);
	
	cout<<"Range: ";
	cin>>range;
	
	for(int i=1; i <= range; i++){
		create_modifiers(i);
		save_loc(i);
	}
}
