#include <iostream>
#include "album.hpp"

void tampilkanAlbum(const Album& album) {
    std::cout << "ID album: " << album.id << std::endl;
    std::cout << "Nama album: " << album.nama << std::endl;
    std::cout << "Deskripsi album: " << album.deskripsi << std::endl;
    std::cout << "Tahun rilis album: " << album.tahunRilis << std::endl;
    std::cout << std::endl;
    std::cout << "DATA ARTIS" << std::endl;
    std::cout << "----------" << std::endl;
    tampilkanArtis(*album.artis);
    std::cout << "----------" << std::endl;
}