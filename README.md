
### Introduction
The goal of this project is to study various parameters of large-scale graphs sourced from the web. Typically, these graphs are characterized by a high number of edges and vertices, making their analysis complex and computationally demanding. The focus will be on exploring graphs from the Stanford Large Network Dataset Collection, which models diverse social networks. These graphs are typically represented in text files containing information about their edges and vertices.

### Overview
This GitHub repository contains a C++ toolkit for analyzing and visualizing large-scale graphs sourced from the Stanford Large Network Dataset Collection.

### Key Features
1. **Graph Parameter Calculation:** Analyze various parameters such as vertices, edges, max degree, connected components, and cycles with 3 vertices.
2. **Degree Distribution Visualization:** Create graphical representations of the degree distribution for each graph.
3. **Degeneracy Computation:** Calculate the degeneracy for each graph using an iterative removal approach.

### Usage
1. **Clone the Repository:**
   ```bash
   git clone https://github.com/Amayes985-stack/Stanford-Algorithm-Project.git
   ```
2. **Compile and Run:**
   Follow the instructions in the README file for compilation and execution.

### Graph Format
Make sure to review and modify the format of graphs from the Stanford database as needed.

### Contribution Guidelines
1. Fork the repository and create a new branch for your contributions.
2. Make changes and submit a pull request.

### License
This project is licensed under the MIT License. See the LICENSE.md file for details.

### Acknowledgments
We appreciate your contributions to advancing graph analysis. Thank you to all contributors!



```plaintext
=======================================================================
Graph Analysis with SNAP - README
=======================================================================

This directory contains a graph analysis program using the SNAP (Stanford Network Analysis Platform) library. The code is written in C++, allowing extraction of various structural and topological properties from directed or undirected graphs.

## Directory Contents

- **graph_analysis_PNG.cpp**: Main program for analyzing directed graphs.
- **graph_analysis_PUNG.cpp**: Main program for analyzing undirected graphs.
- **Makefile**: File for compilation using non-Microsoft compilers.
- **csv_to_txt_twitch.py**: Python script to convert Twitch CSV file to Small World format.
- **csv_to_txt_github.py**, **csv_to_txt_wikipedia.py**, **csv_to_txt_facebook.py**: Similar Python scripts for other datasets.
- **README.txt**: This file.
- **result_pung.txt**: Execution result of the ./graph_parameters_PUNG displayed in an array 
- **result_png.txt**: Execution result of the ./graph_parameters_PNG displayed in an array
- **graph_name_degree_distribution.png** : Graph Display -> Degree and Frequency Distribution 
- **graphe_name_degree_distribution.dat** : Degree and Frequency Distribution 


## Graph Data Formats

The xlsx files for Facebook, Twitch, Wikipedia, and GitHub represent graphs in Excel format. Ensure these files are converted to an appropriate edge-list format (e.g., CSV) before using the analysis programs.

## Compilation and Execution

Ensure that you have the SNAP library installed before compiling the programs. You can use the provided Makefile for compilation with non-Microsoft compilers. The generated executables are `graph_parameters_PNG` and `graph_parameters_PUNG`.

To generate graphs from CSV files, run the Python scripts `csv_to_txt_*.py` before executing the analysis programs.

```bash
make generate_graphs
make execute
make display_graph 
```

## Usage

The analysis programs take edge-list graph files as input and display various graph properties. For example, to analyze the directed graphs use the command:

```bash
g++ -o graph_parameters_PNG graph_analysis_PNG.cpp -I/workspaces/Stanford-Algorithm-Project/snap-core -I/workspaces/Stanford-Algorithm-Project/glib-core -lsnap -lrt -fopenmp
./graph_parameters_PNG 
```

To analyze the undirected graphs, use the command: 

```bash
g++ -o graph_parameters_PUNG graph_analysis_PUNG.cpp -I/workspaces/Stanford-Algorithm-Project/snap-core -I/workspaces/Stanford-Algorithm-Project/glib-core -lsnap -lrt -fopenmp
./graph_parameters_PUNG 
```

To display the distribution of directed graphs, use the command : 

```bash
g++ -o degree_distribution_PNG degree_distribution_PNG.cpp -I/workspaces/Stanford-Algorithm-Project/snap-core -I/workspaces/Stanford-Algorithm-Project/glib-core -lsnap -lrt -fopenmp
./degree_distribution_PNG
```

To display the distribution of undirected graphs, use the command : 

```bash
g++ -o degree_distribution_PUNG degree_distribution_PUNG.cpp -I/workspaces/Stanford-Algorithm-Project/snap-core -I/workspaces/Stanford-Algorithm-Project/glib-core -lsnap -lrt -fopenmp
./degree_distribution_PUNG
```

Make sure to specify paths to snap-core and glib-core libraries at runtime and that -lsnap, -lrt and -fopenmp libraries are installed 

## Algorithmic Complexity

The program utilizes various features of the SNAP library to compute properties such as the number of nodes, number of edges, maximum degree, strongly connected components, cycles, and degeneracy. The complexity depends on specific operations and the structure of the graph.

## Notes

- For optimal performance, the SNAP library uses efficient data structures to represent graphs.
- Specific code sections include graph type detection, maximum degree calculation, connected components calculation, cycle calculation, and degeneracy calculation.

## Cleaning Up

To clean generated files, use the command:

```bash
make clean
```


Happy graph exploration!
```

