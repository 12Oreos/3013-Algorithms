#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#pragma once

struct Node {
    int data = 0;
    Node* next = NULL;
};

class Vector
{
private:
    Node* front;
    Node* rear;
    int size=0;
public:
    //constructors
    Vector() { front = NULL; rear = NULL; }
    //deconstructors
    ~Vector() { while (front != NULL) { if (front != NULL) { popFront(); } } }
    Vector(string Filename);
    Vector(Vector &v);
    Vector(int* A, int size);
    //Pushers
    void pushRear(int data);
    void pushFront(int data);
    void pushFront(Vector& v);
    void pushRear(Vector& v);
    //Popers
    int popRear();
    int popFront();
    int popAt(int loc);
    //Other Functions
    int* printVector();
    void print(ofstream& file);
    int find(int val);
    //string printVector();

};
