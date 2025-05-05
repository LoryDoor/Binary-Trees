# Binary-Trees
Implementazioni degli alberi binari in Linguaggio C++

# Classe Node
Rappresentazione di un nodo formato da un dato di tipo intero.

La classe Node è così modellata:

  - Attributi:
    - ID: Identificativo del nodo, univoco per tutto il programma;
    - payload: Dato contenuto nel nodo;
    - leftChild: puntatore al figlio di sinistra;
    - rightChild: puntatore al figlio di destra;

  - Metodi:
    - Costruttore vuoto;
    - Costruttore partendo dal dato;
    - Distruttore (con de-allocazione ricorsiva);
    - addChild: aggiunge un figlio a sinistra o a destra del nodo;
    - toString(): converte il nodo in un formato stringa stampabile;

# Classe Tree
Rappresentazione di un albero binario formato da nodi con payload intero.

La classe Tree è così modellata:

  - Attributi:
    - nodeCount: contatore dei nodi di cui è composto l'albero;
    - root: puntatore alla radice dell'albero

  - Metodi:
    - Costruttore a partire da una radice pre-allocata;
    - Costruttore a partire da una lista di chiavi numeriche;
    - Distruttore;
    - DFS: Esegue una visita in profondità dell'albero seguendo l'ordine passato come parametro;
    - BFS: Esegue una visita in ampiezza dell'albero seguendo l'ordine passato come parametro;
    - printDFSTreeVisit: Esegue la visita DFS dell'albero e ne stampa il risultato;
    - printBFSTreeVisit: Esegue la visita BFS dell'albero e ne stampa il risultato;
    - findNodeById: Restituisce un puntatore a un dato nodo cercandolo in base al suo ID;
    - findNodeByPayload: Restituisce i puntatori ai nodi con un payload corrispondente a quello cercato;
    - modifyNodeById: Modifica il payload del nodo con l'ID passato come parametro
    - modifyNodeByPayload: Modifica uno dei nodi con un payload corrispondente a quello passato come parametro;
    - addLeafByRef: Aggiunge una foglia, se possibile, ad un nodo fornito per riferimento;
    - addLeafById: Aggiunge una foglia, se possibile, ad un nodo cercato tramite ID;
    - addLeafByPayload: Aggiunge una foglia, se possibile, ad uno dei nodi cercati per payload;
    - removeNodeById: Elimina il nodo con l'ID passato come parametro e tutti i suoi figli;
    - removeNodeByPayload: Elimina uno dei nodi con un payload corrispondente a quello passato come parametro;
 