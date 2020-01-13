#include <string>
#include <map>
#include <vector>

using namespace std;

typedef map<string, unsigned int> datamap;
typedef vector<vector<double> > poisVector2;
typedef vector<vector<unsigned int> > dataVector2; 

#ifndef ENDSTOOLS_H
#define ENDSTOOLS_H

class EndsTools{
	
	public:
		void loadHgsize(datamap& hgData, const string& hgPath);
		vector<string> split(const string& str, const string& delim);
		void loadBedfile(unsigned int* bedData, const string& bedPath, const string& chr_t, unsigned int& tot);
		void loadEndsfile(dataVector2& dataCount, const string& endPath, const unsigned int& win, const string& chr_t);
		void saveBedgraph(const string& outPath, unsigned int* bedData, const unsigned int& size, const string& chr, const int& tot);
		void buildPoisTable(poisVector2& poisTable);
		void analysisEndsfile(const string& endPath, const dataVector2& dataCount, const poisVector2& poisTable, const unsigned int& win,const string& chr_t);
	private:
		//datamap hgData;
};

#endif // ENDSTOOLS_H
