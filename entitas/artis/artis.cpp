#include <iostream>
#include "artis.hpp"

void tampilkanArtis(const Artis& artis) {
    std::cout << "ID artis: " << artis.id << std::endl;
    std::cout << "Nama artis: " << artis.nama << std::endl;
}