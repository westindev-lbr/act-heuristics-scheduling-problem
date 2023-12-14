#include <vector>
#include <iostream>
#include <fstream>
#include "../include/task.hpp"
#include "../include/scheduler.hpp"
#include "../include/heuristik.hpp"

template <typename T>
void display( const std::vector<T>& vec ) {
    for ( const auto& it : vec ) {
        std::cout << it << "\n";
    }
    std::cout << "\n";
}


int main( int argc, char* argv[] ) {

    // ╔ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ╗
    //                        File system
    // ╚ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ═ ╝
    std::string file_name;
    bool random_mode = false;
    bool coef_mode = false;
    bool shortest_job_first_mode = false;
    bool ratio_weight_exectime_mode = false;
    bool hillclimbing_mode = false;


    for ( int i = 1; i < argc; i++ ) {
        if ( std::string( argv[i] ) == "-f" && i + 1 < argc ) {
            file_name = argv[i + 1];
            i++;
        }
        else if ( std::string( argv[i] ) == "-random" ) {
            random_mode = true;
        }
        else if ( std::string( argv[i] ) == "-naif" ) {
            ratio_weight_exectime_mode = true;
        }
        else if ( std::string( argv[i] ) == "-coef" ) {
            coef_mode = true;
        }
        else if ( std::string( argv[i] ) == "-sjf" ) {
            shortest_job_first_mode = true;
        }
        else if ( std::string( argv[i] ) == "-hillc" ) {
            hillclimbing_mode = true;
        }
    }

    if ( !file_name.empty() ) {
        std::cout << "Test data : " << file_name << std::endl;
    }
    else {
        std::cerr << "L'option -f est requise." << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream file( file_name );

    if ( !file ) {
        std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
        return EXIT_FAILURE;
    }


    int nb_tasks;
    file >> nb_tasks;

    // Ordonnanceur init avec nb de tâches
    SchedulerTask scheduler_task { nb_tasks };

    // Lecture du fichier de test et ajout des tâches dans l'ordonnanceur
    while ( file ) {
        int exec_time;
        int priority;
        int deadline;
        file >> exec_time >> priority >> deadline;
        Task current_task { exec_time, priority, deadline };
        scheduler_task.AddTaskInSchedule( current_task );
    }

    if ( random_mode ) {
        scheduler_task.randomizeSchedule();
        scheduler_task.SortByWeightAndShortestExecTime(); // 268302
    }
    else if ( coef_mode ) {
        scheduler_task.NormalizeTaskProperties();
        scheduler_task.SortByWeightOfCriteria();
    }
    else if ( shortest_job_first_mode ) {
        scheduler_task.ShortestJobFirstHeuristik(); // Priority + Exec + AscExec 265543
    }
    else if ( ratio_prio_exectime_mode ) {
        scheduler_task.SortByPriorityAndShortestExecTime(); // 268302
    }
    else if ( hillclimbing_mode ) {
        HillClimbing( scheduler_task );
    }
    else {
        std::cerr << "Aucune option valide spécifiée." << std::endl;
        return EXIT_FAILURE;
    }
    // scheduler_task.SortByExecTime(); // 874128
    // scheduler_task.SortByPriorityDesc(); // 286436
    // scheduler_task.SortByDeadLineDesc(); // 518709
    // scheduler_task.SortByDeadLineAsc(); // 503762
    // scheduler_task.SortByExecTimeAsc(); // 300416


    int result = ComputeDelayFromScheduler( scheduler_task );
    display( scheduler_task.GetSchedule() );
    // std::cout << "\n Temps de retard : " << scheduler_task.GetSumOfWeightedDelay() << std::endl;
    std::cout << "\n Somme Total des retards pondérés : " << result << std::endl;

    return 0;
}