#include "soundBranch.h"

#include <cctype>
#include <iomanip>
#include <iostream>

using namespace std;

/* ===================================================================== */
/*                              UTILITAS                                 */
/* ===================================================================== */

string formatDurasi(unsigned int detik) {
    unsigned int menit = detik / 60;
    unsigned int sisa = detik % 60;
    string hasil = to_string(menit) + ":";
    if (sisa < 10) hasil += "0";
    hasil += to_string(sisa);
    return hasil;
}

string formatWaktu(time_t waktu) {
    char buf[32];
    struct tm* info = localtime(&waktu);
    if (info == nullptr) return "-";
    strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M", info);
    return string(buf);
}

static string keHurufKecil(string s) {
    for (size_t i = 0; i < s.size(); i++) {
        s[i] = (char)tolower((unsigned char)s[i]);
    }
    return s;
}

static bool mengandung(const string& sumber, const string& kata) {
    return keHurufKecil(sumber).find(keHurufKecil(kata)) != string::npos;
}

static string potong(const string& s, size_t panjang) {
    if (s.size() <= panjang) return s;
    if (panjang < 3) return s.substr(0, panjang);
    return s.substr(0, panjang - 2) + "..";
}

static void cetakGaris(int panjang) {
    cout << string(panjang, '-') << "\n";
}

/* ===================================================================== */
/*                      FUNGSI INTERNAL BST & LIST                       */
/* ===================================================================== */

/* ----------------------------- [BST] ----------------------------- */

// [BST] Menyisipkan node baru secara rekursif.
// Bandingkan ID baru dengan ID node saat ini: lebih kecil -> kiri, selain itu -> kanan.
// Rekursi berhenti di posisi kosong (nullptr), lalu node baru ditempatkan di sana.
// Kompleksitas: rata-rata O(log n), terburuk O(n). Mengembalikan root subtree yang baru.
static NodeBSTMusik* sisipBST(NodeBSTMusik* root, NodeBSTMusik* baru) {
    if (root == nullptr) return baru;
    if (baru->idMusik < root->idMusik) {
        root->left = sisipBST(root->left, baru);
    } else {
        root->right = sisipBST(root->right, baru);
    }
    return root;
}

// [BST] Menghapus node ber-ID tertentu. Ada tiga kasus:
//   1. Node tanpa anak kiri  -> digantikan oleh anak kanannya (atau nullptr jika daun)
//   2. Node tanpa anak kanan -> digantikan oleh anak kirinya
//   3. Node dengan dua anak  -> isi node diganti dengan successor in-order
//                               (node terkecil di subtree kanan), lalu successor dihapus
// Yang dihapus di sini hanya node BST; NodeMusik pada child list dihapus terpisah
// oleh hapusMusik(). Parameter berhasil diset true jika ID ditemukan.
static NodeBSTMusik* hapusBST(NodeBSTMusik* root, const string& id, bool& berhasil) {
    if (root == nullptr) return nullptr;

    if (id < root->idMusik) {
        root->left = hapusBST(root->left, id, berhasil);
    } else if (id > root->idMusik) {
        root->right = hapusBST(root->right, id, berhasil);
    } else {
        berhasil = true;
        // Kasus 1: tidak punya anak kiri (termasuk node daun)
        if (root->left == nullptr) {
            NodeBSTMusik* anak = root->right;
            delete root;
            return anak;
        }
        // Kasus 2: hanya punya anak kiri
        if (root->right == nullptr) {
            NodeBSTMusik* anak = root->left;
            delete root;
            return anak;
        }
        // Kasus 3: punya dua anak -> ganti dengan successor (node terkecil di subtree kanan).
        // Successor dicari dengan terus menelusuri anak kiri. Kuncinya disalin ke variabel
        // lokal dulu agar tetap aman dipakai setelah node successor dihapus.
        NodeBSTMusik* succ = root->right;
        while (succ->left != nullptr) succ = succ->left;
        string kunciSucc = succ->idMusik;
        root->idMusik = succ->idMusik;
        root->musik = succ->musik;
        bool dummy = false;
        root->right = hapusBST(root->right, kunciSucc, dummy);
    }
    return root;
}

