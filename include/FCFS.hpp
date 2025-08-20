#ifndef FCFS_HPP
#define FCFS_HPP

#include <processo.hpp>
#include <vector>

class FCFS {
private:
    std::vector<processo> processos;

    // para o i-ésimo processo
    // t[i][0] := tempo de resposta
    // t[i][1] := tempo de espera
    // t[i][2] := tempo de retorno
    std::vector<std::vector<size_t>> tempos;

    float resposta_media;
    float espera_media;
    float retorno_media;

    void calcular_tempos();
    
public:    
    FCFS(const std::vector<processo>& processos);
    
    float get_resposta_media();
    float get_espera_media();
    float get_retorno_media();
};

#endif