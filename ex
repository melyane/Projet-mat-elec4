		if (i2 > matrice::nbL)
			throw IndexInvalid ("i2 supérieur au nombre de ligne");
		if (j2 > matrice::nbC)
			throw IndexInvalid ("j2 supérieur au nombre de colonne");
		if (i1 < 0)
			throw IndexInvalid ("i1 < 0");
		if (j1 < 0)
			throw IndexInvalid ("j1 < 0");
