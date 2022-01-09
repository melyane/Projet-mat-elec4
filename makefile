CC = g++           # le compilateur à utiliser
CFLAGS = -Wall     # les options du compilateur
LDFLAGS = -lsx     # les options pour l’éditeur de liens
SRC = main.cpp # les fichiers sources
PROG = main # nom de l’exécutable
OBJS = $(SRC:.c=.o) # les .o qui en découlent
.SUFFIXES: .cpp .o    # lien entre les suffixes

all: $(PROG)

# étapes de compilation et d’édition de liens
# $@ la cible $^ toutes les dépendances
$(PROG): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

matrice.o: matrice.hpp
IndexInvalid.o: IndexInvalid.hpp
matriceDouble.o: matriceDouble.hpp matrice.hpp
main.o: matrice.hpp matriceDouble.hpp IndexInvalid.hpp

# le lien entre .o et .cpp
# $< dernière dépendance
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

# pour faire propre
.PHONY: clean
clean:
	rm -f *.o *~ core a.out $(PROG)

