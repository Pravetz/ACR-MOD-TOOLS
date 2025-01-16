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
#include <algorithm>

bool stop = false;

using namespace std;
string mode_;

string POPculture_prcnt;	//variable name 
string GetCulture_;
string lockey_gc_i, lockey_gc_ii;
string loc_i, loc_ii;
string loc_arg_buffer, loc_arg_t;

string f_GC_path, f_loc_path, f_lockey_path, f_varloc_path;

void save_varlocs(const string &culture)
{
	ofstream f_varloc_save;
	
	string culture_formated;
	culture_formated = culture;
	culture_formated[0] = toupper(culture_formated[0]);
	for(int i=0; i<culture_formated.length(); i++){
		if(culture_formated[i] == '_'){
			culture_formated[i] = ' ';
			culture_formated[i+1] = toupper(culture_formated[i+1]);
		}
	}
	
	f_varloc_save.open(f_varloc_path.c_str(), fstream::app);
	f_varloc_save << " "+POPculture_prcnt+":0 "+'"'+culture_formated+'"'+"\n";
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
	f_GetCulture_ << "		localisation_key = "+lockey_gc_i+"\n";
	f_GetCulture_ << "		trigger = {\n";
	f_GetCulture_ << "			AND = {\n";
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

void create_pop(string culture)
{
	POPculture_prcnt = "POPculture_"+culture+"_prcnt";
	GetCulture_ = "GetCulture_"+culture;
	lockey_gc_i = "acr_str_prct_"+culture;
	lockey_gc_ii = "acr_str_null_prct_"+culture;
	loc_i = lockey_gc_i+":0"+" "+'"'+"§Y[Root."+POPculture_prcnt+".GetName]§!: "+"[Root."+POPculture_prcnt+".GetValue]"+"%\\n"+'"';
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
		save_varlocs(culture);
	}
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
	static const string exception_list[] = { "(",")","[","]","{","}", "\n", "male_names", "primary", "female_names", "dynasty_names", "graphical_culture", "second_graphical_culture" };
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
	
	while(mode_ != "!exit"){
		getline(cin, mode_);
		
		if(mode_ == "!separate"){
			for(size_t i = 0; i < cultures.size(); i++){
				create_pop(cultures[i]);
			}
		}
		if(mode_ == "!all"){
			int lines = 0;
			cout<<"Customizable loc path: ";
			getline(cin, f_GC_path);
			cout<<"CL keys loc path(expects YAML file, any will work): ";
			getline(cin, f_loc_path);
			
			for(size_t i = 0; i < cultures.size(); i++){
				create_pop(cultures[i]);
			}
		}
		
		if(mode_ == "!all-keys"){
			int lines = 0;
			cout<<"Path to save loc keys: ";
			getline(cin, f_lockey_path);
			
			for(size_t i = 0; i < cultures.size(); i++){
				create_pop(cultures[i]);
			}
		}
		
		if(mode_ == "!all-varloc"){
			int lines = 0;
			cout<<"Path to save variable loc(expects YAML file, any will work): ";
			getline(cin, f_varloc_path);
			
			for(size_t i = 0; i < cultures.size(); i++){
				create_pop(cultures[i]);
			}
		}
	}
	
	return 0;
}
