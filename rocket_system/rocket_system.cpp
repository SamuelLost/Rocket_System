/*
    rocket_system.cpp

    Trabalho de Sistemas Operacionais II

    Modelagem de um sistema básico de Foguete
    utilizando o algoritmo RM (Rate Monotonic).
    
    Tabelinha:

            | Ci |  Ti |
    Task 1  | 30 |  50 |
    Task 2  | 20 | 100 |
    Task 3  | 20 | 120 |
 */

#define HIPERPERIODO 600
#define SYNC 0
#define T1 50
#define D1 50
#define T2 100
#define D2 100
#define T3 120
#define D3 120

// Cabeçalhos das Classes da Biblioteca RTlib
#include <kernel.hpp>
#include <fpsched.hpp>
#include <jtrace.hpp>
#include <texttrace.hpp>
#include <rttask.hpp>

// Escopo das Classes
using namespace MetaSim;
using namespace RTSim;

int main(void){
    
    cout << "Bem vindo! Verificando tudo:" << endl;

    // Cria um arquivo com a escala em formato de texto
    TextTrace ttrace("trace.txt");
    
    // Cria o escalonador RM e o kernel de tempo real
    FPScheduler fpsched;
    RTKernel kern(&fpsched);
    
    // Cria três tasks

    /* t1 tem periodo 50, deadline relativo 50, inicia em 0,
       e se chama "Task 1" */
    cout << "Criando Task 1;" << endl;
    PeriodicTask t1(T1, D1, SYNC, "Task 1");
    
    // Ajusta o WCET da Task 1 para 30
    t1.insertCode("fixed(30);");

    // Ajusta para task Hard
    t1.killOnMiss(true);

    /* t2 tem periodo 100, deadline relativo 100, inicia em 0,
       e se chama "Task 2" */
    cout << "Criando Task 2;" << endl;
    PeriodicTask t2(T2, D2, SYNC, "Task 2");
    
    // Ajusta o WCET da Task 2 para 20
    t2.insertCode("fixed(20);");

    /* t3 tem periodo 120, deadline relativo 120, inicia em 0,
       e se chama "Task 3" */
    cout << "Criando Task 3;" << endl;
    PeriodicTask t3(T3, D3, SYNC, "Task 3");
    
    // Ajusta o WCET da Task 3 para 20
    t3.insertCode("fixed(20);");

    // Adiciona as tasks a escala 
    ttrace.attachToTask(t1);
    ttrace.attachToTask(t2);
    ttrace.attachToTask(t3);
    
    // Adiciona as tasks ao kernel
    kern.addTask(t1,"");
    kern.addTask(t2,"");
    kern.addTask(t3,"");
    
    cout << "Ok! Vamos começar a simulação." << endl << endl;

    try {
        // Executa a simulação por 600 unidades de tempo
        SIMUL.run(HIPERPERIODO);
        cout << endl << "Tudo certo!" << endl;
    }
    catch (BaseExc &e) {
        cout << "Opa, ouve um erro..." << endl;
        cout << e.what() << endl;
    }
}
