#include <iostream>
#include "list-artis.hpp"

ListArtis buatListArtis() {
    ListArtis listArtis;
    listArtis.first = nullptr;
    return listArtis;
}

unsigned int hitungTotalArtis(const ListArtis& listArtis) {
    unsigned int total = 0;

    NodeArtis* current = listArtis.first;
    while (current != nullptr) {
        total++;
        current = current->next;
    }

    return total;
}

bool kosongArtis(const ListArtis& listArtis) {
    return listArtis.first == nullptr;
}

Artis* cariArtis(const ListArtis& listArtis, const std::string& idArtisCari) {
    NodeArtis* current = listArtis.first;
    while (current != nullptr) {
        if (current->artis.id == idArtisCari) {
            return &current->artis;
        }

        current = current->next;
    }

    return nullptr;
}

void tambahArtis(ListArtis& listArtis, const Artis& artisBaru) {
    if (cariArtis(listArtis, artisBaru.id) != nullptr) {
        std::cout << "Artis sudah terdaftar" << std::endl;
        return;
    }

    NodeArtis* nodeArtisBaru = new NodeArtis;
    nodeArtisBaru->artis = artisBaru;
    nodeArtisBaru->firstMusik = nullptr;
    nodeArtisBaru->next = nullptr;

    if (kosongArtis(listArtis)) {
        listArtis.first = nodeArtisBaru;
    } else {
        NodeArtis* current = listArtis.first;
        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = nodeArtisBaru;
    }

    std::cout << "Artis berhasil ditambahkan" << std::endl;
}

void hapusArtis(ListArtis& listArtis, const std::string& idArtisHapus) {
    NodeArtis* current = listArtis.first;
    NodeArtis* previous = nullptr;

    while (current != nullptr && current->artis.id != idArtisHapus) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Artis tidak ditemukan" << std::endl;
        return;
    }

    if (current->firstMusik != nullptr) {
        std::cout << "Artis tidak dapat dihapus karena masih memiliki relasi musik" << std::endl;
        return;
    }

    if (previous == nullptr) {
        listArtis.first = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;

    std::cout << "Artis berhasil dihapus" << std::endl;
}

void tampilkanSemuaArtis(const ListArtis& listArtis) {
    if (kosongArtis(listArtis)) {
        std::cout << "Belum ada artis yang terdaftar" << std::endl;
        return;
    }

    std::cout << "========== DAFTAR ARTIS ==========" << std::endl;

    NodeArtis* current = listArtis.first;
    while (current != nullptr) {
        std::cout << "ID artis: " << current->artis.id << std::endl;
        std::cout << "Nama artis: " << current->artis.nama << std::endl;

        tampilkanSemuaArtisMusik(listArtis, current->artis.id);

        std::cout << "----------------------------------" << std::endl;

        current = current->next;
    }
}


unsigned int hitungTotalArtisMusik(const ListArtis& listArtis, const std::string& idArtis) {
    NodeArtis* currentArtis = listArtis.first;
    while (currentArtis != nullptr && currentArtis->artis.id != idArtis) {
        currentArtis = currentArtis->next;
    }

    if (currentArtis == nullptr) {
        return 0;
    }

    unsigned int total = 0;
    NodeRelasiMusik* currentRelasi = currentArtis->firstMusik;

    while (currentRelasi != nullptr) {
        total++;
        currentRelasi = currentRelasi->next;
    }

    return total;
}

bool kosongArtisMusik(const ListArtis& listArtis, const std::string& idArtis) {
    NodeArtis* current = listArtis.first;
    while (current != nullptr && current->artis.id != idArtis) {
        current = current->next;
    }

    if (current == nullptr) {
        return true;
    }

    return current->firstMusik == nullptr;
}

