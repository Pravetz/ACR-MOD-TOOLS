/*				WRITTEN BY PRAVETZ
 * 		FOR ALL COUNTRIES RELEASED MOD FOR EU4
 * 	USED TO CREATE CULTURE-RELATED VARIABLES AND LOCALIZATION MORE 
 * 	EFFICIENTLY.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

bool stop = false;

using namespace std;
string mode_;

string POPculture_prcnt;	//variable name 
string GetCulture_;
string lockey_gc_i, lockey_gc_ii;
string loc_i, loc_ii;
string loc_arg_buffer, loc_arg_t;

string f_GC_path, f_loc_path, f_lockey_path, f_varloc_path;

void save_varlocs(string culture)
{
	fstream f_varloc_save;
	
	culture[0] = toupper(culture[0]);
	
	f_varloc_save.open(f_varloc_path.c_str(), fstream::app);
	f_varloc_save << " "+POPculture_prcnt+":0 "+'"'+culture+'"'+"\n";
	f_varloc_save.close();
}
void save_loc_keys()
{
	fstream f_lockey_save;
	
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
	
	fstream f_GetCulture_;
	fstream loc_GetCulture_;
	
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

int main()
{
	getline(cin, mode_);
	
	if(mode_ == "!separate"){
		string culture;
		string ifsave;
	
		while(!stop){
			getline(cin, culture);
			if(culture != "!stop"){
				create_pop(culture);
					cout<<"Save to file? (y/n)"<<endl;
					getline(cin, ifsave);
						if(ifsave == "y"){
							stf();
						}
			}
			if(culture == "!stop")
			{
				return 0;
			}
		}
	}
	if(mode_ == "!all"){
		int lines = 0;
		string lc_path;
		getline(cin, lc_path);
		cout<<"Customizable loc path: ";
		getline(cin, f_GC_path);
		cout<<"CL keys loc path(expects YAML file, any will work): ";
		getline(cin, f_loc_path);
		string culture;
		
		fstream load_cultures;
		load_cultures.open(lc_path.c_str());
		while(getline(load_cultures, culture)){
			lines++;
		}
		load_cultures.close();
		load_cultures.open(lc_path.c_str());
		string cultures[lines];
		for(int i=1; i<lines; i++){
			getline(load_cultures, cultures[i]);
			create_pop(cultures[i]);
		}
		load_cultures.close();
	}
	
	if(mode_ == "!all-keys"){
		int lines = 0;
		string lc_path;
		getline(cin, lc_path);
		cout<<"Path to save loc keys: ";
		getline(cin, f_lockey_path);
		string culture;
		
		fstream load_cultures;
		load_cultures.open(lc_path.c_str());
		while(getline(load_cultures, culture)){
			lines++;
		}
		load_cultures.close();
		load_cultures.open(lc_path.c_str());
		string cultures[lines];
		for(int i=1; i<lines; i++){
			getline(load_cultures, cultures[i]);
			create_pop(cultures[i]);
		}
		load_cultures.close();
	}
	
	if(mode_ == "!all-varloc"){
		int lines = 0;
		string lc_path;
		getline(cin, lc_path);
		cout<<"Path to save variable loc(expects YAML file, any will work): ";
		getline(cin, f_varloc_path);
		string culture;
		
		fstream load_cultures;
		load_cultures.open(lc_path.c_str());
		while(getline(load_cultures, culture)){
			lines++;
		}
		load_cultures.close();
		load_cultures.open(lc_path.c_str());
		string cultures[lines];
		for(int i=1; i<lines; i++){
			getline(load_cultures, cultures[i]);
			create_pop(cultures[i]);
		}
		load_cultures.close();
	}
}
