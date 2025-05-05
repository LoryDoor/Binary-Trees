#pragma once

#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include "Node.h"

/* Classe Tree:
 *      - Attributi:
 *          - nodeCount: contatore dei nodi di cui è composto l'albero;
 *          - root: puntatore alla radice dell'albero
 *      - Metodi:
 *          - Costruttore a partire da una radice pre-allocata;
 *          - Costruttore a partire da una lista di chiavi numeriche;
 *          - Distruttore;
 *          - void DFS(Node *startNode, vector<Node*> &nodes, DFSVisitType visitType): Esegue una visita in profondità dell'albero seguendo l'ordine passato come parametro;
 *          - void BFS(Node *startNode, vector<Node*> &nodes, BFSVisitType visitType): Esegue una visita in ampiezza dell'albero seguendo l'ordine passato come parametro;
 *          - void printDFSTreeVisit(int visitType): Esegue la visita dell'albero e ne stampa il risultato;
 *          - void printBFSTreeVisit(BFSVisitType visitType): Esegue la visita dell'albero e ne stampa il risultato;
 *          - Node* findNodeById(int id): Restituisce un puntatore a un dato nodo cercandolo in base al suo ID;
 *          - vector<Node*> findNodeByPayload(int data): Restituisce i puntatori ai nodi con un payload corrispondente a quello cercato;
 *          - void modifyNodeById(int id, int newData): Modifica il payload del nodo con l'ID passato come parametro
 *          - void modifyNodeByPayload(int data, int newData): Modifica uno dei nodi con un payload corrispondente a quello passato come parametro;
 *          - bool addLeafByRef(Node* parent, int payload, ChildOption childOption): Aggiunge una foglia, se possibile, ad un nodo fornito per riferimento;
 *          - bool addLeafById(int searchId, int payload, ChildOption childOption): Aggiunge una foglia, se possibile, ad un nodo cercato tramite ID;
 *          - bool addLeafByPayload(int searchPayload, int payload, ChildOption childOption): Aggiunge una foglia, se possibile, ad uno dei nodi cercati per payload;
 *          - void removeNodeById(int id): Elimina il nodo con l'ID passato come parametro e tutti i suoi figli;
 *          - void removeNodeByPayload(int data): Elimina uno dei nodi con un payload corrispondente a quello passato come parametro;
 */

enum DFSVisitType {
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
};

enum BFSVisitType {
    ABSD,
    ABDS,
    BASD,
    BADS
};

class Tree {
public:
    int nodeCount;
    Node *root;

    Tree(Node *root) {
        this->nodeCount = 0;
        this->root = root;
    }

    Tree(vector<int> keys) {
        this->root = new Node(keys[0]); // La prima chiave è la radice dell'albero
        this->root->parent = nullptr;
        this->nodeCount = 1;
        keys.erase(keys.begin());

        for (int item : keys) {
            Node* currentNode = root;
            // Per ogni chiave stabilisco quale debba essere la sua posizione nell'albero
            while (currentNode != nullptr) {
                if (currentNode->payload <= item) {
                    // Guardo a sinistra
                    if (currentNode->addChild(LEFT, item)) {
                        // Se il nodo figlio viene aggiunto correttamente viene aggiornato il contatore dei nodi e si passa alla chiave successiva
                        this->nodeCount++;
                        break;
                    }
                    // Altrimenti la visita si sposta sul nodo di sinistra e viene iterata
                    currentNode = currentNode->leftChild;
                }
                else {
                    // Guardo a destra
                    if (currentNode->addChild(RIGHT, item)) {
                        // Se il nodo figlio viene aggiunto correttamente viene aggiornato il contatore dei nodi e si passa alla chiave successiva
                        this->nodeCount++;
                        break;
                    }
                    // Altrimenti la visita si sposta sul nodo di destra e viene iterata
                    currentNode = currentNode->rightChild;
                }
            }
        }

        if (this->nodeCount != keys.size()+1) {
            cout << "ERRORE. Non è stato possibile creare interamente l'albero." << endl;
            cout << "Nodi creati: " << nodeCount << endl;
        }
    }

