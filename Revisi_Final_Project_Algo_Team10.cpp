#include <iostream>
#include <string>
using namespace std;

const int MAX_PRODUK = 100;
const int MAX_VENDOR = 100;

string produkNama[MAX_VENDOR][MAX_PRODUK];
int produkStok[MAX_VENDOR][MAX_PRODUK];
double produkHarga[MAX_VENDOR][MAX_PRODUK];
int produkTotalTerjual[MAX_VENDOR][MAX_PRODUK];
int jumlahProduk[MAX_VENDOR] = {0};

string vendorNama[MAX_VENDOR];
string vendorAlamat[MAX_VENDOR];
string vendorKontak[MAX_VENDOR];
int jumlahVendor = 0;

void tambahVendor() {
    if (jumlahVendor >= MAX_VENDOR) {
        cout << "Kapasitas vendor penuh! Tidak dapat menambahkan vendor baru.\n";
        return;
    }
    cout << "Masukkan nama vendor: ";
    cin >> vendorNama[jumlahVendor];
    cout << "Masukkan alamat vendor: ";
    cin >> vendorAlamat[jumlahVendor];
    cout << "Masukkan kontak vendor: ";
    cin >> vendorKontak[jumlahVendor];
    jumlahVendor++;
    cout << "Vendor berhasil ditambahkan!\n";
}

void tambahProdukUntukVendor(int indexVendor) {
    if (jumlahProduk[indexVendor] >= MAX_PRODUK) {
        cout << "Kapasitas produk untuk vendor ini penuh! Tidak dapat menambahkan produk baru.\n";
        return;
    }
    cout << "Masukkan nama produk untuk " << vendorNama[indexVendor] << ": ";
    cin >> produkNama[indexVendor][jumlahProduk[indexVendor]];
    cout << "Masukkan stok produk: ";
    cin >> produkStok[indexVendor][jumlahProduk[indexVendor]];
    cout << "Masukkan harga produk: ";
    cin >> produkHarga[indexVendor][jumlahProduk[indexVendor]];
    produkTotalTerjual[indexVendor][jumlahProduk[indexVendor]] = 0;
    jumlahProduk[indexVendor]++;
    cout << "Produk berhasil ditambahkan untuk vendor " << vendorNama[indexVendor] << "!\n";
}

void tampilkanProdukUntukVendor(int indexVendor) {
    if (jumlahProduk[indexVendor] == 0) {
        cout << "Belum ada produk untuk vendor " << vendorNama[indexVendor] << ".\n";
        return;
    }
    cout << "=== Daftar Produk untuk Vendor " << vendorNama[indexVendor] << " ===\n";
    for (int i = 0; i < jumlahProduk[indexVendor]; i++) {
        cout << i + 1 << ". " << produkNama[indexVendor][i]
             << " | Stok: " << produkStok[indexVendor][i]
             << " | Harga: Rp " << produkHarga[indexVendor][i]
             << " | Total Terjual: " << produkTotalTerjual[indexVendor][i] << "\n";
    }
}

void catatPenjualanUntukVendor(int indexVendor) {
    if (jumlahProduk[indexVendor] == 0) {
        cout << "Tidak ada produk untuk dijual di vendor " << vendorNama[indexVendor] << ".\n";
        return;
    }
    tampilkanProdukUntukVendor(indexVendor);
    int pilihan, jumlah;
    cout << "Pilih nomor produk yang ingin dijual: ";
    cin >> pilihan;
    if (pilihan < 1 || pilihan > jumlahProduk[indexVendor]) {
        cout << "Nomor produk tidak valid!\n";
        return;
    }
    cout << "Masukkan jumlah produk yang terjual: ";
    cin >> jumlah;
    int index = pilihan - 1;
    if (jumlah > produkStok[indexVendor][index]) {
        cout << "Stok tidak mencukupi untuk penjualan ini.\n";
        return;
    }
    produkStok[indexVendor][index] -= jumlah;
    produkTotalTerjual[indexVendor][index] += jumlah;
    cout << "Penjualan berhasil dicatat untuk vendor " << vendorNama[indexVendor] << "!\n";
}

