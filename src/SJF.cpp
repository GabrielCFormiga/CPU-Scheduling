#include "SJF.hpp"
#include <queue>

#define resposta 0
#define espera 1
#define retorno 2

typedef std::pair<size_t, size_t> pico; // {duracao, index do processo}

SJF::SJF(const std::vector<processo>& processos) : processos(processos) {
    tempos.resize(processos.size(), std::vector<size_t>(3));

    calcular_tempos();
}

void SJF::calcular_tempos() {
    std::sort(processos.begin(), processos.end(), [](const processo& a, const processo& b) {
        return a.t_chegada < b.t_chegada;
    });

    std::priority_queue<pico, std::vector<pico>, std::greater<pico>> fila_de_prontos;
    
    size_t i_chegada = 0; // index do próximo processo a chegar
    size_t tempo_atual = 0;

    while (i_chegada < processos.size() || !fila_de_prontos.empty()) {
        if (i_chegada < processos.size() && fila_de_prontos.empty()) {
            fila_de_prontos.push({processos[i_chegada].duracao, i_chegada});
            tempo_atual = processos[i_chegada].t_chegada;
            i_chegada++;
        }

        while (i_chegada < processos.size() && processos[i_chegada].t_chegada <= tempo_atual) {
            fila_de_prontos.push({processos[i_chegada].duracao, i_chegada});
            i_chegada++;
        }

        auto execucao = fila_de_prontos.top();
        fila_de_prontos.pop();
        
        tempos[execucao.second][resposta] = std::max(tempo_atual, processos[execucao.second].t_chegada) - processos[execucao.second].t_chegada;
        tempos[execucao.second][espera] = tempos[execucao.second][resposta];
        tempos[execucao.second][retorno] = tempos[execucao.second][resposta] + processos[execucao.second].duracao;
        tempo_atual += processos[execucao.second].duracao;
        
        while (i_chegada < processos.size() && processos[i_chegada].t_chegada <= tempo_atual) {
            fila_de_prontos.push({processos[i_chegada].duracao, i_chegada});
            i_chegada++;
        }
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

float SJF::get_resposta_media() {
    return resposta_media;
}

float SJF::get_espera_media() {
    return espera_media;
}

float SJF::get_retorno_media() {
    return retorno_media;
}
