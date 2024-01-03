#include "Snap.h"
#include "gnuplot.h"

// Fonction pour calculer et écrire la distribution des degrés dans un fichier
void WriteDegreeDistribution(const PNGraph& Graph, const TStr& GraphName) {
    TIntH DegreeFreq;

    // Calculer la fréquence des degrés de sortie
    for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++) {
        int OutDeg = NI.GetOutDeg();
        DegreeFreq.AddDat(OutDeg)++;
    }

    // Écrire les données dans un fichier
    FILE* OutFile = fopen((GraphName + "_degree_distribution.dat").CStr(), "w");
    fprintf(OutFile, "# Degré Fréquence\n");

    // Utiliser les itérateurs pour parcourir la collection
    for (TIntH::TIter it = DegreeFreq.BegI(); it < DegreeFreq.EndI(); it++) {
        fprintf(OutFile, "%d %d\n", it.GetKey().Val, it.GetDat().Val);
    }
    fclose(OutFile);
}

// Fonction pour tracer la distribution des degrés à l'aide de Gnuplot
void PlotDegreeDistributionGnuplot(const TStr& GraphName) {
    FILE* GnuplotPipe = popen("gnuplot", "w");
    fprintf(GnuplotPipe, "set terminal png\n");
    fprintf(GnuplotPipe, "set output '%s_degree_distribution.png'\n", GraphName.CStr());
    fprintf(GnuplotPipe, "set title 'Distribution des Degrés - %s'\n", GraphName.CStr());
    fprintf(GnuplotPipe, "set xlabel 'Degré'\n");
    fprintf(GnuplotPipe, "set ylabel 'Fréquence'\n");
    fprintf(GnuplotPipe, "plot '%s_degree_distribution.dat' with boxes\n", GraphName.CStr());
    fclose(GnuplotPipe);
}

int main(int argc, char* argv[]) {
    // Initialiser l'environnement Snap
    Env = TEnv(argc, argv, TNotify::StdNotify);
    Env.PrepArgs(TStr::Fmt("Analyse de Graphe Orienté. Build: %s, %s. Heure: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));

    // Spécifier ici les noms des fichiers de graphes que vous souhaitez analyser
    TStrV GraphFiles;
    GraphFiles.Add("CA-GrQc.txt");
    GraphFiles.Add("twitchDE.txt");

    // ... ajouter autant de fichiers que nécessaire

    // Analyser chaque graphe et écrire la distribution des degrés
    for (int i = 0; i < GraphFiles.Len(); i++) {
        const TStr& InFNm = GraphFiles[i];
        PNGraph Graph = TSnap::LoadEdgeList<PNGraph>(InFNm);

        // Écrire la distribution des degrés dans un fichier
        WriteDegreeDistribution(Graph, InFNm.GetFMid());

        // Utiliser Gnuplot pour tracer l'histogramme
        PlotDegreeDistributionGnuplot(InFNm.GetFMid());
    }

    return 0;
}
