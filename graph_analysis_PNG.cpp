#include "Snap.h"

void AnalyzeDirectedGraph(const PNGraph& Graph) {
    TIntV NIdV;
    TCnComV CnComV;

    // 1. Type de graphe: Orienté
    printf("1. Type de graphe: Orienté\n");

    // 2. Nombre de sommets
    const int NumNodes = Graph->GetNodes();
    printf("2. Nombre de sommets: %d\n", NumNodes);

    // 3. Nombre d’arêtes
    const int NumEdges = Graph->GetEdges();
    printf("3. Nombre d'arêtes: %d\n", NumEdges);

    // 4. Degré sortant maximal
    int MaxOutDegree = 0;
    for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++) {
        MaxOutDegree = TMath::Mx(MaxOutDegree, NI.GetOutDeg());
    }
    printf("4. Degré sortant maximum: %d\n", MaxOutDegree);

    // 5. Nombre de composantes fortement connexes
    TSnap::GetSccs(Graph, CnComV);
    const int NumStrongConnComp = CnComV.Len();
    printf("5. Nombre de composantes fortement connexes: %d\n", NumStrongConnComp);

    // 6. Nombre de cycles avec 3 sommets
    const int NumCycles3 = TSnap::GetTriads(Graph);
    printf("6. Nombre de cycles avec 3 sommets: %d\n", NumCycles3);


// 7. Dégénérescence
TIntV DegSeq;
int MaxDegeneracy = 0;  // Variable to store the maximum degeneracy

while (!Graph->Empty()) {
    int MinOutDegree = TInt::Mx;
    int MinOutNId = -1;

    for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++) {
        if (NI.GetOutDeg() < MinOutDegree) {
            MinOutDegree = NI.GetOutDeg();
            MinOutNId = NI.GetId();
        }
    }

    if (MinOutNId != -1) {
        DegSeq.Add(MinOutDegree);
        Graph->DelNode(MinOutNId);  // Remove node with minimum out-degree

        // Update the maximum degeneracy
        MaxDegeneracy = TMath::Mx(MaxDegeneracy, MinOutDegree);

        // Print intermediate steps
    }
}

// Print the maximum degeneracy
printf("7. Dégénérescence : %d\n", MaxDegeneracy);

}


int main(int argc, char* argv[]) {
    Env = TEnv(argc, argv, TNotify::StdNotify);
    Env.PrepArgs(TStr::Fmt("Analyse de Graphe Orienté. Build: %s, %s. Heure: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

    const TStr InFNm = Env.GetIfArgPrefixStr("-i:", "", "Nom du graphe en entrée");
    if (InFNm.Empty()) {
        printf("Error: Input graph file not specified. Use -i:filename.graph\n");
        return 1;
    }

    Try
    PNGraph Graph = TSnap::LoadEdgeList<PNGraph>(InFNm);
    printf("Graph loaded from %s\n", InFNm.CStr());

    AnalyzeDirectedGraph(Graph);

    Catch

    return 0;
}

// ...

// Complexité algorithmique :
// - La lecture du fichier d'entrée est linéaire par rapport au nombre d'arêtes et de sommets du graphe.
// - Les opérations sur le graphe (calcul du degré, composantes fortement connexes, cycles) dépendent des
//   implémentations spécifiques dans la bibliothèque SNAP. En général, ces opérations ont une complexité
//   qui dépend de la structure du graphe (par exemple, O(N) pour un graphe orienté avec N sommets et M arêtes).
// - Le tri de la séquence de degrés et le calcul de la dégénérescence ont une complexité de tri (O(N log N)
//   dans le pire des cas).
// - Dans l'ensemble, la complexité totale dépend des opérations spécifiques effectuées sur le graphe et peut varier.
//   En moyenne, elle sera dominée par la lecture du fichier et les opérations sur le graphe.
// - En conclusion, la complexité algorithmique globale de ce programme dépend des caractéristiques spécifiques du graphe
//   en entrée et des opérations effectuées. En règle générale, elle sera linéaire par rapport à la taille du graphe.
//   Cependant, les opérations spécifiques, telles que le calcul des composantes fortement connexes, des cycles, etc.,
//   peuvent avoir des complexités différentes en fonction de la structure du graphe.
// - Il est important de noter que la bibliothèque SNAP peut utiliser des structures de données efficaces pour représenter
//   les graphes, ce qui peut influencer positivement les performances globales.

// Astuce : La complexité algorithmique peut varier en fonction des propriétés spécifiques du graphe (densité, connectivité, etc.).
//          Si la performance est cruciale, des optimisations spécifiques au domaine peuvent être envisagées.

// Note : Les sections spécifiques du code comprennent la détection du type de graphe, le calcul du degré sortant maximal,
//        le calcul des composantes fortement connexes, le calcul des cycles et le calcul de la dégénérescence.

