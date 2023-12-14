#include "../include/heuristik.hpp"
#include <algorithm>
#include <random>

#define COOLING_FACTOR 0.98
#define COOLDOWN_INTERVAL 100


void HillClimbing( SchedulerTask& initialNode ) {

    // Calcul du retard actuel de l'ordonnanceur
    // Noeud Initial
    SchedulerTask currentScheduler = initialNode;
    currentScheduler.ComputeDelay();
    int currentDelay = currentScheduler.GetSumOfWeightedDelay();

    // const int MAX_ITERATIONS = 1000;
    // const int MAX_CONSECUTIVE_FAILURES = 10;  // Ajustez selon vos besoins
    // int iterations = 0;
    // int consecutiveFailures = 0;

    while ( true) {
        bool bestNeighbourdFound = false;

        for ( int i = 0; i < initialNode.GetNbTasks(); i++ ) {
            for ( int j = 0; j < initialNode.GetNbTasks(); j++ ) {

                currentScheduler.SwapTasks( i, j );
                currentScheduler.CleanScheduler();
                currentScheduler.ComputeDelay();
                int newDelay = currentScheduler.GetSumOfWeightedDelay();

                if ( newDelay < currentDelay ) {
                    currentDelay = newDelay;
                    bestNeighbourdFound = true;
                }
                else {
                    // Annule l'échange de tâche
                    currentScheduler.SwapTasks( i, j );
                }
            }

        }
        // iterations++;

        if ( !bestNeighbourdFound ) break;
    }

    currentScheduler.CleanScheduler();
    initialNode = currentScheduler;
}

int ComputeDelayFromScheduler( SchedulerTask& rScheduler ) {
    rScheduler.CleanScheduler();
    rScheduler.ComputeDelay();
    return rScheduler.GetSumOfWeightedDelay();
}

// Fonction de perturbation (à adapter selon votre problème)
void perturbation( SchedulerTask& scheduler ) {



    int startIndex = 0;
    int endIndex = scheduler.GetNbTasks() - 1;
    scheduler.InvertSequence( startIndex, endIndex );

    int swapIndex1 = 0;
    int swapIndex2 = scheduler.GetNbTasks() -1;
    scheduler.SwapTasks(swapIndex1, swapIndex2);

    int moveRandTaskIndex = rand() % scheduler.GetNbTasks();
    int newMoveRandIndex;
    do {
        newMoveRandIndex = rand() % scheduler.GetNbTasks();
    } while (newMoveRandIndex == moveRandTaskIndex);
    scheduler.MoveTasks(moveRandTaskIndex, newMoveRandIndex);
}

// Critère d'acceptation
bool IsAnAcceptanceCriterion( int rCurrentDelay, int rNewDelay, double rTemperature ) {
    // Implémentation du critère d'acceptation, par exemple, Metropolis
    if ( rNewDelay < rCurrentDelay ) return true;

    double probability = exp( -( rNewDelay - rCurrentDelay ) / rTemperature );
    double randomValue = static_cast< double >( rand() ) / RAND_MAX;

    return randomValue < probability;
}

double UpdateTemperature(double rCurrentTemperature, int rIterations){
    // Stratégie de refroidissement : diminution linéaire

    double coolingFactor = COOLING_FACTOR; // un facteur de décroissance
    int cooldownInterval = COOLDOWN_INTERVAL;  // intervalle de diminutions en nb d'itérations

    // Diminuer la température toutes les cooldownInterval itérations
    if (rIterations % cooldownInterval == 0) {
        rCurrentTemperature *= coolingFactor;
    }

    return rCurrentTemperature;
}

// Fonction principale de l'ILS
void iteratedLocalSearch( SchedulerTask& initialNode, int rMaxIterations, double rInitialTemperature ) {
    SchedulerTask currentScheduler = initialNode;
    int currentDelay = ComputeDelayFromScheduler( currentScheduler );
    int bestSolution = currentDelay;

    for ( int i = 0; i < rMaxIterations; ++i ) {
        perturbation( currentScheduler );
        // Recherche locale Hill-Climbing
        HillClimbing( currentScheduler );

        int newDelay = ComputeDelayFromScheduler( currentScheduler );

        if ( IsAnAcceptanceCriterion( currentDelay, newDelay, rInitialTemperature ) ) {
            currentDelay = newDelay;
            if ( currentDelay < bestSolution ) {
                bestSolution = currentDelay;
                initialNode = currentScheduler;
            }
        }
        // Réduction de la température selon une stratégie définie
        rInitialTemperature = UpdateTemperature(rInitialTemperature, i);
        // std::cout << "DEBUG : " << rInitialTemperature << std::endl;
        // critère d'arrêt
        if ( i >= rMaxIterations ) {
            break;
        }
    }
}