// [BST] Membebaskan seluruh node BST dengan traversal post-order (kiri, kanan, node),
// sehingga anak selalu dihapus sebelum induknya. Hanya node BST yang dihapus,
// bukan NodeMusik yang ditunjuknya.
static void hapusSeluruhBST(NodeBSTMusik* node) {
    if (node == nullptr) return;
    hapusSeluruhBST(node->left);
    hapusSeluruhBST(node->right);
    delete node;
}

/* ----------------------------- [SLL] ----------------------------- */

// [SLL] Menghapus seluruh node pada sebuah relation list.
// head dilewatkan sebagai referensi pointer agar head milik pemanggil ikut menjadi nullptr.
// Yang dihapus hanya node relasi; NodeMusik yang ditunjuknya tetap ada.
static void hapusSeluruhRelasi(NodeRelasi*& head) {
    while (head != nullptr) {
        NodeRelasi* temp = head;
        head = head->next;
        delete temp;
    }
}

// [SLL] Melepas satu relasi yang menunjuk ke musik tertentu dari relation list sebuah playlist.
// Memakai pointer-to-pointer (pp) yang menyimpan ALAMAT dari pointer yang menunjuk ke node
// saat ini (mula-mula &head, lalu &(node->next)). Dengan begitu menghapus node pertama dan
// node tengah ditangani dengan cara yang sama, tanpa variabel "prev" dan tanpa kasus khusus.
// Karena SLL tidak punya pointer prev, tanpa trik ini node sebelumnya harus dilacak manual.
static bool lepasRelasi(NodeRelasi*& head, const NodeMusik* target) {
    NodeRelasi** pp = &head;
    while (*pp != nullptr) {
        if ((*pp)->musik == target) {
            NodeRelasi* temp = *pp;
            *pp = temp->next;
            delete temp;
            return true;
        }
        pp = &((*pp)->next);
    }
    return false;
}

static bool playlistMemuat(const NodePlaylist* p, const NodeMusik* m) {
    for (const NodeRelasi* r = p->relasiHead; r != nullptr; r = r->next) {
        if (r->musik == m) return true;
    }
    return false;
}

static unsigned int hitungRelasi(const NodePlaylist* p) {
    unsigned int n = 0;
    for (const NodeRelasi* r = p->relasiHead; r != nullptr; r = r->next) n++;
    return n;
}

static unsigned int hitungTotalDurasi(const NodePlaylist* p) {
    unsigned int total = 0;
    for (const NodeRelasi* r = p->relasiHead; r != nullptr; r = r->next) {
        total += r->musik->data.durasi;
    }
    return total;
}

/* ===================================================================== */
/*                     INISIALISASI & PEMBERSIHAN                        */
/* ===================================================================== */

void inisialisasi(SoundBranch& sb) {
    sb.playlistHead = nullptr;
    sb.musikHead = nullptr;
    sb.root = nullptr;
    sb.jumlahMusik = 0;
    sb.jumlahPlaylist = 0;
}

void bersihkan(SoundBranch& sb) {
    // [SLL] Parent list + relation list: hapus tiap playlist beserta relation list-nya
    while (sb.playlistHead != nullptr) {
        NodePlaylist* temp = sb.playlistHead;
        sb.playlistHead = temp->next;
        hapusSeluruhRelasi(temp->relasiHead);
        delete temp;
    }
    // [BST] Hapus seluruh node pohon (post-order)
    hapusSeluruhBST(sb.root);
    sb.root = nullptr;
    // [SLL] Child list: hapus node musik satu per satu dari head
    while (sb.musikHead != nullptr) {
        NodeMusik* temp = sb.musikHead;
        sb.musikHead = temp->next;
        delete temp;
    }
    sb.jumlahMusik = 0;
    sb.jumlahPlaylist = 0;
}

