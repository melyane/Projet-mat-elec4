#include <cstdlib>
#include <iostream>
#include "matrice.hpp"
#include "matriceDouble.hpp"
#include "matriceCreuse.hpp"
#include "IndexInvalid.hpp"
#include "ErreurMatriceCreuse.hpp"

using namespace std;                                                                                                                                                                                     
                                                                                                                                                                                                         
int main() {

    matrice<double> *md1 = new matriceDouble(3,6);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 6; j++)
            md1->set(i, j, i+j);

    cout << *md1 << endl << endl;
    matrice<double> *md2 = new matriceDouble(3, 6);
    md2 = md1;
    md2->set(2,2,9.0);
    cout << *md1 << endl << endl;
    cout << *md2 << endl << endl;
/*
    try {
        matrice<double> *md3=md2.submat(1,3,4,2);
        cout << *md3 << endl;
    }
    catch(const IndexInvalid &e) {
        cerr << e.what() << endl;
    }
*/
    matriceCreuse mc(3,4);
    mc.set(1, 2, 8);
    cout << mc << endl;
    matriceCreuse mc2(3,4);
    mc2 = mc;
    cout << mc2 << endl;
    
    return EXIT_SUCCESS;
}  