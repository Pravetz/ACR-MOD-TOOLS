#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
string mode_;
string f_path_variable, f_path_scoped_any, f_path_conditions, f_path_modifiers, f_path_triggers, f_path_assimilation, f_path_assimilation_t, f_path;

void rm_flags_eff(const string &culture)
{
	ofstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "clr_province_flag = expel_"+culture+"\n"; 
	_assim.close();
}

void set_expelled_in_prov_effect(const string &culture)
{
	ofstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "if = {\n"; 
	_assim << "	limit = {\n";
	_assim << "		AND = {\n";
	_assim << "			event_target:prov_expel_target = { has_province_flag = expel_"+culture+" }\n";
	_assim << "		}\n";
	_assim << "	}\n";
	_assim << "	change_culture = "+culture+"\n";
	_assim << "	set_variable = {\n";
	_assim << "		which = expelled_pop_size\n";
	_assim << "		which = PREV\n";
	_assim << "	}\n";
	_assim << "	set_variable = {\n";
	_assim << "		which = local_population\n";
	_assim << "		which = expelled_pop_size\n";
	_assim << "	}\n";
	_assim << "	set_variable = {\n";
	_assim << "		which = expelled_pop_size\n";
	_assim << "		value = 0\n";
	_assim << "	}\n";
	_assim << "}\n";
	_assim.close();
}

void rm_expelled_from_prov_effect(const string &culture)
{
	ofstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "if = {\n"; 
	_assim << "	limit = {\n";
	_assim << "		AND = {\n";
	_assim << "			has_province_flag = expel_"+culture+"\n";
	_assim << "		}\n";
	_assim << "	}\n";
	_assim << "	set_variable = {\n";
	_assim << "		which = expelled_pop_size\n";
	_assim << "		which = local_population\n";
	_assim << "	}\n";
	_assim << "	set_variable = {\n";
	_assim << "		which = expelled_prcnt\n";
	_assim << "		which = POPculture_"+culture+"_prcnt\n";
	_assim << "	}\n";
	_assim << "	divide_variable = {\n";
	_assim << "		which = expelled_prcnt\n";
	_assim << "		value = 100\n";
	_assim << "	}\n";
	_assim << "	multiply_variable = {\n";
	_assim << "		which = expelled_pop_size\n";
	_assim << "		which = expelled_prcnt\n";
	_assim << "	}\n";
	_assim << "	divide_variable = {\n";
	_assim << "		which = expelled_pop_size\n";
	_assim << "		value = 1000\n";
	_assim << "	}\n";
	_assim << "	multiply_variable = {\n";
	_assim << "		which = expelled_pop_size\n";
	_assim << "		value = 1000\n";
	_assim << "	}\n";
	_assim << "	subtract_variable = {\n";
	_assim << "		which = local_population\n";
	_assim << "		which = expelled_pop_size\n";
	_assim << "	}\n";
	_assim << "}\n";
	_assim.close();
}

