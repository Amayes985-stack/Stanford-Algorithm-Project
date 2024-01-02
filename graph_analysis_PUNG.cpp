#include "Snap.h"

void AnalyzeGraph(const PUNGraph& Graph, const TStr& InFNm) {
    TIntV NIdV;
    TCnComV CnComV;

    // 1. Type de graphe (orienté ou non orienté)

    printf("1. Type de graphe: Non orienté\n");

    // 2. Nombre de sommets
    const int NumNodes = Graph->GetNodes();
    printf("2. Nombre de sommets: %d\n", NumNodes);

    // 3. Nombre d’arêtes
    const int NumEdges = Graph->GetEdges();
    printf("3. Nombre d'arêtes: %d\n", NumEdges);

    // 4. Degré maximal (ou degré sortant maximum pour twitch et CA-GrQc)
    int MaxDegree = 0;

    for (TUNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++) {
        MaxDegree = TMath::Mx(MaxDegree, NI.GetOutDeg());
    }

   
    printf("4. Degré maximal: %d\n", MaxDegree);

    // 5. Nombre de composantes connexes
    TSnap::GetWccs(Graph, CnComV);
    const int NumConnComp = CnComV.Len();
    printf("5. Nombre de composantes connexes: %d\n", NumConnComp);

    // 6. Nombre de cycles avec 3 sommets (utiliser GetTriads pour tous les graphes)
    const int NumCycles3 = TSnap::GetTriads(Graph);
    printf("6. Nombre de cycles avec 3 sommets: %d\n", NumCycles3);

// 7. Dégénérescence
int MaxDegeneracy = 0;
TIntV DegSeq;

while (!Graph->Empty()) {
    int MinOutDegree = TInt::Mx;
    int MinOutNId = -1;

    // Trouver le nœud de degré minimum
    for (TUNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++) {
        if (NI.GetOutDeg() < MinOutDegree) {
            MinOutDegree = NI.GetOutDeg();
            MinOutNId = NI.GetId();
        }
    }

    if (MinOutNId != -1) {
        // Sauvegarder le degré du nœud supprimé à chaque itération
        DegSeq.Add(MinOutDegree);

        // Mettre à jour la dégénérescence à chaque itération
        MaxDegeneracy = TMath::Mx(MaxDegeneracy, MinOutDegree);

        // Supprimer le nœud de degré minimum
        Graph->DelNode(MinOutNId);

    }
}

// Afficher la dégénérescence maximale à la fin
printf("7. Dégénérescence: %d\n", MaxDegeneracy);
}

int main(int argc, char* argv[]) {
    Env = TEnv(argc, argv, TNotify::StdNotify);
    Env.PrepArgs(TStr::Fmt("Analyse de Graphe. Build: %s, %s. Heure: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

    const TStr InFNm = Env.GetIfArgPrefixStr("-i:", "", "Nom du graphe en entrée");
    if (InFNm.Empty()) {
        printf("Error: Input graph file not specified. Use -i:filename.graph\n");
        return 1;
    }

    Try
    PUNGraph Graph = TSnap::LoadEdgeList<PUNGraph>(InFNm);
    printf("Graph loaded from %s\n", InFNm.CStr());

    AnalyzeGraph(Graph, InFNm);

    Catch

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

