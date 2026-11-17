#include <iostream>
#include "musik.hpp"

void tampilkanMusik(const Musik& musik) {
    std::cout << "ID musik: " << musik.id << std::endl;
    std::cout << "Judul musik: " << musik.judul << std::endl;
    std::cout << "Durasi musik: " << musik.durasi / 60 << " menit " << musik.durasi % 60 << " detik" << std::endl;
    std::cout << "Tahun rilis musik: " << musik.tahunRilis << std::endl;
}