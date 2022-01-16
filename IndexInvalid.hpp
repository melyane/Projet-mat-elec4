 /*  
 *  Définition de la classe "IndexInvalid"
 *  qui hérite de la classe "exception" et qui permet de 
 *  d'indiquer si les indices des matrices sont valides ou non 
 * 
 *  @author PEZ Mélanie / HATIER Joé
 * 
 */

 #pragma once

 #include <cstdlib>
 #include <iostream>
 #include <exception>

class IndexInvalid : public std::exception{
private:
    std::string msg;
public:
    IndexInvalid (const std::string s) : msg("Indice invalide : " + s){}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};                                                                            
      