#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PRODUK 50
#define PANJANG_NAMA 100

/* Array utama: nama menggunakan array karakter 2 dimensi,
   sedangkan harga, stok, dan terjual menggunakan array 1 dimensi. */
char nama[MAX_PRODUK][PANJANG_NAMA];
int harga[MAX_PRODUK];
int stok[MAX_PRODUK];
int terjual[MAX_PRODUK];
long long pendapatanProduk[MAX_PRODUK];
long long totalPendapatanKumulatif = 0;
int jumlahProduk = 0;

void bersihkanBaris(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int bacaInt(const char *pesan) {
    char buffer[128], tambahan;
    int nilai;
    while (1) {
        printf("%s", pesan);
        if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
        if (sscanf(buffer, " %d %c", &nilai, &tambahan) == 1) return nilai;
        printf("Input harus berupa bilangan bulat. Coba lagi.\n");
    }
}

void bacaTeks(const char *pesan, char hasil[], int ukuran) {
    size_t panjang;
    while (1) {
        printf("%s", pesan);
        if (!fgets(hasil, ukuran, stdin)) {
            hasil[0] = '\0';
            return;
        }
        panjang = strlen(hasil);
        if (panjang > 0 && hasil[panjang - 1] == '\n') hasil[panjang - 1] = '\0';
        else bersihkanBaris();
        if (hasil[0] != '\0') return;
        printf("Nama tidak boleh kosong.\n");
    }
}

int samaNama(const char a[], const char b[]) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++; b++;
    }
    return *a == '\0' && *b == '\0';
}

void dataAwal(void) {
    const char daftarNama[5][PANJANG_NAMA] = {
        "Nasi Goreng", "Mie Goreng", "Air Mineral", "Es Teh", "Roti Cokelat"
    };
    int daftarHarga[5] = {15000, 12000, 5000, 5000, 7000};
    int daftarStok[5] = {20, 15, 40, 30, 18};
    int i;
    jumlahProduk = 5;
    for (i = 0; i < jumlahProduk; i++) {
        strcpy(nama[i], daftarNama[i]);
        harga[i] = daftarHarga[i];
        stok[i] = daftarStok[i];
        terjual[i] = 0;
        pendapatanProduk[i] = 0;
    }
}

void tampilkanProduk(void) {
    int i;
    if (jumlahProduk == 0) {
        printf("\nBelum ada produk.\n");
        return;
    }
    printf("\n================ DAFTAR PRODUK ================\n");
    printf("%-5s %-25s %-15s %-10s %-12s\n", "No", "Nama Produk", "Harga (Rp)", "Stok", "Terjual");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i < jumlahProduk; i++)
        printf("%-5d %-25s %-15d %-10d %-12d\n", i + 1, nama[i], harga[i], stok[i], terjual[i]);
}

void tambahProduk(void) {
    char namaBaru[PANJANG_NAMA];
    int h, s, i;
    if (jumlahProduk >= MAX_PRODUK) {
        printf("Kapasitas penuh. Maksimal %d produk.\n", MAX_PRODUK);
        return;
    }
    bacaTeks("Nama produk: ", namaBaru, sizeof(namaBaru));
    for (i = 0; i < jumlahProduk; i++) {
        if (samaNama(nama[i], namaBaru)) {
            printf("Produk dengan nama tersebut sudah tersedia.\n");
            return;
        }
    }
    h = bacaInt("Harga produk (Rp): ");
    s = bacaInt("Stok awal: ");
    if (h < 0 || s < 0) {
        printf("Harga dan stok tidak boleh negatif. Produk tidak ditambahkan.\n");
        return;
    }
    strcpy(nama[jumlahProduk], namaBaru);
    harga[jumlahProduk] = h;
    stok[jumlahProduk] = s;
    terjual[jumlahProduk] = 0;
    pendapatanProduk[jumlahProduk] = 0;
    jumlahProduk++;
    printf("Produk berhasil ditambahkan.\n");
}

int cariIndeksNama(const char kataKunci[]) {
    int i;
    for (i = 0; i < jumlahProduk; i++) {
        if (samaNama(nama[i], kataKunci)) return i;
    }
    return -1;
}

