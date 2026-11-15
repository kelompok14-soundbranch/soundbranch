#ifndef MLLPLAYLIST_HPP
#define MLLPLAYLIST_HPP

#include <iostream>
#include <string>

#include "musik.hpp"
#include "playlist.hpp"
#include "sllMusik.hpp"

using namespace std;

// Node child (2 kompartemen): pointer ke node musik di SLL utama dan pointer next.
// Data musik TIDAK disalin; child hanya menunjuk ke NodeMusik milik SLL.
struct NodeChildPlaylist {
    NodeMusik* musik;
    NodeChildPlaylist* next;
};

// Node parent (3 kompartemen): data playlist, pointer firstChild, pointer next
struct NodeParentPlaylist {
    Playlist data;
    NodeChildPlaylist* firstChild;
    NodeParentPlaylist* next;
};

// MLL Playlist 2 tingkat: hanya menyimpan pointer ke parent pertama
struct MLLPlaylist {
    NodeParentPlaylist* first;
};

/* ===================== Pengelolaan awal & akhir ===================== */

void inisialisasiMLLPlaylist(MLLPlaylist& m);
void bersihkanMLLPlaylist(MLLPlaylist& m);

/* ===================== Pencarian & informasi ===================== */

NodeParentPlaylist* cariPlaylist(const MLLPlaylist& m, const string& judul);
NodeChildPlaylist* cariMusikPlaylist(const NodeParentPlaylist* p, const string& judul);
// Pencarian tingkat tinggi: user cukup memberi judul playlist dan judul musik
NodeMusik* cariMusikDiPlaylist(const MLLPlaylist& m, const string& judulPlaylist,
                               const string& judulMusik);
void tampilCariMusikDiPlaylist(const MLLPlaylist& m, const string& judulPlaylist,
                               const string& judulMusik);
int jumlahPlaylist(const MLLPlaylist& m);
int jumlahMusikPlaylist(const NodeParentPlaylist* p);
void tampilMLLPlaylist(const MLLPlaylist& m);

/* ===================== Penambahan & perubahan ===================== */

// Parent: insert first, dilewati jika judul playlist sudah ada
bool tambahPlaylist(MLLPlaylist& m, const Playlist& pl);

// Child: insert last, menyimpan pointer ke node musik SLL;
// dilewati jika musik tersebut sudah ada pada playlist
bool tambahChildPlaylist(NodeParentPlaylist* p, NodeMusik* nodeMusik);

// Menambah musik ke playlist bernama judulPlaylist.
// Musik didaftarkan ke SLL dulu (dilewati jika sudah ada), lalu child menunjuk ke node SLL-nya.
bool tambahMusikKePlaylist(MLLPlaylist& m, ListMusik& sll,
                           const string& judulPlaylist, const Musik& musik);

// Menambah frekuensiAkses playlist sebanyak 1
bool aksesPlaylist(MLLPlaylist& m, const string& judulPlaylist);

/* ===================== Penghapusan ===================== */

bool hapusMusikPlaylist(NodeParentPlaylist* p, const string& judul);
bool hapusPlaylist(MLLPlaylist& m, const string& judul);

// Menghapus seluruh child bernama judul di SEMUA playlist.
// WAJIB dipanggil sebelum musik tersebut dihapus dari SLL (mencegah dangling pointer).
int hapusReferensiMusik(MLLPlaylist& m, const string& judul);

#endif