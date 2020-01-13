/**************************************************************************

Copyright: CPY, CUHK
Author: Xingqianli
Date: Jan.08 2020 
Description: determine enriched ends
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
typedef vector<vector<double> > poisVector2;
typedef vector<vector<unsigned int> > dataVector2;

int main(int agrc, char** argv)
{
	message m;
	EndsTools endsTools;
	datamap hgData;
	unsigned int sz;

	if(agrc!=(4+1))
	{
		m.warnMessage("Usage: <win> <hg.size> <chr> <*.ends>");
		exit(1);
	}
	const string win  = *(++argv);
	const string hg_sz = *(++argv);
	const string chr_t = *(++argv);
	const string end = *(++argv);
	
	endsTools.loadHgsize(hgData,hg_sz);
	datamap::iterator iter;
	if((iter=hgData.find(chr_t))==hgData.end())
	{
		m.warnMessage("Error: hg size not found!");
		exit(1);
	}else sz=iter->second;
	
	unsigned int iwin = strtoul(win.c_str(),NULL,0);
	//unsigned int dataCount[sz/iwin+1][2];
	dataVector2 dataCount(sz/iwin+1,vector<unsigned int>(2)); 
	endsTools.loadEndsfile(dataCount,end,iwin,chr_t);
	
	//double poisTable[1001][1001];
	poisVector2 poisTable(1001,vector<double>(1001));
	endsTools.buildPoisTable(poisTable);

	endsTools.analysisEndsfile(end,dataCount,poisTable,iwin,chr_t);
	
	return EXIT_SUCCESS;
}