/* ===================================================================== */
/*                              MUSIK                                    */
/* ===================================================================== */

static void cetakHeaderMusik() {
    cout << left << setw(10) << "ID" << setw(24) << "Judul" << setw(18) << "Artis"
         << setw(18) << "Album" << setw(12) << "Genre" << setw(8) << "Durasi" << "\n";
    cetakGaris(90);
}

static void cetakBarisMusik(const Musik& m) {
    cout << left << setw(10) << potong(m.id, 9) << setw(24) << potong(m.judul, 23)
         << setw(18) << potong(m.artis, 17) << setw(18) << potong(m.album, 17)
         << setw(12) << potong(m.genre, 11) << setw(8) << formatDurasi(m.durasi) << "\n";
}

// [BST] Mencari musik berdasarkan ID secara iteratif.
// Mulai dari root; jika ID sama -> ketemu, jika lebih kecil -> turun ke kiri, selain itu -> kanan.
// Setiap langkah membuang separuh kemungkinan sehingga rata-rata O(log n).
// Mengembalikan pointer ke NodeMusik di child list, atau nullptr jika tidak ada.
NodeMusik* cariMusikById(const SoundBranch& sb, const string& id) {
    NodeBSTMusik* cur = sb.root;
    while (cur != nullptr) {
        if (id == cur->idMusik) return cur->musik;
        cur = (id < cur->idMusik) ? cur->left : cur->right;
    }
    return nullptr;
}

bool tambahMusik(SoundBranch& sb, const Musik& m) {
    if (m.id.empty() || cariMusikById(sb, m.id) != nullptr) return false;

    NodeMusik* baru = new NodeMusik;
    baru->data = m;
    baru->data.createdAt = time(nullptr);
    baru->data.editedAt = baru->data.createdAt;
    baru->next = nullptr;

    // [SLL] Tambahkan di akhir child list (insert last): telusuri sampai node terakhir
    // (next == nullptr), lalu sambungkan node baru. O(n) karena tidak ada pointer tail.
    if (sb.musikHead == nullptr) {
        sb.musikHead = baru;
    } else {
        NodeMusik* p = sb.musikHead;
        while (p->next != nullptr) p = p->next;
        p->next = baru;
    }

    // [BST] Tambahkan node indeks dengan kunci ID musik, menunjuk ke node di child list
    NodeBSTMusik* nodeBST = new NodeBSTMusik{m.id, baru, nullptr, nullptr};
    sb.root = sisipBST(sb.root, nodeBST);

    sb.jumlahMusik++;
    return true;
}

bool editMusik(SoundBranch& sb, const string& id, const Musik& baru) {
    NodeMusik* node = cariMusikById(sb, id);
    if (node == nullptr) return false;

    node->data.judul = baru.judul;
    node->data.artis = baru.artis;
    node->data.album = baru.album;
    node->data.genre = baru.genre;
    node->data.durasi = baru.durasi;
    node->data.editedAt = time(nullptr);
    return true;
}

bool hapusMusik(SoundBranch& sb, const string& id) {
    NodeMusik* target = cariMusikById(sb, id);
    if (target == nullptr) return false;

    // 1. Hapus semua relasi yang menunjuk ke musik ini agar tidak ada pointer menggantung
    for (NodePlaylist* p = sb.playlistHead; p != nullptr; p = p->next) {
        lepasRelasi(p->relasiHead, target);
    }

    // 2. [BST] Hapus node indeks dari BST
    string kunci = id;
    bool berhasil = false;
    sb.root = hapusBST(sb.root, kunci, berhasil);

    // 3. [SLL] Lepas dari child list dengan pointer-to-pointer (lihat lepasRelasi),
    //    lalu bebaskan memorinya. Urutan 1-2-3 penting: relasi dan indeks BST harus
    //    hilang lebih dulu agar tidak ada pointer yang menunjuk ke node yang sudah dihapus.
    NodeMusik** pp = &sb.musikHead;
    while (*pp != nullptr) {
        if (*pp == target) {
            *pp = target->next;
            break;
        }
        pp = &((*pp)->next);
    }
    delete target;

    sb.jumlahMusik--;
    return true;
}

