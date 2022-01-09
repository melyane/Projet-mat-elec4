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
	double * mat;
	int * ligne;
	int * colonne;
	int nbElemCreuse;
	void dupliquer (const matriceCreuse &m) {
		this->mat = new double[nbElemCreuse];
		this->ligne = new int[nbElemCreuse];
		this->colonne = new int[nbElemCreuse];
		for (int k=0; k<nbElemCreuse; k++) {
			this->mat[k] = m.mat[k];
			this->ligne[k] = m.ligne[k];
			this->colonne[k] = m.colonne[k];
		}
	}

public:
	//Constructeur
	matriceCreuse (const int n, const int m) : matrice (n,m), mat(new double [nbElemCreuse]), ligne(new int [nbElemCreuse]), colonne(new int [nbElemCreuse]){
		nbElemCreuse = int (matrice::nbElem*0.1);
		for (int k=0; k<nbElemCreuse; k++) {
			mat[k] = 0.0;
			colonne[k] = -1;
			ligne[k] = -1;
		}
	}

	//Destructeur
	~matriceDouble() {
		delete[] mat;
		delete[] ligne;
		delete[] colonne;
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
			if (this->ligne[k]==i && this->colonne[k]==j)
				return this->mat[i];
		}
		return 0.0;
	}

	//Méthode virtuelle set
	virtual void set (const int i, const int j, const double &x) const override {
		if (i > matrice::nbL)
			throw IndexInvalid ("i > nb Ligne");
		if (j > matrice::nbC)
			throw IndexInvalid("j > nb Colonne");
		
		if (x==0) {
			for (int k=0; k<nbElemCreuse; k++){
				if(this->ligne[k]==i && this->colonne[k]==j){
					//this->mat[k]=0.0;
					this->ligne[k]=-1;
					this->colonne[k]=-1;
				}
			}
		}

		else {
			int test = 1;
			for (int k=0; k<nbElemCreuse; k++){
				if(this->ligne[k]==i && this->colonne[k]==j){
					this->mat[k]=x;
					test=0;
				}
			}
			if (test) {
				for (int k=0; k<nbElemCreuse; k++){
					if(this->ligne[k]==-1) {
						this->mat[k]=x;
						this->ligne[k]=i;
						this->colonne[k]=j;
					}
				}
			}
			else
				throw ErreurMatriceCreuse ("Nombre maximum d'éléments atteint dans la matrice creuse");
		}
	}

	//Méthode virtuelle toString
	virtual std::string toString () const {
		std::ostringstream s;
		s << " ";
		for (int x=0; x<matrice::nbL; x++){
			for(int y=0; y<matrice::nbC; y++){
				s << " " << get(x,y) << " ";
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
};