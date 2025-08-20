#ifndef RR_HPP
#define RR_HPP

#include "processo.hpp"
#include <vector>
#include <algorithm>
#include <queue>

class RR {
private:
    size_t quantum = 2;
    
    std::vector<processo> processos;

    std::vector<std::vector<size_t>> tempos;

    float resposta_media;
    float espera_media;
    float retorno_media;

    void calcular_tempos();

public:
    RR(const std::vector<processo>& processos);

    float get_resposta_media();
    float get_espera_media();
    float get_retorno_media();
};

#endif