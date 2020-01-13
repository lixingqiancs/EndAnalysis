#include <boost/math/distributions/poisson.hpp>
#include<iomanip>
#include <iostream>
 
using namespace std;
using namespace boost::math;
 
int main()
{
        poisson_distribution<> p(1);
        cout << setprecision(15) <<"cdf: ppois(1,1)="<<1-cdf(p,1)<<endl;
 
        return 0;
}
