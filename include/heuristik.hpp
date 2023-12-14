#ifndef HEURISTIK_HPP
#define HEURISTIK_HPP

#include "task.hpp"
#include "scheduler.hpp"

#define COEF_EXTIME 0.430
#define COEF_WEIGHT 0.505
#define COEF_DEADLINE 0.065

// Tris décroissants par caractéristiques
struct DescSortByExecTime {
    inline bool operator() ( const Task& ltask, const Task& rtask ) const {
        return ltask.GetExecTime() > rtask.GetExecTime();
    }
};
struct DescSortByWeight {
    inline bool operator() ( const Task& ltask, const Task& rtask ) const {
        return ltask.GetWeight() > rtask.GetWeight();
    }
};
struct DescSortByDeadLine {
    inline bool operator() ( const Task& ltask, const Task& rtask ) const {
        return ltask.GetDeadline() > rtask.GetDeadline();
    }
};
struct AscSortByExecTime {
    inline bool operator() ( const Task& ltask, const Task& rtask ) const {
        return ltask.GetExecTime() < rtask.GetExecTime();
    }
};
struct AscSortByDeadLine {
    inline bool operator() ( const Task& ltask, const Task& rtask ) const {
        return ltask.GetDeadline() < rtask.GetDeadline();
    }
};
struct DescSortByWeightAndShortestExecTime {
    inline bool operator() ( const Task& ltask, const Task& rtask ) const {
        if ( ltask.GetWeight() == rtask.GetWeight() ) {
            return ltask.GetExecTime() < rtask.GetExecTime();
        }
        return ltask.GetWeight() > rtask.GetWeight();
    }
};

struct AscSortByWeightOfCriteria {
    inline bool operator() ( const Task& ltask, const Task& rtask ) const {
        double scoreL = COEF_EXTIME * ltask.GetNormalizedExecTime() + COEF_WEIGHT * ltask.GetNormalizedWeight() + COEF_DEADLINE * ltask.GetNormalizedDeadline();
        double scoreR = COEF_EXTIME * rtask.GetNormalizedExecTime() + COEF_WEIGHT * rtask.GetNormalizedWeight() + COEF_DEADLINE * rtask.GetNormalizedDeadline();
        return  scoreL > scoreR;
    }
};

int ComputeDelayFromScheduler( SchedulerTask& rScheduler );
void HillClimbing(SchedulerTask& initialNode);
void perturbation( SchedulerTask& scheduler );
bool IsAnAcceptanceCriterion( int rCurrentDelay, int rNewDelay, double rTemperature );
double UpdateTemperature(double rCurrentTemperature, int rIterations);
void iteratedLocalSearch( SchedulerTask& initialNode, int rMaxIterations, double rInitialTemperature );

#endif /* HEURISTIK_HPP */