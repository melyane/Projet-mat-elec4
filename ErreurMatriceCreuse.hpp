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