/*  
 *  Définition de la classe abstraite générique "Matrice"
 *  
 *  @author PEZ Mélanie / HATIER Joé
 *
 */

#pragma once                                                                         

#include <cstdlib>                                                        
#include <iostream>

#include "IndexInvalid.hpp" 

template <typename T>

class matrice {
protected:
  int nbElem; 
  int nbL; 
  int nbC;

public:

  // constructeur
  matrice (const int L=0, const int C=0) : nbL(L), nbC(C), nbElem(L*C) {}
  
  // destructeur
  virtual ~matrice () {}

  /* Role :   Duplique la matrice<T> courante
   */
  void dupliquer (const matrice<T> &mat) {
    this->nbElem = mat.nbElem;
    this->nbL = mat.nbL;
    this->nbC = mat.nbC;
  }
  
  // constructeur de copie
  matrice (const matrice<T> &mat) {
    dupliquer (mat);
  }

  /* Role : Renvoie le nombre de ligne de la matrice<T>
   */
  int getLigne () const {
    return(this->nbL);
  }

  /* Role : Renvoie le nombre de colonne de la matrice<T>
   */
  int getColonne () const {
    return(this->nbC);
  }

  virtual T get (const int i, const int j) const = 0;
  virtual void set (const int i, const int j, const T x) = 0;

  virtual matrice<T>* submat (const int i1, const int i2, const int j1, const int j2) = 0;

  virtual std::string toString() const = 0;

  // surcharge affichage matrice
  friend std::ostream &operator<< (std::ostream &f, const matrice<T> &m) {
    return f<<m.toString();
  }

  //  Méthode est creuse
  virtual bool estCreuse() const=0;

};