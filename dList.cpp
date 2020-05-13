// Josh Falejczyk CS101 Project 2: Racing Stats Doubly Linked List

#ifndef DLIST_H
#define DLIST_H
#include <stdio.h>
#include <iostream>

using namespace std;

typedef struct node { // Node structure for each object in list

    float fuel;
    float time;
    /* Node A dominates Node B if the time for A is less than 
    B and the fuel of A is less than or equal to B */
    bool dominated; // True if Node is dominated by another Node, results in deletion from LL
    node* next;
    node* prev;

} Node; 

class dList {

    public:

        // Merges two subarrays of array[]. 
        // First subarray is array[left..middle] 
        // Second subarray is array[middle + 1..right] 
        void merge(node **array, int left, int middle, int right) { 

            int i, j, k; 
            int leftSubarraySize = middle - left + 1; 
            int rightSubarraySize =  right - middle; 
        
            /* create temp arrays */
            node** leftArray = (node**)malloc(sizeof(node*) * leftSubarraySize);
            node** rightArray = (node**)malloc(sizeof(node*) * rightSubarraySize); 
        
            /* Copy data to temp arrays leftArray[] and rightArray[] */
            for (i = 0; i < leftSubarraySize; i ++) {

                leftArray[i] = array[left + i];

            } 
            for (j = 0; j < rightSubarraySize; j ++) {

                rightArray[j] = array[middle + 1 + j]; 

            }
        
            /* Merge the temp arrays back into array[left..right]*/
            i = 0; // Initial index of first subarray 
            j = 0; // Initial index of second subarray 
            k = left; // Initial index of merged subarray 
            while (i < leftSubarraySize && j < rightSubarraySize) { 
                
                if (leftArray[i]->time < rightArray[j]->time) { 
                    
                    array[k] = leftArray[i]; 
                    i++; 

                } else if (leftArray[i]->time == rightArray[j]->time) {

                    if (leftArray[i]->fuel < rightArray[j]->fuel) {

                        array[k] = leftArray[i];
                        i ++;

                    } else {

                        array[k] = rightArray[j];
                        j ++;

                    }

                } else { 
                
                    array[k] = rightArray[j]; 
                    j++; 

                } 
                k++; 
            } 
        
            /* Copy the remaining elements of leftArray[], if there 
            are any */
            while (i < leftSubarraySize) { 
            
                array[k] = leftArray[i]; 
                i++; 
                k++; 

            } 
        
            /* Copy the remaining elements of rightArray[], if there 
            are any */
            while (j < rightSubarraySize) {

                array[k] = rightArray[j]; 
                j++; 
                k++;

            } 
        } 
  
        /* left is for left index and right is right index of the 
        sub-array of array to be sorted */
        void mergeSort(node **array, int left, int right) {

            if (left < right) {

                int middle = (left + right) / 2; 
        
                // Sort first and second halves 
                mergeSort(array, left, middle); 
                mergeSort(array, middle + 1, right); 
        
                merge(array, left, middle, right); 

            } 
        } 

        // Deletes Node from LL given Node
        void deleteNode(node* del) 
        { 

            // Node to be deleted is head
            if (del->prev == NULL) {

                del->next->prev = NULL;
                head = del->next;
                

                return;

            } else if (del->next == NULL) { // If node to be deleted is tail

                del->prev->next = NULL;
                tail = del->prev;
                

                return;

            } else { // Node to be deleted is middle

                del->prev->next = del->next;
                del->next->prev = del->prev;
                

                return;

            }


            return; 
        }

