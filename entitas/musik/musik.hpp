#ifndef MUSIK_HPP
#define MUSIK_HPP

#include <string>

struct Musik {
    std::string id;
    std::string judul;
    int durasi;
    short tahunRilis;
};

// I.S.: terdefinisi musik valid
// F.S.: ditampilkan seluruh data musik. musik tidak mengalami perubahan
void tampilkanMusik(const Musik& musik);

#endif