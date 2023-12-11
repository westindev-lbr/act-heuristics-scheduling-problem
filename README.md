# TP 4 - Heuristiques - Problème d'ordonnancement

## Utilisation

### *Compilation :*

```shell
❯ make all
```

*Clean :*

```shell
❯ make clean
```

### *Exécution :*

```shell
❯ ./heuristik -f <file_name.txt> <mode>
```

- -random : Solution aléatoire
- -coef : Heuristique évaluation par coefficient
- -sjf : Heuristique priorité + temps d'éxécution puis tri du reste des tâches par temps d'éxécution le plus court
- -rpe : Heuristique tri par priorité desc puis tri asc par temps d'éxécution

*Exemple :*

```shell
❯ ./heuristik -f SMTWP/n100_15_b.txt -coef 
```

*Exemple 2 :*

```shell
❯ ./heuristik -f SMTWP/n100_35_b.txt -random 
````

```shell
# Output: 
❯ ./heuristik -f SMTWP/n100_35_b.txt -coef  

Test data : SMTWP/n100_35_b.txt
ExecTime: 1, Priority: 10, Deadline: 2275, CompletionTime: 1, Delay : 0, NormalizedExecTime : 1, NormalizedPriority : 1, NormalizedDeadline : 0.706257
ExecTime: 2, Priority: 10, Deadline: 2902, CompletionTime: 3, Delay : 0, NormalizedExecTime : 0.989796, NormalizedPriority : 1, NormalizedDeadline : 0.34299
ExecTime: 20, Priority: 10, Deadline: 2636, CompletionTime: 23, Delay : 0, NormalizedExecTime : 0.806122, NormalizedPriority : 1, NormalizedDeadline : 0.497103
ExecTime: 1, Priority: 8, Deadline: 1997, CompletionTime: 24, Delay : 0, NormalizedExecTime : 1, NormalizedPriority : 0.777778, NormalizedDeadline : 0.867323

 Somme Total des retards pondérés : 47629
```

