# TP 4 - Heuristiques - Problème d'ordonnancement

## Utilisation

### *Compiler :*

```shell
❯ make all
```

### *Clean :*

```shell
❯ make clean
```

### *Exécution :*

```shell
❯ cd bin
❯ ./heuristik -f <../tests/SMTWP/file_name.txt> <mode>
```

__Liste des modes :__

- -random : Solution aléatoire
- -coef : Heuristique évaluation par coefficient
- -sjf : Heuristique priorité + temps d'éxécution puis tri du reste des tâches par temps d'éxécution le plus court
- -rpe : Heuristique tri par priorité desc puis tri asc par temps d'éxécution
- -hillc : Recherche Hill-Climbing
- ils : Recherche Locale itérée

*Exemple :*

```shell
❯ ./heuristik -f ../tests/SMTWP/n100_15_b.txt -hillc
```

*Exemple 2 :*

```shell
❯ ./heuristik -f ../tests/SMTWP/n100_35_b.txt -random
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
