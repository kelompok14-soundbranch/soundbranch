#ifndef LIST_ALBUM_HPP
#define LIST_ALBUM_HPP

#include <string>

#include "../../entitas/album.hpp"
#include "../__common__/node-relasi-musik.hpp"

struct NodeAlbum {
    Album album;
    NodeRelasiMusik* firstMusik;

    NodeAlbum* next;
};

struct ListAlbum {
    NodeAlbum* first;
};

// mengembalikan ListAlbum kosong
ListAlbum buatListAlbum();

// mengembalikan total seluruh album yang terdapat dalam listAlbum
unsigned int hitungTotalAlbum(const ListAlbum& listAlbum);

// mengembalikan true jika listAlbum kosong, atau false jika listAlbum memiliki minimal satu album
bool kosongAlbum(const ListAlbum& listAlbum);

// mengembalikan pointer ke album yang memiliki ID sesuai idAlbumCari dalam listAlbum, atau nullptr jika album tidak ditemukan
Album* cariAlbum(const ListAlbum& listAlbum, const std::string& idAlbumCari);

// I.S.: listAlbum mungkin kosong atau sudah berisi sejumlah album. Pointer artis pada albumBaru mungkin nullptr atau menunjuk pada data artis yang valid
// F.S.: jika pointer artis tidak valid atau album dengan ID yang sama sudah terdaftar, listAlbum tidak berubah. Jika tidak, data albumBaru ditambahkan pada bagian akhir listAlbum
void tambahAlbum(ListAlbum& listAlbum, const Album& albumBaru);

// I.S.: listAlbum mungkin kosong atau sudah berisi sejumlah album
// F.S.: jika album tidak ditemukan atau masih memiliki relasi musik, listAlbum tidak berubah. Jika album ditemukan dan tidak memiliki relasi musik, album dihapus
void hapusAlbum(ListAlbum& listAlbum, const std::string& idAlbumHapus);

// I.S.: listAlbum mungkin kosong atau sudah berisi sejumlah album
// F.S.: jika listAlbum kosong, ditampilkan pesan bahwa belum ada album yang terdaftar. Jika tidak kosong, seluruh album beserta informasi artis dan daftar musik yang terhubung pada setiap album ditampilkan. listAlbum tidak mengalami perubahan
void tampilkanSemuaAlbum(const ListAlbum& listAlbum);



// mengembalikan total seluruh relasi musik yang terdapat pada album dengan ID sesuai idAlbum, atau 0 jika album tidak ditemukan atau tidak memiliki musik
unsigned int hitungTotalAlbumMusik(const ListAlbum& listAlbum, const std::string& idAlbum);

// mengembalikan true jika album dengan ID sesuai idAlbum tidak ditemukan atau album tidak memiliki relasi musik, atau false jika album memiliki minimal satu relasi musik
bool kosongAlbumMusik(const ListAlbum& listAlbum, const std::string& idAlbum);

// mengembalikan list album yang memiliki relasi dengan data musik yang ditunjuk oleh pointer musik, atau list album kosong jika pointer musik tidak valid atau tidak ditemukan relasi yang sesuai
ListAlbum cariAlbumMusik(const ListAlbum& listAlbum, Musik* const musik);

// I.S.: listAlbum mungkin kosong atau sudah memiliki album dan relasi musik. Pointer musik mungkin nullptr atau menunjuk pada data musik yang valid
// F.S.: jika pointer musik tidak valid, album tidak ditemukan, atau musik sudah terdaftar pada album tersebut, listAlbum tidak berubah. Jika tidak, relasi baru ditambahkan pada bagian akhir daftar relasi musik dari album dengan ID sesuai idAlbum
void tambahAlbumMusik(ListAlbum& listAlbum, const std::string& idAlbum, Musik* const musik);

// I.S.: listAlbum mungkin kosong atau sudah memiliki album dan relasi musik. Pointer musik mungkin nullptr atau menunjuk pada data musik yang valid
// F.S.: jika pointer musik tidak valid, album tidak ditemukan, atau musik tidak terdaftar pada album tersebut, struktur ListAlbum tidak berubah. Jika relasi ditemukan, node relasi musik dihapus dan hubungan antar-node relasi tetap terjaga
void hapusAlbumMusik(ListAlbum& listAlbum, const std::string& idAlbum, Musik* const musik);

// I.S.: listAlbum mungkin kosong atau sudah memiliki album dan relasi musik
// F.S.: jika album tidak ditemukan, ditampilkan pesan bahwa album tidak ditemukan. Jika album belum memiliki musik, ditampilkan pesan bahwa album belum memiliki musik. Jika album memiliki relasi musik, seluruh judul musik yang terhubung dengan album tersebut ditampilkan. listAlbum tidak mengalami perubahan
void tampilkanSemuaAlbumMusik(const ListAlbum& listAlbum, const std::string& idAlbum);

#endif
