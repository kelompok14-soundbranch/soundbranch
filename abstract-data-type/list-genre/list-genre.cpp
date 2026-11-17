#include <iostream>
#include "list-genre.hpp"

ListGenre buatListGenre() {
    ListGenre listGenre;
    listGenre.first = nullptr;
    return listGenre;
}

unsigned int hitungTotalGenre(const ListGenre& listGenre) {
    unsigned int total = 0;

    NodeGenre* current = listGenre.first;
    while (current != nullptr) {
        total++;
        current = current->next;
    }

    return total;
}

bool kosongGenre(const ListGenre& listGenre) {
    return listGenre.first == nullptr;
}

Genre* cariGenre(const ListGenre& listGenre, const std::string& namaGenreCari) {
    NodeGenre* current = listGenre.first;
    while (current != nullptr) {
        if (current->genre.nama == namaGenreCari) {
            return &current->genre;
        }

        current = current->next;
    }

    return nullptr;
}

void tambahGenre(ListGenre& listGenre, const Genre& genreBaru) {
    if (cariGenre(listGenre, genreBaru.nama) != nullptr) {
        throw std::string("Sudah ada genre lain dengan nama yang sama");
    }

    NodeGenre* nodeGenreBaru = new NodeGenre;
    nodeGenreBaru->genre = genreBaru;
    nodeGenreBaru->firstMusik = nullptr;
    nodeGenreBaru->next = nullptr;
    
    if (kosongGenre(listGenre)) {
        listGenre.first = nodeGenreBaru;
    } else {
        NodeGenre* current = listGenre.first;
        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = nodeGenreBaru;
    }
}

void hapusGenre(ListGenre& listGenre, const std::string& namaGenreHapus) {
    NodeGenre* current = listGenre.first;
    NodeGenre* previous = nullptr;
    while (current != nullptr && current->genre.nama != namaGenreHapus) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        throw std::string("Genre tidak ditemukan");
    }

    if (current->firstMusik != nullptr) {
        throw std::string("Genre tidak dapat dihapus karena masih memiliki relasi musik");
    }

    if (previous == nullptr) {
        listGenre.first = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;
}

void tampilkanSemuaGenre(const ListGenre& listGenre) {
    if (kosongGenre(listGenre)) {
        std::cout << "Belum ada genre yang terdaftar" << std::endl;
        return;
    }

    unsigned int nomor = 1;
    NodeGenre* current = listGenre.first;
    while (current != nullptr) {
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Genre " << nomor << std::endl;
        tampilkanGenre(current->genre);
        std::cout << std::endl;
        tampilkanSemuaGenreMusik(listGenre, current->genre.nama);
        std::cout << "----------------------------------" << std::endl;

        nomor++;
        current = current->next;
    }
}



unsigned int hitungTotalGenreMusik(const ListGenre& listGenre, const std::string& namaGenre) {
    NodeGenre* currentGenre = listGenre.first;
    while (currentGenre != nullptr && currentGenre->genre.nama != namaGenre) {
        currentGenre = currentGenre->next;
    }

    if (currentGenre == nullptr) {
        return 0;
    }

    unsigned int total = 0;
    NodeRelasiMusik* currentRelasi = currentGenre->firstMusik;
    while (currentRelasi != nullptr) {
        total++;
        currentRelasi = currentRelasi->next;
    }

    return total;
}

bool kosongGenreMusik(const ListGenre& listGenre, const std::string& namaGenre) {
    NodeGenre* current = listGenre.first;
    while (current != nullptr && current->genre.nama != namaGenre) {
        current = current->next;
    }

    if (current == nullptr) {
        return true;
    }

    return current->firstMusik == nullptr;
}

ListGenre cariSemuaGenreMusik(const ListGenre& listGenre, Musik* const musik) {
    ListGenre hasil = buatListGenre();

    NodeGenre* currentGenre = listGenre.first;
    while (currentGenre != nullptr) {
        NodeRelasiMusik* currentRelasi = currentGenre->firstMusik;
        while (currentRelasi != nullptr) {
            if (currentRelasi->musik == musik) {
                Genre genreBaru;
                genreBaru.nama = currentGenre->genre.nama;

                NodeGenre* nodeGenreBaru = new NodeGenre;
                nodeGenreBaru->genre = genreBaru;
                nodeGenreBaru->firstMusik = nullptr;
                nodeGenreBaru->next = nullptr;

                if (kosongGenre(hasil)) {
                    hasil.first = nodeGenreBaru;
                } else {
                    NodeGenre* current = hasil.first;
                    while (current->next != nullptr) {
                        current = current->next;
                    }

                    current->next = nodeGenreBaru;
                }

                NodeRelasiMusik* nodeRelasiBaru = new NodeRelasiMusik;
                nodeRelasiBaru->musik = musik;
                nodeRelasiBaru->next = nullptr;

                nodeGenreBaru->firstMusik = nodeRelasiBaru;

                break;
            }

            currentRelasi = currentRelasi->next;
        }

        currentGenre = currentGenre->next;
    }

    return hasil;
}

