#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include <vector>
#include <random>
#include "task.hpp"

/**
 * @class : SchedulerTask -> Ordonnanceur de tâches
 * @property:
*/
class SchedulerTask {
private:
    int mNbTasks;
    int mSumOfWeightedDelays;
    int mTime;
    std::vector<Task> mTasks;

public:
    SchedulerTask( int n );

    // Getter
    const std::vector<Task>& GetSchedule() const;
    int GetCompletionTime() const;
    int GetSumOfWeightedDelay() const;
    int GetNbTasks() const;

    // Setter
    void CleanScheduler();
    void AddTaskInSchedule( Task rTask );
    void AddTaskExecTime( int rTime );

    // Methods
    void ComputeDelay();
    void ShortestJobFirstHeuristik();
    void NormalizeTaskProperties();
    void randomizeSchedule();

    // Heuristiques de tri
    void SortByPriorityDesc();
    void SortByDeadLineAsc();
    void SortByExecTimeDesc();
    void SortByExecTimeAsc();
    void SortByPriorityAndShortestExecTime();
    void SortByWeightOfCriteria();
    void SortRemainingTasksByExecTime( int rCurrentIndex );
    // Perturbations
    void SwapTasks(int rIndex1, int rIndex2);
    void InvertSequence(int rIndex1, int rIndex2);
    void MoveTasks(int rIndex1, int rIndex2);
};

#endif /* SCHEDULER_HPP */
