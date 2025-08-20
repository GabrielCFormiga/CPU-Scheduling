#ifndef SJF_HPP
#define SJF_HPP

#include "processo.hpp"
#include <vector>
#include <algorithm>
class SJF {
private:
    std::vector<processo> processos;
    
    std::vector<std::vector<size_t>> tempos;
    
    float resposta_media;
    float espera_media;
    float retorno_media;

    void calcular_tempos();

public:
    SJF(const std::vector<processo>& processos);

    float get_resposta_media();
    float get_espera_media();
    float get_retorno_media();
};

#endif