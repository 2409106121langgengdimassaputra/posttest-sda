#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Item {
    string namaItem;
    int jumlah;
    string tipe;
    Item* next;
    Item(const string& n, int j, const string& t) : namaItem(n), jumlah(j), tipe(t), next(nullptr) {}
};

class Inventory {
private:
    Item* head;
    int defaultJumlah;   
    int insertPos;      

public:
    Inventory(int duaDigitTerakhir, int posisiSisip) {
        head = nullptr;
        defaultJumlah = duaDigitTerakhir;
        insertPos = posisiSisip;
    }

    ~Inventory() {
        clearAll();
    }

    void clearAll() {
        Item* cur = head;
        while (cur) {
            Item* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
        head = nullptr;
    }

    void tambahItemBaru(const string& nama, const string& tipe) {
        Item* node = new Item(nama, defaultJumlah, tipe);
        if (!head) {
            head = node;
        } else {
            Item* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = node;
        }
        cout << "Item '" << nama << "' ditambahkan dengan jumlah awal " << defaultJumlah << ".\n";
    }

    void sisipkanItem(const string& nama, const string& tipe) {
        int pos = insertPos;
        Item* node = new Item(nama, defaultJumlah, tipe);
        if (pos <= 1 || !head) {
            node->next = head;
            head = node;
            cout << "Item '" << nama << "' disisipkan di posisi 1 (di depan).\n";
            return;
        }

        Item* cur = head;
        int idx = 1;
        while (cur->next && idx < pos - 1) {
            cur = cur->next;
            idx++;
        }
        node->next = cur->next;
        cur->next = node;
        cout << "Item '" << nama << "' disisipkan pada posisi " << (idx + 1) << ".\n";
    }

    void hapusItemTerakhir() {
        if (!head) {
            cout << "Inventory kosong. Tidak ada yang dihapus.\n";
            return;
        }
        if (!head->next) {
            cout << "Item '" << head->namaItem << "' dihapus (satu-satunya item).\n";
            delete head;
            head = nullptr;
            return;
        }
        Item* cur = head;
        while (cur->next && cur->next->next) cur = cur->next;
        cout << "Item '" << cur->next->namaItem << "' (terakhir) dihapus.\n";
        delete cur->next;
        cur->next = nullptr;
    }

    void gunakanItem(const string& nama) {
        if (!head) {
            cout << "Inventory kosong.\n";
            return;
        }
        Item* cur = head;
        Item* prev = nullptr;
        while (cur) {
            if (cur->namaItem == nama) break;
            prev = cur;
            cur = cur->next;
        }
        if (!cur) {
            cout << "Item '" << nama << "' tidak ditemukan di inventory.\n";
            return;
        }
        cur->jumlah -= 1;
        cout << "Item '" << nama << "' digunakan. Jumlah sekarang: " << cur->jumlah << ".\n";
        if (cur->jumlah <= 0) {
            if (!prev) {
                head = cur->next;
            } else {
                prev->next = cur->next;
            }
            delete cur;
            cout << "Jumlah menjadi 0 -> item dihapus dari inventory.\n";
        }
    }

    void tampilkanInventory() const {
        if (!head) {
            cout << "Inventory kosong.\n";
            return;
        }
        cout << "=== DAFTAR ITEM ===\n";
        Item* cur = head;
        int idx = 1;
        while (cur) {
            cout << idx << ". Nama : " << cur->namaItem
                 << " | Jumlah : " << cur->jumlah
                 << " | Tipe : " << cur->tipe << "\n";
            cur = cur->next;
            idx++;
        }
        cout << "===================\n";
    }

    void tampilkanPersonalisasi() const {
        cout << "(Personalisasi) Jumlah awal tiap item = " << defaultJumlah
             << " | Posisi sisip = " << insertPos << "\n";
    }
};

void flushInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    const string nama = "Langgeng Dimas Saputra";
    const string nim = "2409106121";

    int nim_int = 2409106121; 
    int duaDigitTerakhir = nim_int % 100; 
    int digitTerakhir = nim_int % 10; 
    int posisiSisip = digitTerakhir == 0 ? 2 : (digitTerakhir + 1); 

    Inventory inv(duaDigitTerakhir, posisiSisip);

    int pilihan = -1;
    while (true) {
        cout << "\n+----------------------------------------------------------+\n";
        cout << "|            GAME INVENTORY MANAGEMENT                    |\n";
        cout << "|  [ " << nama << " - " << nim << " ]\n";
        cout << "+----------------------------------------------------------+\n";
        cout << "1. Tambah Item Baru\n";
        cout << "2. Sisipkan Item (posisi personal)\n";
        cout << "3. Hapus Item Terakhir\n";
        cout << "4. Gunakan Item\n";
        cout << "5. Tampilkan Inventory\n";
        cout << "0. Keluar\n";
        cout << "+----------------------------------------------------------+\n";
        cout << "Pilih > ";
        if (!(cin >> pilihan)) {
            cout << "Input tidak valid. Masukkan angka.\n";
            cin.clear();
            flushInput();
            continue;
        }
        flushInput();

        if (pilihan == 0) {
            cout << "Keluar. Sampai jumpa!\n";
            break;
        }

        switch (pilihan) {
            case 1: {
                string namaItem, tipe;
                cout << "Masukkan nama item: ";
                getline(cin, namaItem);
                cout << "Masukkan tipe item (contoh: Sword, Potion): ";
                getline(cin, tipe);
                inv.tambahItemBaru(namaItem, tipe);
                break;
            }
            case 2: {
                string namaItem, tipe;
                cout << "Masukkan nama item yang akan disisipkan: ";
                getline(cin, namaItem);
                cout << "Masukkan tipe item: ";
                getline(cin, tipe);
                inv.sisipkanItem(namaItem, tipe);
                break;
            }
            case 3: {
                inv.hapusItemTerakhir();
                break;
            }
            case 4: {
                string namaItem;
                cout << "Masukkan nama item yang akan digunakan: ";
                getline(cin, namaItem);
                inv.gunakanItem(namaItem);
                break;
            }
            case 5: {
                inv.tampilkanInventory();
                inv.tampilkanPersonalisasi();
                break;
            }
            default:
                cout << "Pilihan tidak dikenali.\n";
        }
    }

    return 0;
}

