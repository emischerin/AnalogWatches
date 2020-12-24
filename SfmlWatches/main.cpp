#include "Watches.h"
#include <string>
#include <iostream>
int main()
{
	Watches w;
	try {
		w.RunWatches();
	}
	catch(std::string& error_msg){
		std::cerr << error_msg << std::endl;
	} 
}