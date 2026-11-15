#ifndef SLLMUSIK_H
#define SLLMUSIK_H

#include <iostream>
#include <string>

#include "musik.hpp"

using namespace std;

// Node musik (2 kompartemen): data musik dan pointer next
struct NodeMusik {
    Musik data;
    NodeMusik* next;
};

// List musik: hanya menyimpan pointer ke node pertama (first)
struct ListMusik {
    NodeMusik* first;
};

/*  Pengelolaan awal & akhir */

void inisialisasiMusik(ListMusik& l);   // membuat list kosong
void bersihkanMusik(ListMusik& l);      // membebaskan seluruh node

/* Pencarian & informasi */

NodeMusik* cariMusik(const ListMusik& l, const string& judul);   // nullptr jika tidak ada
bool sudahAdaMusik(const ListMusik& l, const string& judul);     // true jika judul sudah terdaftar
int jumlahMusik(const ListMusik& l);                             // banyak musik pada list
void tampilMusik(const ListMusik& l);                            // mencetak seluruh musik

/*  Penambahan (insert last) */

// Menambah musik di akhir list; dilewati jika judulnya sudah ada (tidak duplikat).
// Mengembalikan true jika benar-benar ditambahkan, false jika dilewati.
bool tambahMusik(ListMusik& l, const Musik& m);

/*  Penghapusan  */

bool hapusAwalMusik(ListMusik& l, Musik& hasil);                     // delete first
bool hapusAkhirMusik(ListMusik& l, Musik& hasil);                    // delete last
bool hapusSetelahMusik(NodeMusik* prev, Musik& hasil);               // delete after prev
bool hapusMusik(ListMusik& l, const string& judul);                  // hapus berdasarkan judul

#endif