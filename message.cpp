/**************************************************************************

Copyright: CPY, CUHK
Author: Xingqianli
Date: Jan.04 2020 
Description: Bed2ends
Version: 1.0
File: message.cpp

**************************************************************************/


#include <iostream>
#include "message.h"

using namespace std;

void message::printMessage(const string& str){
	cout << str << endl;
}

void message::warnMessage(const string& str){
	cerr << str << endl;
}




