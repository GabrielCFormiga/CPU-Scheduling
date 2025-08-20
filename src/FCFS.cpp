#include "FCFS.hpp"
#include <algorithm>

#define resposta 0
#define espera 1
#define retorno 2

FCFS::FCFS(const std::vector<processo>& processos) : processos(processos) {
    tempos.resize(processos.size(), std::vector<size_t>(3));

    calcular_tempos();
}

void FCFS::calcular_tempos() {
    std::sort(processos.begin(), processos.end(), [](const processo& a, const processo& b) {
        return a.t_chegada < b.t_chegada;
    });

    // tratamento do primeiro processo
    tempos[0][resposta] = 0;
    tempos[0][espera] = 0;
    tempos[0][retorno] = processos[0].duracao;

    // inicializacao e calculo dos tempos dos outros processos
    size_t tempo_atual = processos[0].t_chegada + processos[0].duracao;

    for (size_t i = 1; i < processos.size(); ++i) {
        tempos[i][resposta] = std::max(tempo_atual, processos[i].t_chegada) - processos[i].t_chegada;
        tempos[i][espera] = tempos[i][resposta];
        tempos[i][retorno] = tempos[i][espera] + processos[i].duracao;
        tempo_atual = std::max(tempo_atual, processos[i].t_chegada) + processos[i].duracao;
    }

    // calculos das medias
    float soma = 0;
    for (const auto &t : tempos) {
        soma += t[resposta];
    }
    resposta_media = soma / tempos.size();

    soma = 0;
    for (const auto &t : tempos) {
        soma += t[espera];
    }
    espera_media = soma / tempos.size();

    soma = 0;
    for (const auto &t : tempos) {
        soma += t[retorno];
    }
    retorno_media = soma / tempos.size();
}

float FCFS::get_resposta_media() {
    return resposta_media;
}

float FCFS::get_espera_media() {
    return espera_media;
}

float FCFS::get_retorno_media() {
    return retorno_media;
}