    ~Tree() {
        delete this->root;
    }

    void DFS(Node *startNode, stack<Node*> &nodes, DFSVisitType visitType) {
        Node *currentNode = startNode;

        if (currentNode == nullptr) {
            return;
        }

        if (visitType == PRE_ORDER) {
            // Applicazione dell'algoritmo di visita per profondità Pre-Order
            nodes.push(currentNode);
            DFS(currentNode->rightChild, nodes, visitType);
            DFS(currentNode->leftChild, nodes, visitType);
        }
        else if (visitType == IN_ORDER) {
            // Applicazione dell'algoritmo di visita per profondità In-Order
            DFS(currentNode->rightChild, nodes, visitType);
            nodes.push(currentNode);
            DFS(currentNode->leftChild, nodes, visitType);
        }
        else if (visitType == POST_ORDER) {
            // Applicazione dell'algoritmo di visita per profondità Post-Order
            DFS(currentNode->rightChild, nodes, visitType);
            DFS(currentNode->leftChild, nodes, visitType);
            nodes.push(currentNode);
        }
        else {
            cout << "ERRORE. Non è possibile visitare l'albero." << endl;
        }
    }

    void BFS(Node *startNode, vector<Node*> &nodes, BFSVisitType visitType) {

        if (startNode == nullptr) {
            return;
        }

        // Coda per la visita in ampiezza
        queue<Node*> q;
        q.push(startNode);

        while (!q.empty()) {
            Node* currentNode = q.front();
            q.pop();
            nodes.push_back(currentNode);

            // Visite eseguite in maniera da rispettare l'ordine
            if(visitType == ABSD || visitType == BADS) {
                if (currentNode->rightChild != nullptr) {
                    q.push(currentNode->rightChild);
                }
                if (currentNode->leftChild != nullptr) {
                    q.push(currentNode->leftChild);
                }
            }
            else if(visitType == ABDS || visitType == BASD) {
                if (currentNode->leftChild != nullptr) {
                    q.push(currentNode->leftChild);
                }
                if (currentNode->rightChild != nullptr) {
                    q.push(currentNode->rightChild);
                }
            }
            else {
                cout << "ERRORE. Non è possibile visitare l'albero." << endl;
                return;
            }
        }

        // Se il tipo di visita è top-down (ABSD, ABDS) usiamo l'ordine ottenuto
        if (visitType == BASD || visitType == BADS) {
            // Altrimenti, se è bottom-up (BASD, BADS) invertiamo il vettore
            reverse(nodes.begin(), nodes.end());
        }
    }

    void printDFSTreeVisit(DFSVisitType visitType) {
        vector<Node*> nodes;
        stack<Node*> visitedNodes;

        DFS(this->root, visitedNodes, visitType);

        while(!visitedNodes.empty()) {
            nodes.push_back(visitedNodes.top());
            visitedNodes.pop();
        }
        reverse(nodes.begin(), nodes.end());

        if (visitType == PRE_ORDER) {
            cout << "Visita DFS Pre-Order dell'albero: " << endl;
            for (Node *node : nodes) {
                cout << "\t" << node->toString() << endl;
            }
        }
        else if (visitType == IN_ORDER) {
            cout << "Visita DFS In-Order dell'albero: " << endl;
            for (Node *node : nodes) {
                cout << "\t" << node->toString() << endl;
            }
        }
        else if (visitType == POST_ORDER) {
            cout << "Visita DFS Post-Order dell'albero: " << endl;
            for (Node *node : nodes) {
                cout << "\t" << node->toString() << endl;
            }
        }
        else {
            cout << "ERRORE. Impossibile stampare la visita." << endl;
        }
    }

