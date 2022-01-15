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

	void dupliquer (const matriceCreuse &m) {
		this->mat = new double[nbElemCreuse];
		this->indice = new int[nbElemCreuse];
		for (int k=0; k<nbElemCreuse; k++) {
			this->mat[k] = m.mat[k];
			this->indice[k] = m.indice[k];
		}
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
		// si l'indice n'est pas référencé
		if (x==0) 
			test = 0;
		else {	
			if(test==1) {
				for (int k=0; k<nbElemCreuse; k++){
					if(this->indice[k]==-1) {
						this->mat[k]=x;
						this->indice[k]=i*matrice::nbC+j;
						test=0; break;
					}
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

	//Méthode subat
	virtual matrice<double>* submat (const int i1, const int i2, const int j1, const int j2) {
		if (i1 > i2)
			throw IndexInvalid ("i1 > i2");
		if (j1 > j2)
			throw IndexInvalid ("j1 > j2");
		if (j2 > matrice::nbC || i2 > matrice::nbL)
			throw IndexInvalid ("i2 > nbL ou j2 > nbC");
		if (i1 < 0 || j1 < 0)
			throw IndexInvalid ("i1 ou j1 négatif");

		matrice<double> *m = new matriceCreuse(i2-i1+1, j2-j1+1);

		double e;
		for(int x=i1; x<=i2; x++){
			for(int y=j1; y<=j2; y++) {
				e=get(x, y);
				if (e!=0)
					m->set(x-i1, y-j1, e);
			}
		}
		return m;
	}
};
