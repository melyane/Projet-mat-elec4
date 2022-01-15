#pragma once
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <sstream>

#include "matrice.hpp"
#include "IndexInvalid.hpp" 
#include "ErreurMatriceCreuse.hpp"

class matriceCreuse : public matrice<double> {
protected:
	int nbElemCreuse;
	double * mat;
	int * indice;

	void dupliquer (const matriceCreuse &m) {
		this->mat = new double[nbElemCreuse];
		this->indice = new int[nbElemCreuse];
		for (int k=0; k<nbElemCreuse; k++) {
			this->mat[k] = m.mat[k];
			this->indice[k] = m.indice[k];
		}
	}

public:
	//Constructeur
	matriceCreuse (const int n, const int m) : matrice(n,m), nbElemCreuse(int(matrice::nbElem*0.1)), mat(new double [nbElemCreuse]), indice(new int [nbElemCreuse]){
		for (int k=0; k<nbElemCreuse; k++) {
			mat[k] = 0.0;
			indice[k] = -1; // -1 pour les indices non utilisés
		}
	}

	//Destructeur
	~matriceCreuse() {
		delete[] mat;
		delete[] indice;
	}

	virtual bool estCreuse() const override {
		return true;
	}

	//Constructeur de copie
	matriceCreuse (const matriceCreuse &m) {
		dupliquer(m);
	}

	//Méthode virtuelle get
	virtual double get (const int i, const int j) const override {
		if (i > matrice::nbL)
			throw IndexInvalid ("i > nb Ligne");
		if (j > matrice::nbC)
			throw IndexInvalid("j > nb Colonne");
		
		for (int k=0; k<nbElemCreuse; k++) {
			if (this->indice[k]==i*matrice::nbC+j)
				return this->mat[k];
		}
		return 0.0;
	}

	//Méthode virtuelle set
	virtual void set (const int i, const int j, const double x) override {
		if (i > matrice::nbL)
			throw IndexInvalid ("i > nb Ligne");
		if (j > matrice::nbC)
			throw IndexInvalid("j > nb Colonne");
		
		int test=1;
		for(int k=0; k<nbElemCreuse; k++) {
			// si l'indice est déjà référencé
			if(this->indice[k]==i*matrice::nbC+j) {
				if(x==0) {
					this->indice[k]=-1;
					test=0; break;
				}
				else {
					this->mat[k]=x;
					test=0; break;
				}
			}
		}
		std::cout<<std::endl;
		// si l'indice n'est pas référencé
		if(test==1) {
			for (int k=0; k<nbElemCreuse; k++){
				if(this->indice[k]==-1) {
					this->mat[k]=x;
					this->indice[k]=i*matrice::nbC+j;
					test=0; break;
				}
			}
		}
		// set impossible
		if(test==1)
			throw ErreurMatriceCreuse ("Nombre maximum d'éléments atteint dans la matrice creuse");
	}

	//Méthode virtuelle toString
	virtual std::string toString () const {
		std::ostringstream s;
		s << " ";
		for (int x=0; x<matrice::nbL; x++){
			for(int y=0; y<matrice::nbC; y++){
				s << " " << this->get(x,y) << " ";
			}
			s << "\n ";
		}
		return s.str();
	}

	//Surcharge de l'opérateur d'affectation
	matriceCreuse &operator=(const matriceCreuse &m) {
		dupliquer(m);
		return *this;
	}

/*
	//Méthode de convertion
	virtual matrice<double>* convertion() const {
		matriceDouble *md(matrice::nbL,matrice::nbC);
		for (int i=0; i<matrice::nbL; i++) {
			for (int j=0; j<matrice::nbC; j++)
					md->set(i,j,this->get(i,j));
			}
			return md;
	}
*/
};