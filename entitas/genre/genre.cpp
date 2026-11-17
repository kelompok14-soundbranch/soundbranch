#include <iostream>
#include "genre.hpp"

Genre* buatGenre(const std::string& nama) {
    if (nama == "") {
        return nullptr;
    }

    Genre* genre = new Genre;
    genre->nama = nama;

    return genre;
}

void tampilkanGenre(const Genre& genre) {
    std::cout << "Nama genre: " << genre.nama << std::endl;
}