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
    if (albumBaru.artis == nullptr) {
        std::cout << "Data artis tidak valid" << std::endl;
        return;
    }

    if (cariAlbum(listAlbum, albumBaru.id) != nullptr) {
        std::cout << "Album sudah terdaftar" << std::endl;
        return;
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

    std::cout << "Album berhasil ditambahkan" << std::endl;
}

void hapusAlbum(ListAlbum& listAlbum, const std::string& idAlbumHapus) {
    NodeAlbum* current = listAlbum.first;
    NodeAlbum* previous = nullptr;

    while (current != nullptr && current->album.id != idAlbumHapus) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Album tidak ditemukan" << std::endl;
        return;
    }

    if (current->firstMusik != nullptr) {
        std::cout << "Album tidak dapat dihapus karena masih memiliki relasi musik" << std::endl;
        return;
    }

    if (previous == nullptr) {
        listAlbum.first = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;

    std::cout << "Album berhasil dihapus" << std::endl;
}

void tampilkanSemuaAlbum(const ListAlbum& listAlbum) {
    if (kosongAlbum(listAlbum)) {
        std::cout << "Belum ada album yang terdaftar" << std::endl;
        return;
    }

    std::cout << "========== DAFTAR ALBUM ==========" << std::endl;

    NodeAlbum* current = listAlbum.first;
    while (current != nullptr) {
        std::cout << "ID album: " << current->album.id << std::endl;
        std::cout << "Nama album: " << current->album.nama << std::endl;
        std::cout << "Deskripsi: " << current->album.deskripsi << std::endl;
        std::cout << "Tahun rilis: " << current->album.tahunRilis << std::endl;

        if (current->album.artis != nullptr) {
            std::cout << "Artis: " << current->album.artis->nama << std::endl;
        } else {
            std::cout << "Artis: Tidak diketahui" << std::endl;
        }

        tampilkanSemuaAlbumMusik(listAlbum, current->album.id);

        std::cout << "----------------------------------" << std::endl;

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

ListAlbum cariAlbumMusik(const ListAlbum& listAlbum, Musik* const musik) {
    ListAlbum hasil = buatListAlbum();

    if (musik == nullptr) {
        return hasil;
    }

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
    if (musik == nullptr) {
        std::cout << "Data musik tidak valid" << std::endl;
        return;
    }

    NodeAlbum* currentAlbum = listAlbum.first;
    while (currentAlbum != nullptr && currentAlbum->album.id != idAlbum) {
        currentAlbum = currentAlbum->next;
    }

    if (currentAlbum == nullptr) {
        std::cout << "Album tidak ditemukan" << std::endl;
        return;
    }

    NodeRelasiMusik* currentRelasi = currentAlbum->firstMusik;
    while (currentRelasi != nullptr) {
        if (currentRelasi->musik == musik) {
            std::cout << "Musik sudah terdaftar pada album tersebut" << std::endl;
            return;
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

    std::cout << "Relasi album musik berhasil ditambahkan" << std::endl;
}

void hapusAlbumMusik(ListAlbum& listAlbum, const std::string& idAlbum, Musik* const musik) {
    if (musik == nullptr) {
        std::cout << "Data musik tidak valid" << std::endl;
        return;
    }

    NodeAlbum* currentAlbum = listAlbum.first;
    while (currentAlbum != nullptr && currentAlbum->album.id != idAlbum) {
        currentAlbum = currentAlbum->next;
    }

    if (currentAlbum == nullptr) {
        std::cout << "Album tidak ditemukan" << std::endl;
        return;
    }

    NodeRelasiMusik* currentRelasi = currentAlbum->firstMusik;
    NodeRelasiMusik* previousRelasi = nullptr;

    while (currentRelasi != nullptr && currentRelasi->musik != musik) {
        previousRelasi = currentRelasi;
        currentRelasi = currentRelasi->next;
    }

    if (currentRelasi == nullptr) {
        std::cout << "Musik tidak terdaftar pada album tersebut" << std::endl;
        return;
    }

    if (previousRelasi == nullptr) {
        currentAlbum->firstMusik = currentRelasi->next;
    } else {
        previousRelasi->next = currentRelasi->next;
    }

    delete currentRelasi;

    std::cout << "Relasi album musik berhasil dihapus" << std::endl;
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

    std::cout << "Daftar musik:" << std::endl;

    NodeRelasiMusik* currentRelasi = currentAlbum->firstMusik;
    unsigned int nomor = 1;

    while (currentRelasi != nullptr) {
        if (currentRelasi->musik != nullptr) {
            std::cout << nomor << ". " << currentRelasi->musik->judul << std::endl;
            nomor++;
        }

        currentRelasi = currentRelasi->next;
    }
}
