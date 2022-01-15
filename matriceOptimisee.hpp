#pragma once                                                                         
#include <cstdlib>                                                        
#include <iostream>
#include <assert.h>

#include "matriceCreuse.hpp"
#include "matriceDouble.hpp"

class matriceOptimisee {

protected:
    matrice<double> *m;
    int taille;
    int nbElemNonNuls;

    // méthodes de conversion 
    void convertirEnDouble() {
        int x = this->getLigne();
        int y = this->getColonne();
        matriceDouble *md = new matriceDouble(x,y);
        for(int i=0; i<x; i++) {
            for (int j=0; j<y; j++) {
                md->set(i,j,this->get(i,j));
            }
        }
        this->m=md;
    }
    void convertirEnCreuse() {
        assert(this->estCreuse());
        int x = this->getLigne();
        int y = this->getColonne();
        matriceCreuse *mc = new matriceCreuse(x,y);
        for(int i=0; i<x; i++) {
            for (int j=0; j<y; j++) {
                mc->set(i,j,this->get(i,j));
            }
        }
        this->m=mc;
    }

public:
    // constructeur
    matriceOptimisee(const int li=0, const int co=0) : taille(li*co), nbElemNonNuls(0) {
        matriceCreuse *mc = new matriceCreuse(li,co);
        m = mc;
    }

    // vérifie si la matrice est creuse
    int estCreuse() const {
        return (this->nbElemNonNuls < this->taille*0.1);
    }

    // méthodes sur la taille
    int getLigne() const {
        return this->m->getLigne();
    }
    int getColonne() const {
        return this->m->getColonne();
    }
    int getSize() const {
        return this->taille;
    }
    int getNbElemNonNuls() const {
        return this->nbElemNonNuls;
    }

    // méthodes sur les valeurs
    double get(int i, int j) const {
        return this->m->get(i,j);
    }

    double set(int i, int j, double val) {
        // valeur précédente
        double Pval = this->get(i,j);
        // précédent état creuse
        int previous_EtatCreuse = this->estCreuse();

        // pas de changement sur le nombre d'éléments non nuls
        if ((Pval==0 && val==0) || (Pval!=0 && val!=0)) {
            this->m->set(i,j,val);
        }
        // changement sur le nb d'elem non nuls
        else {
            // ancienne val non nul et nouvelle val nulle
            if(val == 0) {
                this->nbElemNonNuls--;
                this->m->set(i,j,val);
                if((this->estCreuse()) && (previous_EtatCreuse==0))
                    this->convertirEnCreuse();
            }
            // anciene val nulle et nouvelle val non nulle
            else {
                this->nbElemNonNuls++;
                if((!(this->estCreuse())) && (previous_EtatCreuse==1)) 
                    this->convertirEnDouble();
                this->m->set(i,j,val);
            }
        }   
    }

    // somme entre matrices
    // this + m2
    matriceOptimisee* somme(const matriceOptimisee *m2) const {
        int x = this->getLigne();
        int y = this->getColonne();        
        assert(x == m2->getLigne());
        assert(y == m2->getColonne());
        matriceOptimisee *res = new matriceOptimisee(x,y);
        for (int i=0; i<x; i++) {
            for (int j=0; j<y; j++) {
                res->set(i,j,m2->get(i,j)+this->get(i,j));
            }
        }
        return res;
    }

    // produit entre matrices
    // this * m2
    matriceOptimisee* produit(const matriceOptimisee *m2) const {
        int l1 = this->getLigne(); 
        int c1 = this->getColonne(); 
        int l2 = m2->getLigne(); 
        int c2 = m2->getColonne(); 
        assert(c1==l2);   
        matriceOptimisee *res = new matriceOptimisee(l1, c2);
        for(int i = 0; i < l1; i++) {
            for(int j = 0; j < c2; j++) {
                for(int k = 0; k < c1; k++) {
                    res->set(i,j,res->get(i,j)+this->get(i,k)*m2->get(k,j));
                }
            }
        }
        return res;
    }

    // conversion en string pour affichage
    std::string toString () const {
        std::ostringstream s;
        s << *(this->m);
    }

    // surcharge affichage matrice
    friend std::ostream &operator<< (std::ostream &f, const matriceOptimisee &m) {
        return f<<m.toString();
    }

};
