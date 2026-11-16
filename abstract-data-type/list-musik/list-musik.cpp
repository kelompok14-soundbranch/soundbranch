
#include <iostream>
#include "list-musik.hpp"

ListMusik buatListMusik() {
    ListMusik listMusik;
    listMusik.first = nullptr;
    return listMusik;
}

unsigned int hitungTotalMusik(const ListMusik& listMusik) {
    unsigned int total = 0;

    NodeMusik* current = listMusik.first;
    while (current != nullptr) {
        total++;
        current = current->next;
    }

    return total;
}

bool kosongMusik(const ListMusik& listMusik) {
    return listMusik.first == nullptr;
}

Musik* cariMusik(const ListMusik& listMusik, const std::string& idMusikCari) {
    NodeMusik* current = listMusik.first;
    while (current != nullptr) {
        if (current->musik.id == idMusikCari) {
            return &current->musik;
        }

        current = current->next;
    }

    return nullptr;
}

void tambahMusik(ListMusik& listMusik, const Musik& musikBaru) {
    if (cariMusik(listMusik, musikBaru.id) != nullptr) {
        std::cout << "Musik sudah terdaftar" << std::endl;
        return;
    }

    NodeMusik* nodeMusikBaru = new NodeMusik;
    nodeMusikBaru->musik = musikBaru;
    nodeMusikBaru->next = nullptr;

    if (kosongMusik(listMusik)) {
        listMusik.first = nodeMusikBaru;
    } else {
        NodeMusik* current = listMusik.first;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = nodeMusikBaru;
    }

    std::cout << "Musik berhasil ditambahkan" << std::endl;
}

void hapusMusik(ListMusik& listMusik, const std::string& idMusikHapus) {
    NodeMusik* current = listMusik.first;
    NodeMusik* previous = nullptr;

    while (current != nullptr && current->musik.id != idMusikHapus) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Musik tidak ditemukan" << std::endl;
        return;
    }

    if (previous == nullptr) {
        listMusik.first = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;

    std::cout << "Musik berhasil dihapus" << std::endl;
}

void tampilkanSemuaMusik(const ListMusik& listMusik) {
    if (kosongMusik(listMusik)) {
        std::cout << "Belum ada musik yang terdaftar" << std::endl;
        return;
    }

    std::cout << "========== DAFTAR MUSIK ==========" << std::endl;

    NodeMusik* current = listMusik.first;
    unsigned int nomor = 1;

    while (current != nullptr) {
        std::cout << nomor << ". " << std::endl;
        std::cout << "ID musik: " << current->musik.id << std::endl;
        std::cout << "Judul: " << current->musik.judul << std::endl;
        std::cout << "Durasi: " << current->musik.durasi << " detik" << std::endl;
        std::cout << "Tahun rilis: " << current->musik.tahunRilis << std::endl;
        std::cout << "----------------------------------" << std::endl;

        nomor++;
        current = current->next;
    }
}

void tampilkanSemuaMusikLengkap(const ListMusik& listMusik, const ListArtis& listArtis, const ListAlbum& ListAlbum, const ListGenre& ListGenre, const ListPlaylist& listPlaylist) {
    if (kosongMusik(listMusik)) {
        std::cout << "Belum ada musik yang terdaftar" << std::endl;
        return;
    }

    std::cout << "========== DAFTAR MUSIK LENGKAP ==========" << std::endl;

    NodeMusik* current = listMusik.first;
    unsigned int nomor = 1;

    while (current != nullptr) {
        std::cout << nomor << ". " << std::endl;
        std::cout << "ID musik: " << current->musik.id << std::endl;
        std::cout << "Judul: " << current->musik.judul << std::endl;
        std::cout << "Durasi: " << current->musik.durasi << " detik" << std::endl;
        std::cout << "Tahun rilis: " << current->musik.tahunRilis << std::endl;
        tampilkanSemuaArtis(cariArtisMusik(listArtis, &current->musik));
        tampilkanSemuaAlbum(cariAlbumMusik(ListAlbum, &current->musik));
        tampilkanSemuaGenre(cariGenreMusik(ListGenre, &current->musik));
        tampilkanSemuaPlaylist(cariPlaylistMusik(listPlaylist, &current->musik));
        std::cout << "----------------------------------" << std::endl;

        nomor++;
        current = current->next;
    }
}