 /*  
 *  Définition de la classe "ErreurMatriceCreuse"
 *  qui hérite de la classe "exception" et qui permet de 
 *  controler la validité d'une matrice creuse 
 *  (indices / nombre d'elements...) 
 * 
 *  @author PEZ Mélanie / HATIER Joé
 * 
 */

 #pragma once

 #include <cstdlib>
 #include <iostream>
 #include <exception>

class ErreurMatriceCreuse : public std::exception{
private:
    std::string msg;
public:
    ErreurMatriceCreuse (const std::string s) : msg("Erreur matrice creuse : " + s){}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};   