// [BST] Traversal in-order (kiri, node, kanan): menghasilkan musik terurut menaik berdasarkan ID.
static void inorderMusik(const NodeBSTMusik* node) {
    if (node == nullptr) return;
    inorderMusik(node->left);
    cetakBarisMusik(node->musik->data);
    inorderMusik(node->right);
}

void tampilSemuaMusik(const SoundBranch& sb) {
    if (sb.root == nullptr) {
        cout << "Belum ada data musik.\n";
        return;
    }
    cout << "\n=== Daftar Musik (terurut berdasarkan ID) ===\n";
    cetakHeaderMusik();
    inorderMusik(sb.root);
    cetakGaris(90);
    cout << "Total: " << sb.jumlahMusik << " musik\n";
}

void tampilDetailMusik(const SoundBranch& sb, const NodeMusik* node) {
    if (node == nullptr) return;
    const Musik& m = node->data;
    cout << "\n--- Detail Musik ---\n";
    cout << "ID        : " << m.id << "\n";
    cout << "Judul     : " << m.judul << "\n";
    cout << "Artis     : " << m.artis << "\n";
    cout << "Album     : " << m.album << "\n";
    cout << "Genre     : " << m.genre << "\n";
    cout << "Durasi    : " << formatDurasi(m.durasi) << " (" << m.durasi << " detik)\n";
    cout << "Dibuat    : " << formatWaktu(m.createdAt) << "\n";
    cout << "Diedit    : " << formatWaktu(m.editedAt) << "\n";

    cout << "Ada di playlist: ";
    bool ada = false;
    for (const NodePlaylist* p = sb.playlistHead; p != nullptr; p = p->next) {
        if (playlistMemuat(p, node)) {
            if (ada) cout << ", ";
            cout << p->data.nama << " (" << p->data.id << ")";
            ada = true;
        }
    }
    if (!ada) cout << "-";
    cout << "\n";
}

unsigned int cariDanTampilMusik(const SoundBranch& sb, KategoriCari kategori,
                                const string& kataKunci) {
    if (kategori == CARI_ID) {
        // Pencarian memanfaatkan BST
        NodeMusik* hasil = cariMusikById(sb, kataKunci);
        if (hasil == nullptr) return 0;
        tampilDetailMusik(sb, hasil);
        return 1;
    }

    // Pencarian judul/artis/album: penelusuran child list (tidak peka huruf besar/kecil)
    unsigned int jumlah = 0;
    for (const NodeMusik* p = sb.musikHead; p != nullptr; p = p->next) {
        const string* medan = nullptr;
        if (kategori == CARI_JUDUL) medan = &p->data.judul;
        else if (kategori == CARI_ARTIS) medan = &p->data.artis;
        else medan = &p->data.album;

        if (mengandung(*medan, kataKunci)) {
            if (jumlah == 0) {
                cout << "\n=== Hasil Pencarian ===\n";
                cetakHeaderMusik();
            }
            cetakBarisMusik(p->data);
            jumlah++;
        }
    }
    if (jumlah > 0) {
        cetakGaris(90);
        cout << "Ditemukan: " << jumlah << " musik\n";
    }
    return jumlah;
}

/* ===================================================================== */
/*                             PLAYLIST                                  */
/* ===================================================================== */

// [SLL] Pencarian playlist: penelusuran linear pada parent list dari head sampai nullptr. O(n).
NodePlaylist* cariPlaylistById(const SoundBranch& sb, const string& id) {
    for (NodePlaylist* p = sb.playlistHead; p != nullptr; p = p->next) {
        if (p->data.id == id) return p;
    }
    return nullptr;
}

