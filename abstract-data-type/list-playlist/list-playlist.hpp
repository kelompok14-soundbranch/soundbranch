#ifndef LIST_PLAYLIST_HPP
#define LIST_PLAYLIST_HPP

#include <string>
#include "../../entitas/playlist.hpp"
#include "../__common__/node-relasi-musik.hpp"

struct NodePlaylist {
    Playlist playlist;
    NodeRelasiMusik* firstMusik;
    NodePlaylist* next;
};

struct ListPlaylist {
    NodePlaylist* first;
};

// mengembalikan ListPlaylist kosong
ListPlaylist buatListPlaylist();

// mengembalikan total seluruh playlist yang terdapat dalam listPlaylist
unsigned int hitungTotalPlaylist(const ListPlaylist& listPlaylist);

// mengembalikan true jika listPlaylist kosong, atau false jika memiliki minimal satu playlist
bool kosongPlaylist(const ListPlaylist& listPlaylist);

// mengembalikan pointer ke playlist dengan judul sesuai judulPlaylistCari, atau nullptr jika tidak ditemukan
Playlist* cariPlaylist(const ListPlaylist& listPlaylist, const std::string& judulPlaylistCari);

// I.S.: listPlaylist mungkin kosong atau sudah berisi sejumlah playlist
// F.S.: jika playlist dengan judul yang sama sudah terdaftar, listPlaylist tidak berubah. Jika tidak, playlistBaru ditambahkan pada bagian akhir listPlaylist
void tambahPlaylist(ListPlaylist& listPlaylist, const Playlist& playlistBaru);

// I.S.: listPlaylist mungkin kosong atau sudah berisi sejumlah playlist
// F.S.: jika playlist tidak ditemukan atau masih memiliki relasi musik, listPlaylist tidak berubah. Jika playlist ditemukan dan tidak memiliki relasi musik, playlist dihapus
void hapusPlaylist(ListPlaylist& listPlaylist, const std::string& judulPlaylistHapus);

// I.S.: listPlaylist mungkin kosong atau sudah berisi sejumlah playlist
// F.S.: jika listPlaylist kosong, ditampilkan pesan bahwa belum ada playlist yang terdaftar. Jika tidak kosong, seluruh playlist beserta daftar musik yang terhubung pada setiap playlist ditampilkan. listPlaylist tidak mengalami perubahan
void tampilkanSemuaPlaylist(const ListPlaylist& listPlaylist);



// mengembalikan total seluruh relasi musik pada playlist dengan judul sesuai judulPlaylist, atau 0 jika playlist tidak ditemukan atau tidak memiliki musik
unsigned int hitungTotalPlaylistMusik(const ListPlaylist& listPlaylist, const std::string& judulPlaylist);

// mengembalikan true jika playlist tidak ditemukan atau tidak memiliki relasi musik, atau false jika playlist memiliki minimal satu relasi musik
bool kosongPlaylistMusik(const ListPlaylist& listPlaylist, const std::string& judulPlaylist);

// mengembalikan list playlist yang memiliki relasi dengan musik yang ditunjuk oleh pointer musik, atau list playlist kosong jika pointer musik nullptr atau tidak ditemukan relasi yang sesuai
ListPlaylist cariPlaylistMusik(const ListPlaylist& listPlaylist, Musik* const musik);

// I.S.: listPlaylist mungkin kosong atau sudah memiliki playlist dan relasi musik. Pointer musik mungkin nullptr atau menunjuk pada data musik yang valid
// F.S.: jika pointer musik nullptr, playlist tidak ditemukan, atau musik sudah terdaftar pada playlist tersebut, listPlaylist tidak berubah. Jika tidak, relasi baru ditambahkan pada bagian akhir daftar relasi musik playlist
void tambahPlaylistMusik(ListPlaylist& listPlaylist, const std::string& judulPlaylist, Musik* const musik);

// I.S.: listPlaylist mungkin kosong atau sudah memiliki playlist dan relasi musik. Pointer musik mungkin nullptr atau menunjuk pada data musik yang valid
// F.S.: jika pointer musik nullptr, playlist tidak ditemukan, atau musik tidak terdaftar pada playlist tersebut, listPlaylist tidak berubah. Jika relasi ditemukan, node relasi musik dihapus dan hubungan antar-node relasi tetap terjaga
void hapusPlaylistMusik(ListPlaylist& listPlaylist, const std::string& judulPlaylist, Musik* const musik);

// I.S.: listPlaylist mungkin kosong atau sudah memiliki playlist dan relasi musik
// F.S.: jika playlist tidak ditemukan, ditampilkan pesan bahwa playlist tidak ditemukan. Jika playlist belum memiliki musik, ditampilkan pesan bahwa playlist belum memiliki musik. Jika playlist memiliki relasi musik, seluruh judul musik yang terhubung dengan playlist tersebut ditampilkan. listPlaylist tidak mengalami perubahan
void tampilkanSemuaPlaylistMusik(const ListPlaylist& listPlaylist, const std::string& judulPlaylist);

#endif