    void printBFSTreeVisit(BFSVisitType visitType) {
        vector<Node*> nodes;

        BFS(this->root, nodes, visitType);

        if (visitType == ABSD) {
            cout << "Visita BFS \"Alto-Basso, Sinistra-Destra\": " << endl;
            for (Node *node : nodes) {
                cout << "\t" << node->toString() << endl;
            }
        }
        else if(visitType == ABDS) {
            cout << "Visita BFS \"Alto-Basso, Destra-Sinistra\": " << endl;
            for (Node *node : nodes) {
                cout << "\t" << node->toString() << endl;
            }
        }
        else if(visitType == BASD) {
            cout << "Visita BFS \"Basso-Alto, Sinistra-Destra\": " << endl;
            for (Node *node : nodes) {
                cout << "\t" << node->toString() << endl;
            }
        }
        else if(visitType == BADS) {
            cout << "Visita BFS \"Basso-Alto, Destra-Sinistra\": " << endl;
            for (Node *node : nodes) {
                cout << "\t" << node->toString() << endl;
            }
        }
        else {
            cout << "ERRORE. Impossibile stampare la visita." << endl;
        }
    }

    Node* findNodeById(int id) {
        // Visito l'albero per ricavare uno stack contenente i riferimenti a tutti i nodi
        stack<Node*> nodes;
        DFS(this->root, nodes, IN_ORDER);

        // Visito lo stack dei nodi e cerco l'ID passato come parametro
        while(!nodes.empty()){
            Node* node = nodes.top();
            if (node->ID == id) {
                // Se lo trovo restituisco il puntatore a quel nodo
                return node;
            }
            nodes.pop();
        }

        return nullptr;
    }

    vector<Node*> findNodeByPayload(int data) {
        // Visito l'albero per ricavare uno stack contenente i riferimenti a tutti i nodi
        stack<Node*> nodes;
        DFS(this->root, nodes, IN_ORDER);

        vector<Node*> foundNodes{};
        //Visito lo stack dei nodi e cerco i nodi con un payload uguale a quello passato come parametro
        while(!nodes.empty()){
            Node *node = nodes.top();
            if (node->payload == data) {
                // Quando li trovo li aggiungo al vector apposito
                foundNodes.push_back(node);
            }
            nodes.pop();
        }

        return foundNodes;
    }

    void modifyNodeById(int id, int newData) {
        Node *node = findNodeById(id); // Cerco il nodo da modificare
        if (node != nullptr) {
            // Se esiste lo aggiorno e stampo a console un messaggio di successo
            node->payload = newData;
            cout << "Nodo [" << node->ID << "] aggiornato correttamente" << endl;
        }
        else {
            cout << "Nodo non trovato." << endl;
        }
    }

    void modifyNodeByPayload(int data, int newData) {
        vector<Node*> foundNodes = findNodeByPayload(data);

        if (foundNodes.empty()) {
            cout << "Non è stato trovato alcun nodo." << endl;
        }
        else if (foundNodes.size() == 1) {
            // Quando è stato trovato un unico nodo con quello specifico payload lo aggiorno e stampo a console un messaggio di successo
            foundNodes[0]->payload = newData;
            cout << "Nodo [" << foundNodes[0]->ID << "] aggiornato correttamente" << endl;
        }
        else {
            // Se invece sono stati trovati più nodi con un certo payload
            cout << "Sono stati trovati più nodi corrispondenti alla ricerca." << endl;
            cout << "Quale si desidera modificare?" << endl;
            for (int i = 0; i < foundNodes.size(); i++) {
                // Stampo a video
                cout << i+1 << ". " << foundNodes[i]->toString() << endl;
            }
            // Permetto all'utente di scegliere quale modificare
            int scelta;
            do {

                cout << "Digitare la scelta: ";
                cin >> scelta;

                if (scelta < 1 || scelta >= foundNodes.size()) {
                    cout << "ERRORE. Digitare una scelta valida." << endl;
                }
            }while (scelta < 1 || scelta >= foundNodes.size());
            scelta -= 1;
            // Fatta la scelta aggiorno il nodo e stampo il messaggio di successo
            foundNodes[scelta]->payload = newData;
            cout << "Nodo [" << foundNodes[scelta]->ID << "] aggiornato correttamente" << endl;
        }
    }

