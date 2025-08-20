#include "FCFS.hpp"
#include "SJF.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

vector<processo> leitura_processos(const string& caminho) {
    ifstream arquivo(caminho);
    vector<processo> processos;
    processo p;

    while (arquivo >> p.t_chegada >> p.duracao) {
        processos.push_back(p);
    }

    arquivo.close();
    return processos;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <caminho_do_arquivo>" << std::endl;
        return 1;
    }

    std::vector<processo> processos = leitura_processos(argv[1]);
    
    FCFS fcfs(processos);
    SJF sjf(processos);

    cout << fixed << setprecision(1);
    cout << "FCFS\t" << fcfs.get_retorno_media() << "\t" 
         << fcfs.get_resposta_media() << "\t" 
         << fcfs.get_espera_media() << endl;
    
    cout << "SJF\t" << sjf.get_retorno_media() << "\t" 
         << sjf.get_resposta_media() << "\t" 
         << sjf.get_espera_media() << endl;

    return 0;
}