void create_expel_eff(const string &culture)
{
	ofstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "if = {\n"; 
	_assim << "	limit = {\n";
	_assim << "		AND = {\n";
	_assim << "			owner = {\n";
	_assim << "				primary_culture = "+culture+"\n";
	_assim << "			}\n";
	_assim << "		}\n";
	_assim << "		AND = {\n";
	_assim << "			has_province_flag = expel_$culture$\n";
	_assim << "		}\n";
	_assim << "	}\n";
	
	_assim << "	if = {\n"; 
	_assim << "		limit = {\n";
	_assim << "			NOT = {\n";
	_assim << "				check_variable = {\n";
	_assim << "					which = POPculture_"+culture+"_prcnt\n";
	_assim << "					value = 1\n";
	_assim << "				}\n";
	_assim << "			}\n";
	_assim << "		}\n";
	_assim << "		set_variable = {\n";
	_assim << "			which = POPculture_"+culture+"_prcnt\n";
	_assim << "			which = POPculture_$culture$_prcnt\n";
	_assim << "		}\n";
	_assim << "		set_variable = {\n";
	_assim << "			which = POPculture_$culture$_prcnt\n";
	_assim << "			value = 0\n";
	_assim << "		}\n";
	_assim << "	}\n";
	
	_assim << "	if = {\n"; 
	_assim << "		limit = {\n";
	_assim << "			AND = {\n";
	_assim << "				check_variable = {\n";
	_assim << "					which = POPculture_"+culture+"_prcnt\n";
	_assim << "					value = 1\n";
	_assim << "				}\n";
	_assim << "			}\n";
	_assim << "		}\n";
	_assim << "		change_variable = {\n";
	_assim << "			which = POPculture_"+culture+"_prcnt\n";
	_assim << "			which = POPculture_$culture$_prcnt\n";
	_assim << "		}\n";
	_assim << "		set_variable = {\n";
	_assim << "			which = POPculture_$culture$_prcnt\n";
	_assim << "			value = 0\n";
	_assim << "		}\n";
	_assim << "	}\n";
	
	_assim << "}\n";
	_assim.close();
}

void evt_toexpel_culture_options_loc(const string &culture)
{
	//options from acr_pop_actions.txt file(EVT ID: acr_pop_actions.1)
	string culture_formated;
	culture_formated = culture;
	culture_formated[0] = toupper(culture_formated[0]);
	for(int i=0; i<culture_formated.length(); i++){
		if(culture_formated[i] == '_'){
			culture_formated[i] = ' ';
			culture_formated[i+1] = toupper(culture_formated[i+1]);
		}
	}
	
	ofstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "acr_pop_actions.1."+culture+":0 "+'"'+culture_formated+'"'+"\n";
	_assim.close();
}

void evt_toexpel_culture_options(const string &culture)
{
	ofstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "option = {\n"; 
	_assim << "name = acr_pop_actions.1."+culture+"\n";
	_assim << "trigger = {\n";
	_assim << "	AND = { is_unaccepted_popculture_trigger = { culture = "+culture+" scope = owner } }\n";
	_assim << "}\n";
	_assim << "set_province_flag = expel_"+culture+"\n";
	_assim << "}\n";
	_assim.close();
}

void create_effect_any_unacc_tri(const string &culture, size_t culture_id)
{
	ofstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "if = {\n"; 
	_assim << "	limit = {\n";
	_assim << "		NOT = {\n";
	_assim << "			AND = {\n";
	_assim << "				check_variable = {\n";
	_assim << "					which = culture_id\n";
	_assim << "					value = " << culture_id << "\n";
	_assim << "				}\n";
	_assim << "				NOT = {\n";
	_assim << "					check_variable = {\n";
	_assim << "						which = culture_id\n";
	_assim << "						value = " << culture_id + 1 << "\n";
	_assim << "					}\n";
	_assim << "				}\n";
	_assim << "			}\n";
	_assim << "		}\n";
	_assim << "		AND = {\n";
	_assim << "			check_variable = {\n";
	_assim << "				which = POPculture_"+culture+"_prcnt\n";
	_assim << "				value = $val$\n";
	_assim << "			}\n";
	_assim << "		}\n";
	_assim << "		NOT = {\n";
	_assim << "			owner = {\n";
	_assim << "				accepted_culture = "+culture+"\n";
	_assim << "				primary_culture = "+culture+"\n";
	_assim << "			}\n";
	_assim << "		}\n";
	_assim << "		NOT = {\n";
	_assim << "			check_variable = {\n";
	_assim << "				which = POPculture_$culture$_prcnt\n";
	_assim << "				value = $val$\n";
	_assim << "			}\n";
	_assim << "		}\n";
	_assim << "	}\n";
	_assim << "	change_variable = {\n";
	_assim << "		which = POPculture_$culture$_prcnt\n";
	_assim << "		value = $val$\n";
	_assim << "	}\n";
	_assim << "	subtract_variable = {\n";
	_assim << "		which = POPculture_"+culture+"_prcnt\n";
	_assim << "		value = $val$\n";
	_assim << "	}\n";
	_assim << "}\n";
	_assim.close();
}