    bool addLeafByRef(Node* parent, int payload, ChildOption childOption) {
        if(parent->addChild(childOption, payload)) {
            // Se il nodo viene aggiunto correttamente incremento il contatore dei nodi e restituisco true
            this->nodeCount++;
            return true;
        }
        return false;
    }

    bool addLeafById(int searchId, int payload, ChildOption childOption) {
        Node* parent = findNodeById(searchId);
        if (parent == nullptr) {
            // Se non viene trovato alcun nodo restituisco false
            cout << "Nodo non trovato." << endl;
            return false;
        }

        return addLeafByRef(parent, payload, childOption);
    }

    bool addLeafByPayload(int searchPayload, int payload, ChildOption childOption) {
        vector<Node*> foundNodes = findNodeByPayload(searchPayload);

        if(foundNodes.empty()) {
            // Se non viene trovato alcun nodo restituisco false
            cout << "Non è stato trovato alcun nodo." << endl;
            return false;
        }

        if(foundNodes.size() == 1) {
            // Se esiste un solo nodo aggiungo il figlio ad esso
            return addLeafByRef(foundNodes[0], payload, childOption);
        }

        // Se sono stati trovati più nodi
        cout << "Sono stati trovati più nodi corrispondenti alla ricerca." << endl;
        cout << "A quale si desidera aggiungere il nuovo figlio?" << endl;
        for (int i = 0; i < foundNodes.size(); i++) {
            // Stampo a video
            cout << i+1 << ". " << foundNodes[i]->toString() << endl;
        }
        // Permetto all'utente di scegliere quale modificare
        int sceltaNodo = 0;
        do {
            cout << "Digitare la scelta: ";
            cin >> sceltaNodo;
            if (sceltaNodo < 1 || sceltaNodo > foundNodes.size()) {
                cout << "ERRORE. Digitare una scelta valida." << endl;
            }
        }while (sceltaNodo < 1 || sceltaNodo > foundNodes.size());
        sceltaNodo -= 1;
        return addLeafByRef(foundNodes[sceltaNodo], payload, childOption);
    }

    void removeNodeById(int id) {
        Node *node = findNodeById(id); // Cerco il nodo da eliminare
        if (node != nullptr) {
            // Se esiste chiedo all'utente la conferma di eliminazione
            int scelta;
            cout << "Sei sicuro di voler eliminare il nodo [ " << node->ID << " ]?" << endl;
            cout << "NOTA: L'eliminazione di un nodo comporta l'eliminazione della porzione di albero di cui è padre." << endl;
            do {
                cout << "Digitare la scelta: " << endl;
                cout << "\t 0 - No" << endl;
                cout << "\t 1 - Si" << endl;
                cin >> scelta;
                if (scelta != 0 && scelta != 1) {
                    cout << "ERRORE. Digitare una scelta valida." << endl;
                }
            }while (scelta != 0 && scelta != 1);
            if (scelta == 1) {
                // Se l'utente fornisce la conferma rimuovo il nodo e stampo il messaggio di successo
                int deletedID = node->ID;
                if (node->parent->leftChild == node) {
                    node->parent->leftChild = nullptr;
                }
                else if (node->parent->rightChild == node) {
                    node->parent->rightChild = nullptr;
                }
                delete node;
                this->nodeCount--;
                cout << "Nodo [" << deletedID << "] eliminato correttamente" << endl;
            }
            else {
                // Altrimenti annullo l'operazione
                cout << "Eliminazione annullata." << endl;
            }
        }
        else {
            // Se non esiste
            cout << "Nodo non trovato." << endl;
        }
    }

