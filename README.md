```plaintext
=======================================================================
Analyse de Graphe avec SNAP - README
=======================================================================

Ce répertoire contient un programme d'analyse de graphe utilisant la bibliothèque SNAP (Stanford Network Analysis Platform). Le code est écrit en C++, permettant l'extraction de diverses propriétés structurelles et topologiques de graphes orientés ou non orientés.

## Contenu du Répertoire

- **graph_analysis_PNG.cpp**: Programme principal pour l'analyse de graphes orientés.
- **graph_analysis_PUNG.cpp**: Programme principal pour l'analyse de graphes non orientés.
- **Makefile**: Fichier pour la compilation avec des compilateurs non-Microsoft.
- **csv_to_txt_twitch.py**: Script Python pour convertir le fichier CSV Twitch en format Small World.
- **csv_to_txt_github.py**, **csv_to_txt_wikipedia.py**, **csv_to_txt_facebook.py**: Scripts Python similaires pour d'autres ensembles de données.
- **README.txt**: Ce fichier.

## Formats de Données de Graphe

Les fichiers xlsx de Facebook, Twitch, Wikipedia et GitHub représentent des graphes au format Excel. Assurez-vous de convertir ces fichiers dans un format approprié de liste d'arêtes (par exemple, CSV) avant d'utiliser les programmes d'analyse.

## Compilation et Exécution

Assurez-vous d'avoir la bibliothèque SNAP installée avant de compiler les programmes. Vous pouvez utiliser le Makefile fourni pour la compilation avec des compilateurs non-Microsoft. Les exécutables générés sont `graph_parameters_PNG` et `graph_parameters_PUNG`.

Pour générer des graphes à partir de fichiers CSV, exécutez les scripts Python `csv_to_txt_*.py` avant de lancer les programmes d'analyse.

```bash
make generate_graphs
make execute
```

## Utilisation

Les programmes d'analyse prennent en entrée des fichiers de graphe au format liste d'arêtes et affichent diverses propriétés du graphe. Par exemple, pour analyser le graphe orienté CA-GrQc.txt, utilisez la commande :

```bash
./graph_parameters_PNG -i:CA-GrQc.txt
```

Assurez-vous de spécifier les chemins vers les bibliothèques snap-core et glib-core lors de l'exécution.

## Complexité Algorithmique

Le programme utilise diverses fonctionnalités de la bibliothèque SNAP pour calculer des propriétés telles que le nombre de nœuds, le nombre d'arêtes, le degré maximal, les composantes fortement connexes, les cycles et la dégénérescence. La complexité dépend des opérations spécifiques et de la structure du graphe.

## Notes

- Pour des performances optimales, la bibliothèque SNAP utilise des structures de données efficaces pour représenter les graphes.
- Les sections spécifiques du code incluent la détection du type de graphe, le calcul du degré maximal, le calcul des composantes connexes, le calcul des cycles et le calcul de la dégénérescence.

## Nettoyage

Pour supprimer les fichiers générés, utilisez la commande :

```bash
make clean
```


Bonne exploration de graphes !
```

Assurez-vous d'ajuster les détails en fonction de votre projet, tels que les noms de fichiers, les commandes de compilation, etc.
