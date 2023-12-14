#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>

#define COEF_EXTIME 0.430
#define COEF_WEIGHT 0.505
#define COEF_DEADLINE 0.065

// Classe Tâche
class Task {
private:
    int mExecutionTime;
    int mWeight;
    int mDeadline;
    int mCompletionTime;
    int mDelay;
    double mNormalizedExecTime;
    double mNormalizedWeight;
    double mNormalizedDeadline;
public:
    Task( int rExecTime, int rWeight, int rDeadLine );

    // Getters
    int GetWeightedDelay() const;
    int GetExecTime() const;
    int GetWeight() const;
    int GetDeadline() const;
    double GetNormalizedExecTime() const;
    double GetNormalizedWeight() const;
    double GetNormalizedDeadline() const;

    // Setters
    void SetCompletionTime( int rTime );
    void SetNormalizedProperties( double rNe, double rNp, double rNd );

    // Methods
    void ComputeWeightedDelay();

    friend std::ostream& operator<<( std::ostream& os, const Task& task );
};

#endif /* TASK_HPP */