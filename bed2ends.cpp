/**************************************************************************

Copyright: CPY, CUHK
Author: Xingqianli
Date: Jan.04 2020 
Description: Bed2ends
Version: 1.0
File: main.cpp

**************************************************************************/

#include "message.h"
#include "EndsTools.h"
#include <cstdlib>
#include <iostream>
//#include <string>
//#include <unordered_map>
#include <map>

using namespace std;
typedef map<string, unsigned int> datamap;

int main(int agrc, char** argv)
{
	message m;
	EndsTools endsTools;
	//unsigned int* data = NULL;	
	datamap hgData;
	unsigned int sz;
	unsigned int tot=0;

	if(agrc!=(4+1))
	{
		m.warnMessage("usage: <hg.size> <chr> <outprefix> <bed>");
		exit(1);
	}
	//m.warnMessage("Bed2ends is Working!");	

	const string hg_size = *(++argv);
	const string chr_t = *(++argv);
	const string output = *(++argv);
	const string bed_file = *(++argv);
	
	endsTools.loadHgsize(hgData,hg_size);
	
	datamap::iterator iter;
	if((iter=hgData.find(chr_t))==hgData.end())
	{
		m.warnMessage("Error: hg size not found!");
		exit(1);
	}else sz=iter->second;
	//cout << chr_t <<  " hg.size:  " << sz <<endl;	

	unsigned int* data = new unsigned int[sz+1];
	//unsigned int data[sz+1];
	endsTools.loadBedfile(data,bed_file,chr_t,tot);
	
	string outPath = output + ".ends.C++.bedgraph";
	endsTools.saveBedgraph(outPath,data,sz,chr_t,tot);
	
	delete [] data;
	//cerr << "Tot: " << tot << endl;

	return EXIT_SUCCESS;
}
