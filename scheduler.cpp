#include "scheduler.hpp"
#include "heuristik.hpp"


// Implementation de la classe SchedulerTask ======
SchedulerTask::SchedulerTask( int n ) {
    this->mNbTasks = n;
    this->mSumOfWeightedDelays = 0;
    this->mTime = 0;
}


int SchedulerTask::GetCompletionTime()      const {
    return this->mTime;
}
int SchedulerTask::GetSumOfWeightedDelay()  const {
    return this->mSumOfWeightedDelays;
}
int SchedulerTask::GetNbTasks()             const {
    return this->mNbTasks;
}
const std::vector<Task>& 
SchedulerTask::GetSchedule()                const {
    return this->mTasks;
}


void SchedulerTask::CleanScheduler() {
    this->mSumOfWeightedDelays = 0;
    this->mTime = 0;
}


void SchedulerTask::AddTaskInSchedule( Task rTask ) {
    this->mTasks.push_back( rTask );
}

void SchedulerTask::AddTaskExecTime( int rTime ) {
    this->mTime += rTime;
}

/**
 * Calcul le retard de l'ordonnanceur
 * Parcours toutes les tâches
 * - Accumule le temps d'éxécution de la totalité des tâches
 * - Met à jour le temps de complétion de la tâche
 * - Calcule le retard pondéré de la tâche
 * - Accumule les retards de la totalité des tâches
*/
void  SchedulerTask::ComputeDelay() {
    for ( auto& it : this->mTasks ) {
        this->mTime += it.GetExecTime();
        it.SetCompletionTime( this->mTime );
        it.ComputeWeightedDelay();
        this->mSumOfWeightedDelays += it.GetWeightedDelay();
    }
}

void SchedulerTask::randomizeSchedule() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle( this->mTasks.begin(), this->mTasks.end(), std::default_random_engine( seed ) );

}

void SchedulerTask::NormalizeTaskProperties() {
    // Tri par temps d'exécution ascendant pour trouver les valeurs min et max
    this->SortByExecTimeAsc();
    double minExecTimeValue = static_cast< double >( this->mTasks[0].GetExecTime() );
    double maxExecTimeValue = static_cast< double >( this->mTasks[this->mNbTasks - 1].GetExecTime() );

    // Tri par priorité descendant pour trouver les valeurs min et max
    this->SortByPriorityDesc();
    double minPriorityValue = static_cast< double >( this->mTasks[this->mNbTasks - 1].GetPriority() );
    double maxPriorityValue = static_cast< double >( this->mTasks[0].GetPriority() );

    // Tri par date limite ascendante pour trouver les valeurs min et max
    this->SortByDeadLineAsc();
    double minDeadLine = static_cast< double >( this->mTasks[0].GetDeadline() );
    double maxDeadLine = static_cast< double >( this->mTasks[this->mNbTasks - 1].GetDeadline() );

    for ( auto& task : this->mTasks ) {
        // Inversion de la normalisation du temps d'éxécution afin que les valeurs plus petites offrent un meilleur score
        double ne = 1.0 - ( static_cast< double >( task.GetExecTime() ) - minExecTimeValue ) / ( maxExecTimeValue - minExecTimeValue );
        double np = ( static_cast< double >( task.GetPriority() ) - minPriorityValue ) / ( maxPriorityValue - minPriorityValue );
        // Inversion de la normalisation de la deadline afin que les valeurs plus petites offrent un meilleur score
        double nd = 1.0 - ( static_cast< double >( task.GetDeadline() ) - minDeadLine ) / ( maxDeadLine - minDeadLine );
        task.SetNormalizedProperties( ne, np, nd );
    }
}

// Fonction pour échanger deux tâches dans la séquence
void SchedulerTask::SwapTasks( int rIndex1, int rIndex2 ) {
    if ( rIndex1 >= 0 && rIndex1 < this->mNbTasks && rIndex2 >= 0 && rIndex2 < this->mNbTasks ) {
        std::swap( this->mTasks[rIndex1], this->mTasks[rIndex2] );
    }
    else {
        std::cerr << "Indices de tâches invalides pour l'échange." << std::endl;
    }
}

void  SchedulerTask::ShortestJobFirstHeuristik() {
    // Tri par priorité puis plus petit temps d'éxécution
    this->SortByPriorityAndShortestExecTime();
    bool hasSortedRemainedTask = false;

    int index = 0;
    for ( auto& it : this->mTasks ) {
        this->mTime += it.GetExecTime();
        it.SetCompletionTime( this->mTime );
        it.ComputeWeightedDelay();
        this->mSumOfWeightedDelays += it.GetWeightedDelay();
        // Si retard changer de stratégie en triant le reste des tâches par temps d'éxécution uniquement
        if ( it.GetWeightedDelay() > 0 && !hasSortedRemainedTask ) {
            this->SortRemainingTasksByExecTime( index + 1 );
            std::cout << "Last task before delay : " << it << "\n" << std::endl;
            hasSortedRemainedTask = true;
        }
        index++;
    }
}

// Methodes de tris par caractéristiques
void SchedulerTask::SortByExecTimeDesc() {
    std::sort( this->mTasks.begin(), this->mTasks.end(), DescSortByExecTime() );
}
void SchedulerTask::SortByExecTimeAsc() {
    std::sort( this->mTasks.begin(), this->mTasks.end(), AscSortByExecTime() );
}
void SchedulerTask::SortByPriorityDesc() {
    std::sort( this->mTasks.begin(), this->mTasks.end(), DescSortByPriority() );
}
void SchedulerTask::SortByDeadLineAsc() {
    std::sort( this->mTasks.begin(), this->mTasks.end(), AscSortByDeadLine() );
}
void SchedulerTask::SortByPriorityAndShortestExecTime() {
    std::sort( this->mTasks.begin(), this->mTasks.end(), DescSortByPriorityAndShortestExecTime() );
}

void SchedulerTask::SortByWeightOfCriteria() {
    std::sort( this->mTasks.begin(), this->mTasks.end(), AscSortByWeightOfCriteria() );
}

// Tri les tâches restantes à partir d'un index passé en paramètre
void SchedulerTask::SortRemainingTasksByExecTime( int rCurrentIndex ) {
    std::sort( this->mTasks.begin() + rCurrentIndex, this->mTasks.end(), AscSortByExecTime() );
}