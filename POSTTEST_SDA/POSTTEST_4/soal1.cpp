#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

// Fungsi Push: Menambahkan elemen ke atas Stack
void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

// Fungsi Pop: Menghapus dan mengembalikan elemen teratas Stack
char pop(Node*& top) {
    if (top == nullptr) return '\0'; // Stack kosong
    Node* temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}

// Fungsi utama untuk membalik string
string reverseString(string s) {
    Node* stackTop = nullptr;
    string reversed = "";

    // 1️⃣ Push setiap karakter ke stack
    for (char c : s) {
        push(stackTop, c);
    }

    // 2️⃣ Pop satu per satu untuk membalik urutan
    while (stackTop != nullptr) {
        reversed += pop(stackTop);
    }

    return reversed;
}

int main() {
    string text = "Struktur Data";
    cout << "Teks asli: " << text << endl;
    cout << "Teks terbalik: " << reverseString(text) << endl;
    return 0;
}
