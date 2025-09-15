#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    double ipk;
};

int main() {
    const int N = 5;
    Mahasiswa mhs[N];

    cout << "Input data 5 mahasiswa:\n";
    for (int i = 0; i < N; i++) {
        cout << "Mahasiswa ke-" << i + 1 << endl;
        cout << "Nama : "; cin >> mhs[i].nama;
        cout << "NIM  : "; cin >> mhs[i].nim;
        cout << "IPK  : "; cin >> mhs[i].ipk;
        cout << endl;
    }

    // cari IPK tertinggi
    int idxTinggi = 0;
    for (int i = 1; i < N; i++) {
        if (mhs[i].ipk > mhs[idxTinggi].ipk) {
            idxTinggi = i;
        }
    }

    cout << "\nMahasiswa dengan IPK tertinggi:\n";
    cout << "Nama : " << mhs[idxTinggi].nama << endl;
    cout << "NIM  : " << mhs[idxTinggi].nim << endl;
    cout << "IPK  : " << mhs[idxTinggi].ipk << endl;

    return 0;
}