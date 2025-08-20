#include "SJF.hpp"

#define resposta 0
#define espera 1
#define retorno 2

SJF::SJF(const std::vector<processo>& processos) : processos(processos) {
    tempos.resize(processos.size(), std::vector<size_t>(3));

    calcular_tempos();
}

void SJF::calcular_tempos() {
    std::sort(processos.begin(), processos.end(), [](const processo& a, const processo& b) {
        return a.t_chegada < b.t_chegada;
    });
    
    // tratamento dos primeiros processos
    fila_de_prontos.push({processos[0].duracao, 0});

    size_t i_chegada = 1; // index do próximo processo a chegar

    for (i_chegada; i_chegada < processos.size(); ++i_chegada) {
        if (processos[i_chegada].t_chegada > processos[0].t_chegada) break;
        fila_de_prontos.push({processos[i_chegada].duracao, i_chegada});
    }

    auto execucao = fila_de_prontos.top();
    fila_de_prontos.pop();

    tempos[execucao.second][resposta] = 0;
    tempos[execucao.second][espera] = 0;
    tempos[execucao.second][retorno] = processos[execucao.second].duracao;

    // inicializacao e calculo dos tempos dos outros processos
    size_t tempo_atual = processos[execucao.second].t_chegada + processos[execucao.second].duracao;

    while (i_chegada < processos.size() || !fila_de_prontos.empty()) {
        while (i_chegada < processos.size() && processos[i_chegada].t_chegada <= tempo_atual) {
            fila_de_prontos.push({processos[i_chegada].duracao, i_chegada});
            i_chegada++;
        }

        if (fila_de_prontos.empty()) {
            // a fila de prontos estava vazia e o proximo processo a chegar executa imediatamente
            // eh impossivel a filar de prontos estar vazia aqui com i_chegada == processos.size()
            tempos[i_chegada][resposta] = 0;
            tempos[i_chegada][espera] = 0;
            tempos[i_chegada][retorno] = processos[i_chegada].duracao;
            tempo_atual = processos[i_chegada].t_chegada + processos[i_chegada].duracao;
            i_chegada++;
        } else {
            // a fila nao estava vazia, entao executamos o proximo processo imediatamente
            execucao = fila_de_prontos.top();
            fila_de_prontos.pop();

            tempos[execucao.second][resposta] = std::max(tempo_atual, processos[execucao.second].t_chegada) - processos[execucao.second].t_chegada;
            tempos[execucao.second][espera] = tempos[execucao.second][resposta];
            tempos[execucao.second][retorno] = tempos[execucao.second][resposta] + processos[execucao.second].duracao;
            tempo_atual += processos[execucao.second].duracao;
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