        // Constructor
        dList(float timeArray[], float fuelArray[], int size) {

            // Setup of LL
            array = (node**)malloc(sizeof(node*) * size);
            counter = size - 1;
            counter ++;
            node* node1 = (node*)malloc(sizeof(node));
            node1->next = NULL;
            node1->prev = NULL;
            node1->time = timeArray[0];
            node1->fuel = fuelArray[0];
            node1->dominated = 0;
            head = node1;
            tail = node1;
            array[0] = node1;
            for (int i = 1; i < size; i ++) {

                node* node2 = (node*)malloc(sizeof(node));
                node2->prev = NULL;
                node2->next = head;
                head->prev = node2;
                head = node2;
                node2->time = timeArray[i];
                node2->fuel = fuelArray[i];
                node2->dominated = 0;

            }
            node* nodePtr = head;
            for (int i = 0; i < size; i ++) {

                array[i] = nodePtr;
                nodePtr = nodePtr->next;

            }

            // Sort
            mergeSort(array, 0, size - 1);

            // Fix node ordering
            head = array[0];
            tail = array[size - 1];
            for (int i = 1; i < size - 1; i ++) {

                array[i]->next = array[i + 1];
                array[i]->prev = array[i - 1];

            }
            head->next = array[1];
            head->prev = NULL;
            tail->prev = array[size - 2];
            tail->next = NULL;

            // Handle dominated nodes
            for (int i = 0; i < size - 1; i ++) {

                if (array[i]->time <= array[i + 1]->time && array[i]->fuel <= array[i + 1]->fuel) {

                    array[i + 1]->dominated = true;
                    deleteNode(array[i + 1]);

                }

            }
            
        }

        // Output function
        void out(char order = 'a') {

            if (order == 'a') {

                for (node* nodePtr = head; nodePtr != NULL; nodePtr = nodePtr->next) { // Test, outputs all nodes, even dominated
                        
                    cout << "Time " << nodePtr->time << "  Fuel " << nodePtr->fuel << endl;

                }

            } else if (order == 'd') {

                for (node* nodePtr = tail; nodePtr != NULL; nodePtr = nodePtr->prev) {

                    cout << "Time " << nodePtr->time << "  Fuel " << nodePtr->fuel << endl;

                }

            } else {

                cout << "Invalid order" << endl;

            }

        }

        // Output function similar to former, but outputs "limit"-many entries of LL
        void out(int limit, char order = 'a') {

            int counter = 0;
            if (order == 'a') {

                for (node* nodePtr = head; nodePtr != NULL && counter < limit; nodePtr = nodePtr->next) {

                    cout << "Time " << nodePtr->time << "  Fuel " << nodePtr->fuel << endl;
                    counter ++;

                }

            } else if (order == 'd') {

                for (node* nodePtr = tail; nodePtr != NULL && counter < limit; nodePtr = nodePtr->prev) {

                    cout << "Time " << nodePtr->time << "  Fuel " << nodePtr->fuel << endl;
                    counter ++;

                }

            } else {

                cout << "Invalid order" << endl;

            }

        }

        // Insert Node into LL
        int insert(float newTime, float newFuel) {

            node* newNode = (node*)malloc(sizeof(node)); // Create node
            newNode->time = newTime;
            newNode->fuel = newFuel;
            newNode->dominated = 0;
            newNode->next = NULL;
            newNode->prev = NULL;
            counter ++;

            node* nodePtr = head;
            node* extraNode;
            if (head->time > newNode->time) { // Adding before head

                newNode->prev = NULL;
                newNode->next = head;
                head->prev = newNode;
                head = newNode;

            } else {
                
                while (nodePtr && nodePtr->time <= newNode->time) {

                    nodePtr = nodePtr->next;

                }
                if (nodePtr != NULL && nodePtr->time >= newNode->time) { // Adds in middle

                    extraNode = nodePtr->prev;
                    extraNode->next = newNode;
                    nodePtr->prev = newNode;
                    newNode->prev = extraNode;
                    newNode->next = nodePtr;

                } else { // Adding after tail

                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;
                    newNode->next = NULL;

                }

            }

            // Check for domination and remove dominated nodes
            node* dominator = head;
            node* nodePtr2 = head->next;
            while (nodePtr2) {

                if (nodePtr2->fuel < dominator->fuel) {

                    dominator = nodePtr2;

                } else {

                    nodePtr2->dominated = true;
                    deleteNode(nodePtr2);

                }
                nodePtr2 = nodePtr2->next;

            }


            return counter;
        }

    private:

        node** array; // Array implementation of LL
        node* head;
        node* tail;
        int counter; // Counts size of LL

};

#endif