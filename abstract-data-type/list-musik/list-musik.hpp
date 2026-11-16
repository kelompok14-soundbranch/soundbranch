#ifndef LIST_MUSIK_HPP
#define LIST_MUSIK_HPP

#include <string>

#include "../../entitas/musik.hpp"
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

// I.S.: listMusik mungkin kosong atau sudah berisi sejumlah musik
// F.S.: jika musik dengan ID yang sama sudah terdaftar, listMusik tidak berubah. Jika belum terdaftar, data musikBaru ditambahkan pada bagian akhir listMusik
void tambahMusik(ListMusik& listMusik, const Musik& musikBaru);

// I.S.: listMusik mungkin kosong atau sudah berisi sejumlah musik. Musik yang akan dihapus tidak memiliki relasi pada MLL genre, artis, album, maupun playlist
// F.S.: jika musik tidak ditemukan, listMusik tidak berubah. Jika musik ditemukan, node musik dihapus dan hubungan antar-node musik tetap terjaga
void hapusMusik(ListMusik& listMusik, const std::string& idMusikHapus);

// I.S.: listMusik mungkin kosong atau sudah berisi sejumlah musik
// F.S.: jika listMusik kosong, ditampilkan pesan bahwa belum ada musik yang terdaftar. Jika tidak kosong, seluruh data musik ditampilkan. listMusik tidak mengalami perubahan
void tampilkanSemuaMusik(const ListMusik& listMusik);

// I.S.: listMusik mungkin kosong atau sudah berisi sejumlah musik
// F.S.: jika listMusik kosong, ditampilkan pesan bahwa belum ada musik yang terdaftar. Jika tidak kosong, seluruh data musik ditampilkan beserta artis, album, genre, dan playlist-nya. listMusik tidak mengalami perubahan
void tampilkanSemuaMusikLengkap(const ListMusik& listMusik, const ListArtis& listArtis, const ListAlbum& ListAlbum, const ListGenre& ListGenre, const ListPlaylist& listPlaylist);

#endif