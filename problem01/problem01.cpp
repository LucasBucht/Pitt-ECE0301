#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    const double e = exp(1);
    int n = 0;
    double approx = 0.00;
    
    do{
        n++;
        approx = pow(1.0 + (1.0/n), n);
     } while ((abs(approx - e) > 0.01));
        
    std:: cout << "The smallest n found to approximate e within 0.01 is " << n << std:: endl;
    std:: cout << "And bye, my first C++ program!" << std::endl;
    return EXIT_SUCCESS;
}
