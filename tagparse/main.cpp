#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>

void string_strip_inplace(std::string &dst, bool reverse=false){
	size_t substr_pos = 0;
	if(reverse){
		substr_pos = dst.find_last_not_of(" \t\v\n\r");
		if(substr_pos != std::string::npos){
			dst = dst.substr(0, substr_pos);
		}
	}
	else{
		substr_pos = dst.find_first_not_of(" \t\v\n\r");
		if(substr_pos != std::string::npos){
			dst = dst.substr(substr_pos);
		}
	}
}

std::string get_tag_from_string(const std::string &src){
	return src.substr(0, 3);
}

void parse_tags(std::unordered_set<std::string> &parsed_tags, const std::string &path){
	std::ifstream tagfile;
	tagfile.open(path);
	if(tagfile){
		std::string parsed = "";
		while(std::getline(tagfile, parsed)){
			if(parsed.empty() || parsed[0] == '#'){
				continue; // skip comment or empty lines
			}
			string_strip_inplace(parsed);
			if(parsed.length() < 3){
				continue;	// skip empty lines
			}
			std::string TAG = get_tag_from_string(parsed);
			if(parsed_tags.count(TAG) == 0){
				parsed_tags.insert(TAG);
				std::cout<<TAG<<'\n';
			}
		}
		
		tagfile.close();
	}
}

int main(int argc, char **argv){
	std::unordered_set<std::string> parsed_tags = {};
	for(int i = 1; i < argc; i++){
		parse_tags(parsed_tags, argv[i]);
	}
	
	return 0;
}