void ubahProduk(void) {
    int no, indeks, pilihan;
    tampilkanProduk();
    if (jumlahProduk == 0) return;
    no = bacaInt("Nomor produk yang akan diubah (0 untuk batal): ");
    if (no == 0) return;
    if (no < 1 || no > jumlahProduk) {
        printf("Nomor produk tidak ditemukan.\n");
        return;
    }
    indeks = no - 1;
    printf("1. Ubah nama\n2. Ubah harga\n3. Ubah stok\n4. Ubah harga dan stok\n");
    pilihan = bacaInt("Pilih perubahan: ");
    if (pilihan == 1) {
        char namaBaru[PANJANG_NAMA];
        bacaTeks("Nama baru: ", namaBaru, sizeof(namaBaru));
        if (cariIndeksNama(namaBaru) != -1 && !samaNama(nama[indeks], namaBaru)) {
            printf("Nama tersebut sudah digunakan produk lain.\n"); return;
        }
        strcpy(nama[indeks], namaBaru);
    } else if (pilihan >= 2 && pilihan <= 4) {
        int h = harga[indeks], s = stok[indeks];
        if (pilihan == 2 || pilihan == 4) h = bacaInt("Harga baru (Rp): ");
        if (pilihan == 3 || pilihan == 4) s = bacaInt("Stok baru: ");
        if (h < 0 || s < 0) {
            printf("Harga dan stok tidak boleh negatif. Perubahan dibatalkan.\n"); return;
        }
        harga[indeks] = h; stok[indeks] = s;
    } else {
        printf("Pilihan perubahan tidak tersedia.\n"); return;
    }
    printf("Data produk berhasil diperbarui.\n");
}

void tambahStok(void) {
    int no, tambahan;
    tampilkanProduk();
    if (jumlahProduk == 0) return;
    no = bacaInt("Nomor produk: ");
    if (no < 1 || no > jumlahProduk) {
        printf("Nomor produk tidak ditemukan.\n"); return;
    }
    tambahan = bacaInt("Jumlah stok yang ditambahkan: ");
    if (tambahan <= 0) {
        printf("Penambahan stok harus lebih dari nol.\n"); return;
    }
    stok[no - 1] += tambahan;
    printf("Stok %s sekarang %d.\n", nama[no - 1], stok[no - 1]);
}

void transaksi(void) {
    int jumlahBeli[MAX_PRODUK] = {0};
    int no, qty, i, ada = 0;
    long long total = 0;
    if (jumlahProduk == 0) { printf("Belum ada produk untuk dijual.\n"); return; }
    printf("\n=== TRANSAKSI PENJUALAN ===\n");
    printf("Masukkan nomor produk dan jumlah pembelian. Nomor 0 untuk selesai.\n");
    tampilkanProduk();
    while (1) {
        no = bacaInt("Nomor produk (0 selesai): ");
        if (no == 0) break;
        if (no < 1 || no > jumlahProduk) { printf("Nomor produk tidak ditemukan.\n"); continue; }
        qty = bacaInt("Jumlah pembelian: ");
        if (qty <= 0) { printf("Jumlah pembelian harus lebih dari nol.\n"); continue; }
        if (jumlahBeli[no - 1] + qty > stok[no - 1]) {
            printf("Stok %s tidak mencukupi. Tersedia %d, sudah dimasukkan %d.\n",
                   nama[no - 1], stok[no - 1], jumlahBeli[no - 1]);
            continue;
        }
        jumlahBeli[no - 1] += qty;
        printf("%s x %d dicatat.\n", nama[no - 1], qty);
    }
    for (i = 0; i < jumlahProduk; i++) if (jumlahBeli[i] > 0) ada = 1;
    if (!ada) { printf("Transaksi dibatalkan: tidak ada produk yang dibeli.\n"); return; }
    printf("\n================ STRUK PEMBELIAN ================\n");
    printf("%-25s %-8s %-12s %-12s\n", "Produk", "Jumlah", "Harga", "Subtotal");
    for (i = 0; i < jumlahProduk; i++) {
        if (jumlahBeli[i] > 0) {
            long long subtotal = (long long)harga[i] * jumlahBeli[i];
            printf("%-25s %-8d %-12d %-12lld\n", nama[i], jumlahBeli[i], harga[i], subtotal);
            total += subtotal;
        }
    }
    printf("--------------------------------------------------\nTotal pembayaran: Rp %lld\n", total);
    /* Stok dan jumlah terjual baru diperbarui setelah transaksi selesai. */
    for (i = 0; i < jumlahProduk; i++) {
        stok[i] -= jumlahBeli[i];
        terjual[i] += jumlahBeli[i];
        pendapatanProduk[i] += (long long)harga[i] * jumlahBeli[i];
        totalPendapatanKumulatif += (long long)harga[i] * jumlahBeli[i];
    }
    printf("Transaksi berhasil. Stok telah diperbarui.\n");
}

void cariProduk(void) {
    char kataKunci[PANJANG_NAMA];
    int indeks;
    bacaTeks("Masukkan nama produk yang dicari: ", kataKunci, sizeof(kataKunci));
    indeks = cariIndeksNama(kataKunci);
    if (indeks == -1) printf("Produk '%s' tidak ditemukan.\n", kataKunci);
    else printf("Ditemukan: %s | Harga: Rp %d | Stok: %d | Terjual: %d\n",
                nama[indeks], harga[indeks], stok[indeks], terjual[indeks]);
}

