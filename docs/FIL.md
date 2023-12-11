# TP - Heuristique

Proposer 2 heuristiques

1 naïve  et 1 plus avancée

A construire un ordonenecment ( une permutation des numéros des tâches )

Fournir un tableau de n valeurs

## Fichiers d'instances

Chaque fichier d'instances contient les n+1 lignes suivantes :

- la première ligne indique le nombre de tâches n
- Chacune des n lignes suivantes (i : {1..n}) contient trois valeurs correspondant respectivement à pi (le temps d'execution), wi (le poids) et di (la date limite), de la tâche i.

Exemple :
Temps : 1
Poids : 9
Date limite : 2012

## Valeurs objectives

100_15 : 172995
100_16 : 407703
100_17 : 332804
100_18 : 544838
100_19 : 477684
100_35 : 19114
100_36 : 108293
100_37 : 181850
100_38 : 90440
100_39 : 151701
100_40 : 129728
100_41 : 462324
100_42 : 425875
100_43 : 320537
100_44 : 360193
100_85 : 284
100_86 : 66850
100_87 : 84229
100_88 : 55544
100_89 : 54612

1000_1 : 661265390
1000_2 : 684518705

## Test

Cj = 0 à l'instant 0;

O1 => Cj += 1   instant 1
O2 => Cj += 7   instant 8
O3 => Cj += 3   instant 11
O4 => Cj += 10  instant 21
O5 => Cj += 3   instant 24

Description du problème

On considère le problème qui consiste à ordonnancer n tâches sur une machine séquentielle.
La machine ne peut exécuter qu’une seule tâche à la fois.
Toutes les tâches sont disponibles à l’instant 0.
Chaque tâche j ∈{1, 2, . . . , n} possède:
•Un temps d’exécution pj,
•Un poid wj qui renseigne sur l’importance de la tâche
•Un temps dj qui correspond à la limite à laquelle l’exécution de la tâche doit être
terminée.
Au delà de cette limite, la tâche est considérée en retard.

Pour un ordonnancement O fixé (c.à.d une séquence d’exécution des tâches sur les
machines), on note
    •Cj le temps de compl ́etion de la tˆache j, et
    •Tj := max{Cj−dj, 0} le retard de la tˆache j.
L’objectif est alors de minimiser la somme totale des retards pondérés.
Autrement dit, on s’intéresse au problème d’optimisation qui consiste à trouver un ordonnance-
ment O qui minimise la fonction f d ́efinie par:
f(O) := n∑j=1 wj·Tj

Combiner les 3 critères

La sommme des Dj / n  pour avoir la moyenne de date limite

Le ratio Pj / Wj -> un Tri

## Q1

## Q1.1

3 tris sur chaque critère
puis pondération des tris sur le reste

si retard > 0
    retrier le reste

tri par priorité au départ
ou
tri par ratio tps d'execution / priorité

puis tri sur le reste en fonction de la deadline

```shell
Hill Climbing : 
S : = Solution initiale // Laquelle ?
Repeat : 
    N(s) <- opérateur de voisinage // Lequel ?
    S' <- choisir une solution dans N(s) telle que f(s') < f(s)
    S <-  S'
Until : plus d'amélioration possible (optimum local)
```

    // modifications des coefficients
    // voir les voisinages du cour
    // swap 
    // inversion
    // insertion

Pour VND

- prendre k = 2 voisinages

Pour ILS
recherche locale et trouver une solution meilleure
recherche un optimum local

avoir un critère d'arrêt

Perturbations ("le moves ") par exemple k swaps
