#include "../include/task.hpp"

std::ostream& operator<<( std::ostream& os, const Task& task ) {
    os << "ExecTime: " << task.mExecutionTime
        << ", Priority: " << task.mWeight
        << ", Deadline: " << task.mDeadline
        << ", CompletionTime: " << task.mCompletionTime
        << ", Delay : " << task.mDelay
        << ", NormalizedExecTime : " << task.mNormalizedExecTime
        << ", NormalizedPriority : " << task.mNormalizedWeight
        << ", NormalizedDeadline : " << task.mNormalizedDeadline;
    return os;
}

/**
 * Constructeur de la classe Task
 * @param rExecTime : Temps d'éxécution
 * @param rPriority : Importance de la tâche
 * @param rDeadLine : Date limite de complétion d'une tâche
*/
Task::Task( int rExecTime, int rPriority, int rDeadLine ) {
    this->mExecutionTime = rExecTime;
    this->mWeight = rPriority;
    this->mDeadline = rDeadLine;
    this->mCompletionTime = 0;
    this->mDelay = 0;
    this->mNormalizedExecTime = 0.0;
    this->mNormalizedWeight = 0.0;
    this->mNormalizedDeadline = 0.0;
}

int Task::GetWeightedDelay() const {
    return this->mDelay;
}

int Task::GetExecTime() const {
    return this->mExecutionTime;
}
int Task::GetWeight() const {
    return this->mWeight;
}
int Task::GetDeadline() const {
    return this->mDeadline;
}

double Task::GetNormalizedExecTime() const {
    return this->mNormalizedExecTime;
}
double Task::GetNormalizedWeight() const {
    return this->mNormalizedWeight;
}
double Task::GetNormalizedDeadline() const {
    return this->mNormalizedDeadline;
}


void Task::SetCompletionTime( int rTime ) {
    this->mCompletionTime = rTime;
}

void Task::ComputeWeightedDelay() {
    this->mDelay = std::max( this->mCompletionTime - this->mDeadline, 0 ) * this->mWeight;
}

void Task::SetNormalizedProperties( double rNe, double rNp, double rNd ) {
    this->mNormalizedExecTime = rNe;
    this->mNormalizedWeight = rNp;
    this->mNormalizedDeadline = rNd;
}
