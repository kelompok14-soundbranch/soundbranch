#ifndef MLLPLAYLIST_HPP
#define MLLPLAYLIST_HPP

#include <iostream>
#include <string>

#include "musik.hpp"
#include "playlist.hpp"
#include "sllMusik.hpp"

using namespace std;

// Node child (2 kompartemen): data musik dan pointer next
struct NodeChildPlaylist {
    Musik data;
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
int jumlahPlaylist(const MLLPlaylist& m);
int jumlahMusikPlaylist(const NodeParentPlaylist* p);
void tampilMLLPlaylist(const MLLPlaylist& m);

/* ===================== Penambahan & perubahan ===================== */

// Parent: insert first, dilewati jika judul playlist sudah ada
bool tambahPlaylist(MLLPlaylist& m, const Playlist& pl);

// Child: insert last, dilewati jika judul musik sudah ada pada playlist tersebut
bool tambahChildPlaylist(NodeParentPlaylist* p, const Musik& musik);

// Menambah musik ke playlist bernama judulPlaylist + sinkronisasi ke SLL utama
bool tambahMusikKePlaylist(MLLPlaylist& m, ListMusik& sll,
                           const string& judulPlaylist, const Musik& musik);

// Menambah frekuensiAkses playlist sebanyak 1
bool aksesPlaylist(MLLPlaylist& m, const string& judulPlaylist);

/* ===================== Penghapusan ===================== */

bool hapusMusikPlaylist(NodeParentPlaylist* p, const string& judul);
bool hapusPlaylist(MLLPlaylist& m, const string& judul);

#endif