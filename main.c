#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRANSAKSI 10
#define JUMLAH_ALAT 5

// --- Data Perlengkapan Camping ---
char namaAlat[JUMLAH_ALAT][30] = {
    "Tenda Kapasitas 4 Orang",
    "Sleeping Bag",
    "Kompor Portable",
    "Matras Camping",
    "Lampu Camping"
};

int hargaAlat[JUMLAH_ALAT] = {50000, 15000, 20000, 10000, 12000};

// --- DATA RIWAYAT TRANSAKSI (Array Paralel) ---
char riwayatNama[MAX_TRANSAKSI][50];
char riwayatAlat[MAX_TRANSAKSI][30];
int riwayatUnit[MAX_TRANSAKSI];
int riwayatLama[MAX_TRANSAKSI];
long riwayatTotal[MAX_TRANSAKSI];
int jumlahTransaksi = 0; // Counter jumlah transaksi saat ini

// --- FUNGSI ---
void tampilkanDaftarPeralatan();
float hitungDiskon(int lamaSewa);
void prosesPenyewaan();
void tampilkanRiwayat();

// --- FUNGSI UTAMA ---
int main() {
    int pilihan;

    do {
        printf("\n=====================================\n");
        printf("           ADVENTURE CAMP            \n");
        printf("    SISTEM PENYEWAAN PERALATAN       \n");
        printf("=====================================\n");
        printf("1. Lihat Daftar Peralatan\n");
        printf("2. Sewa Peralatan\n");
        printf("3. Lihat Riwayat Transaksi\n");
        printf("4. Keluar\n");
        printf("-------------------------------------\n");
        printf("Pilih menu [1-4]: ");
        scanf("%d", &pilihan);
        getchar(); // Membersihkan buffer enter

        switch (pilihan) {
            case 1:
                tampilkanDaftarPeralatan();
                break;
            case 2:
                prosesPenyewaan();
                break;
            case 3:
                tampilkanRiwayat();
                break;
            case 4:
                printf("\nTerima kasih telah menggunakan layanan Adventure Camp!\n");
                break;
            default:
                printf("\nPilihan tidak valid. Silakan pilih menu 1 - 4.\n");
        }
    } while (pilihan != 4);

    return 0;
}

// -----------------------------------------------------------------
// 1. FUNGSI MENAMPILKAN DAFTAR PERALATAN
// -----------------------------------------------------------------
void tampilkanDaftarPeralatan() {
    printf("\n======================================================\n");
    printf("               DAFTAR PERALATAN CAMPING               \n");
    printf("======================================================\n");
    printf("No.  %-30s %s\n", "Peralatan", "Harga Sewa / Hari");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < JUMLAH_ALAT; i++) {
        printf("%-4d %-30s Rp%d\n", i + 1, namaAlat[i], hargaAlat[i]);
    }
    printf("======================================================\n");
}

// -----------------------------------------------------------------
// 2. FUNGSI MENGHITUNG PERSENTASE DISKON
// -----------------------------------------------------------------
float hitungDiskon(int lamaSewa) {
    if (lamaSewa >= 5) {
        return 0.15; // Diskon 15%
    } else if (lamaSewa >= 3) {
        return 0.10; // Diskon 10%
    } else {
        return 0.00; // Diskon 0%
    }
}

