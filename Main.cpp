#include  "Tree.h"
#include <locale>

/* PROGRAMMA: Esempio didattico di implementazione degli alberi binari in Linguaggio C++.
 * AUTORE: Lorenzo Porta - ITT "G. Fauser" - Novara
 * ULTIMA MODIFICA: 07/04/2025
 */

int main() {

    setlocale(LC_ALL, "Italian");
    const vector<int> chiaviAlbero1 = {50, 40, 60, 35, 45, 55, 65, 32, 37, 42, 47, 52, 57, 62, 67};

    Tree* AlberoBinario = new Tree(chiaviAlbero1);

    cout << endl;
    cout << "L'albero è composto da: " << AlberoBinario->nodeCount << " nodi" << endl;

    cout << endl;
    cout << "Visite per profondità dell'albero: " << endl << endl;
    AlberoBinario->printDFSTreeVisit(PRE_ORDER);
    cout << endl;
    AlberoBinario->printDFSTreeVisit(IN_ORDER);
    cout << endl;
    AlberoBinario->printDFSTreeVisit(POST_ORDER);
    cout << endl;

    cout << endl << "Visite per ampiezza dell'albero:" << endl << endl;
    AlberoBinario->printBFSTreeVisit(ABSD);
    cout << endl;
    AlberoBinario->printBFSTreeVisit(ABDS);
    cout << endl;
    AlberoBinario->printBFSTreeVisit(BASD);
    cout << endl;
    AlberoBinario->printBFSTreeVisit(BADS);
    cout << endl;

    AlberoBinario->addLeafById(10, 60, RIGHT);
    AlberoBinario->addLeafById(8, 100, LEFT);
    AlberoBinario->printDFSTreeVisit(IN_ORDER);
    cout << endl;

    AlberoBinario->removeNodeByPayload(60);
    AlberoBinario->printDFSTreeVisit(IN_ORDER);
    cout << endl;

    AlberoBinario->removeNodeById(16);
    AlberoBinario->printDFSTreeVisit(IN_ORDER);
    cout << endl;

    delete AlberoBinario;
    cout << "Albero deallocati." << endl
        << "Fine programma." << endl;

    return 0;
}
