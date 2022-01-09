#pragma once
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <sstream>

#include "matrice.hpp"
#include "IndexInvalid.hpp" 

class matriceCreuse : public matrice<double> {
protected:

public:
	matriceCreuse (const int n, const int m) : matrice (n,m), mat(new double [matrice::nbElem]){
		for (int i = 0; i < matrice::nbElem; i++) {
			mat[i] = 0.0;
		}
	}
	
};