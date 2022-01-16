 /*  
 *  Utilisation des classes du projet.
 *
 *  @author PEZ Mélanie / HATIER Joé
 * 
 */

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
    // TEST PARTIE I

    //Test fonctions de la classe matrice double
    cout << "\n____________________________TEST PARTIE I____________________________\n\nTest fonctions de la classe matrice double" << endl;
    matriceDouble md1(5,10);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 10; j++)
            md1.set(i, j, i+j);

    cout << "md1 :\n" << md1 << endl;
    matriceDouble md2(5, 10);
    md2 = md1;
    md1.set(2,2,9);
    cout << "md2 = md1 :\n" << md2 << endl;
    cout << "md1 : valeur (2,2) = " <<  md1.get(2,2) << "\n" << md1 << endl;
    cout << "md2 :\n" << md2 << endl;

    cout << "Test classe exception IndexInvalid" << endl;
    try {
        matrice <double> *md3=md2.submat(1,3,4,2);
        cout << *md3 << endl;
    }
    catch(const IndexInvalid &e) {
        cerr << e.what() << endl;
    }

    matrice<double> *md4=md1.submat(1,4,3,7);
    cout << "\nmd4 = md1.submat(1,4,3,7) :\n" << *md4 << endl;


    //Test fonctions de la classe matrice creuse
    cout << "Test fonctions de la classe matrice creuse" << endl;
    matriceCreuse mc1(5,10);
    mc1.set(1, 2, 5);
    mc1.set(3, 7, 4);
    cout << "mc1 :\n" << mc1 << endl;
    matriceCreuse mc2(5,10);
    mc2=mc1;
    mc1.set(1, 2, 2);
    cout << "mc2 = mc1 :\n" << mc2 << endl;
    cout << "mc1 : valeur (1,2) = " <<  mc1.get(1,2) << "\n" << mc1 << endl;
    cout << "mc2 :\n" << mc2 << endl;

    matrice<double> *mc3=mc1.submat(1,4,3,7);
    cout << "mc3 = mc1.submat(1,4,3,7) :\n" << *mc3 << endl;
    


    // TEST PARTIE II (matriceOptimisee)
    cout << "____________________________TEST PARTIE II____________________________\n\nTest fonctions de la classe matrice optimisée" << endl;
    matriceOptimisee mo1(5,10);
    mo1.set(1,1,1);
    mo1.set(4,5,6);
    mo1.set(4,9,9);
    cout << "mo1 : est creuse ? " << mo1.estCreuse() << "\n" << mo1 << endl;

    matriceOptimisee mo2(5,10);
    for (int i=0; i<10; i++)
        mo2.set(3,i,i);
    cout << "mo2 : est creuse ? " << mo2.estCreuse() << "\n" << mo2 << endl;

    matriceOptimisee *mo3 = mo1.somme(mo2);
    cout << "mo3 = mo1+mo2 : est creuse ? " << mo3->estCreuse() << "\n" << *mo3 << endl;

    matriceOptimisee mo4(10,5); 
    mo4.alea(0,100);
    cout << "mo4 : est creuse ? " << mo4.estCreuse() << "\n" << mo4 << endl;

    matriceOptimisee *mo5 = mo1.produit(mo4);
    cout << "mo5 = mo1xmo4 : est creuse ? " << mo5->estCreuse() << "\n" << *mo5 << endl;

    cout << "mo1 : est creuse ? " << mo1.estCreuse() << "\n" << mo1 << endl;
    mo1.set(2,1,1);
    mo1.set(3,5,6);
    cout << "valeur (2,1) = " <<  mo1.get(2,1) << " valeur (3,5) = " <<  mo1.get(3,5) << "\nmo1 : est creuse ? " << mo1.estCreuse() << "\n" << mo1 << endl;
        
    return EXIT_SUCCESS;
}