#include <stdio.h>
#include "node.cpp"
#include <iostream>

using namespace std;

class linkedList{
    Node* head;

    public: 
        linkedList(){ 
            head = NULL;
            
        }

        void insertNode(int data){
            Node* newNode = new Node(data);
            if(head == NULL){
                head = newNode;
                return ;
            }
            
            Node* temp = head; //copy of head to move within the list
            while(temp-> next != NULL){ //keep moving until pointer reached the last node that is pointing to NULL
                temp = temp->next;
            }
            temp->next = newNode;
        };
        
        void printList(){
            Node* temp = head;
            while (temp != NULL){
                cout << temp->data << ", ";
                temp = temp->next;
            }
            cout << endl;
        }
        
        void deleteNode(int key) {
            if (head == NULL) { //nothing to delete
                return;
            }
            if (head->data == key) {//if key is the root
                Node* temp = head;
                head = head->next;
                delete temp;
                return;
            }
            Node* temp = head;//copy of root
            while(temp->next != nullptr && temp->next->data != key) {
                temp = temp->next;
            }
            if(temp->next == nullptr) {
                cout << "Node with data " << key << " not found." << endl;
                return;
            }
            Node* nodeToDelete = temp->next;
            temp->next = temp->next->next; //to link the list before deleting the node
            delete nodeToDelete;
        }
        

};