void create_effect_change_any_in_favor_of_scope_culture(const string &culture, size_t culture_id){
	ofstream _assim;
	_assim.open(f_path_scoped_any.c_str(), fstream::app);
	_assim << "if = {\n"; 
	_assim << "	limit = {\n";
	_assim << "		AND = {\n";
	_assim << "			$scope$ = {\n";
	_assim << "				primary_culture = " << culture << "\n";
	_assim << "			}\n";
	_assim << "		}\n";
	_assim << "	}\n";
	_assim << "	change_any_popculture_by_val_effect = { culture = " << culture << " val = $val$ culture_id = " << culture_id << " }\n";
	_assim << "}\n";
	_assim.close();
}

void create_effect_anytri(const string &culture)
{
	ofstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "if = {\n"; 
	_assim << "	limit = {\n";
	_assim << "		AND = {\n";
	_assim << "			check_variable = {\n";
	_assim << "				which = POPculture_"+culture+"_prcnt\n";
	_assim << "				value = $val$\n";
	_assim << "			}\n";
	_assim << "		}\n";
	_assim << "		NOT = {\n";
	_assim << "			check_variable = {\n";
	_assim << "				which = POPculture_$culture$_prcnt\n";
	_assim << "				value = $val$\n";
	_assim << "			}\n";
	_assim << "		}\n";
	_assim << "	}\n";
	_assim << "	change_variable = {\n";
	_assim << "		which = POPculture_$culture$_prcnt\n";
	_assim << "		value = $val$\n";
	_assim << "	}\n";
	_assim << "	subtract_variable = {\n";
	_assim << "		which = POPculture_"+culture+"_prcnt\n";
	_assim << "		value = $val$\n";
	_assim << "	}\n";
	_assim << "}\n";
	_assim.close();
}

void filter_cultures(const string &culture)
{
	ofstream _filtered;
	_filtered.open(f_path.c_str(), fstream::app);
	_filtered << culture+"\n";
	_filtered.close();
}

void create_effect(const string &culture1, const string &culture2){
	ofstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "assimilate_culture_acr_effect = { culture1 = "+culture1+" culture2 = "+culture2+" }\n";
	_assim.close();
}

void create_assimilation(const string &culture1, const string &culture2){
	ofstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "set_popculture_asm_modifier_acr_effect = { culture1 = "+culture1+" culture2 = "+culture2+" scope = owner }\n";
	_assim.close();
}

void create_assimilation_t(const string &culture1){
	ofstream _assim_t;
	_assim_t.open(f_path_assimilation_t.c_str(), fstream::app);
	_assim_t << "is_unaccepted_popculture_trigger = { culture = "+culture1+" scope = owner }\n";
	_assim_t.close();
}

void create_triggers(const string &culture1, const string &culture2){
	ofstream _triggers;
	_triggers.open(f_path_triggers.c_str(), fstream::app);
	_triggers << "has_assimilation_modifier = { culture1 = "+culture1+" culture2 = "+culture2+" }\n";
	_triggers.close();
}

void create_modifiers(const string &culture1, const string &culture2){
	ofstream _modifiers;
	_modifiers.open(f_path_modifiers.c_str(), fstream::app);
	_modifiers << culture1+"_assimilates_"+culture2+" = {\n";
	_modifiers << "	picture = acr_culture_conversion\n";	//replace modifiers here
	_modifiers << "}\n";
	_modifiers.close();
}

void create_variable(const string &culture){
	ofstream _variables;
	_variables.open(f_path_variable.c_str(), fstream::app);
	_variables << "set_variable = {\n";
	_variables << "	which = POPculture_"+culture+"_prcnt\n";
	_variables << "	value = 0\n";	// 0%, will be changed to 100% in condition
	_variables << "}\n";
	_variables.close();
}

