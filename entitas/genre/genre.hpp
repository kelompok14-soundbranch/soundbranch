#ifndef GENRE_HPP
#define GENRE_HPP

#include <string>

struct Genre {
    std::string nama;
};

// mengembalikan pointer ke genre baru valid jika nama yang diberikan valid, atau nullptr jika salah satunya tidak valid
Genre* buatGenre(const std::string& nama);

// I.S.: terdefinisi genre valid
// F.S.: ditampilkan seluruh data genre. genre tidak mengalami perubahan
void tampilkanGenre(const Genre& genre);

#endif