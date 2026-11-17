#ifndef ARTIS_HPP
#define ARTIS_HPP

#include <string>

struct Artis {
    std::string id;
    std::string nama;
};

// I.S.: terdefinisi artis valid
// F.S.: ditampilkan seluruh data artis. artis tidak mengalami perubahan
void tampilkanArtis(const Artis& artis);

#endif