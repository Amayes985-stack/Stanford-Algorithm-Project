#include "Snap.h"

// Structure pour stocker les résultats d'analyse d'un graphe
struct GraphResult {
    TStr GraphName;
    int NumNodes;
    int NumEdges;
    int MaxDegree;
    int NumConnComp;
    int NumCycles3;
    int MaxDegeneracy;  // Ajout du champ pour stocker la dégénérescence
};

void AnalyzeGraph(const PUNGraph& Graph, const TStr& GraphName, GraphResult& Result) {
    TIntV NIdV;
    TCnComV CnComV;

    // 1. Type de graphe (orienté ou non orienté)
    //printf("1. Type de graphe: Non orienté\n");

    // 2. Nombre de sommets
    const int NumNodes = Graph->GetNodes();
    //printf("2. Nombre de sommets: %d\n", NumNodes);

    // 3. Nombre d’arêtes
    const int NumEdges = Graph->GetEdges();
    //printf("3. Nombre d'arêtes: %d\n", NumEdges);

    // 4. Degré maximal
    int MaxDegree = 0;

    for (TUNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++) {
        MaxDegree = TMath::Mx(MaxDegree, NI.GetDeg());
    }

    //printf("4. Degré maximal: %d\n", MaxDegree);

    // 5. Nombre de composantes connexes
    TSnap::GetWccs(Graph, CnComV);
    const int NumConnComp = CnComV.Len();
    //printf("5. Nombre de composantes connexes: %d\n", NumConnComp);

    // 6. Nombre de cycles avec 3 sommets
    const int NumCycles3 = TSnap::GetTriads(Graph);
    //printf("6. Nombre de cycles avec 3 sommets: %d\n", NumCycles3);

    // 7. Dégénérescence
    int MaxDegeneracy = 0;
    TIntV DegSeq;

    while (!Graph->Empty()) {
        int MinDeg = TInt::Mx;
        int MinNId = -1;

        // Trouver le nœud de degré minimum
        for (TUNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++) {
            if (NI.GetDeg() < MinDeg) {
                MinDeg = NI.GetDeg();
                MinNId = NI.GetId();
            }
        }

        if (MinNId != -1) {
            // Sauvegarder le degré du nœud supprimé à chaque itération
            DegSeq.Add(MinDeg);

            // Mettre à jour la dégénérescence à chaque itération
            MaxDegeneracy = TMath::Mx(MaxDegeneracy, MinDeg);

            // Supprimer le nœud de degré minimum
            Graph->DelNode(MinNId);
        }
    }

    // Afficher la dégénérescence maximale à la fin
    //printf("7. Dégénérescence: %d\n", MaxDegeneracy);

    // Assignez les résultats à la structure GraphResult
    Result.GraphName = GraphName;
    Result.NumNodes = NumNodes;
    Result.NumEdges = NumEdges;
    Result.MaxDegree = MaxDegree;
    Result.NumConnComp = NumConnComp;
    Result.NumCycles3 = NumCycles3;
    Result.MaxDegeneracy = MaxDegeneracy;  // Ajoutez cette ligne pour stocker la dégénérescence

    // Ajout du résultat supplémentaire (vous pouvez définir cette valeur en fonction de votre logique)
}

int main(int argc, char* argv[]) {
    Env = TEnv(argc, argv, TNotify::StdNotify);
    Env.PrepArgs(TStr::Fmt("Analyse de Graphe Non Orienté. Build: %s, %s. Heure: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

    // Spécifiez ici les noms des fichiers de graphes que vous souhaitez analyser
    TStrV GraphFiles;
    GraphFiles.Add("FacebookSites.txt");
    GraphFiles.Add("GitHub.txt");
    GraphFiles.Add("Wikipedia1.txt");
    // ... ajoutez autant de fichiers que nécessaire

    // Créez un vecteur pour stocker les résultats de chaque graphe
    TVec<GraphResult> Results;

    // Analysez chaque graphe et stockez les résultats dans le vecteur
    for (int i = 0; i < GraphFiles.Len(); i++) {
        const TStr& InFNm = GraphFiles[i];
        PUNGraph Graph = TSnap::LoadEdgeList<PUNGraph>(InFNm);
        GraphResult Result;

        // Analysez le graphe
        AnalyzeGraph(Graph, InFNm.GetFMid(), Result);

        // Stockez les résultats dans le vecteur
        Results.Add(Result);
    }

    // Imprimez les résultats sous forme de tableau
    printf("| Nom du Graphe | Nombre de Sommets | Nombre d'Arêtes | Degré Maximal | Nombre de Composantes Connexes | Nombre de Cycles avec 3 Sommets | Dégénérescence | Résultat |\n");
    printf("|---------------|---------------------|-----------------|---------------|------------------------|-------------------------------|-----------------|---------|\n");

    for (int i = 0; i < Results.Len(); i++) {
        const GraphResult& Result = Results[i];
        printf("| %-13s| %-20d| %-15d| %-13d| %-23d| %-31d| %-15d|\n",
               Result.GraphName.CStr(), Result.NumNodes, Result.NumEdges, Result.MaxDegree,
               Result.NumConnComp, Result.NumCycles3, Result.MaxDegeneracy);
    }

    return 0;
}


// Complexité algorithmique :
// - La lecture du fichier d'entrée est linéaire par rapport au nombre d'arêtes et de sommets du graphe.
// - Les opérations sur le graphe (calcul du degré, composantes connexes, cycles) dépendent des implémentations
//   spécifiques dans la bibliothèque SNAP. En général, ces opérations ont une complexité qui dépend de la structure
//   du graphe (par exemple, O(N) pour un graphe non orienté avec N sommets et M arêtes).
// - Le tri de la séquence de degrés et le calcul de la dégénérescence ont une complexité de tri (O(N log N) dans
//   le pire des cas).
// - Dans l'ensemble, la complexité totale dépend des opérations spécifiques effectuées sur le graphe et peut varier.
//   En moyenne, elle sera dominée par la lecture du fichier et les opérations sur le graphe.
// - En conclusion, la complexité algorithmique globale de ce programme dépend des caractéristiques spécifiques du graphe
//   en entrée et des opérations effectuées. En règle générale, elle sera linéaire par rapport à la taille du graphe.
//   Cependant, les opérations spécifiques, telles que le calcul des composantes connexes, des cycles, etc., peuvent avoir
//   des complexités différentes en fonction de la structure du graphe.

// Note : Il est important de noter que la bibliothèque SNAP peut utiliser des structures de données efficaces
//        pour représenter les graphes, ce qui peut influencer positivement les performances globales.

// En ce qui concerne les sections spécifiques du code :

// - La détection du type de graphe (orienté ou non orienté) est effectuée en vérifiant le nom du fichier d'entrée.
// - Le calcul du degré maximal (ou du degré sortant maximum pour certains graphes) est effectué en parcourant tous
//   les nœuds du graphe.
// - Le calcul des composantes connexes utilise les fonctions GetWccs ou GetSccs en fonction du type de graphe.
// - Le calcul des cycles utilise la fonction GetTriads pour tous les graphes.
// - Le calcul de la dégénérescence implique le tri de la séquence de degrés et le calcul du degré de dégénérescence.

// Astuce : La complexité algorithmique peut varier en fonction des propriétés spécifiques du graphe (densité, connectivité, etc.).
//          Si la performance est cruciale, des optimisations spécifiques au domaine peuvent être envisagées.

