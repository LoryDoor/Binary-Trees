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
    - bool addChild(int childOption, int data): aggiunge un figlio a sinistra o a destra del nodo;
    - string toString() : converte il nodo in un formato stringa stampabile;

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
    - void DFS(Node *startNode, vector<Node*> &nodes, DFSVisitType visitType): Esegue una visita in profondità dell'albero seguendo l'ordine passato come parametro;
    - void BFS(Node *startNode, vector<Node*> &nodes, BFSVisitType visitType): Esegue una visita in ampiezza dell'albero seguendo l'ordine passato come parametro;
    - void printDFSTreeVisit(int visitType): Esegue la visita dell'albero e ne stampa il risultato;
    - void printBFSTreeVisit(BFSVisitType visitType): Esegue la visita dell'albero e ne stampa il risultato;
    - Node* findNodeById(int id): Restituisce un puntatore a un dato nodo cercandolo in base al suo ID;
    - vector<Node*> findNodeByPayload(int data): Restituisce i puntatori ai nodi con un payload corrispondente a quello cercato;
    - void modifyNodeById(int id, int newData): Modifica il payload del nodo con l'ID passato come parametro
    - void modifyNodeByPayload(int data, int newData): Modifica uno dei nodi con un payload corrispondente a quello passato come parametro;
    - bool addLeafByRef(Node* parent, int payload, ChildOption childOption): Aggiunge una foglia, se possibile, ad un nodo fornito per riferimento;
    - bool addLeafById(int searchId, int payload, ChildOption childOption): Aggiunge una foglia, se possibile, ad un nodo cercato tramite ID;
    - bool addLeafByPayload(int searchPayload, int payload, ChildOption childOption): Aggiunge una foglia, se possibile, ad uno dei nodi cercati per payload;
    - void removeNodeById(int id): Elimina il nodo con l'ID passato come parametro e tutti i suoi figli;
    - void removeNodeByPayload(int data): Elimina uno dei nodi con un payload corrispondente a quello passato come parametro;
 