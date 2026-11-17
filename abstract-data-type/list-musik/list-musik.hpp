#ifndef LIST_MUSIK_HPP
#define LIST_MUSIK_HPP

#include <string>

#include "../../entitas/musik/musik.hpp"
#include "../list-artis/list-artis.hpp"
#include "../list-album/list-album.hpp"
#include "../list-genre/list-genre.hpp"
#include "../list-playlist/list-playlist.hpp"

struct NodeMusik {
    Musik musik;
    NodeMusik* next;
};

struct ListMusik {
    NodeMusik* first;
};

// mengembalikan ListMusik kosong
ListMusik buatListMusik();

// mengembalikan total seluruh musik yang terdapat dalam listMusik
unsigned int hitungTotalMusik(const ListMusik& listMusik);

// mengembalikan true jika listMusik kosong, atau false jika listMusik memiliki minimal satu musik
bool kosongMusik(const ListMusik& listMusik);

// mengembalikan pointer ke musik yang memiliki ID sesuai idMusikCari dalam listMusik, atau nullptr jika musik tidak ditemukan
Musik* cariMusik(const ListMusik& listMusik, const std::string& idMusikCari);

// I.S.: listMusik mungkin kosong atau sudah berisi sejumlah musik. musikBaru adalah musik yang valid
// F.S.: jika musik dengan ID yang sama sudah terdaftar, listMusik tidak berubah. Jika belum terdaftar, data musikBaru ditambahkan pada bagian akhir listMusik
void tambahMusik(ListMusik& listMusik, const Musik& musikBaru);

// I.S.: listMusik mungkin kosong atau sudah berisi sejumlah musik.
// F.S.: jika musik ditemukan, seluruh relasinya pada list artis, album, genre, dan playlist ikut dihapus sebelum node musik dihapus.
// Jika musik tidak ditemukan, fungsi melempar pesan error dan seluruh list tetap tidak berubah.
void hapusMusik(ListMusik& listMusik, ListArtis& listArtis, ListAlbum& listAlbum, ListGenre& listGenre, ListPlaylist& listPlaylist, const std::string& idMusikHapus);

// I.S.: listMusik mungkin kosong atau sudah berisi sejumlah musik
// F.S.: jika listMusik kosong, ditampilkan pesan bahwa belum ada musik yang terdaftar. Jika tidak kosong, seluruh data musik ditampilkan beserta artis, album, genre, dan playlist-nya. listMusik tidak mengalami perubahan
void tampilkanSemuaMusik(const ListMusik& listMusik, const ListArtis& listArtis, const ListAlbum& ListAlbum, const ListGenre& ListGenre, const ListPlaylist& listPlaylist);

#endif