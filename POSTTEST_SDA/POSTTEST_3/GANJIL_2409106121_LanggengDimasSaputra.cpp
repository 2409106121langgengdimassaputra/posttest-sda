#include <iostream>
#include <iomanip>   // setw
#include <string>
using namespace std;

// ==================== STRUCT NODE ====================
struct Node {
    int id;
    string nama;
    float nilai;
    Node *prev; // pointer ke node sebelumnya
    Node *next; // pointer ke node selanjutnya
};

Node *head = NULL;
Node *tail = NULL;

// ==================== FUNGSI TAMBAH DEPAN ====================
void insertDepan(int id, string nama, float nilai) {
    Node *baru = new Node;
    baru->id = id;
    baru->nama = nama;
    baru->nilai = nilai;
    baru->prev = NULL;
    baru->next = head;

    if (head != NULL)
        head->prev = baru;
    else
        tail = baru; // jika list kosong

    head = baru;
    cout << "Data berhasil ditambahkan di depan!\n";
}

// ==================== FUNGSI TAMBAH BELAKANG ====================
void insertBelakang(int id, string nama, float nilai) {
    Node *baru = new Node;
    baru->id = id;
    baru->nama = nama;
    baru->nilai = nilai;
    baru->next = NULL;
    baru->prev = tail;

    if (tail != NULL)
        tail->next = baru;
    else
        head = baru; // jika list kosong

    tail = baru;
    cout << "Data berhasil ditambahkan di belakang!\n";
}

// ==================== FUNGSI HAPUS DATA ====================
void hapusData(int id) {
    Node *hapus = head;
    while (hapus != NULL && hapus->id != id)
        hapus = hapus->next;

    if (hapus == NULL) {
        cout << "Data dengan ID " << id << " tidak ditemukan!\n";
        return;
    }

    if (hapus->prev != NULL)
        hapus->prev->next = hapus->next;
    else
        head = hapus->next;

    if (hapus->next != NULL)
        hapus->next->prev = hapus->prev;
    else
        tail = hapus->prev;

    delete hapus;
    cout << "Data berhasil dihapus!\n";
}

// ==================== TAMPIL DEPAN -> BELAKANG ====================
void tampilDepan() {
    if (head == NULL) {
        cout << "List masih kosong.\n";
        return;
    }
    cout << left << setw(5) << "ID" << setw(15) << "Nama" << setw(8) << "Nilai" << "\n";
    cout << "--------------------------------\n";
    Node *bantu = head;
    while (bantu != NULL) {
        cout << left << setw(5) << bantu->id << setw(15) << bantu->nama
             << setw(8) << bantu->nilai << "\n";
        bantu = bantu->next;
    }
}

// ==================== TAMPIL BELAKANG -> DEPAN ====================
void tampilBelakang() {
    if (tail == NULL) {
        cout << "List masih kosong.\n";
        return;
    }
    cout << left << setw(5) << "ID" << setw(15) << "Nama" << setw(8) << "Nilai" << "\n";
    cout << "--------------------------------\n";
    Node *bantu = tail;
    while (bantu != NULL) {
        cout << left << setw(5) << bantu->id << setw(15) << bantu->nama
             << setw(8) << bantu->nilai << "\n";
        bantu = bantu->prev;
    }
}

// ==================== CARI DATA (ID / NAMA) ====================
void cariData() {
    if (head == NULL) {
        cout << "List kosong.\n";
        return;
    }

    int pilihan;
    cout << "Cari berdasarkan:\n1. ID\n2. Nama\nPilih: ";
    cin >> pilihan;

    if (pilihan == 1) {
        int idCari;
        cout << "Masukkan ID: ";
        cin >> idCari;
        Node *bantu = head;
        while (bantu != NULL && bantu->id != idCari)
            bantu = bantu->next;
        if (bantu == NULL)
            cout << "Data ID " << idCari << " tidak ditemukan.\n";
        else
            cout << ">> Ditemukan: ID=" << bantu->id << ", Nama=" << bantu->nama
                 << ", Nilai=" << bantu->nilai << "\n";
    }
    else if (pilihan == 2) {
        string namaCari;
        cout << "Masukkan Nama: ";
        cin.ignore();
        getline(cin, namaCari);
        Node *bantu = head;
        bool ketemu = false;
        while (bantu != NULL) {
            if (bantu->nama == namaCari) {
                cout << ">> Ditemukan: ID=" << bantu->id << ", Nama=" << bantu->nama
                     << ", Nilai=" << bantu->nilai << "\n";
                ketemu = true;
            }
            bantu = bantu->next;
        }
        if (!ketemu)
            cout << "Data Nama " << namaCari << " tidak ditemukan.\n";
    }
    else
        cout << "Pilihan tidak valid!\n";
}

// ==================== MAIN MENU ====================
int main() {
    int pilihan, id;
    string nama;
    float nilai;

    do {
        cout << "\n====== MENU DOUBLE LINKED LIST ======\n";
        cout << "1. Tambah Data Depan\n";
        cout << "2. Tambah Data Belakang\n";
        cout << "3. Hapus Data (ID)\n";
        cout << "4. Tampil Dari Depan\n";
        cout << "5. Tampil Dari Belakang\n";
        cout << "6. Cari Data (ID/Nama)\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan ID: "; cin >> id;
                cin.ignore();
                cout << "Masukkan Nama: "; getline(cin, nama);
                cout << "Masukkan Nilai: "; cin >> nilai;
                insertDepan(id, nama, nilai);
                break;
            case 2:
                cout << "Masukkan ID: "; cin >> id;
                cin.ignore();
                cout << "Masukkan Nama: "; getline(cin, nama);
                cout << "Masukkan Nilai: "; cin >> nilai;
                insertBelakang(id, nama, nilai);
                break;
            case 3:
                cout << "Masukkan ID yang akan dihapus: ";
                cin >> id;
                hapusData(id);
                break;
            case 4:
                tampilDepan();
                break;
            case 5:
                tampilBelakang();
                break;
            case 6:
                cariData();
                break;
            case 0:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Menu tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}