    void removeNodeByPayload(int data) {
        vector<Node*> foundNodes = findNodeByPayload(data);

        if (foundNodes.empty()) {
            cout << "Non è stato trovato alcun nodo." << endl;
        }
        else if (foundNodes.size() == 1) {
            // Quando è stato trovato un unico nodo con quello specifico payload chiedo all'utente la conferma di eliminazione
            int scelta;
            cout << "Sei sicuro di voler eliminare il nodo [ " << foundNodes[0]->ID << " ]?" << endl;
            cout << "NOTA: L'eliminazione di un nodo comporta l'eliminazione della porzione di albero di cui è padre." << endl;
            do {
                cout << "Digitare la scelta: " << endl;
                cout << "\t 0 - No" << endl;
                cout << "\t 1 - Si" << endl;
                cin >> scelta;
                if (scelta != 0 && scelta != 1) {
                    cout << "ERRORE. Digitare una scelta valida." << endl;
                }
            }while (scelta != 0 && scelta != 1);
            if (scelta == 1) {
                // Se l'utente fornisce la conferma rimuovo il nodo e stampo il messaggio di successo
                int deletedID = foundNodes[0]->ID;
                if (foundNodes[0]->parent->leftChild == foundNodes[0]) {
                    foundNodes[0]->parent->leftChild = nullptr;
                }
                else if (foundNodes[0]->parent->rightChild == foundNodes[0]) {
                    foundNodes[0]->parent->rightChild = nullptr;
                }
                delete foundNodes[0];
                this->nodeCount--;
                cout << "Nodo [" << deletedID << "] eliminato correttamente" << endl;
            }
            else {
                // Altrimenti annullo l'operazione
                cout << "Eliminazione annullata." << endl;
            }
        }
        else {
            // Se invece sono stati trovati più nodi con un certo payload
            cout << "Sono stati trovati più nodi corrispondenti alla ricerca." << endl;
            cout << "Quale si desidera eliminare?" << endl;
            for (int i = 0; i < foundNodes.size(); i++) {
                // Stampo a video
                cout << i+1 << ". " << foundNodes[i]->toString() << endl;
            }
            // Permetto all'utente di scegliere quale modificare
            int sceltaNodo = 0;
            do {
                cout << "Digitare la scelta: ";
                cin >> sceltaNodo;
                if (sceltaNodo < 1 || sceltaNodo > foundNodes.size()) {
                    cout << "ERRORE. Digitare una scelta valida." << endl;
                }
            }while (sceltaNodo < 1 || sceltaNodo > foundNodes.size());
            sceltaNodo -= 1;
            // Fatta la scelta chiedo all'utente la conferma per eliminare il nodo
            int sceltaEliminazione;
            cout << "Sei sicuro di voler eliminare il nodo [ " << foundNodes[sceltaNodo]->ID << " ]?" << endl;
            cout << "NOTA: L'eliminazione di un nodo comporta l'eliminazione della porzione di albero di cui è padre." << endl;
            do {
                cout << "Digitare la scelta: " << endl;
                cout << "\t 0 - No" << endl;
                cout << "\t 1 - Si" << endl;
                cin >> sceltaEliminazione;
                if (sceltaEliminazione != 0 && sceltaEliminazione != 1) {
                    cout << "ERRORE. Digitare una scelta valida." << endl;
                }
            }while (sceltaEliminazione != 0 && sceltaEliminazione != 1);
            if (sceltaEliminazione == 1) {
                // Se l'utente fornisce la conferma rimuovo il nodo e stampo il messaggio di successo
                int deletedID = foundNodes[sceltaNodo]->ID;
                if (foundNodes[sceltaNodo]->parent->leftChild == foundNodes[sceltaNodo]) {
                    foundNodes[sceltaNodo]->parent->leftChild = nullptr;
                }
                else if (foundNodes[sceltaNodo]->parent->rightChild == foundNodes[sceltaNodo]) {
                    foundNodes[sceltaNodo]->parent->rightChild = nullptr;
                }
                delete foundNodes[sceltaNodo];
                this->nodeCount--;
                cout << "Nodo [" << deletedID << "] eliminato correttamente" << endl;
            }
            else {
                // Altrimenti annullo l'operazione
                cout << "Eliminazione annullata." << endl;
            }
        }
    }
};