void create_setup(const string &culture){
	ofstream _conditions;
	_conditions.open(f_path_conditions.c_str(), fstream::app);
	_conditions << "if = {\n";
	_conditions << "	limit = {\n";
	_conditions << "		culture = "+culture+"\n";
	_conditions << "	}\n";
	_conditions << "	set_variable = {\n";
	_conditions << "		which = POPculture_"+culture+"_prcnt\n";
	_conditions << "		value = 100\n";
	_conditions << "	}\n";
	_conditions << "}\n";
	_conditions.close();
}

std::vector<std::string> split_string(const std::string &str, const std::string &separators){
	size_t last_seppos = 0;
	size_t seppos = 0;
	std::vector<std::string> strings;
	
	while((seppos = str.find_first_of(separators, seppos)) != std::string::npos){
		if(seppos - last_seppos - (last_seppos > 0) > 0){
			strings.push_back(str.substr(last_seppos + (last_seppos >= 0), seppos - last_seppos - (last_seppos >= 0)));
		}
		last_seppos = seppos;
		seppos++;
	}
	strings.push_back(str.substr(last_seppos + 1));
	if(!strings[strings.size() - 1].length()){
		strings.pop_back();
	}
	
	return strings;
}

size_t count_tab_appearances(const string &str){
	size_t counter = 0;
	for(; counter < str.length() && str[counter] == '\t'; counter++);
	return counter;
}

vector<string> parse_culture_names(ifstream &file){
	string parse_line = "";
	static const string exception_list[] = { "(",")","[","]","{","}", "\n", "country", "province", "male_names", "primary", "female_names", "dynasty_names", "graphical_culture", "second_graphical_culture" };
	vector<string> culture_names;
	
	while(getline(file, parse_line)){
		if(count_tab_appearances(parse_line) == 1){
			vector<string> tokens = split_string(parse_line, " \t={}()[]");
			if(find(begin(exception_list), end(exception_list), tokens[0]) == end(exception_list) && tokens[0][0] != '#' && !tokens[0].empty()){
				culture_names.push_back(tokens[0]);
			}
		}
	}
	
	return culture_names;
}


