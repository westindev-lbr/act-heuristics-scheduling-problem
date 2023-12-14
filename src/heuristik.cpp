#include "../include/heuristik.hpp"
#include <algorithm>
#include <random>



void HillClimbing( SchedulerTask& initialNode ) {
    // Calcul du retard actuel de l'ordonnanceur
    // Noeud Initial
    SchedulerTask currentScheduler = initialNode;
    currentScheduler.ComputeDelay();
    int currentDelay = currentScheduler.GetSumOfWeightedDelay();

    while ( true ) {
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
        if ( !bestNeighbourdFound ) break;
    }
    currentScheduler.CleanScheduler();
    initialNode = currentScheduler;
}

int ComputeDelayFromScheduler( SchedulerTask& rScheduler ) {
    rScheduler.ComputeDelay();
    return rScheduler.GetSumOfWeightedDelay();
}