ListArtis cariArtisMusik(const ListArtis& listArtis, Musik* const musik) {
    ListArtis hasil = buatListArtis();

    if (musik == nullptr) {
        return hasil;
    }

    NodeArtis* currentArtis = listArtis.first;
    while (currentArtis != nullptr) {
        NodeRelasiMusik* currentRelasi = currentArtis->firstMusik;

        while (currentRelasi != nullptr) {
            if (currentRelasi->musik == musik) {
                NodeArtis* nodeArtisBaru = new NodeArtis;
                nodeArtisBaru->artis = currentArtis->artis;
                nodeArtisBaru->firstMusik = nullptr;
                nodeArtisBaru->next = nullptr;

                if (kosongArtis(hasil)) {
                    hasil.first = nodeArtisBaru;
                } else {
                    NodeArtis* current = hasil.first;

                    while (current->next != nullptr) {
                        current = current->next;
                    }

                    current->next = nodeArtisBaru;
                }

                NodeRelasiMusik* nodeRelasiBaru = new NodeRelasiMusik;
                nodeRelasiBaru->musik = musik;
                nodeRelasiBaru->next = nullptr;

                nodeArtisBaru->firstMusik = nodeRelasiBaru;

                break;
            }

            currentRelasi = currentRelasi->next;
        }

        currentArtis = currentArtis->next;
    }

    return hasil;
}

void tambahArtisMusik(ListArtis& listArtis, const std::string& idArtis, Musik* const musik) {
    if (musik == nullptr) {
        std::cout << "Data musik tidak valid" << std::endl;
        return;
    }

    NodeArtis* currentArtis = listArtis.first;
    while (currentArtis != nullptr && currentArtis->artis.id != idArtis) {
        currentArtis = currentArtis->next;
    }

    if (currentArtis == nullptr) {
        std::cout << "Artis tidak ditemukan" << std::endl;
        return;
    }

    NodeRelasiMusik* currentRelasi = currentArtis->firstMusik;
    while (currentRelasi != nullptr) {
        if (currentRelasi->musik == musik) {
            std::cout << "Musik sudah terdaftar pada artis tersebut" << std::endl;
            return;
        }

        currentRelasi = currentRelasi->next;
    }

    NodeRelasiMusik* nodeRelasiBaru = new NodeRelasiMusik;
    nodeRelasiBaru->musik = musik;
    nodeRelasiBaru->next = nullptr;

    if (currentArtis->firstMusik == nullptr) {
        currentArtis->firstMusik = nodeRelasiBaru;
    } else {
        currentRelasi = currentArtis->firstMusik;

        while (currentRelasi->next != nullptr) {
            currentRelasi = currentRelasi->next;
        }

        currentRelasi->next = nodeRelasiBaru;
    }

    std::cout << "Relasi artis musik berhasil ditambahkan" << std::endl;
}

void hapusArtisMusik(ListArtis& listArtis, const std::string& idArtis, Musik* const musik) {
    if (musik == nullptr) {
        std::cout << "Data musik tidak valid" << std::endl;
        return;
    }

    NodeArtis* currentArtis = listArtis.first;
    while (currentArtis != nullptr && currentArtis->artis.id != idArtis) {
        currentArtis = currentArtis->next;
    }

    if (currentArtis == nullptr) {
        std::cout << "Artis tidak ditemukan" << std::endl;
        return;
    }

    NodeRelasiMusik* currentRelasi = currentArtis->firstMusik;
    NodeRelasiMusik* previousRelasi = nullptr;

    while (currentRelasi != nullptr && currentRelasi->musik != musik) {
        previousRelasi = currentRelasi;
        currentRelasi = currentRelasi->next;
    }

    if (currentRelasi == nullptr) {
        std::cout << "Musik tidak terdaftar pada artis tersebut" << std::endl;
        return;
    }

    if (previousRelasi == nullptr) {
        currentArtis->firstMusik = currentRelasi->next;
    } else {
        previousRelasi->next = currentRelasi->next;
    }

    delete currentRelasi;

    std::cout << "Relasi artis musik berhasil dihapus" << std::endl;
}

void tampilkanSemuaArtisMusik(const ListArtis& listArtis, const std::string& idArtis) {
    NodeArtis* currentArtis = listArtis.first;
    while (currentArtis != nullptr && currentArtis->artis.id != idArtis) {
        currentArtis = currentArtis->next;
    }

    if (currentArtis == nullptr) {
        std::cout << "Artis tidak ditemukan" << std::endl;
        return;
    }

    if (currentArtis->firstMusik == nullptr) {
        std::cout << "Artis belum memiliki musik" << std::endl;
        return;
    }

    std::cout << "Daftar musik:" << std::endl;

    NodeRelasiMusik* currentRelasi = currentArtis->firstMusik;
    unsigned int nomor = 1;

    while (currentRelasi != nullptr) {
        if (currentRelasi->musik != nullptr) {
            std::cout << nomor << ". " << currentRelasi->musik->judul << std::endl;
            nomor++;
        }

        currentRelasi = currentRelasi->next;
    }
}