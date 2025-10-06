#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void exchangeHeadAndTail(Node*& head_ref) {
    if (head_ref == nullptr || head_ref->next == head_ref)
        return; // Tidak perlu ditukar jika kosong/1 node

    Node* head = head_ref;
    Node* tail = head_ref->prev;

    Node* headNext = head->next;
    Node* tailPrev = tail->prev;

    // Jika hanya 2 node
    if (headNext == tail) {
        tail->next = head;
        tail->prev = head;
        head->next = tail;
        head->prev = tail;
        head_ref = tail;
        return;
    }

    // Ubah koneksi sekitar head dan tail
    tailPrev->next = head;
    headNext->prev = tail;

    tail->next = headNext;
    tail->prev = head->prev;

    head->next = tailPrev->next;
    head->prev = tailPrev;

    // Update pointer prev dan next dari head_ref
    tail->prev->next = tail;
    head_ref->prev = tail;

    head_ref = tail; // tail jadi head baru
}

void printList(Node* head_ref) {
    if (head_ref == nullptr) {
        cout << "List kosong\n";
        return;
    }
    Node* current = head_ref;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

void insertEnd(Node*& head_ref, int data) {
    Node* newNode = new Node{data, nullptr, nullptr};
    if (head_ref == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }
    Node* tail = head_ref->prev;
    newNode->next = head_ref;
    newNode->prev = tail;
    tail->next = newNode;
    head_ref->prev = newNode;
}

int main() {
    Node* head = nullptr;

    insertEnd(head, 1);
    insertEnd(head, 2);
    insertEnd(head, 3);
    insertEnd(head, 4);
    insertEnd(head, 5);

    cout << "List sebelum exchange: ";
    printList(head);

    exchangeHeadAndTail(head);

    cout << "List setelah exchange head dan tail: ";
    printList(head);
    return 0;
}