bool tambahPlaylist(SoundBranch& sb, const Playlist& pl) {
    if (pl.id.empty() || cariPlaylistById(sb, pl.id) != nullptr) return false;

    NodePlaylist* baru = new NodePlaylist;
    baru->data = pl;
    baru->data.frekuensiAkses = 0;
    baru->data.createdAt = time(nullptr);
    baru->data.editedAt = baru->data.createdAt;
    baru->relasiHead = nullptr;
    baru->next = nullptr;

    // [SLL] Tambahkan di akhir parent list (insert last)
    if (sb.playlistHead == nullptr) {
        sb.playlistHead = baru;
    } else {
        NodePlaylist* p = sb.playlistHead;
        while (p->next != nullptr) p = p->next;
        p->next = baru;
    }
    sb.jumlahPlaylist++;
    return true;
}

bool editPlaylist(SoundBranch& sb, const string& id, const string& nama, const string& deskripsi) {
    NodePlaylist* p = cariPlaylistById(sb, id);
    if (p == nullptr) return false;
    p->data.nama = nama;
    p->data.deskripsi = deskripsi;
    p->data.editedAt = time(nullptr);
    return true;
}

// [SLL] Menghapus playlist dari parent list (pointer-to-pointer, lihat lepasRelasi),
// termasuk seluruh node relasinya. Data musik di child list/BST tidak terpengaruh.
bool hapusPlaylist(SoundBranch& sb, const string& id) {
    NodePlaylist** pp = &sb.playlistHead;
    while (*pp != nullptr) {
        if ((*pp)->data.id == id) {
            NodePlaylist* target = *pp;
            *pp = target->next;
            // Hapus seluruh relasi playlist (data musik TIDAK ikut terhapus)
            hapusSeluruhRelasi(target->relasiHead);
            delete target;
            sb.jumlahPlaylist--;
            return true;
        }
        pp = &((*pp)->next);
    }
    return false;
}

void tampilSemuaPlaylist(const SoundBranch& sb) {
    if (sb.playlistHead == nullptr) {
        cout << "Belum ada data playlist.\n";
        return;
    }
    cout << "\n=== Daftar Playlist ===\n";
    cout << left << setw(10) << "ID" << setw(24) << "Nama" << setw(30) << "Deskripsi"
         << setw(8) << "Lagu" << setw(8) << "Akses" << "\n";
    cetakGaris(80);
    for (const NodePlaylist* p = sb.playlistHead; p != nullptr; p = p->next) {
        cout << left << setw(10) << potong(p->data.id, 9) << setw(24) << potong(p->data.nama, 23)
             << setw(30) << potong(p->data.deskripsi, 29) << setw(8) << hitungRelasi(p)
             << setw(8) << p->data.frekuensiAkses << "\n";
    }
    cetakGaris(80);
    cout << "Total: " << sb.jumlahPlaylist << " playlist\n";
}

bool tampilDetailPlaylist(SoundBranch& sb, const string& id, bool hitungAkses) {
    NodePlaylist* p = cariPlaylistById(sb, id);
    if (p == nullptr) return false;

    if (hitungAkses) p->data.frekuensiAkses++;

    cout << "\n--- Detail Playlist ---\n";
    cout << "ID        : " << p->data.id << "\n";
    cout << "Nama      : " << p->data.nama << "\n";
    cout << "Deskripsi : " << p->data.deskripsi << "\n";
    cout << "Diakses   : " << p->data.frekuensiAkses << " kali\n";
    cout << "Dibuat    : " << formatWaktu(p->data.createdAt) << "\n";
    cout << "Diedit    : " << formatWaktu(p->data.editedAt) << "\n";

    if (p->relasiHead == nullptr) {
        cout << "\nPlaylist ini belum memiliki musik.\n";
        return true;
    }

    cout << "\nIsi playlist:\n";
    cetakHeaderMusik();
    for (const NodeRelasi* r = p->relasiHead; r != nullptr; r = r->next) {
        cetakBarisMusik(r->musik->data);
    }
    cetakGaris(90);
    cout << "Jumlah musik : " << hitungRelasi(p) << "\n";
    cout << "Total durasi : " << formatDurasi(hitungTotalDurasi(p)) << "\n";
    return true;
}

