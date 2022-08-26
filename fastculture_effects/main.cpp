#include <iostream>
#include <string>
#include <fstream>

using namespace std;
string mode_;
string f_path_variable, f_path_conditions, f_path_modifiers, f_path_triggers, f_path_assimilation, f_path_assimilation_t, f_path;

void rm_flags_eff(string culture)
{
	fstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "clr_province_flag = expel_"+culture+"\n"; 
	_assim.close();
}

void set_expelled_in_prov_effect(string culture)
{
	fstream _assim;
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

void rm_expelled_from_prov_effect(string culture)
{
	fstream _assim;
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
	//_assim << "	expel_minority_acr_effect = { culture = "+culture+" }\n";
	_assim << "}\n";
	_assim.close();
}

void create_expel_eff(string culture)
{
	fstream _assim;
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

void evt_toexpel_culture_options_loc(string culture)
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
	
	fstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "acr_pop_actions.1."+culture+":0 "+'"'+culture_formated+'"'+"\n";
	_assim.close();
}

void evt_toexpel_culture_options(string culture)
{
	fstream _assim;
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

void create_effect_any_unacc_tri(string culture)
{
	fstream _assim;
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

void create_effect_anytri(string culture)
{
	fstream _assim;
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

void filter_cultures(string culture)
{
	fstream _filtered;
	_filtered.open(f_path.c_str(), fstream::app);
	_filtered << culture+"\n";
	_filtered.close();
}

void create_effect(string culture1, string culture2){
	fstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "assimilate_culture_acr_effect = { culture1 = "+culture1+" culture2 = "+culture2+" }\n";
	_assim.close();
}

void create_assimilation(string culture1, string culture2){
	fstream _assim;
	_assim.open(f_path_assimilation.c_str(), fstream::app);
	_assim << "set_popculture_asm_modifier_acr_effect = { culture1 = "+culture1+" culture2 = "+culture2+" scope = owner }\n";
	_assim.close();
}

void create_assimilation_t(string culture1){
	fstream _assim_t;
	_assim_t.open(f_path_assimilation_t.c_str(), fstream::app);
	_assim_t << "is_unaccepted_popculture_trigger = { culture1 = "+culture1+" scope = owner }\n";
	_assim_t.close();
}

void create_triggers(string culture1, string culture2){
	fstream _triggers;
	_triggers.open(f_path_triggers.c_str(), fstream::app);
	_triggers << "has_assimilation_modifier = { culture1 = "+culture1+" culture2 = "+culture2+" }\n";
	_triggers.close();
}

void create_modifiers(string culture1, string culture2){
	fstream _modifiers;
	_modifiers.open(f_path_modifiers.c_str(), fstream::app);
	_modifiers << culture1+"_assimilates_"+culture2+" = {\n";
	_modifiers << "picture = acr_culture_conversion\n";	//replace modifiers here
	_modifiers << "}\n";
	_modifiers.close();
}

void create_variable(string culture){
	fstream _variables;
	_variables.open(f_path_variable.c_str(), fstream::app);
	_variables << "set_variable = {\n";
	_variables << "	which = POPculture_"+culture+"_prcnt\n";
	_variables << "	value = 0\n";	// 0%, will be changed to 100% in condition
	_variables << "}\n";
	_variables.close();
}

void create_setup(string culture){
	fstream _conditions;
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

int main()
{
	int lines = 0;
	string path_cultures;
	cout<<"Path to file with cultures: ";
	getline(cin, path_cultures);
	
	fstream _cultures;
	_cultures.open(path_cultures.c_str());
	
	string culture;
	while(getline(_cultures, culture)){
		lines++;
	}
	_cultures.close();
	string cultures[lines];
	_cultures.open(path_cultures.c_str());
	
	for(int i=0; i<lines; i++){
		getline(_cultures, cultures[i]);
	}
	_cultures.close();
	cout<<"Commands: !var, !cdt, !mod, !tri, !asm(!asm-tri, !asm-eff, !asm-etr, !asm-evt, !asm-unactr), !flt"<<endl;
	getline(cin, mode_);
	
	if(mode_ == "!var"){
		cout<<"Variables save path: ";
		getline(cin, f_path_variable);
		for(int i=0; i<lines; i++){
			create_variable(cultures[i]);
		}
	}
	if(mode_ == "!cdt"){
		cout<<"Conditions save path: ";
		getline(cin, f_path_conditions);
		for(int i=0; i<lines; i++){
			create_setup(cultures[i]);
		}
	}
	if(mode_ == "!mod"){
		cout<<"Modifier save path: ";
		getline(cin, f_path_modifiers);
		for(int i=0; i<lines; i++){
			for(int j=0; j<lines; j++){
				if(cultures[i] != cultures[j]){
					create_modifiers(cultures[i], cultures[j]);
				}
			}
		}
	}
	if(mode_ == "!tri"){
		cout<<"Triggers save path: ";
		getline(cin, f_path_triggers);
		for(int i=0; i<lines; i++){
			for(int j=0; j<lines; j++){
				if(cultures[i] != cultures[j]){
					create_triggers(cultures[i], cultures[j]);
				}
			}
		}
	}
	if(mode_ == "!asm"){
		cout<<"Save path: ";
		getline(cin, f_path_assimilation);
		for(int i=0; i<lines; i++){
			for(int j=0; j<lines; j++){
				if(cultures[i] != cultures[j]){
					create_assimilation(cultures[i], cultures[j]);
				}
			}
		}
	}
	if(mode_ == "!asm-tri"){
		cout<<"Save path: ";
		getline(cin, f_path_assimilation_t);
		for(int i=0; i<lines; i++){
			create_assimilation_t(cultures[i]);
		}
	}
	if(mode_ == "!asm-eff"){
		cout<<"Save path: ";
		getline(cin, f_path_assimilation);
		for(int i=0; i<lines; i++){
			for(int j=0; j<lines; j++){
				if(cultures[i] != cultures[j]){
					create_effect(cultures[i], cultures[j]);
				}
			}
		}
	}
	if(mode_ == "!asm-etr"){
		cout<<"Save path: ";
		getline(cin, f_path_assimilation);
		for(int i=0; i<lines; i++){
			create_effect_anytri(cultures[i]);
		}
	}
	if(mode_ == "!asm-unactr"){
		cout<<"Save path: ";
		getline(cin, f_path_assimilation);
		for(int i=0; i<lines; i++){
			create_effect_any_unacc_tri(cultures[i]);
		}
	}
	if(mode_ == "!asm-evt"){
		cout<<"Save path: ";
		getline(cin, f_path_assimilation);
		for(int i=0; i<lines; i++){
			evt_toexpel_culture_options(cultures[i]);
		}
	}
	if(mode_ == "!asm-exp"){
		cout<<"Save path: ";
		getline(cin, f_path_assimilation);
		for(int i=0; i<lines; i++){
			create_expel_eff(cultures[i]);
		}
	}
	if(mode_ == "!rmf"){
		cout<<"Save path: ";
		getline(cin, f_path_assimilation);
		for(int i=0; i<lines; i++){
			rm_flags_eff(cultures[i]);
		}
	}
	if(mode_ == "!rm-eff"){
		cout<<"Save path: ";
		getline(cin, f_path_assimilation);
		for(int i=0; i<lines; i++){
			rm_expelled_from_prov_effect(cultures[i]);
		}
	}
	if(mode_ == "!set-exp"){
		cout<<"Save path: ";
		getline(cin, f_path_assimilation);
		for(int i=0; i<lines; i++){
			set_expelled_in_prov_effect(cultures[i]);
		}
	}
	if(mode_ == "!exp-loc"){
		cout<<"Save path: ";
		getline(cin, f_path_assimilation);
		for(int i=0; i<lines; i++){
			evt_toexpel_culture_options_loc(cultures[i]);
		}
	}
	if(mode_ == "!flt"){
		string load_cg;
		cout<<"Save path: ";
		getline(cin, f_path);
		cout<<"Path to culture groups list: ";
		getline(cin, load_cg);
		
		fstream _culture_groups;
		_culture_groups.open(load_cg.c_str());
		string loader;
		int lines_c = 0;
		while(getline(_culture_groups, loader)){
			lines_c++;
		}
		_culture_groups.close();
		string culture_groups[lines_c];
		_culture_groups.open(load_cg.c_str());
		for(int i=0; i<lines_c; i++){
			getline(_culture_groups, culture_groups[i]);
		}
		_culture_groups.close();
		
		for(int i=0; i<lines; i++){
			for(int j=0; j<lines_c; j++){
				if(cultures[i]==culture_groups[j]){
					filter_cultures(cultures[i]);
				}
			}
		}
	}
	
	return 0;
}
