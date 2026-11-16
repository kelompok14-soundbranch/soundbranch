#ifndef LIST_ARTIS_HPP
#define LIST_ARTIS_HPP

#include <string>

#include "../../entitas/artis.hpp"
#include "../__common__/node-relasi-musik.hpp"

struct NodeArtis {
    Artis artis;
    NodeRelasiMusik* firstMusik;

    NodeArtis* next;
};

struct ListArtis {
    NodeArtis* first;
};

// mengembalikan ListArtis kosong
ListArtis buatListArtis();

// mengembalikan total seluruh artis yang terdapat dalam listArtis
unsigned int hitungTotalArtis(const ListArtis& listArtis);

// mengembalikan true jika listArtis kosong, atau false jika listArtis memiliki minimal satu artis
bool kosongArtis(const ListArtis& listArtis);

// mengembalikan pointer ke artis yang memiliki ID sesuai idArtisCari dalam listArtis, atau nullptr jika artis tidak ditemukan
Artis* cariArtis(const ListArtis& listArtis, const std::string& idArtisCari);

// I.S.: listArtis mungkin kosong atau sudah berisi sejumlah artis
// F.S.: jika artis dengan ID yang sama sudah terdaftar, listArtis tidak berubah. Jika belum terdaftar, data artisBaru ditambahkan pada bagian akhir listArtis
void tambahArtis(ListArtis& listArtis, const Artis& artisBaru);

// I.S.: listArtis mungkin kosong atau sudah berisi sejumlah artis
// F.S.: jika artis tidak ditemukan atau masih memiliki relasi musik, listArtis tidak berubah. Jika artis ditemukan dan tidak memiliki relasi musik, artis dihapus
void hapusArtis(ListArtis& listArtis, const std::string& idArtisHapus);

// I.S.: listArtis mungkin kosong atau sudah berisi sejumlah artis
// F.S.: jika listArtis kosong, ditampilkan pesan bahwa belum ada artis yang terdaftar. Jika tidak kosong, seluruh artis beserta daftar musik yang terhubung pada setiap artis ditampilkan. listArtis tidak mengalami perubahan
void tampilkanSemuaArtis(const ListArtis& listArtis);



// mengembalikan total seluruh relasi musik yang terdapat pada artis dengan ID sesuai idArtis, atau 0 jika artis tidak ditemukan atau tidak memiliki musik
unsigned int hitungTotalArtisMusik(const ListArtis& listArtis, const std::string& idArtis);

// mengembalikan true jika artis dengan ID sesuai idArtis tidak ditemukan atau artis tidak memiliki relasi musik, atau false jika artis memiliki minimal satu relasi musik
bool kosongArtisMusik(const ListArtis& listArtis, const std::string& idArtis);

// mengembalikan list artis yang memiliki relasi dengan data musik yang ditunjuk oleh pointer musik, atau list artis kosong jika pointer musik tidak valid atau tidak ditemukan relasi yang sesuai
ListArtis cariArtisMusik(const ListArtis& listArtis, Musik* const musik);

// I.S.: listArtis mungkin kosong atau sudah memiliki artis dan relasi musik. Pointer musik mungkin nullptr atau menunjuk pada data musik yang valid
// F.S.: jika pointer musik tidak valid atau artis tidak ditemukan atau musik sudah terdaftar pada artis tersebut, listArtis tidak berubah. Jika tidak, relasi baru ditambahkan pada bagian akhir daftar relasi musik dari artis dengan ID sesuai idArtis
void tambahArtisMusik(ListArtis& listArtis, const std::string& idArtis, Musik* const musik);

// I.S.: listArtis mungkin kosong atau sudah memiliki artis dan relasi musik. Pointer musik mungkin nullptr atau menunjuk pada data musik yang valid
// F.S.: jika pointer musik tidak valid, artis tidak ditemukan, atau musik tidak terdaftar pada artis tersebut, struktur ListArtis tidak berubah. Jika relasi ditemukan, node relasi musik dihapus dan hubungan antar-node relasi tetap terjaga
void hapusArtisMusik(ListArtis& listArtis, const std::string& idArtis, Musik* const musik);

// I.S.: listArtis mungkin kosong atau sudah memiliki artis dan relasi musik
// F.S.: jika artis tidak ditemukan, ditampilkan pesan bahwa artis tidak ditemukan. Jika artis belum memiliki musik, ditampilkan pesan bahwa artis belum memiliki musik. Jika artis memiliki relasi musik, seluruh judul musik yang terhubung dengan artis tersebut ditampilkan. listArtis tidak mengalami perubahan
void tampilkanSemuaArtisMusik(const ListArtis& listArtis, const std::string& idArtis);

#endif