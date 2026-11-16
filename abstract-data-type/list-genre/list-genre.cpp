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
        std::cout << "Genre sudah terdaftar" << std::endl;
        return;
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

    std::cout << "Genre berhasil ditambahkan" << std::endl;
}

void hapusGenre(ListGenre& listGenre, const std::string& namaGenreHapus) {
    NodeGenre* current = listGenre.first;
    NodeGenre* previous = nullptr;
    while (current != nullptr && current->genre.nama != namaGenreHapus) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Genre tidak ditemukan" << std::endl;
        return;
    }

    if (current->firstMusik != nullptr) {
        std::cout << "Genre tidak dapat dihapus karena masih memiliki relasi musik" << std::endl;
        return;
    }

    if (previous == nullptr) {
        listGenre.first = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;

    std::cout << "Genre berhasil dihapus" << std::endl;
}

void tampilkanSemuaGenre(const ListGenre& listGenre) {
    if (kosongGenre(listGenre)) {
        std::cout << "Belum ada genre yang terdaftar" << std::endl;
        return;
    }

    std::cout << "========== DAFTAR GENRE ==========" << std::endl;

    NodeGenre* current = listGenre.first;
    while (current != nullptr) {
        std::cout << "Nama genre: " << current->genre.nama << std::endl;
        tampilkanSemuaGenreMusik(listGenre, current->genre.nama);
        std::cout << "----------------------------------" << std::endl;

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

ListGenre cariGenreMusik(const ListGenre& listGenre, const Musik* const musik) {
    ListGenre hasil = buatListGenre();

    if (musik == nullptr) {
        return hasil;
    }

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
                nodeRelasiBaru->musik = const_cast<Musik*>(musik);
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
    if (musik == nullptr) {
        std::cout << "Data musik tidak valid" << std::endl;
        return;
    }

    NodeGenre* currentGenre = listGenre.first;
    while (currentGenre != nullptr && currentGenre->genre.nama != namaGenre) {
        currentGenre = currentGenre->next;
    }

    if (currentGenre == nullptr) {
        std::cout << "Genre tidak ditemukan" << std::endl;
        return;
    }

    NodeRelasiMusik* currentRelasi = currentGenre->firstMusik;
    while (currentRelasi != nullptr) {
        if (currentRelasi->musik == musik) {
            std::cout << "Musik sudah terdaftar pada genre tersebut" << std::endl;
            return;
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

    std::cout << "Relasi genre musik berhasil ditambahkan" << std::endl;
}

void hapusGenreMusik(ListGenre& listGenre, const std::string& namaGenre, Musik* const musik) {
    if (musik == nullptr) {
        std::cout << "Data musik tidak valid" << std::endl;
        return;
    }
    
    NodeGenre* currentGenre = listGenre.first;
    while (currentGenre != nullptr && currentGenre->genre.nama != namaGenre) {
        currentGenre = currentGenre->next;
    }
    
    if (currentGenre == nullptr) {
        std::cout << "Genre tidak ditemukan" << std::endl;
        return;
    }
    
    NodeRelasiMusik* currentRelasi = currentGenre->firstMusik;
    NodeRelasiMusik* previousRelasi = nullptr;
    while (currentRelasi != nullptr && currentRelasi->musik != musik) {
        previousRelasi = currentRelasi;
        currentRelasi = currentRelasi->next;
    }
    
    if (currentRelasi == nullptr) {
        std::cout << "Musik tidak terdaftar pada genre tersebut" << std::endl;
        return;
    }
    
    if (previousRelasi == nullptr) {
        currentGenre->firstMusik = currentRelasi->next;
    } else {
        previousRelasi->next = currentRelasi->next;
    }
    
    delete currentRelasi;
    
    std::cout << "Relasi genre musik berhasil dihapus" << std::endl;
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
    
    std::cout << "Daftar musik:" << std::endl;

    NodeRelasiMusik* currentRelasi = currentGenre->firstMusik;
    unsigned int nomor = 1;
    while (currentRelasi != nullptr) {
        if (currentRelasi->musik != nullptr) {
            std::cout << nomor << ". " << currentRelasi->musik->judul << std::endl;
            nomor++;
        }

        currentRelasi = currentRelasi->next;
    }
}