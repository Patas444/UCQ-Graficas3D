#pragma once

//Librerias STD
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>

//Third Parties
#include <SFML/Graphics.hpp>

//MACRO for safe realese of resorces
#define SAFE_PTR_REALESE(x) if(x != nullptr) { deletex; x=nullptr;}

#define MESSAGE(classObj, method, state)					\
{															\
	std::ostringstream os_;									\
	os_<< classObj << "::" << method << ":"					\
		<< "[CREATION OF RESORCE" << ":" << state << "] \n";\
	std::cerr << os_.str();									\
}

#define ERROR(classObj, method, errorMSG)						\
{																\
	std::ostringstream os_;										\
	os_<< "ERROR :" << classObj << "::" << method << ":"		\
		<< "Error in data from params [" << errorMSG << "] \n";	\
	std::cerr << os_.str();										\
	exit(1);													\
}