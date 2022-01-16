/*  
 *  Définition de la classe "Matriceoptimisee"   
 *  Elle permet notamment la convertion de matrice 
 *  creuse / double et inversement.
 *
 *  @author PEZ Mélanie / HATIER Joé
 *
 */

#pragma once

#include <cstdlib>                                                        
#include <iostream>
#include <assert.h>

#include "matrice.hpp"
#include "matriceCreuse.hpp"
#include "matriceDouble.hpp"

class matriceOptimisee {

protected:
    matrice<double> *m;
    int taille;
    int nbElemNonNuls;

    // Méthodes de conversion

    /* Role : Convertir une matrice creuse en matrice double
    */
    void convertirEnDouble() {
        int x = this->getLigne();
        int y = this->getColonne();
        matriceDouble *md = new matriceDouble(x,y);
        for(int i=0; i<x; i++) {
            for (int j=0; j<y; j++) {
                md->set(i,j,this->get(i,j));
            }
        }
        delete m;
        this->m=md;
    }

    /*Role : Convertir une matrice double en matrice creuse 
    *       seulement si il y a bien 10% d’éléments non nuls.
    */
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
        delete m;
        this->m=mc;
    }

    /* Role : Dupliquer une matrice double
     */
    void dupliquer (const matriceOptimisee &m) {
        this->taille=m.taille;
        this->nbElemNonNuls=m.nbElemNonNuls;
        int x = m.getLigne();
        int y = m.getColonne();
        if(m.estCreuse()==1) {
            matriceCreuse *m1 = new matriceCreuse(x,y);
            for(int i=0; i<x; i++) {
                for (int j=0; j<y; j++) {
                    m1->set(i,j,m.get(i,j));
                }
            }
            this->m=m1;
        }
        else {
            matriceDouble *m1 = new matriceDouble(x,y);
            for(int i=0; i<x; i++) {
                for (int j=0; j<y; j++) {
                    m1->set(i,j,m.get(i,j));
                }
            }
            this->m=m1;
        }
    }

public:

    // constructeur
    matriceOptimisee(const int li, const int co) : taille(li*co), nbElemNonNuls(0) {
        matriceCreuse *mc = new matriceCreuse(li,co);
        m = mc;
    }

    //Constructeur de copie
    matriceOptimisee (const matriceOptimisee &m) {
        dupliquer(m);
    }
    
    //Surcharge de l'opérateur d'affectation
    matriceOptimisee &operator=(const matriceOptimisee &m) {
        dupliquer(m);
        return *this;
    }

    // Role : Vérifier si la matrice est creuse
    int estCreuse() const {
        return (this->nbElemNonNuls < this->taille*0.1);
    }

    // Role : Renvoie le nombre de ligne de la matrice
    int getLigne() const {
        return this->m->getLigne();
    }

    // Role : Renvoie le nombre de colonne de la matrice
    int getColonne() const {
        return this->m->getColonne();
    }

    // Role : Retourne la taille de la matrice
    int getSize() const {
        return this->taille;
    }

    // Role : Renvoie le nombre d'éléments non nuls de la matrice
    int getNbElemNonNuls() const {
        return this->nbElemNonNuls;
    }

    // méthodes sur les valeurs
    double get(int i, int j) const {
        return this->m->get(i,j);
    }

    // Méthodes sur les valeurs

    // Role :   Renvoie le réel présent à l'indice[i,j]
    void set(int i, int j, double val) {
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

    /* Role : Renvoie la somme de deux matrices
    * this + m2
    */
    matriceOptimisee* somme(const matriceOptimisee &m2) const {
        int x = this->getLigne();
        int y = this->getColonne();        
        assert(x == m2.getLigne());
        assert(y == m2.getColonne());
        matriceOptimisee *res = new matriceOptimisee(x,y);
        for (int i=0; i<x; i++) {
            for (int j=0; j<y; j++) {
                //std::cout << "TEST " << res->estCreuse() << std::endl;
                res->set(i,j,m2.get(i,j)+this->get(i,j));
            }
        }
        return res;
    }

    /* Role : Renvoie le produit entre deux matrices
    * this * m2
    */
    matriceOptimisee* produit(const matriceOptimisee &m2) const {
        int l1 = this->getLigne(); 
        int c1 = this->getColonne(); 
        int l2 = m2.getLigne(); 
        int c2 = m2.getColonne(); 
        assert(c1==l2);   
        matriceOptimisee *res = new matriceOptimisee(l1, c2);
        for(int i = 0; i < l1; i++) {
            for(int j = 0; j < c2; j++) {
                for(int k = 0; k < c1; k++) {
                    res->set(i,j,res->get(i,j)+this->get(i,k)*m2.get(k,j));
                }
            }
        }
        return res;
    }

    // Conversion en string pour affichage
    std::string toString () const {
        std::ostringstream s;
        s << *(this->m);
        return s.str();
    }

    // Surcharge affichage matrice
    friend std::ostream &operator<< (std::ostream &f, const matriceOptimisee &m) {
        return f<<m.toString();
    }

    // Remplissage aléatoire
    void alea(int min, int max) {
        int x = this->getLigne();
        int y = this->getColonne();
        for(int i=0; i<x; i++) {
            for(int j=0; j<y; j++) {
                this->set(i,j,((double)rand()*(max-min)/(double)RAND_MAX-min));
            }
        }
    }
};
