#include <iostream>
#include <fstream>

#define MAXMAGNITUDE 2097152

int main(int argc, char **argv){
	if(argc < 2){
		return EXIT_SUCCESS;
	}
	
	std::ofstream _file;
	_file.open(argv[1]);
	_file <<"	set_variable = {\n"<<
			"		which = temp_counter\n"<<
			"		value = $amount$\n"<<
			"	}\n";
	for(int i = MAXMAGNITUDE; i > 0; i>>=1){
		_file <<"	if = {\n"<<
				"		limit = {\n"<<
				"			AND = {\n"<<
				"				check_variable = {\n"<<
				"					which = temp_counter\n"<<
				"					value = "<<i<<"\n"<<
				"				}\n"<<
				"			}\n"<<
				"		}\n"<<
				"		$action$ = "<<i<<"\n"<<
				"		subtract_variable = {\n"<<
				"			which = temp_counter\n"<<
				"			value = "<<i<<"\n"<<
				"		}\n"<<
				"	}\n";
	}
	
	return EXIT_SUCCESS;
}