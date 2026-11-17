#include <iostream>
#include "list-album.hpp"

ListAlbum buatListAlbum() {
    ListAlbum listAlbum;
    listAlbum.first = nullptr;
    return listAlbum;
}

unsigned int hitungTotalAlbum(const ListAlbum& listAlbum) {
    unsigned int total = 0;

    NodeAlbum* current = listAlbum.first;
    while (current != nullptr) {
        total++;
        current = current->next;
    }

    return total;
}

bool kosongAlbum(const ListAlbum& listAlbum) {
    return listAlbum.first == nullptr;
}

Album* cariAlbum(const ListAlbum& listAlbum, const std::string& idAlbumCari) {
    NodeAlbum* current = listAlbum.first;
    while (current != nullptr) {
        if (current->album.id == idAlbumCari) {
            return &current->album;
        }

        current = current->next;
    }

    return nullptr;
}

void tambahAlbum(ListAlbum& listAlbum, const Album& albumBaru) {
    if (cariAlbum(listAlbum, albumBaru.id) != nullptr) {
        throw std::string("Sudah ada album lain dengan ID yang sama");
    }

    NodeAlbum* nodeAlbumBaru = new NodeAlbum;
    nodeAlbumBaru->album = albumBaru;
    nodeAlbumBaru->firstMusik = nullptr;
    nodeAlbumBaru->next = nullptr;

    if (kosongAlbum(listAlbum)) {
        listAlbum.first = nodeAlbumBaru;
    } else {
        NodeAlbum* current = listAlbum.first;
        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = nodeAlbumBaru;
    }
}

void hapusAlbum(ListAlbum& listAlbum, const std::string& idAlbumHapus) {
    NodeAlbum* current = listAlbum.first;
    NodeAlbum* previous = nullptr;

    while (current != nullptr && current->album.id != idAlbumHapus) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        throw std::string("Album tidak ditemukan");
    }

    if (current->firstMusik != nullptr) {
        throw std::string("Album tidak dapat dihapus karena masih memiliki relasi musik");
    }

    if (previous == nullptr) {
        listAlbum.first = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;
}

void tampilkanSemuaAlbum(const ListAlbum& listAlbum) {
    if (kosongAlbum(listAlbum)) {
        std::cout << "Belum ada album yang terdaftar" << std::endl;
        return;
    }

    unsigned int nomor = 1;
    NodeAlbum* current = listAlbum.first;
    while (current != nullptr) {
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Album " << nomor << std::endl;
        tampilkanAlbum(current->album);
        std::cout << std::endl;
        tampilkanSemuaAlbumMusik(listAlbum, current->album.id);
        std::cout << "----------------------------------" << std::endl;

        nomor++;
        current = current->next;
    }
}


unsigned int hitungTotalAlbumMusik(const ListAlbum& listAlbum, const std::string& idAlbum) {
    NodeAlbum* currentAlbum = listAlbum.first;
    while (currentAlbum != nullptr && currentAlbum->album.id != idAlbum) {
        currentAlbum = currentAlbum->next;
    }

    if (currentAlbum == nullptr) {
        return 0;
    }

    unsigned int total = 0;
    NodeRelasiMusik* currentRelasi = currentAlbum->firstMusik;

    while (currentRelasi != nullptr) {
        total++;
        currentRelasi = currentRelasi->next;
    }

    return total;
}

bool kosongAlbumMusik(const ListAlbum& listAlbum, const std::string& idAlbum) {
    NodeAlbum* current = listAlbum.first;
    while (current != nullptr && current->album.id != idAlbum) {
        current = current->next;
    }

    if (current == nullptr) {
        return true;
    }

    return current->firstMusik == nullptr;
}

ListAlbum cariSemuaAlbumMusik(const ListAlbum& listAlbum, Musik* const musik) {
    ListAlbum hasil = buatListAlbum();
    
    NodeAlbum* currentAlbum = listAlbum.first;
    while (currentAlbum != nullptr) {
        NodeRelasiMusik* currentRelasi = currentAlbum->firstMusik;

        while (currentRelasi != nullptr) {
            if (currentRelasi->musik == musik) {
                NodeAlbum* nodeAlbumBaru = new NodeAlbum;
                nodeAlbumBaru->album = currentAlbum->album;
                nodeAlbumBaru->firstMusik = nullptr;
                nodeAlbumBaru->next = nullptr;

                if (kosongAlbum(hasil)) {
                    hasil.first = nodeAlbumBaru;
                } else {
                    NodeAlbum* current = hasil.first;

                    while (current->next != nullptr) {
                        current = current->next;
                    }

                    current->next = nodeAlbumBaru;
                }

                NodeRelasiMusik* nodeRelasiBaru = new NodeRelasiMusik;
                nodeRelasiBaru->musik = musik;
                nodeRelasiBaru->next = nullptr;

                nodeAlbumBaru->firstMusik = nodeRelasiBaru;

                break;
            }

            currentRelasi = currentRelasi->next;
        }

        currentAlbum = currentAlbum->next;
    }

    return hasil;
}

