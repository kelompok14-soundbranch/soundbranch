#ifndef ALBUM_HPP
#define ALBUM_HPP

#include <string>

struct Album {
    std::string id;
    std::string nama;
    std::string deskripsi;
    unsigned short tahunRilis;
};

#endif