// -----------------------------------------------------------------
// 3. FUNGSI PROSES PENYEWAAN & STRUK
// -----------------------------------------------------------------
void prosesPenyewaan() {
    // Cek jika kapasitas riwayat transaksi sudah penuh
    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        printf("\n[PEMBERITAHUAN] Kapasitas transaksi penuh! Tidak dapat menerima transaksi baru.\n");
        return;
    }

    char nama[50];
    int kodeAlat, jumlahUnit, lamaSewa;
    char kembaliMenu;

    printf("\n=====================================\n");
    printf("          FORM PENYEWAAN             \n");
    printf("=====================================\n");

    // Input Nama Penyewa
    printf("Masukkan Nama Penyewa : ");
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = 0; // Menghapus newline

    // Validasi Pilihan Peralatan
    do {
        tampilkanDaftarPeralatan();
        printf("Pilih Nomor Peralatan [1-%d]: ", JUMLAH_ALAT);
        scanf("%d", &kodeAlat);
        if (kodeAlat < 1 || kodeAlat > JUMLAH_ALAT) {
            printf("[Peringatan] Nomor peralatan tidak valid. Silakan ulangi!\n");
        }
    } while (kodeAlat < 1 || kodeAlat > JUMLAH_ALAT);

    // Validasi Jumlah Unit (Minimal 1)
    do {
        printf("Masukkan Jumlah Unit (Min. 1) : ");
        scanf("%d", &jumlahUnit);
        if (jumlahUnit < 1) {
            printf("[Peringatan] Jumlah unit minimal 1. Silakan ulangi!\n");
        }
    } while (jumlahUnit < 1);

    // Validasi Lama Sewa (Minimal 1 Hari)
    do {
        printf("Masukkan Lama Sewa (Hari, Min. 1) : ");
        scanf("%d", &lamaSewa);
        if (lamaSewa < 1) {
            printf("[Peringatan] Lama sewa minimal 1 hari. Silakan ulangi!\n");
        }
    } while (lamaSewa < 1);

    // Perhitungan Biaya
    int indexAlat = kodeAlat - 1;
    long hargaSatuan = hargaAlat[indexAlat];
    long subtotal = hargaSatuan * jumlahUnit * lamaSewa;
    float persenDiskon = hitungDiskon(lamaSewa);
    long diskon = (long)(subtotal * persenDiskon);
    long totalBayar = subtotal - diskon;

    // Cetak Struk Penyewaan
    printf("\n=====================================\n");
    printf("           ADVENTURE CAMP            \n");
    printf("           STRUK PENYEWAAN           \n");
    printf("=====================================\n");
    printf("Nama Penyewa   : %s\n", nama);
    printf("Peralatan      : %s\n", namaAlat[indexAlat]);
    printf("Harga per Hari : Rp%ld\n", hargaSatuan);
    printf("Jumlah Unit    : %d\n", jumlahUnit);
    printf("Lama Sewa      : %d hari\n", lamaSewa);
    printf("Subtotal       : Rp%ld\n", subtotal);
    printf("Diskon (%.0f%%)  : Rp%ld\n", persenDiskon * 100, diskon);
    printf("-------------------------------------\n");
    printf("TOTAL BAYAR    : Rp%ld\n", totalBayar);
    printf("=====================================\n");
    printf("Terima kasih telah menggunakan\nlayanan Adventure Camp!\n");

    // Simpan Transaksi ke Array Riwayat
    strcpy(riwayatNama[jumlahTransaksi], nama);
    strcpy(riwayatAlat[jumlahTransaksi], namaAlat[indexAlat]);
    riwayatUnit[jumlahTransaksi] = jumlahUnit;
    riwayatLama[jumlahTransaksi] = lamaSewa;
    riwayatTotal[jumlahTransaksi] = totalBayar;
    jumlahTransaksi++;

    // Pertanyaan Navigasi Kembalikan ke Menu Utama
    printf("\nKembali ke menu utama? (Y/T): ");
    scanf(" %c", &kembaliMenu);
    if (kembaliMenu == 'T' || kembaliMenu == 't') {
        printf("\nTerima kasih telah menggunakan layanan Adventure Camp!\n");
        exit(0);
    }
}

// -----------------------------------------------------------------
// 4. FUNGSI MENAMPILKAN RIWAYAT TRANSAKSI (DENGAN TABEL LENGKAP)
// -----------------------------------------------------------------
void tampilkanRiwayat() {
    printf("\n=========================================================================================\n");
    printf("                                   RIWAYAT TRANSAKSI                                     \n");
    printf("=========================================================================================\n");

    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi penyewaan.\n");
        printf("=========================================================================================\n");
        return;
    }

    long totalPendapatan = 0;
    // Header Tabel: No, Nama, Peralatan, Unit, Lama Sewa, Total
    printf("%-3s | %-12s | %-26s | %-6s | %-10s | %s\n",
           "No", "Nama", "Peralatan", "Unit", "Lama Sewa", "Total");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahTransaksi; i++) {
        printf("%-3d | %-12s | %-26s | %-6d | %-8d hari | Rp%ld\n",
               i + 1,
               riwayatNama[i],
               riwayatAlat[i],
               riwayatUnit[i],
               riwayatLama[i],
               riwayatTotal[i]);

        totalPendapatan += riwayatTotal[i];
    }

    printf("-----------------------------------------------------------------------------------------\n");
    printf("Jumlah Transaksi : %d\n", jumlahTransaksi);
    printf("Total Pendapatan : Rp%ld\n", totalPendapatan);
    printf("=========================================================================================\n");
}
