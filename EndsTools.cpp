/**************************************************************************

Copyright: CPY, CUHK
Author: Xingqianli
Date: Jan.06 2020 
Description: EndsTools, the function set of ends
Version: 1.0
File: EndsTools.cpp

**************************************************************************/


#include <iostream>
#include <cstring>
#include "message.h"
#include <map>
#include <fstream>
#include "EndsTools.h"
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <boost/math/distributions/poisson.hpp>

#define kend 0
#define kN 1

using namespace std;
using namespace boost::math;

typedef map<string, unsigned int> datamap;
typedef vector<vector<double> > poisVector2;
typedef vector<vector<unsigned int> > dataVector2; 

void EndsTools::loadHgsize(datamap& hgData, const string& hgPath){
	message m;
	ifstream hgFile(hgPath.c_str(),ios::in);
	if(!hgFile){
		m.warnMessage("hg.size file failed to open! The currently entered file name is "+hgPath);
		exit(1);
	}	
	//m.warnMessage("File successfully opened! The hg.size File is "+hgPath);	

	string hgSize;
	vector<string> dataArray;
	while(getline(hgFile,hgSize)){
		dataArray = split(hgSize,"\t");
		hgData[dataArray[0]] = strtoul(dataArray[1].c_str(),NULL,0);
	}
	
	hgFile.close();
}


vector<string> EndsTools::split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;
	char * strs = new char[str.length() + 1]; 
	strcpy(strs, str.c_str()); 
 
	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());
 
	char *p = strtok(strs, d);
	while(p) {
		string s = p;
		res.push_back(s); 
		p = strtok(NULL, d);
	}
 
	return res;
}

void EndsTools::loadBedfile(unsigned int* bedData, const string& bedPath, const string& chr_t, unsigned int& tot){
	message m;
	ifstream bedFile(bedPath.c_str(),ios::in);
	if(!bedFile){
		m.warnMessage("bed file failed to open! The currently entered file name is "+bedPath);
		exit(1);
	}
	m.warnMessage("File successfully opened! The bed file is "+bedPath);

	string chr;
	unsigned int start;
	unsigned int end;
	string dataLine;
	vector<string> dataArray;
	while(getline(bedFile,dataLine)){
		dataArray = split(dataLine,"\t");
		chr = dataArray[0];
		if(chr!=chr_t) continue;
		start = strtoul(dataArray[1].c_str(),NULL,0);
		end = strtoul(dataArray[2].c_str(),NULL,0);
		++bedData[start];
		++bedData[end];
		tot+=2;
		//m.warnMessage("Save Data!");	
	}	
	bedFile.close();
}

void EndsTools::saveBedgraph(const string& outPath, unsigned int* bedData, const unsigned int& size, const string& chr, const int& tot){
	message m;
	ofstream outFile(outPath.c_str(),ios::out);
	if(!outFile){
		m.warnMessage("Writing to the file failed! The currently entered file name is "+outPath);	
		exit(1);
	}
	
	unsigned int h,s,e;
	double prt;
	for(unsigned int pos=0; pos<=size; ++pos){
		if(bedData[pos]==0) continue;
		h=bedData[pos];
		s=pos;
		e=pos+1;
		prt=((double)h)/tot*1e6;
		//cout << "h: " << h  << "\ttot: " << tot << endl;
		outFile << chr << '\t' << s << '\t' << e << '\t' << h << '\t' << setprecision(15) << prt << endl;
	}
	
	m.warnMessage("File successfully written! The output is "+outPath);
	outFile.close();
}



void EndsTools::loadEndsfile(dataVector2& dataCount, const string& endPath, const unsigned int& win, const string& chr_t){
	message m;
	ifstream endFile(endPath.c_str(),ios::in);
	if(!endFile){
		m.warnMessage("end file failed to open! The currently entered file name is "+endPath);	
		exit(0);
	}
	m.warnMessage("File successfully opened! The end file is "+endPath);

	string chr,dataLine;
	unsigned int idx;
	vector<string> dataArray;
	while(getline(endFile,dataLine)){
		dataArray = split(dataLine,"\t");
		chr = dataArray[0];
		if(chr!=chr_t) continue;
		idx = strtoul(dataArray[1].c_str(),NULL,0) / win;
		dataCount[idx][kend] += strtoul(dataArray[3].c_str(),NULL,0);
		++dataCount[idx][kN];
	}
	endFile.close();
}

void EndsTools::buildPoisTable(poisVector2& poisTable){
	double prob;
	for(int lambda=1; lambda<=1000; ++lambda){
		poisson_distribution<> pois(lambda);
		for(int obs=0; obs<=1000; ++obs){
			prob = cdf(pois,obs);
			poisTable[lambda][obs] = 1-prob;		
		}
	}
}

void EndsTools::analysisEndsfile(const string& endPath, const dataVector2& dataCount, const poisVector2& poisTable, const unsigned int& win,const string& chr_t){
	message m;
	ifstream endFile(endPath.c_str(),ios::in);
	if(!endFile){
		m.warnMessage("end file failed to open! The currently entered file name is "+endPath);
	}
	
	string chr,dataLine;
	vector<string> dataArray;
	unsigned int idx, lambda,end_occ;
	double pval,temp;
	while(getline(endFile,dataLine)){
		dataArray = split(dataLine,"\t");
		chr = dataArray[0];
		if(chr!=chr_t) continue;
		idx = strtoul(dataArray[1].c_str(),NULL,0)/win;
		lambda = dataCount[idx][kend] / dataCount[idx][kN];
		end_occ = strtoul(dataArray[3].c_str(),NULL,0);
		
		//cout << "lambda: " << lambda << "\tend_occ: " << end_occ << "\tidx: " << idx << "\tend: " << dataCount[idx][kend] << "\tN: " << dataCount[idx][kN]  << endl;	
		temp = poisTable[lambda][end_occ];
		if(temp==0){
			poisson_distribution<> pois(lambda);
			pval=1-cdf(pois,end_occ);
		}
		else pval=temp;
		float fold_change = ((float)end_occ) / lambda;
		cout << chr << '\t'  << dataArray[1] << '\t' << dataArray[2] << '\t' << dataArray[3] << '\t' << dataArray[4] << '\t' << lambda << '\t';
		printf("%.2f\t", fold_change);
		cout << setprecision(15) << pval << endl;
	}
	endFile.close();
}
