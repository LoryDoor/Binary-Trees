#pragma once

#include <iostream>
#include <string>
using namespace std;

/* Classe Node:
 *      - Attributi:
 *          - ID: Identificativo del nodo, univoco per tutto il programma;
 *          - payload: Dato contenuto nel nodo;
 *          - leftChild: puntatore al figlio di sinistra;
 *          - rightChild: puntatore al figlio di destra;
 *      - Metodi:
 *          - Costruttore vuoto;
 *          - Costruttore partendo dal dato;
 *          - Distruttore [con de-allocazione ricorsiva];
 *          - bool addChild(int childOption, int data): aggiunge un figlio a sinistra o a destra del nodo;
 *          - string toString() : converte il nodo in un formato stringa stampabile;
 */

enum ChildOption {
    LEFT,
    RIGHT
};

static int GlobalNodeCount = 0;

class Node {
public:
    int ID;
    int payload;
    Node *parent;
    Node *leftChild;
    Node *rightChild;

    Node(){}

    Node(int data) {
        ID = GlobalNodeCount++;
        payload = data;
        leftChild = nullptr;
        rightChild = nullptr;
    }

    ~Node() {
        delete leftChild;  // Dealloca il sottoalbero sinistro (chiamata ricorsiva)
        delete rightChild; // Dealloca il sottoalbero destro (chiamata ricorsiva)
    }

    bool addChild(int childOption, int data) {
        // Aggiunta del nodo figlio a sinistra
        if (childOption == LEFT) {
            // Eseguo un controllo per impedire la sovrascrittura di un nodo già presente
            if (this->leftChild == nullptr) {
                // Se il nodo non è presente lo creo
                this->leftChild =  new Node(data);
                this->leftChild->parent = this;
                return true;
            }
            // Se il nodo figlio è già presente stampo un messaggio di errore a video e restituisco false
            return false;
        }

        // Aggiunta del nodo figlio a destra
        if (childOption == RIGHT) {
            // Eseguo un controllo per impedire la sovrascrittura di un nodo già presente
            if (this->rightChild == nullptr) {
                // Se il nodo non è presente lo creo
                this->rightChild = new Node(data);
                this->rightChild->parent = this;
                return true;
            }
            // Se il nodo figlio è già presente restituisco false
            return false;
        }

        // Errore nei parametri forniti
        cout << "ERRORE. Impossibile creare il nodo." << endl;
        return false;
    }

    string toString() {
        return "Node ID: " + to_string(ID) + "; Node payload: " + to_string(payload) + ";";
    }
};
