#ifndef HEURISTIK_HPP
#define HEURISTIK_HPP

#include "task.hpp"
#include "scheduler.hpp"

#define COEF_EXTIME 0.430
#define COEF_PRIORITY 0.505
#define COEF_DEADLINE 0.065

// Tris décroissants par caractéristiques
struct DescSortByExecTime {
    inline bool operator() ( const Task& ltask, const Task& rtask ) const {
        return ltask.GetExecTime() > rtask.GetExecTime();
    }
};
struct DescSortByPriority {
    inline bool operator() ( const Task& ltask, const Task& rtask ) const {
        return ltask.GetPriority() > rtask.GetPriority();
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
struct DescSortByPriorityAndShortestExecTime {
    inline bool operator() ( const Task& ltask, const Task& rtask ) const {
        if ( ltask.GetPriority() == rtask.GetPriority() ) {
            return ltask.GetExecTime() < rtask.GetExecTime();
        }
        return ltask.GetPriority() > rtask.GetPriority();
    }
};

struct AscSortByWeightOfCriteria {
    inline bool operator() ( const Task& ltask, const Task& rtask ) const {
        double scoreL = COEF_EXTIME * ltask.GetNormalizedExecTime() + COEF_PRIORITY * ltask.GetNormalizedPriority() + COEF_DEADLINE * ltask.GetNormalizedDeadline();
        double scoreR = COEF_EXTIME * rtask.GetNormalizedExecTime() + COEF_PRIORITY * rtask.GetNormalizedPriority() + COEF_DEADLINE * rtask.GetNormalizedDeadline();
        return  scoreL > scoreR;
    }
};

int ComputeDelayFromScheduler( SchedulerTask& rScheduler );
void HillClimbing(SchedulerTask& initialNode);

#endif /* HEURISTIK_HPP */