void produkTerlarisUntukVendor(int indexVendor) {
    if (jumlahProduk[indexVendor] == 0) {
        cout << "Belum ada produk untuk vendor " << vendorNama[indexVendor] << ".\n";
        return;
    }
    int indexTerlaris = 0;
    for (int i = 1; i < jumlahProduk[indexVendor]; i++) {
        if (produkTotalTerjual[indexVendor][i] > produkTotalTerjual[indexVendor][indexTerlaris]) {
            indexTerlaris = i;
        }
    }
    cout << "=== Produk Terlaris untuk Vendor " << vendorNama[indexVendor] << " ===\n";
    cout << "Produk: " << produkNama[indexVendor][indexTerlaris]
         << " | Total Terjual: " << produkTotalTerjual[indexVendor][indexTerlaris] << "\n";
}

void tampilkanMenuAdmin() {
    int pilihan;
    do {
        cout << "=== Menu Utama Admin ===\n";
        cout << "1. Tambah Vendor\n";
        cout << "2. Tambah Produk untuk Vendor\n";
        cout << "3. Tampilkan Produk untuk Vendor\n";
        cout << "4. Catat Penjualan untuk Vendor\n";
        cout << "5. Produk Terlaris untuk Vendor\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        int vendorPilih;
        switch (pilihan) {
            case 1:
                tambahVendor();
                break;
            case 2:
                cout << "Pilih vendor untuk menambah produk (1 - " << jumlahVendor << "): ";
                cin >> vendorPilih;
                if (vendorPilih < 1 || vendorPilih > jumlahVendor) {
                    cout << "Vendor tidak valid!\n";
                } else {
                    tambahProdukUntukVendor(vendorPilih - 1);
                }
                break;
            case 3:
                cout << "Pilih vendor untuk menampilkan produk (1 - " << jumlahVendor << "): ";
                cin >> vendorPilih;
                if (vendorPilih < 1 || vendorPilih > jumlahVendor) {
                    cout << "Vendor tidak valid!\n";
                } else {
                    tampilkanProdukUntukVendor(vendorPilih - 1);
                }
                break;
            case 4:
                cout << "Pilih vendor untuk mencatat penjualan (1 - " << jumlahVendor << "): ";
                cin >> vendorPilih;
                if (vendorPilih < 1 || vendorPilih > jumlahVendor) {
                    cout << "Vendor tidak valid!\n";
                } else {
                    catatPenjualanUntukVendor(vendorPilih - 1);
                }
                break;
            case 5:
                cout << "Pilih vendor untuk melihat produk terlaris (1 - " << jumlahVendor << "): ";
                cin >> vendorPilih;
                if (vendorPilih < 1 || vendorPilih > jumlahVendor) {
                    cout << "Vendor tidak valid!\n";
                } else {
                    produkTerlarisUntukVendor(vendorPilih - 1);
                }
                break;
            case 6:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                break;
        }
        cout << "\n";
    } while (pilihan != 6);
}

void tampilkanMenuUser() {
    int pilihan;
    do {
        cout << "=== Menu Utama User ===\n";
        cout << "1. Tampilkan Produk untuk Vendor\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        int vendorPilihUser;
        switch (pilihan) {
            case 1:
                cout << "Pilih vendor untuk menampilkan produk (1 - " << jumlahVendor << "): ";
                cin >> vendorPilihUser;
                if (vendorPilihUser < 1 || vendorPilihUser > jumlahVendor) {
                    cout << "Vendor tidak valid!\n";
                } else {
                    tampilkanProdukUntukVendor(vendorPilihUser - 1);
                }
                break;
            case 6:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid atau tidak diizinkan untuk role user!\n";
                break;
        }
        cout << "\n";
    } while (pilihan != 6);
}

int main() {
    string role;
    do {
        cout << "Masukkan role Anda (admin/user): ";
        cin >> role;

        if (role == "admin") {
            tampilkanMenuAdmin();
        } else if (role == "user") {
            tampilkanMenuUser();
        } else {
            cout << "Role tidak valid! Harap masukkan 'admin' atau 'user'.\n";
        }
    } while (role != "exit");

    return 0;
}