void tampilStatistikPlaylist(const SoundBranch& sb) {
    if (sb.playlistHead == nullptr) {
        cout << "Belum ada data playlist.\n";
        return;
    }

    int n = 0;
    NodePlaylist** arr = new NodePlaylist*[sb.jumlahPlaylist];
    for (NodePlaylist* p = sb.playlistHead; p != nullptr && n < (int)sb.jumlahPlaylist; p = p->next) {
        arr[n++] = p;
    }

    // Insertion sort: frekuensi akses terbesar di atas
    for (int i = 1; i < n; i++) {
        NodePlaylist* key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j]->data.frekuensiAkses < key->data.frekuensiAkses) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    unsigned int totalRelasi = 0;
    cout << "\n=== Statistik Playlist (urut frekuensi akses) ===\n";
    cout << left << setw(5) << "No" << setw(10) << "ID" << setw(24) << "Nama"
         << setw(8) << "Lagu" << setw(12) << "Durasi" << setw(8) << "Akses" << "\n";
    cetakGaris(67);
    for (int i = 0; i < n; i++) {
        const NodePlaylist* p = arr[i];
        totalRelasi += hitungRelasi(p);
        cout << left << setw(5) << (i + 1) << setw(10) << potong(p->data.id, 9)
             << setw(24) << potong(p->data.nama, 23) << setw(8) << hitungRelasi(p)
             << setw(12) << formatDurasi(hitungTotalDurasi(p))
             << setw(8) << p->data.frekuensiAkses << "\n";
    }
    cetakGaris(67);
    cout << "Total playlist : " << sb.jumlahPlaylist << "\n";
    cout << "Total musik    : " << sb.jumlahMusik << "\n";
    cout << "Total relasi   : " << totalRelasi << "\n";
    if (n > 0 && arr[0]->data.frekuensiAkses > 0) {
        cout << "Paling sering diakses: " << arr[0]->data.nama
             << " (" << arr[0]->data.frekuensiAkses << " kali)\n";
    }
    delete[] arr;
}

/* ===================================================================== */
/*                              RELASI                                   */
/* ===================================================================== */

StatusRelasi tambahRelasi(SoundBranch& sb, const string& idPlaylist, const string& idMusik) {
    NodePlaylist* p = cariPlaylistById(sb, idPlaylist);
    if (p == nullptr) return RELASI_PLAYLIST_TIDAK_ADA;

    NodeMusik* m = cari
    +MusikById(sb, idMusik);
    if (m == nullptr) return RELASI_MUSIK_TIDAK_ADA;

    if (playlistMemuat(p, m)) return RELASI_SUDAH_ADA;

    // [SLL] Buat node relasi yang menunjuk ke NodeMusik (tanpa menyalin data musik),
    // lalu sambungkan di akhir relation list milik playlist ini.
    NodeRelasi* baru = new NodeRelasi{m, nullptr};
    if (p->relasiHead == nullptr) {
        p->relasiHead = baru;
    } else {
        NodeRelasi* r = p->relasiHead;
        while (r->next != nullptr) r = r->next;
        r->next = baru;
    }
    p->data.editedAt = time(nullptr);
    return RELASI_OK;
}

StatusRelasi hapusRelasi(SoundBranch& sb, const string& idPlaylist, const string& idMusik) {
    NodePlaylist* p = cariPlaylistById(sb, idPlaylist);
    if (p == nullptr) return RELASI_PLAYLIST_TIDAK_ADA;

    NodeMusik* m = cariMusikById(sb, idMusik);
    if (m == nullptr) return RELASI_MUSIK_TIDAK_ADA;

    if (!lepasRelasi(p->relasiHead, m)) return RELASI_TIDAK_ADA;
    p->data.editedAt = time(nullptr);
    return RELASI_OK;
}