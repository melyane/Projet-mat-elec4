#include <cstdlib>
#include <iostream>
#include "matrice.hpp"
#include "matriceDouble.hpp"
#include "matriceCreuse.hpp"
#include "IndexInvalid.hpp"
#include "ErreurMatriceCreuse.hpp"

#include "matriceOptimisee.hpp"

using namespace std;

int main() {

    // SECOND TEST with matriceOptimisee

    matriceOptimisee *mo = new matriceOptimisee(10,10);
    cout << "mo est creuse : " << mo->estCreuse() << endl;
    cout << *mo << endl;
    mo->set(1,1,11);
    cout << "valeur (1,1) : " << mo->get(1,1) << endl;
    cout << *mo << endl;
    mo->set(6,5,56);
    mo->set(6,9,69);
    cout << "mo est creuse : " << mo->estCreuse() << endl;
    cout << *mo << endl;
    for (int i=0; i<10; i++)
        mo->set(8,i,80+i);
    cout << "mo est creuse : " << mo->estCreuse() << endl;
    cout << *mo << endl;

    /*

    // FIRST TEST

    matriceDouble md1(5,10);

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 10; j++)
            md1.set(i, j, i+j);

    cout << "md1 :\n" << md1 << endl;
    matriceDouble md2(5, 10);
    md2 = md1;
    md2.set(2,2,9.0);
    cout << "md1 :\n" << md1 << endl;
    cout << "md2 :\n" << md2 << endl;

    try {
        matrice <double> *md3=md2.submat(1,3,4,2);
        cout << *md3 << endl;
    }
    catch(const IndexInvalid &e) {
        cerr << e.what() << endl;
    }

    matrice<double> *md4=md1.submat(1,4,3,7);
    cout << *md4 << endl;

    matriceCreuse mc(5,10);
    mc.set(1, 2, 5);
    mc.set(3, 7, 4);
    cout << mc << endl;
    matriceCreuse mc2(5,10);
    mc2=mc;
    mc.set(1, 2, 2);
    cout << mc2 << endl;
    cout << mc << endl;

    matrice<double> *mc3=mc.submat(1,4,3,7);
    cout << *mc3 << endl;

    */
    
    return EXIT_SUCCESS;
}