#ifndef LIST_ALBUM_HPP
#define LIST_ALBUM_HPP

#include <string>

#include "../../entitas/album/album.hpp"
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

// mengembalikan true jika listAlbum kosong, atau false jika listAlbum sudah berisi sejumlah album
bool kosongAlbum(const ListAlbum& listAlbum);

// mengembalikan pointer ke album dengan ID idAlbumCari dalam listAlbum, atau nullptr jika idAlbumCari tidak valid
Album* cariAlbum(const ListAlbum& listAlbum, const std::string& idAlbumCari);

// I.S.: listAlbum mungkin kosong atau sudah berisi sejumlah album. albumBaru adalah album yang valid
// F.S.: jika album dengan ID yang sama sudah terdaftar, listAlbum tidak berubah. Jika tidak, data albumBaru ditambahkan pada bagian akhir listAlbum
void tambahAlbum(ListAlbum& listAlbum, const Album& albumBaru);

// I.S.: listAlbum sudah berisi sejumlah album. idAlbumHapus mungkin valid atau tidak valid
// F.S.: jika idAlbumHapus tidak valid atau album masih memiliki relasi musik, listAlbum tidak berubah. Jika tidak, album dihapus dari listAlbum
void hapusAlbum(ListAlbum& listAlbum, const std::string& idAlbumHapus);

// I.S.: listAlbum mungkin kosong atau sudah berisi sejumlah album
// F.S.: jika listAlbum kosong, ditampilkan pesan bahwa belum ada album yang terdaftar. Jika tidak kosong, seluruh data album beserta artis dan daftar musik album ditampilkan. listAlbum tidak berubah
void tampilkanSemuaAlbum(const ListAlbum& listAlbum);



// mengembalikan total seluruh relasi musik yang terdapat pada album dengan ID idAlbum, atau 0 jika idAlbum tidak valid atau album tidak memiliki musik
unsigned int hitungTotalAlbumMusik(const ListAlbum& listAlbum, const std::string& idAlbum);

// mengembalikan true jika idAlbum tidak valid atau album tidak memiliki relasi musik, atau false jika album memiliki sejumlah relasi musik
bool kosongAlbumMusik(const ListAlbum& listAlbum, const std::string& idAlbum);

// mengembalikan ListAlbum berisi semua album yang berelasi dengan data musik yang ditunjuk oleh pointer musik, atau ListAlbum kosong jika pointer musik tidak valid atau tidak ditemukan relasi yang sesuai
ListAlbum cariSemuaAlbumMusik(const ListAlbum& listAlbum, Musik* const musik);

// I.S.: listAlbum mungkin kosong atau sudah memiliki album dan relasi musik. idAlbum mungkin valid atau tidak valid. Pointer musik menunjuk ke musik yang valid
// F.S.: jika idAlbum tidak valid atau musik sudah terdaftar pada album mana pun, listAlbum tidak berubah. Jika tidak, relasi musik baru ditambahkan pada bagian akhir daftar relasi musik dari album dengan ID idAlbum dalam listAlbum
void tambahAlbumMusik(ListAlbum& listAlbum, const std::string& idAlbum, Musik* const musik);

// I.S.: listAlbum sudah memiliki album dan relasi musik. idAlbum mungkin valid atau tidak valid. Pointer musik menunjuk ke musik yang valid
// F.S.: jika idAlbum tidak valid atau musik tidak terdaftar pada album mana pun, listAlbum tidak berubah. Jika tidak, relasi antara musik dan album dengan ID idAlbum dihapus dalam listAlbum
void hapusAlbumMusik(ListAlbum& listAlbum, const std::string& idAlbum, Musik* const musik);

// I.S. listAlbum sudah memiliki album dan relasi musik. Pointer musik menunjuk ke musik yang valid
// F.S. musik yang ditunjuk pointer musik tidak lagi memiliki album dalam listAlbum
void hapusSemuaAlbumMusik(ListAlbum& listAlbum, Musik* const musik);

// I.S.: listAlbum mungkin kosong atau sudah memiliki album dan relasi musik. idAlbum mungkin valid atau tidak valid
// F.S.: jika idAlbum tidak valid, ditampilkan pesan bahwa album tidak ditemukan. Jika album belum memiliki musik, ditampilkan pesan bahwa album belum memiliki musik. Jika album memiliki relasi musik, seluruh data musik yang terhubung ditampilkan. listAlbum tidak berubah
void tampilkanSemuaAlbumMusik(const ListAlbum& listAlbum, const std::string& idAlbum);

#endif
