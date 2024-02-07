#include "Vector.h"

Vector::Vector(string Filename) {
    front = NULL;
    rear = NULL;
    ifstream in(Filename);
    int input;
    while (!in.eof()) {
        in >> input;
        pushRear(input);
    }
    in.close();
}

Vector::Vector(Vector& v) { //this is temporary fix this make it an actual copy
    int* Array = v.printVector();
    for (int i = 1; i < v.size+1; i++) {
        pushFront(Array[v.size-i]);
    }
    delete Array;
}

Vector::Vector(int* A, int Asize) {
    for (int i = 0; i < Asize; i++) {
        pushRear(A[i]);
    }
}

void Vector::pushRear(int data) {
    //Create New Node
    Node* nNode = new Node();
    nNode->data = data;
    size++;

    //Check if vector is empty
    if (front == NULL) {
        front = nNode;
        rear = nNode;
    }
    else {
        rear->next = nNode;
        rear = nNode;
    }
}

void Vector::pushFront(int data) {
    Node* nNode = new Node();
    nNode->data = data;
    size++;
    //Check if vector is empty
    if (front == NULL) {
        front = nNode;
        rear = nNode;
    }
    else {
        nNode->next = front;
        front = nNode;
    }
}

void Vector::pushFront(Vector& v) {
    int* Array = v.printVector();
    for (int i = 1; i < v.size + 1; i++) {
        pushFront(Array[v.size - i]);
    }
    delete Array;
}

void Vector::pushRear(Vector& v) {
    int* Array = v.printVector();
    for (int i = 1; i < v.size + 1; i++) {
        pushRear(Array[v.size - i]);
    }
    delete Array;
}

int Vector::popRear() {
    /* if there is only one item in the list, remove it */
    int val;
    if (front == NULL) { return-1; }
    else if (front->next == NULL) {
        val = front->data;
        delete front;
        front = NULL;
        size--;
        return val;
    }

    /* get to the second to last node in the list */
    else {
        Node* current = front;
        while (current->next->next != NULL) {
            current = current->next;
        }

        /* now current points to the second to last item of the list, so let's remove current->next */
        val = current->next->data;
        delete current->next;
        current->next = nullptr;
        size--;
        return val;
    }
}

int Vector::popFront() {
    int val;
    if (front == NULL) { return-1; }
    else if (front->next == NULL) {
        val = front->data;
        delete front;
        front = NULL;
        size--;
        return val;
    }
    else {
        Node* temp = front;
        front = front->next;
        val = temp->data;
        delete temp;
        size--;
        return val;

    }
}

int* Vector::printVector() {
    Node* travel = front;
    Node* counter = front;
    size = 0;
    while (counter->next != NULL)
    {
        counter = counter->next;
        size++;
    }
    int* Array = new int[size];
    for (int i = 0; i<size; i++) {
        Array[i] = travel->data;
        travel = travel->next;
   }
    return Array;
}

void Vector::print(ofstream& file) {
    if (front == NULL) { return; }
    Node* travel = front;
    file << "[";
    while (travel != NULL) {
        file << travel->data << " ";
        travel = travel->next;
    }
    file << "]\n";
}

int Vector::find(int val) {
    int* A = printVector();
    for (int i = 0; i < size; i++) {
        if (A[i] == val) { return val; }
    }
    return -1;
}

int Vector::popAt(int loc) {
    if (front == NULL || loc >size) { return-1; }
    Node* travel = front;
    Node* prev = front;
    for (int i = 1; i < loc; i++) {
        travel = travel->next;
    }
    prev = travel;
    travel = travel->next;
    prev->next = travel->next;
    int val = travel->data;
    delete travel;
}