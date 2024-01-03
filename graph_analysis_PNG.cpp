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

void AnalyzeDirectedGraph(const PNGraph& Graph, const TStr& GraphName, GraphResult& Result) {
    TIntV NIdV;
    TCnComV CnComV;

    // 1. Type de graphe: Orienté
    //printf("1. Type de graphe: Orienté\n");

    // 2. Nombre de sommets
    const int NumNodes = Graph->GetNodes();
    //printf("2. Nombre de sommets: %d\n", NumNodes);

    // 3. Nombre d’arêtes
    const int NumEdges = Graph->GetEdges();
    //printf("3. Nombre d'arêtes: %d\n", NumEdges);

    // 4. Degré sortant maximal
    int MaxOutDegree = 0;
    for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++) {
        MaxOutDegree = TMath::Mx(MaxOutDegree, NI.GetOutDeg());
    }
    //printf("4. Degré sortant maximum: %d\n", MaxOutDegree);

    // 5. Nombre de composantes fortement connexes
    TSnap::GetSccs(Graph, CnComV);
    const int NumStrongConnComp = CnComV.Len();
    //printf("5. Nombre de composantes fortement connexes: %d\n", NumStrongConnComp);

    // 6. Nombre de cycles avec 3 sommets
    const int NumCycles3 = TSnap::GetTriads(Graph);
    //printf("6. Nombre de cycles avec 3 sommets: %d\n", NumCycles3);

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

    // Assignez les résultats à la structure GraphResult
    Result.GraphName = GraphName;
    Result.NumNodes = NumNodes;
    Result.NumEdges = NumEdges;
    Result.MaxDegree = MaxOutDegree;
    Result.NumConnComp = NumStrongConnComp;
    Result.NumCycles3 = NumCycles3;
    Result.MaxDegeneracy = MaxDegeneracy;  // Ajoutez cette ligne pour stocker la dégénérescence

    // Print the maximum degeneracy
    //printf("7. Dégénérescence : %d\n", MaxDegeneracy);
}

int main(int argc, char* argv[]) {
    Env = TEnv(argc, argv, TNotify::StdNotify);
    Env.PrepArgs(TStr::Fmt("Analyse de Graphe Orienté. Build: %s, %s. Heure: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

    // Spécifiez ici les noms des fichiers de graphes que vous souhaitez analyser
    TStrV GraphFiles;
    GraphFiles.Add("CA-GrQc.txt");
    GraphFiles.Add("twitchDE.txt");
    // ... ajoutez autant de fichiers que nécessaire

    // Créez un vecteur pour stocker les résultats de chaque graphe
    TVec<GraphResult> Results;

    // Analysez chaque graphe et stockez les résultats dans le vecteur
    for (int i = 0; i < GraphFiles.Len(); i++) {
        const TStr& InFNm = GraphFiles[i];
        PNGraph Graph = TSnap::LoadEdgeList<PNGraph>(InFNm);
        GraphResult Result;

        // Analysez le graphe
        AnalyzeDirectedGraph(Graph, InFNm.GetFMid(), Result);

        // Stockez les résultats dans le vecteur
        Results.Add(Result);
    }

    // Imprimez les résultats sous forme de tableau
    printf("| Nom du Graphe | Nombre de Sommets | Nombre d'Arêtes | Degré Sortant Maximal | Nombre de Composantes Fortement Connexes | Nombre de Cycles avec 3 Sommets | Dégénérescence |\n");
    printf("|---------------|---------------------|-----------------|----------------|-------------------------------|---------------------------------|-----------------|\n");

    for (int i = 0; i < Results.Len(); i++) {
        const GraphResult& Result = Results[i];
        printf("| %-13s| %-20d| %-15d| %-14d| %-29d| %-31d| %-15d|\n",
               Result.GraphName.CStr(), Result.NumNodes, Result.NumEdges, Result.MaxDegree,
               Result.NumConnComp, Result.NumCycles3, Result.MaxDegeneracy);
    }

    return 0;
}
