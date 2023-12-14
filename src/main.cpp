#include <vector>
#include <iostream>
#include <fstream>
#include "../include/task.hpp"
#include "../include/scheduler.hpp"
#include "../include/heuristik.hpp"

#define MAX_ITERATIONS 1000
#define TEMPERATURE 80.0

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
    bool ils_mode = false;


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
        else if ( std::string( argv[i] ) == "-ils" ) {
            ils_mode = true;
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

    clock_t td, ta, tf;

    if ( random_mode ) {
        td = clock();
        scheduler_task.randomizeSchedule();
        ta=clock();
        tf = ta - td;
        std::cout << "Résultats algorithme random : " << std::endl;
    }
    else if ( ratio_weight_exectime_mode ) {
        td = clock();
        scheduler_task.SortByWeightAndShortestExecTime(); // 268302
        ta=clock();
        tf = ta - td;
        std::cout << "Résultats algorithme naïf (tri desc par poids puis tri asc par tps d'exécution) : " << std::endl;
    }
    else if ( coef_mode ) {
        td = clock();
        scheduler_task.NormalizeTaskProperties();
        scheduler_task.SortByWeightOfCriteria();
        ta=clock();
        tf = ta - td;
        std::cout << "Résultats algorithme coefficient de critères : " << std::endl;
    }
    else if ( shortest_job_first_mode ) {
        td = clock();
        scheduler_task.ShortestJobFirstHeuristik(); // Priority + Exec + AscExec 265543
        ta=clock();
        tf = ta - td;
        std::cout << "Résultats algorithme shortest_job_first : " << std::endl;
    }
    else if ( hillclimbing_mode ) {
        td = clock();
        HillClimbing( scheduler_task );
        ta=clock();
        tf = ta - td;
        std::cout << "Résultats algorithme HillClimbing(SwapTask) : " << std::endl;
    }
    else if ( ils_mode ) {
        td = clock();
        HillClimbing( scheduler_task );
        iteratedLocalSearch( scheduler_task, MAX_ITERATIONS, TEMPERATURE );
        ta=clock();
        tf = ta - td;
        std::cout << "Résultats algorithme ILS : " << std::endl;

    }
    else {
        std::cerr << "Aucune option valide spécifiée." << std::endl;
        return EXIT_FAILURE;
    }


    int result = ComputeDelayFromScheduler( scheduler_task );

    int val_optimale = 54612;
    std::cout << "Somme Total des retards pondérés : "
        << result << std::endl;
    std::cout << "Ecart relatif par rapport à la solution optimale : "
        << ( ( static_cast<double>(result) - val_optimale ) / val_optimale ) * 100.0 << "%" << std::endl;
    std::cout << "Le temps d'éxécution est de "
        << std::fixed << std::setprecision( 6 ) << ( ( float ) tf ) / CLOCKS_PER_SEC << " secondes" << std::endl;
    std::cout << "--------------------------------\n"<< std::endl; 
    return 0;
}