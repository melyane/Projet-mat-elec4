#pragma once
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <sstream>

#include "matrice.hpp"
#include "IndexInvalid.hpp" 

class matriceDouble : public matrice<double> {
protected:
	double * mat;
	void dupliquer (const matriceDouble &m) {
		this->mat = new double [matrice::nbElem];
		for (int i = 0; i < matrice::nbElem; i++)
			this->mat[i] = m.mat[i];
	} 
public:
	//Constructeur
	matriceDouble (const int n, const int m) : matrice (n,m), mat(new double [matrice::nbElem]){
		for (int i = 0; i < matrice::nbElem; i++) {
			mat[i] = 0.0;
		}
	}

	//Constructeur de copie
	matriceDouble (const matriceDouble &m) {
		dupliquer (m);
	}

	//Destructeur
	~matriceDouble() {
		delete[] mat;
	}

	//Méthode virtuelle get
	virtual double get (const int i, const int j) const override {
		assert (i <= matrice::nbL && j <= matrice::nbC);
		return this->mat[i*matrice::nbC+j];
	}

	//Méthode virtuelle set
	virtual void set (const int i, const int j, const double &x) override{
		assert (i <= matrice::nbL && j <= matrice::nbC);
		this->mat[i*matrice::nbC+j] = x;
	}
	
	//Méthode virtuelle toString
	virtual std::string toString () const {
		std::ostringstream s;
		s << " ";
		for (int i = 0; i < matrice::nbL; i++){
			for(int j = 0; j < matrice::nbC; j++){
				s << " " << get(i,j) << " ";
			}
			s << "\n ";
		}
		return s.str();
	}
	
	//surcharge de l'opérateur d'affectation
	matriceDouble &operator=(const matriceDouble &m) {
		dupliquer(m);
		return *this;
	};

	//la surcharge de l'opérateur << n'est pas nécessaire 
	//car elle est déjà présente dans la classe mère

	//Rajout question 5
	virtual matrice<double>* submat (const int i1, const int i2, const int j1, const int j2) {
		if (i1 > i2)
			throw IndexInvalid ("i1 > i2");
		if (j1 > j2)
			throw IndexInvalid ("j1 > j2");

		matrice<double> *m = new matriceDouble(i2-i1+1, j2-j1+1);
		int a=0,b;

		for(int x = i1-1; x < i2; x++){
			b=0;
			for(int y = j1-1; y < j2; y++)
				m->set(get(x, y), a, b++);
			a++;
		}
		return m;
	}
};