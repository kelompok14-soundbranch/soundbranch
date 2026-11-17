#ifndef LIST_GENRE_HPP
#define LIST_GENRE_HPP

#include <string>

#include "../../entitas/genre/genre.hpp"
#include "../__common__/node-relasi-musik.hpp"

struct NodeGenre {
    Genre genre;
    NodeRelasiMusik* firstMusik;

    NodeGenre* next;
};

struct ListGenre {
    NodeGenre* first;
};

// mengembalikan listGenre kosong
ListGenre buatListGenre();

// mengembalikan total seluruh genre yang terdapat dalam listGenre
unsigned int hitungTotalGenre(const ListGenre& listGenre);

// mengembalikan true jika listGenre kosong, atau false jika listGenre memiliki minimal satu genre
bool kosongGenre(const ListGenre& listGenre);

// mengembalikan pointer ke genre yang memiliki nama sesuai namaGenreCari dalam listGenre, atau nullptr jika genre tidak ditemukan
Genre* cariGenre(const ListGenre& listGenre, const std::string& namaGenreCari);

// I.S.: listGenre mungkin kosong atau sudah berisi sejumlah genre. genreBaru adalah genre yang valid
// F.S.: jika genre dengan nama yang sama sudah terdaftar, listGenre tidak berubah. Jika belum terdaftar, data genreBaru ditambahkan pada bagian akhir listGenre
void tambahGenre(ListGenre& listGenre, const Genre& genreBaru);

// I.S.: listGenre mungkin kosong atau sudah berisi sejumlah genre
// F.S.: jika genre tidak ditemukan atau masih memiliki relasi musik, listGenre tidak berubah. Jika genre ditemukan dan tidak memiliki relasi musik, genre dihapus
void hapusGenre(ListGenre& listGenre, const std::string& namaGenreHapus);

// I.S.: listGenre mungkin kosong atau sudah berisi sejumlah genre
// F.S.: jika listGenre kosong, ditampilkan pesan bahwa belum ada genre yang terdaftar. Jika tidak kosong, seluruh genre beserta daftar musik yang terhubung pada setiap genre ditampilkan. listGenre tidak mengalami perubahan
void tampilkanSemuaGenre(const ListGenre& listGenre);



// mengembalikan total seluruh relasi musik yang terdapat pada genre dengan nama sesuai namaGenre, atau 0 jika genre tidak ditemukan atau tidak memiliki musik
unsigned int hitungTotalGenreMusik(const ListGenre& listGenre, const std::string& namaGenre);

// mengembalikan true jika genre dengan nama sesuai namaGenre tidak ditemukan atau genre tidak memiliki relasi musik, atau false jika genre memiliki minimal satu relasi musik
bool kosongGenreMusik(const ListGenre& listGenre, const std::string& namaGenre);

// mengembalikan list genre yang memiliki relasi dengan musik yang ditunjuk oleh pointer musik, atau list genre kosong jika pointer musik tidak valid atau tidak ditemukan relasi yang sesuai
ListGenre cariSemuaGenreMusik(const ListGenre& listGenre, Musik* const musik);

// I.S.: listGenre mungkin kosong atau sudah memiliki genre dan relasi musik. Pointer musik mungkin nullptr atau menunjuk pada data musik yang valid
// F.S.: jika pointer musik tidak valid atau genre tidak ditemukan atau musik sudah terdaftar pada genre tersebut, listGenre tidak berubah. Jika tidak, relasi baru ditambahkan pada bagian akhir daftar relasi musik dari genre dengan nama sesuai namaGenre
void tambahGenreMusik(ListGenre& listGenre, const std::string& namaGenre, Musik* const musik);

// I.S.: listGenre mungkin kosong atau sudah memiliki genre dan relasi musik. Pointer musik mungkin nullptr atau menunjuk pada data musik yang valid
// F.S.: jika pointer musik tidak valid, genre tidak ditemukan, atau musik tidak terdaftar pada genre tersebut, struktur ListGenre tidak berubah. Jika relasi ditemukan, node relasi musik dihapus dan hubungan antar-node relasi tetap terjaga
void hapusGenreMusik(ListGenre& listGenre, const std::string& namaGenre, Musik* const musik);

// I.S. listGenre sudah memiliki genre dan relasi musik. Pointer musik menunjuk ke musik yang valid
// F.S. musik yang ditunjuk pointer musik tidak lagi memiliki genre dalam listGenre
void hapusSemuaGenreMusik(ListGenre& listGenre, Musik* const musik);

// I.S.: listGenre mungkin kosong atau sudah memiliki genre dan relasi musik
// F.S.: jika genre tidak ditemukan, ditampilkan pesan bahwa genre tidak ditemukan. Jika genre belum memiliki musik, ditampilkan pesan bahwa genre belum memiliki musik. Jika genre memiliki relasi musik, seluruh judul musik yang terhubung dengan genre tersebut ditampilkan. listGenre tidak mengalami perubahan
void tampilkanSemuaGenreMusik(const ListGenre& listGenre, const std::string& namaGenre);

#endif