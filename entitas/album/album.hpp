#ifndef ALBUM_HPP
#define ALBUM_HPP

#include <string>
#include "../artis/artis.hpp"

struct Album {
    std::string id;
    std::string nama;
    std::string deskripsi;
    short tahunRilis;

    Artis* artis;
};

// I.S.: terdefinisi album valid
// F.S.: ditampilkan seluruh data album. album tidak mengalami perubahan
void tampilkanAlbum(const Album& album);

#endif