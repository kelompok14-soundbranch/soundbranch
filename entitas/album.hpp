#ifndef ALBUM_HPP
#define ALBUM_HPP

#include <string>
#include "artis.hpp"

struct Album {
    std::string id;
    std::string nama;
    std::string deskripsi;
    unsigned short tahunRilis;

    Artis* artis;
};

#endif