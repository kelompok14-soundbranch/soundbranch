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
        throw std::string("Sudah ada artis lain dengan ID yang sama");
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
}

void hapusArtis(ListArtis& listArtis, const std::string& idArtisHapus) {
    NodeArtis* current = listArtis.first;
    NodeArtis* previous = nullptr;

    while (current != nullptr && current->artis.id != idArtisHapus) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        throw std::string("Artis tidak ditemukan");
    }

    if (current->firstMusik != nullptr) {
        throw std::string("Artis tidak dapat dihapus karena masih memiliki relasi musik");
    }

    if (previous == nullptr) {
        listArtis.first = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;
}

void tampilkanSemuaArtis(const ListArtis& listArtis) {
    if (kosongArtis(listArtis)) {
        std::cout << "Belum ada artis yang terdaftar" << std::endl;
        return;
    }

    unsigned int nomor = 1;
    NodeArtis* current = listArtis.first;
    while (current != nullptr) {
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Artis " << nomor << std::endl;
        tampilkanArtis(current->artis);
        std::cout << std::endl;
        tampilkanSemuaArtisMusik(listArtis, current->artis.id);
        std::cout << "----------------------------------" << std::endl;

        nomor++;
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

ListArtis cariSemuaArtisMusik(const ListArtis& listArtis, Musik* const musik) {
    ListArtis hasil = buatListArtis();

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
    NodeArtis* currentArtis = listArtis.first;
    while (currentArtis != nullptr && currentArtis->artis.id != idArtis) {
        currentArtis = currentArtis->next;
    }

    if (currentArtis == nullptr) {
        throw std::string("Artis tidak ditemukan");
    }

    NodeRelasiMusik* currentRelasi = currentArtis->firstMusik;
    while (currentRelasi != nullptr) {
        if (currentRelasi->musik == musik) {
            throw std::string("Musik sudah terdaftar pada artis tersebut sebelumnya");
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
}

void hapusArtisMusik(ListArtis& listArtis, const std::string& idArtis, Musik* const musik) {
    NodeArtis* currentArtis = listArtis.first;
    while (currentArtis != nullptr && currentArtis->artis.id != idArtis) {
        currentArtis = currentArtis->next;
    }

    if (currentArtis == nullptr) {
        throw std::string("Artis tidak ditemukan");
    }

    NodeRelasiMusik* currentRelasi = currentArtis->firstMusik;
    NodeRelasiMusik* previousRelasi = nullptr;

    while (currentRelasi != nullptr && currentRelasi->musik != musik) {
        previousRelasi = currentRelasi;
        currentRelasi = currentRelasi->next;
    }

    if (currentRelasi == nullptr) {
        throw std::string("Musik tidak terdaftar pada artis tersebut");
    }

    if (previousRelasi == nullptr) {
        currentArtis->firstMusik = currentRelasi->next;
    } else {
        previousRelasi->next = currentRelasi->next;
    }

    delete currentRelasi;
}

void hapusSemuaArtisMusik(ListArtis& listArtis, Musik* const musik) {
    NodeArtis* currentArtis = listArtis.first;

    while (currentArtis != nullptr) {
        NodeRelasiMusik* currentRelasi = currentArtis->firstMusik;
        NodeRelasiMusik* previousRelasi = nullptr;

        while (currentRelasi != nullptr) {
            if (currentRelasi->musik == musik) {
                NodeRelasiMusik* hapus = currentRelasi;

                if (previousRelasi == nullptr) {
                    currentArtis->firstMusik = currentRelasi->next;
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

        currentArtis = currentArtis->next;
    }
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

    std::cout << "DAFTAR MUSIK" << std::endl;

    unsigned int nomor = 1;
    NodeRelasiMusik* currentRelasi = currentArtis->firstMusik;

    while (currentRelasi != nullptr) {
        if (currentRelasi->musik != nullptr) {
            std::cout << "----------" << std::endl;
            std::cout << "Relasi artis musik " << nomor << std::endl;
            tampilkanMusik(*currentRelasi->musik);
            std::cout << "----------" << std::endl;
            nomor++;
        }

        currentRelasi = currentRelasi->next;
    }
}