void tambahAlbumMusik(ListAlbum& listAlbum, const std::string& idAlbum, Musik* const musik) {
    NodeAlbum* currentAlbum = listAlbum.first;
    while (currentAlbum != nullptr && currentAlbum->album.id != idAlbum) {
        currentAlbum = currentAlbum->next;
    }

    if (currentAlbum == nullptr) {
        throw std::string("Album tidak ditemukan");
    }

    NodeRelasiMusik* currentRelasi = currentAlbum->firstMusik;
    while (currentRelasi != nullptr) {
        if (currentRelasi->musik == musik) {
            throw std::string("Musik sudah terdaftar pada album tersebut sebelumnya");
        }

        currentRelasi = currentRelasi->next;
    }

    NodeRelasiMusik* nodeRelasiBaru = new NodeRelasiMusik;
    nodeRelasiBaru->musik = musik;
    nodeRelasiBaru->next = nullptr;

    if (currentAlbum->firstMusik == nullptr) {
        currentAlbum->firstMusik = nodeRelasiBaru;
    } else {
        currentRelasi = currentAlbum->firstMusik;

        while (currentRelasi->next != nullptr) {
            currentRelasi = currentRelasi->next;
        }

        currentRelasi->next = nodeRelasiBaru;
    }
}

void hapusAlbumMusik(ListAlbum& listAlbum, const std::string& idAlbum, Musik* const musik) {
    NodeAlbum* currentAlbum = listAlbum.first;
    while (currentAlbum != nullptr && currentAlbum->album.id != idAlbum) {
        currentAlbum = currentAlbum->next;
    }

    if (currentAlbum == nullptr) {
        throw std::string("Album tidak ditemukan");
    }

    NodeRelasiMusik* currentRelasi = currentAlbum->firstMusik;
    NodeRelasiMusik* previousRelasi = nullptr;

    while (currentRelasi != nullptr && currentRelasi->musik != musik) {
        previousRelasi = currentRelasi;
        currentRelasi = currentRelasi->next;
    }

    if (currentRelasi == nullptr) {
        throw std::string("Musik tidak terdaftar pada album tersebut");
    }

    if (previousRelasi == nullptr) {
        currentAlbum->firstMusik = currentRelasi->next;
    } else {
        previousRelasi->next = currentRelasi->next;
    }

    delete currentRelasi;
}

void hapusSemuaAlbumMusik(ListAlbum& listAlbum, Musik* const musik) {
    NodeAlbum* currentAlbum = listAlbum.first;

    while (currentAlbum != nullptr) {
        NodeRelasiMusik* currentRelasi = currentAlbum->firstMusik;
        NodeRelasiMusik* previousRelasi = nullptr;

        while (currentRelasi != nullptr) {
            if (currentRelasi->musik == musik) {
                NodeRelasiMusik* nodeHapus = currentRelasi;

                if (previousRelasi == nullptr) {
                    currentAlbum->firstMusik = currentRelasi->next;
                } else {
                    previousRelasi->next = currentRelasi->next;
                }

                currentRelasi = currentRelasi->next;
                delete nodeHapus;
            } else {
                previousRelasi = currentRelasi;
                currentRelasi = currentRelasi->next;
            }
        }

        currentAlbum = currentAlbum->next;
    }
}

void tampilkanSemuaAlbumMusik(const ListAlbum& listAlbum, const std::string& idAlbum) {
    NodeAlbum* currentAlbum = listAlbum.first;
    while (currentAlbum != nullptr && currentAlbum->album.id != idAlbum) {
        currentAlbum = currentAlbum->next;
    }

    if (currentAlbum == nullptr) {
        std::cout << "Album tidak ditemukan" << std::endl;
        return;
    }

    if (currentAlbum->firstMusik == nullptr) {
        std::cout << "Album belum memiliki musik" << std::endl;
        return;
    }

    std::cout << "DAFTAR MUSIK" << std::endl;

    unsigned int nomor = 1;
    NodeRelasiMusik* currentRelasi = currentAlbum->firstMusik;

    while (currentRelasi != nullptr) {
        if (currentRelasi->musik != nullptr) {
            std::cout << "----------" << std::endl;
            std::cout << "Relasi album musik " << nomor << std::endl;
            tampilkanMusik(*currentRelasi->musik);
            std::cout << "----------" << std::endl;
            nomor++;
        }

        currentRelasi = currentRelasi->next;
    }
}