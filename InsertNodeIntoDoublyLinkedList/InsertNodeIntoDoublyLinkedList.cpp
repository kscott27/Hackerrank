#include <bits/stdc++.h>

using namespace std;

class DoublyLinkedListNode {
    public:
        int data;
        DoublyLinkedListNode *next;
        DoublyLinkedListNode *prev;

        DoublyLinkedListNode(int node_data) {
            this->data = node_data;
            this->next = nullptr;
            this->prev = nullptr;
        }
};

class DoublyLinkedList {
    public:
        DoublyLinkedListNode *head;
        DoublyLinkedListNode *tail;

        DoublyLinkedList() {
            this->head = nullptr;
            this->tail = nullptr;
        }

        void insert_node(int node_data) {
            DoublyLinkedListNode* node = new DoublyLinkedListNode(node_data);

            if (!this->head) {
                this->head = node;
            } else {
                this->tail->next = node;
                node->prev = this->tail;
            }

            this->tail = node;
        }
};

void print_doubly_linked_list(DoublyLinkedListNode* node, string sep, ofstream& fout) {
    while (node) {
        fout << node->data;

        node = node->next;

        if (node) {
            fout << sep;
        }
    }
}

void free_doubly_linked_list(DoublyLinkedListNode* node) {
    while (node) {
        DoublyLinkedListNode* temp = node;
        node = node->next;

        free(temp);
    }
}

// Complete the sortedInsert function below.

/*
 * For your reference:
 *
 * DoublyLinkedListNode {
 *     int data;
 *     DoublyLinkedListNode* next;
 *     DoublyLinkedListNode* prev;
 * };
 *
 */

DoublyLinkedListNode* insertBefore(DoublyLinkedListNode* currentNode, DoublyLinkedListNode* newNode) {
  newNode->next = currentNode;
  newNode->prev = currentNode->prev;
  currentNode->prev = newNode;
  if( newNode->prev != NULL )
    newNode->prev->next = newNode;
  return newNode;
}

DoublyLinkedListNode* insertAfter(DoublyLinkedListNode* currentNode, DoublyLinkedListNode* newNode) {
  newNode->next = NULL;
  newNode->prev = currentNode;
  currentNode->next = newNode;
  return newNode;
}

DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* head, int data) {  
  DoublyLinkedListNode* currentNode = head;
  while( currentNode != NULL ) {
    if( currentNode->data > data ) {
      DoublyLinkedListNode* newNode = insertBefore( currentNode, new DoublyLinkedListNode(data) );
      return currentNode == head ? newNode : head;
    }
    else if( currentNode->next == NULL ) {
      insertAfter( currentNode, new DoublyLinkedListNode(data) );
      return head;
    }
    currentNode = currentNode->next;
  }
  return new DoublyLinkedListNode(data);
}

int main() {
  return 0;
}