
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
        throw std::string("Sudah ada musik lain dengan ID yang sama");
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
}

void hapusMusik(ListMusik& listMusik, ListArtis& listArtis, ListAlbum& listAlbum, ListGenre& listGenre, ListPlaylist& listPlaylist, const std::string& idMusikHapus) {
    NodeMusik* current = listMusik.first;
    NodeMusik* previous = nullptr;

    while (current != nullptr && current->musik.id != idMusikHapus) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        throw std::string("Musik tidak ditemukan");
    }

    hapusSemuaArtisMusik(listArtis, &current->musik);
    hapusSemuaAlbumMusik(listAlbum, &current->musik);
    hapusSemuaGenreMusik(listGenre, &current->musik);
    hapusSemuaPlaylistMusik(listPlaylist, &current->musik);

    if (previous == nullptr) {
        listMusik.first = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;
}

void tampilkanSemuaMusik(const ListMusik& listMusik, const ListArtis& listArtis, const ListAlbum& ListAlbum, const ListGenre& ListGenre, const ListPlaylist& listPlaylist) {
    if (kosongMusik(listMusik)) {
        std::cout << "Belum ada musik yang terdaftar" << std::endl;
        return;
    }

    NodeMusik* current = listMusik.first;
    unsigned int nomor = 1;

    while (current != nullptr) {
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Musik " << nomor << std::endl;
        tampilkanMusik(current->musik);
        std::cout << std::endl;
        tampilkanSemuaArtis(cariSemuaArtisMusik(listArtis, &current->musik));
        std::cout << std::endl;
        tampilkanSemuaAlbum(cariSemuaAlbumMusik(ListAlbum, &current->musik));
        std::cout << std::endl;
        tampilkanSemuaGenre(cariSemuaGenreMusik(ListGenre, &current->musik));
        std::cout << std::endl;
        tampilkanSemuaPlaylist(cariSemuaPlaylistMusik(listPlaylist, &current->musik));
        std::cout << "----------------------------------" << std::endl;

        nomor++;
        current = current->next;
    }
}