void tukarProduk(int a, int b) {
    char tempNama[PANJANG_NAMA];
    int temp;
    strcpy(tempNama, nama[a]); strcpy(nama[a], nama[b]); strcpy(nama[b], tempNama);
    temp = harga[a]; harga[a] = harga[b]; harga[b] = temp;
    temp = stok[a]; stok[a] = stok[b]; stok[b] = temp;
    temp = terjual[a]; terjual[a] = terjual[b]; terjual[b] = temp;
    { long long tempPendapatan = pendapatanProduk[a]; pendapatanProduk[a] = pendapatanProduk[b]; pendapatanProduk[b] = tempPendapatan; }
}

void urutkanProduk(void) {
    int pilihan, i, j;
    pilihan = bacaInt("\n1. Harga termurah\n2. Jumlah terjual terbanyak\nPilih: ");
    if (pilihan != 1 && pilihan != 2) { printf("Pilihan pengurutan tidak tersedia.\n"); return; }
    for (i = 0; i < jumlahProduk - 1; i++) {
        for (j = 0; j < jumlahProduk - i - 1; j++) {
            int perluTukar = (pilihan == 1) ? (harga[j] > harga[j + 1]) : (terjual[j] < terjual[j + 1]);
            if (perluTukar) tukarProduk(j, j + 1);
        }
    }
    printf("Produk berhasil diurutkan.\n");
    tampilkanProduk();
}

void laporanPenjualan(void) {
    int i, indeksTerlaris = -1;
    long long totalUnit = 0;
    printf("\n================ LAPORAN PENJUALAN ================\n");
    printf("%-5s %-25s %-12s %-15s\n", "No", "Nama Produk", "Terjual", "Pendapatan (Rp)");
    for (i = 0; i < jumlahProduk; i++) {
        long long pendapatan = pendapatanProduk[i];
        printf("%-5d %-25s %-12d %-15lld\n", i + 1, nama[i], terjual[i], pendapatan);
        totalUnit += terjual[i];
        if (indeksTerlaris == -1 || terjual[i] > terjual[indeksTerlaris]) indeksTerlaris = i;
    }
    printf("----------------------------------------------------\n");
    printf("Total unit terjual : %lld\n", totalUnit);
    printf("Total pendapatan   : Rp %lld\n", totalPendapatanKumulatif);
    if (indeksTerlaris == -1 || totalUnit == 0) printf("Produk terlaris    : Belum ada penjualan.\n");
    else {
        printf("Produk terlaris    : %s (%d unit)\n", nama[indeksTerlaris], terjual[indeksTerlaris]);
        printf("Catatan: jika jumlah tertinggi sama, produk pertama dalam daftar ditampilkan.\n");
    }
}

void cekStokMenipis(void) {
    int i, ditemukan = 0;
    printf("\n========== PRODUK DENGAN STOK KURANG DARI 5 ==========\n");
    for (i = 0; i < jumlahProduk; i++) {
        if (stok[i] < 5) {
            printf("%-25s Stok: %d\n", nama[i], stok[i]);
            ditemukan = 1;
        }
    }
    if (!ditemukan) printf("Tidak ada produk dengan stok kurang dari 5.\n");
}

void tampilkanMenu(void) {
    printf("\n==================================================\n");
    printf("       SISTEM MONITORING STOK DAN PENJUALAN       \n");
    printf("                  KANTIN KAMPUS                   \n");
    printf("==================================================\n");
    printf("1. Lihat Daftar Produk\n2. Tambah Produk\n3. Ubah Produk\n");
    printf("4. Transaksi Penjualan\n5. Tambah Stok\n6. Cari Produk\n");
    printf("7. Urutkan Produk\n8. Laporan Penjualan\n9. Cek Stok Menipis\n0. Keluar\n");
}

int main(void) {
    int pilihan;
    dataAwal();
    do {
        tampilkanMenu();
        pilihan = bacaInt("Pilih menu: ");
        switch (pilihan) {
            case 1: tampilkanProduk(); break;
            case 2: tambahProduk(); break;
            case 3: ubahProduk(); break;
            case 4: transaksi(); break;
            case 5: tambahStok(); break;
            case 6: cariProduk(); break;
            case 7: urutkanProduk(); break;
            case 8: laporanPenjualan(); break;
            case 9: cekStokMenipis(); break;
            case 0: printf("Terima kasih. Program selesai.\n"); break;
            default: printf("Pilihan menu tidak tersedia. Masukkan angka 0 sampai 9.\n");
        }
    } while (pilihan != 0);
    return 0;
}
