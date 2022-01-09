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
      