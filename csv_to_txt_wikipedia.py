# Importation de la bibliothèque pandas pour la manipulation de données tabulaires
import pandas as pd

# Fonction de conversion d'un fichier CSV en format Small World
def convert_csv_to_smallworld(input_csv_file, output_graph_file):
    # Lecture du fichier CSV
    df = pd.read_csv(input_csv_file)

    # Ouverture du fichier de graphe de sortie en mode écriture
    with open(output_graph_file, 'w') as f:
        # Écriture de l'en-tête dans le fichier de sortie
        f.write("# Undirected graph: Wikipedia1.txt \n")
        f.write("# id_1 id_2\n")

        # Écriture des arêtes dans le fichier de sortie
        for _, row in df.iterrows():
            # S'il n'y a qu'une seule valeur dans la ligne, on la ignore
            if len(row) == 1:
                continue

            # Écriture des arêtes dans le fichier de sortie
            for i in range(len(row) - 1):
                f.write(f"{row[i]}\t{row[i + 1]}\n")

    # Affichage d'un message de réussite
    print(f"Conversion effectuée avec succès. Résultat écrit dans le fichier {output_graph_file}")

# Exemple d'utilisation
input_csv_file = 'Wikipedia1.csv'
output_graph_file = 'Wikipedia1.txt'
convert_csv_to_smallworld(input_csv_file, output_graph_file)