Make sure to adjust details based on your project, such as file names, compilation commands, etc.
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
- **result_pung.txt** : Résultat d’exécution du . /graph_parameters_PUNG affiché dans un tableau 
- **result_png.txt** : Résultat d’exécution du . /graph_parameters_PNG affiché dans un tableau
- **graph_name_degree_distribution.png** : Affichage graphique -> Distribution de degrés et de fréquences 
- **graphe_name_degree_distribution.dat** : Distribution des degrés et des fréquences 


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

Les programmes d'analyse prennent en entrée des fichiers de graphe au format liste d'arêtes et affichent diverses propriétés du graphe. Par exemple, pour analyser les graphes orientés, utilisez la commande :

```bash
g++ -o graph_parameters_PNG graph_analysis_PNG.cpp -I/workspaces/Stanford-Algorithm-Project/snap-core -I/workspaces/Stanford-Algorithm-Project/glib-core -lsnap -lrt -fopenmp
./graph_parameters_PNG 
```
Pour analyser les graphes non orientés, utiliser la commande : 

```bash
g++ -o graph_parameters_PUNG graph_analysis_PUNG.cpp -I/workspaces/Stanford-Algorithm-Project/snap-core -I/workspaces/Stanford-Algorithm-Project/glib-core -lsnap -lrt -fopenmp
./graph_parameters_PUNG 
```
Pour afficher la distribution de degrés et de fréquence des graphes orientés, utiliser la commande : 

```bash
g++ -o degree_distribution_PNG degree_distribution_PNG.cpp -I/workspaces/Stanford-Algorithm-Project/snap-core -I/workspaces/Stanford-Algorithm-Project/glib-core -lsnap -lrt -fopenmp
./degree_distribution_PNG
```
Pour afficher la distribution de degrés et de fréquence des graphes non orientés, utiliser la commande : 

```bash
g++ -o degree_distribution_PNG degree_distribution_PNG.cpp -I/workspaces/Stanford-Algorithm-Project/snap-core -I/workspaces/Stanford-Algorithm-Project/glib-core -lsnap -lrt -fopenmp
./degree_distribution_PNG
```

Assurez-vous de spécifier les chemins vers les bibliothèques snap-core et glib-core lors de l'exécution et que les libraires -lsnap, -lrt et -fopenmp sont bien installés 

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


Bonne exploration de graphes !
```

Assurez-vous d'ajuster les détails en fonction de votre projet, tels que les noms de fichiers, les commandes de compilation, etc.