void tambahGenreMusik(ListGenre& listGenre, const std::string& namaGenre, Musik* const musik) {
    NodeGenre* currentGenre = listGenre.first;
    while (currentGenre != nullptr && currentGenre->genre.nama != namaGenre) {
        currentGenre = currentGenre->next;
    }

    if (currentGenre == nullptr) {
        throw std::string("Genre tidak ditemukan");
    }

    NodeRelasiMusik* currentRelasi = currentGenre->firstMusik;
    while (currentRelasi != nullptr) {
        if (currentRelasi->musik == musik) {
            throw std::string("Musik sudah terdaftar pada genre tersebut sebelumnya");
        }

        currentRelasi = currentRelasi->next;
    }

    NodeRelasiMusik* nodeRelasiBaru = new NodeRelasiMusik;
    nodeRelasiBaru->musik = musik;
    nodeRelasiBaru->next = nullptr;

    if (currentGenre->firstMusik == nullptr) {
        currentGenre->firstMusik = nodeRelasiBaru;
    } else {
        currentRelasi = currentGenre->firstMusik;
    
        while (currentRelasi->next != nullptr) {
            currentRelasi = currentRelasi->next;
        }
    
        currentRelasi->next = nodeRelasiBaru;
    }
}

void hapusGenreMusik(ListGenre& listGenre, const std::string& namaGenre, Musik* const musik) {    
    NodeGenre* currentGenre = listGenre.first;
    while (currentGenre != nullptr && currentGenre->genre.nama != namaGenre) {
        currentGenre = currentGenre->next;
    }
    
    if (currentGenre == nullptr) {
        throw std::string("Genre tidak ditemukan");
    }
    
    NodeRelasiMusik* currentRelasi = currentGenre->firstMusik;
    NodeRelasiMusik* previousRelasi = nullptr;
    while (currentRelasi != nullptr && currentRelasi->musik != musik) {
        previousRelasi = currentRelasi;
        currentRelasi = currentRelasi->next;
    }
    
    if (currentRelasi == nullptr) {
        throw std::string("Musik tidak terdaftar pada genre tersebut");
    }
    
    if (previousRelasi == nullptr) {
        currentGenre->firstMusik = currentRelasi->next;
    } else {
        previousRelasi->next = currentRelasi->next;
    }
    
    delete currentRelasi;
}

void hapusSemuaGenreMusik(ListGenre& listGenre, Musik* const musik) {
    NodeGenre* currentGenre = listGenre.first;

    while (currentGenre != nullptr) {
        NodeRelasiMusik* currentRelasi = currentGenre->firstMusik;
        NodeRelasiMusik* previousRelasi = nullptr;

        while (currentRelasi != nullptr) {
            if (currentRelasi->musik == musik) {
                NodeRelasiMusik* hapus = currentRelasi;

                if (previousRelasi == nullptr) {
                    currentGenre->firstMusik = currentRelasi->next;
                } else {
                    previousRelasi->next = currentRelasi->next;
                }

                currentRelasi = currentRelasi->next;
                delete hapus;
            } else {
                previousRelasi = currentRelasi;
                currentRelasi = currentRelasi->next;
            }
        }

        currentGenre = currentGenre->next;
    }
}

void tampilkanSemuaGenreMusik(const ListGenre& listGenre, const std::string& namaGenre) {
    NodeGenre* currentGenre = listGenre.first;
    while (currentGenre != nullptr && currentGenre->genre.nama != namaGenre) {
        currentGenre = currentGenre->next;
    }

    if (currentGenre == nullptr) {
        std::cout << "Genre tidak ditemukan" << std::endl;
        return;
    }

    if (currentGenre->firstMusik == nullptr) {
        std::cout << "Genre belum memiliki musik" << std::endl;
        return;
    }
    
    std::cout << "DAFTAR MUSIK" << std::endl;

    unsigned int nomor = 1;
    NodeRelasiMusik* currentRelasi = currentGenre->firstMusik;
    while (currentRelasi != nullptr) {
        if (currentRelasi->musik != nullptr) {
            std::cout << "----------" << std::endl;
            std::cout << "Relasi genre musik " << nomor << std::endl;
            tampilkanMusik(*currentRelasi->musik);
            std::cout << "----------" << std::endl;
            nomor++;
        }

        currentRelasi = currentRelasi->next;
    }
}