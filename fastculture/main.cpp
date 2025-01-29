/*				WRITTEN BY PRAVETZ
 * 		FOR ALL COUNTRIES RELEASED MOD FOR EU4
 * 	USED TO CREATE CULTURE-RELATED VARIABLES AND LOCALIZATION MORE 
 * 	EFFICIENTLY.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <unordered_map>
#include <algorithm>

bool stop = false;

using namespace std;
string mode_;

unordered_map<string, string> locs;
string current_culture;
string POPculture_prcnt;	//variable name 
string GetCulture_;
string GetCulture_Country_Scope_;
string lockey_gc_i, lockey_gc_ii;
string loc_i, loc_ii;
string loc_arg_buffer, loc_arg_t;

string f_GC_path, f_CGC_path, f_loc_path, f_lockey_path, f_varloc_path;

std::string format_name(const std::string &str){
	if(locs.find(str) != locs.end()){
		return locs[str];
	}
	string str_formated;
	str_formated = str;
	str_formated[0] = toupper(str_formated[0]);
	for(int i=0; i<str_formated.length(); i++){
		if(str_formated[i] == '_'){
			str_formated[i] = ' ';
			str_formated[i+1] = toupper(str_formated[i+1]);
		}
	}
	
	return str_formated;
}

void save_varlocs(const string &culture, const string &group)
{
	ofstream f_varloc_save;
	
	string culture_formated = format_name(culture);
	string group_formated = format_name(group);
	
	f_varloc_save.open(f_varloc_path.c_str(), fstream::app);
	f_varloc_save << " "+POPculture_prcnt+":0 "+'"'+culture_formated+" ("+group_formated+")\""+"\n";
	f_varloc_save.close();
}
void save_loc_keys()
{
	ofstream f_lockey_save;
	
	f_lockey_save.open(f_lockey_path.c_str());	// will overwrite every time, not append
	f_lockey_save << loc_arg_buffer;
	f_lockey_save.close();
}

void stf()
{
	if(f_GC_path == ""){
		cout<<"Customizable loc path: ";
		getline(cin, f_GC_path);
	}
	if(f_loc_path == ""){
		cout<<"CL keys loc path(expects YAML file, any will work): ";
		getline(cin, f_loc_path);
	}
	
	ofstream f_GetCulture_;
	ofstream loc_GetCulture_;
	
	f_GetCulture_.open(f_GC_path.c_str(), fstream::app);
	f_GetCulture_ << "\n";
	f_GetCulture_ << "defined_text = {\n";
	f_GetCulture_ << "	name = "+GetCulture_+"\n";
	f_GetCulture_ << "	text = {\n";
	f_GetCulture_ << "		localisation_key = "+lockey_gc_i+"_accepted\n";
	f_GetCulture_ << "		trigger = {\n";
	f_GetCulture_ << "			AND = {\n";
	f_GetCulture_ << "				owner = { accepted_culture = " + current_culture + " }\n";
	f_GetCulture_ << "				check_variable = {\n";
	f_GetCulture_ << "					which = "+POPculture_prcnt+"\n";
	f_GetCulture_ << "					value = 1\n";
	f_GetCulture_ << "				}\n";
	f_GetCulture_ << "			}\n";
	f_GetCulture_ << "		}\n";
	f_GetCulture_ << "	}\n";
	f_GetCulture_ << "	text = {\n";
	f_GetCulture_ << "		localisation_key = "+lockey_gc_i+"_unaccepted\n";
	f_GetCulture_ << "		trigger = {\n";
	f_GetCulture_ << "			AND = {\n";
	f_GetCulture_ << "				NOT = { owner = { accepted_culture = " + current_culture + " } }\n";
	f_GetCulture_ << "				check_variable = {\n";
	f_GetCulture_ << "					which = "+POPculture_prcnt+"\n";
	f_GetCulture_ << "					value = 1\n";
	f_GetCulture_ << "				}\n";
	f_GetCulture_ << "			}\n";
	f_GetCulture_ << "		}\n";
	f_GetCulture_ << "	}\n";
	f_GetCulture_ << "	text = {\n";
	f_GetCulture_ << "		localisation_key = "+lockey_gc_ii+"\n";
	f_GetCulture_ << "		trigger = {\n";
	f_GetCulture_ << "			always = yes\n";
	f_GetCulture_ << "		}\n";
	f_GetCulture_ << "	}\n";
	f_GetCulture_ << "}\n";
	f_GetCulture_.close();
	
	f_GetCulture_.open(f_CGC_path.c_str(), fstream::app);
	f_GetCulture_ << "\n";
	f_GetCulture_ << "defined_text = {\n";
	f_GetCulture_ << "	name = "+GetCulture_Country_Scope_+"\n";
	f_GetCulture_ << "	text = {\n";
	f_GetCulture_ << "		localisation_key = "+lockey_gc_i+"_accepted\n";
	f_GetCulture_ << "		trigger = {\n";
	f_GetCulture_ << "			AND = {\n";
	f_GetCulture_ << "				accepted_culture = " + current_culture + "\n";
	f_GetCulture_ << "				check_variable = {\n";
	f_GetCulture_ << "					which = "+POPculture_prcnt+"\n";
	f_GetCulture_ << "					value = 1\n";
	f_GetCulture_ << "				}\n";
	f_GetCulture_ << "			}\n";
	f_GetCulture_ << "		}\n";
	f_GetCulture_ << "	}\n";
	f_GetCulture_ << "	text = {\n";
	f_GetCulture_ << "		localisation_key = "+lockey_gc_i+"_unaccepted\n";
	f_GetCulture_ << "		trigger = {\n";
	f_GetCulture_ << "			AND = {\n";
	f_GetCulture_ << "				NOT = { accepted_culture = " + current_culture + " }\n";
	f_GetCulture_ << "				check_variable = {\n";
	f_GetCulture_ << "					which = "+POPculture_prcnt+"\n";
	f_GetCulture_ << "					value = 1\n";
	f_GetCulture_ << "				}\n";
	f_GetCulture_ << "			}\n";
	f_GetCulture_ << "		}\n";
	f_GetCulture_ << "	}\n";
	f_GetCulture_ << "	text = {\n";
	f_GetCulture_ << "		localisation_key = "+lockey_gc_ii+"\n";
	f_GetCulture_ << "		trigger = {\n";
	f_GetCulture_ << "			always = yes\n";
	f_GetCulture_ << "		}\n";
	f_GetCulture_ << "	}\n";
	f_GetCulture_ << "}\n";
	f_GetCulture_.close();
	
	loc_GetCulture_.open(f_loc_path.c_str(), fstream::app);
	loc_GetCulture_ << " "+loc_i+"\n";
	loc_GetCulture_ << " "+loc_ii+"\n";
	loc_GetCulture_.close();
}

void create_pop(string culture, string group)
{
	current_culture = culture;
	POPculture_prcnt = "POPculture_"+culture+"_prcnt";
	GetCulture_ = "GetCulture_"+culture;
	GetCulture_Country_Scope_ = "CountryGetCulture_"+culture;
	lockey_gc_i = "acr_str_prct_"+culture;
	lockey_gc_ii = "acr_str_null_prct_"+culture;
	loc_i = lockey_gc_i+"_accepted:0"+" "+'"'+"§G[Root."+POPculture_prcnt+".GetName]§!: "+"[Root."+POPculture_prcnt+".GetValue]"+"%\\n"+'"'+'\n';
	loc_i += lockey_gc_i+"_unaccepted:0"+" "+'"'+"§R[Root."+POPculture_prcnt+".GetName]§!: "+"[Root."+POPculture_prcnt+".GetValue]"+"%\\n"+'"';
	loc_ii = lockey_gc_ii+":0"+" "+'"'+'"';
	loc_arg_t = "[Root."+GetCulture_+"]";
	loc_arg_buffer = loc_arg_buffer+loc_arg_t;
	
	if(mode_ == "!separate"){
		cout<<POPculture_prcnt<<endl;
		cout<<"defined_text = {"<<endl;
		cout<<"	name = "+GetCulture_<<endl;
		cout<<"	random = no"<<endl;
		cout<<"	text = {"<<endl;
		cout<<"		localisation_key = "+lockey_gc_i<<endl;
		cout<<"		trigger = {"<<endl;
		cout<<"			AND = {"<<endl;
		cout<<"				check_variable = {"<<endl;
		cout<<"					which = "+POPculture_prcnt<<endl;
		cout<<"					value = 1"<<endl;
		cout<<"				}"<<endl;
		cout<<"			}"<<endl;
		cout<<"		}"<<endl;
		cout<<"	}"<<endl;
		cout<<"	text = {"<<endl;
		cout<<"		localisation_key = "+lockey_gc_ii<<endl;
		cout<<"		trigger = {"<<endl;
		cout<<"			always = yes"<<endl;
		cout<<"		}"<<endl;
		cout<<"	}"<<endl;
		cout<<"}"<<endl;
		cout<<loc_i<<endl;
		cout<<loc_ii<<endl;
		cout<<loc_arg_buffer<<endl;
	}
	
	if(mode_ == "!all"){
		stf();
	}
	if(mode_ == "!all-keys"){
		save_loc_keys();
	}
	if(mode_ == "!all-varloc"){
		save_varlocs(culture, group);
	}
}

std::vector<std::string> split_string(const std::string &str, const std::string &separators){
	size_t last_seppos = 0;
	size_t seppos = 0;
	std::vector<std::string> strings;
	bool last_pos_was_separator = false;
	
	while((seppos = str.find_first_of(separators, seppos)) != std::string::npos){
		if(seppos - last_seppos - (last_seppos > 0) > 0){
			last_pos_was_separator = (separators.find_first_of(str[last_seppos]) != std::string::npos);
			strings.push_back(str.substr(last_seppos + last_pos_was_separator, seppos - last_seppos - last_pos_was_separator));
		}
		last_seppos = seppos;
		seppos++;
	}
	if(last_seppos + 1 < str.length()){
		strings.push_back(str.substr(last_seppos + 1));
	}
	if(!strings.empty() && !strings[strings.size() - 1].length()){
		strings.pop_back();
	}
	
	return strings;
}

size_t count_tab_appearances(const string &str){
	size_t counter = 0;
	for(; counter < str.length() && str[counter] == '\t'; counter++);
	return counter;
}

void load_locs(ifstream &file){
	string parse_line = "";
	while(getline(file, parse_line)){
		vector<string> tokens = split_string(parse_line, "\t");
		if(tokens.size() != 2){
			continue;
		}
		else{
			locs[tokens[0]] = tokens[1];
		}
	}
}

vector<string> parse_culture_names(ifstream &file, std::unordered_map<string, string> &cultures_groups){
	string parse_line = "";
	static const string exception_list[] = { "(",")","[","]","{","}", "\n", "country", "province", "male_names", "primary", "female_names", "dynasty_names", "graphical_culture", "second_graphical_culture" };
	vector<string> culture_names;
	string current_group = "";
	
	while(getline(file, parse_line)){
		if(count_tab_appearances(parse_line) == 1){
			vector<string> tokens = split_string(parse_line, " \t={}()[]");
			if(find(begin(exception_list), end(exception_list), tokens[0]) == end(exception_list) && tokens[0][0] != '#' && !tokens[0].empty()){
				culture_names.push_back(tokens[0]);
				cultures_groups.emplace(tokens[0], current_group);
			}
		}
		else if(count_tab_appearances(parse_line) == 0){
			vector<string> tokens = split_string(parse_line, " \t={}()[]");
			if(!tokens.empty() && find(begin(exception_list), end(exception_list), tokens[0]) == end(exception_list) && tokens[0][0] != '#' && !tokens[0].empty()){
				current_group = tokens[0];
			}
		}
	}
	
	return culture_names;
}

int main()
{
	string path_cultures;
	string path_cultures_locs;
	cout<<"Path to file with cultures: ";
	getline(cin, path_cultures);
	cout<<"Path to file with culture localization (optional): ";
	getline(cin, path_cultures_locs);
	
	ifstream _cultures;
	_cultures.open(path_cultures.c_str());
	vector<string> cultures;
	unordered_map<string, string> cultures_groups;
	if(_cultures){
		cultures = parse_culture_names(_cultures, cultures_groups);
	}
	else{
		cout << "Failed to open file in path \""<< path_cultures <<"\"" << endl;
		return 0;
	}
	_cultures.close();
	if(!path_cultures_locs.empty()){
		_cultures.open(path_cultures_locs.c_str());
		if(_cultures){
			load_locs(_cultures);
		}
		else{
			cout << "Failed to open file in path \""<< path_cultures_locs <<"\"" << endl;
		}
	}
	
	while(mode_ != "!exit"){
		getline(cin, mode_);
		
		if(mode_ == "!lst"){
			for(int i=0; i<cultures.size(); i++){
				cout<<i<<'\t'<<cultures[i]<<'\n';
			}
			cout<<"Culture groups: "<<std::endl;
			string last_group = "";
			for(int i=0; i<cultures.size(); i++){
				if(last_group != cultures_groups[cultures[i]]){
					last_group = cultures_groups[cultures[i]];
					std::cout<<last_group<<std::endl;
				}
			}
		}
		
		if(mode_ == "!separate"){
			for(size_t i = 0; i < cultures.size(); i++){
				create_pop(cultures[i], cultures_groups[cultures[i]]);
			}
		}
		if(mode_ == "!all"){
			int lines = 0;
			cout<<"Customizable loc (province) path: ";
			getline(cin, f_GC_path);
			cout<<"Customizable loc (country) path: ";
			getline(cin, f_CGC_path);
			cout<<"CL keys loc path(expects YAML file, any will work): ";
			getline(cin, f_loc_path);
			
			for(size_t i = 0; i < cultures.size(); i++){
				create_pop(cultures[i], cultures_groups[cultures[i]]);
			}
		}
		
		if(mode_ == "!all-keys"){
			int lines = 0;
			cout<<"Path to save loc keys: ";
			getline(cin, f_lockey_path);
			
			for(size_t i = 0; i < cultures.size(); i++){
				create_pop(cultures[i], cultures_groups[cultures[i]]);
			}
		}
		
		if(mode_ == "!all-varloc"){
			int lines = 0;
			cout<<"Path to save variable loc(expects YAML file, any will work): ";
			getline(cin, f_varloc_path);
			
			for(size_t i = 0; i < cultures.size(); i++){
				create_pop(cultures[i], cultures_groups[cultures[i]]);
			}
		}
	}
	
	return 0;
}
