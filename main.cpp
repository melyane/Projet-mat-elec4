#include <cstdlib>                                                                                                                                                                                       
#include <iostream>                                                                                                                                                                                      
#include "matrice.hpp"                                                                                                                                                                                   
#include "matriceDouble.hpp"                                                                                                                                                                             
#include "IndexInvalid.hpp"                                                                                                                                                                             
                                                                                                                                                                                                         
using namespace std;                                                                                                                                                                                     
                                                                                                                                                                                                         
int main() {

    matriceDouble m1(3,6);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 6; j++)
            m1.set(i, j, i+j);

    cout << m1 << endl << endl;
    matriceDouble m2(3, 6);
    m2 = m1;
    m2.set(2,2,9.0);
    cout << m1 << endl << endl;
    cout << m2 << endl << endl;

    try {
        matrice<double> *m3=m2.submat(1,3,4,2);
        cout << *m3 << endl;
    }
    catch(const IndexInvalid &e) {
        cerr << e.what() << endl;
    }

    return EXIT_SUCCESS;
}  