int main()
{
	string path_cultures;
	cout<<"Path to file with cultures: ";
	getline(cin, path_cultures);
	
	ifstream _cultures;
	_cultures.open(path_cultures.c_str());
	vector<string> cultures;
	if(_cultures){
		cultures = parse_culture_names(_cultures);
	}
	else{
		cout << "Failed to open file in path \""<< path_cultures <<"\"" << endl;
		return 0;
	}
	_cultures.close();
	cout<<"Commands: !lst, !var, !cdt, !mod, !tri, !asm(!asm-tri, !asm-eff, !asm-etr, !asm-evt, !asm-unactr), !flt"<<endl;
	while(mode_ != "!exit"){
		getline(cin, mode_);
		
		if(mode_ == "!lst"){
			for(int i=0; i<cultures.size(); i++){
				cout<<i<<'\t'<<cultures[i]<<'\n';
			}
		}
		
		if(mode_ == "!var" || mode_ == "!all"){
			cout<<"Variables save path: ";
			getline(cin, f_path_variable);
			for(int i=0; i<cultures.size(); i++){
				create_variable(cultures[i]);
			}
		}
		if(mode_ == "!cdt" || mode_ == "!all"){
			cout<<"Conditions save path: ";
			getline(cin, f_path_conditions);
			for(int i=0; i<cultures.size(); i++){
				create_setup(cultures[i]);
			}
		}
		if(mode_ == "!mod" || mode_ == "!all"){
			cout<<"Modifier save path: ";
			getline(cin, f_path_modifiers);
			for(int i=0; i<cultures.size(); i++){
				for(int j=0; j<cultures.size(); j++){
					if(cultures[i] != cultures[j]){
						create_modifiers(cultures[i], cultures[j]);
					}
				}
			}
		}
		if(mode_ == "!tri" || mode_ == "!all"){
			cout<<"Triggers save path: ";
			getline(cin, f_path_triggers);
			for(int i=0; i<cultures.size(); i++){
				for(int j=0; j<cultures.size(); j++){
					if(cultures[i] != cultures[j]){
						create_triggers(cultures[i], cultures[j]);
					}
				}
			}
		}
		if(mode_ == "!asm" || mode_ == "!all"){
			cout<<"create_assimilation Save path: ";
			getline(cin, f_path_assimilation);
			for(int i=0; i<cultures.size(); i++){
				for(int j=0; j<cultures.size(); j++){
					if(cultures[i] != cultures[j]){
						create_assimilation(cultures[i], cultures[j]);
					}
				}
			}
		}
		if(mode_ == "!asm-tri" || mode_ == "!all"){
			cout<<"triggers Save path: ";
			getline(cin, f_path_assimilation_t);
			for(int i=0; i<cultures.size(); i++){
				create_assimilation_t(cultures[i]);
			}
		}
		if(mode_ == "!asm-eff" || mode_ == "!all"){
			cout<<"effects Save path: ";
			getline(cin, f_path_assimilation);
			for(int i=0; i<cultures.size(); i++){
				for(int j=0; j<cultures.size(); j++){
					if(cultures[i] != cultures[j]){
						create_effect(cultures[i], cultures[j]);
					}
				}
			}
		}
		if(mode_ == "!asm-etr" || mode_ == "!all"){
			cout<<"create_effect_anytri Save path: ";
			getline(cin, f_path_assimilation);
			for(int i=0; i<cultures.size(); i++){
				create_effect_anytri(cultures[i]);
			}
		}
		if(mode_ == "!asm-unactr" || mode_ == "!all"){
			cout<<"effect_any_unacc_tri Save path: ";
			getline(cin, f_path_assimilation);
			for(int i=0; i<cultures.size(); i++){
				create_effect_any_unacc_tri(cultures[i], i);
			}
		}
		if(mode_ == "!asm-scope" || mode_ == "!all"){
			cout<<"scoped value changed Save path: ";
			getline(cin, f_path_scoped_any);
			for(int i=0; i<cultures.size(); i++){
				create_effect_change_any_in_favor_of_scope_culture(cultures[i], i);
			}
		}
		if(mode_ == "!asm-evt" || mode_ == "!all"){
			cout<<"toexpel_culture_options Save path: ";
			getline(cin, f_path_assimilation);
			for(int i=0; i<cultures.size(); i++){
				evt_toexpel_culture_options(cultures[i]);
			}
		}
		if(mode_ == "!asm-exp" || mode_ == "!all"){
			cout<<"create_expel_eff Save path: ";
			getline(cin, f_path_assimilation);
			for(int i=0; i<cultures.size(); i++){
				create_expel_eff(cultures[i]);
			}
		}
		if(mode_ == "!rmf" || mode_ == "!all"){
			cout<<"rm_flags_eff Save path: ";
			getline(cin, f_path_assimilation);
			for(int i=0; i<cultures.size(); i++){
				rm_flags_eff(cultures[i]);
			}
		}
		if(mode_ == "!rm-eff" || mode_ == "!all"){
			cout<<"rm_expelled_from_prov_effects Save path: ";
			getline(cin, f_path_assimilation);
			for(int i=0; i<cultures.size(); i++){
				rm_expelled_from_prov_effect(cultures[i]);
			}
		}
		if(mode_ == "!set-exp" || mode_ == "!all"){
			cout<<"set_expelled Save path: ";
			getline(cin, f_path_assimilation);
			for(int i=0; i<cultures.size(); i++){
				set_expelled_in_prov_effect(cultures[i]);
			}
		}
		if(mode_ == "!exp-loc" || mode_ == "!all"){
			cout<<"culture_options_loc Save path: ";
			getline(cin, f_path_assimilation);
			for(int i=0; i<cultures.size(); i++){
				evt_toexpel_culture_options_loc(cultures[i]);
			}
		}
	}
	
	return 0;
}
