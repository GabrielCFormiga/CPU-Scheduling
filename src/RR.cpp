#include "RR.hpp"

#define resposta 0
#define espera 1
#define retorno 2

typedef std::pair<size_t, size_t> pico; // {duracao, index do processo}

RR::RR(const std::vector<processo>& processos) : processos(processos) {
    tempos.resize(processos.size(), std::vector<size_t>(3));

    calcular_tempos();
}

void RR::calcular_tempos() {
    std::sort(processos.begin(), processos.end(), [](const processo& a, const processo& b) {
        return a.t_chegada < b.t_chegada;
    });

    std::queue<pico> fila_de_prontos; // index dos processos
    std::vector<bool> primeira_execucao(processos.size(), true);

    fila_de_prontos.push({processos[0].duracao, 0});

    size_t i_chegada = 1; // index do próximo processo a chegar
    size_t tempo_atual = processos[0].t_chegada;

    // calculo dos tempos
    // para o rr vou calcular o tempo de espera ao final, fazendo t_espera = t_retorno - t_duracao
    while (i_chegada < processos.size() || !fila_de_prontos.empty()) {
        while (i_chegada < processos.size() && (fila_de_prontos.empty() || processos[i_chegada].t_chegada <= tempo_atual)) {
            fila_de_prontos.push({processos[i_chegada].duracao, i_chegada});
            i_chegada++;
        }

        auto execucao = fila_de_prontos.front();
        fila_de_prontos.pop();

        if (primeira_execucao[execucao.second]) {
            primeira_execucao[execucao.second] = false;
            tempos[execucao.second][resposta] = tempo_atual - processos[execucao.second].t_chegada;
        }

        if (execucao.first <= quantum) {
            // processo executa completamente
            tempo_atual += execucao.first;
            tempos[execucao.second][retorno] = tempo_atual - processos[execucao.second].t_chegada;
            tempos[execucao.second][espera] = tempos[execucao.second][retorno] - processos[execucao.second].duracao;
        } else {
            // processo executa parcialmente e volta pra fila
            execucao.first -= quantum;
            tempo_atual += quantum;

            // processos que chegam antes ou ao mesmo tempo que o em execucao vai para o final da fila tem prioridade
            while (i_chegada < processos.size() && processos[i_chegada].t_chegada <= tempo_atual) {
                fila_de_prontos.push({processos[i_chegada].duracao, i_chegada});
                i_chegada++;
            }

            fila_de_prontos.push(execucao);
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

float RR::get_resposta_media() {
    return resposta_media;
}

float RR::get_espera_media() {
    return espera_media;
}

float RR::get_retorno_media() {
    return retorno_media;
}
