// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr), current(nullptr) {}

Train::~Train() {
    if (!first) return;
    Car* iterator = first->next;
    while (iterator != first) {
        Car* next = iterator->next;
        delete iterator;
        iterator = next;
    }
    delete first;
}

void Train::addCar(bool light) {
    Car* newCar = new Car{ light, nullptr, nullptr };
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
        current = first;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    if (!first) return 0;
    resetOps();
    current = first;

    if (!current->light) {
        current->light = true;
    }

    int totalLength = 0;
    bool isFound = false;

    while (!isFound) {
        while (true) {
            current = current->next;
            countOp++;
            totalLength++;

            if (current->light) {
                current->light = false;
                break;
            }
        }

        int stepsBack = 0;
        while (stepsBack < totalLength) {
            current = current->prev;
            countOp++;
            stepsBack++;
        }

        if (!current->light) {
            isFound = true;
        } else {
            totalLength = 0;
        }
    }

    return totalLength;
}

int Train::getOpCount() {
    return countOp;
}

void Train::resetOps() {
    countOp = 0;
}
