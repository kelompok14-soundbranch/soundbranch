#include <iostream>
#include "list-playlist.hpp"

ListPlaylist buatListPlaylist() {
    ListPlaylist listPlaylist;
    listPlaylist.first = nullptr;
    return listPlaylist;
}

unsigned int hitungTotalPlaylist(const ListPlaylist& listPlaylist) {
    unsigned int total = 0;

    NodePlaylist* current = listPlaylist.first;
    while (current != nullptr) {
        total++;
        current = current->next;
    }

    return total;
}

bool kosongPlaylist(const ListPlaylist& listPlaylist) {
    return listPlaylist.first == nullptr;
}

Playlist* cariPlaylist(const ListPlaylist& listPlaylist, const std::string& namaPlaylistCari) {
    NodePlaylist* current = listPlaylist.first;
    while (current != nullptr) {
        if (current->playlist.judul == namaPlaylistCari) {
            return &current->playlist;
        }

        current = current->next;
    }

    return nullptr;
}

void tambahPlaylist(ListPlaylist& listPlaylist, const Playlist& playlistBaru) {
    if (cariPlaylist(listPlaylist, playlistBaru.judul) != nullptr) {
        std::cout << "Playlist sudah terdaftar" << std::endl;
        return;
    }

    NodePlaylist* nodePlaylistBaru = new NodePlaylist;
    nodePlaylistBaru->playlist = playlistBaru;
    nodePlaylistBaru->firstMusik = nullptr;
    nodePlaylistBaru->next = nullptr;
    
    if (kosongPlaylist(listPlaylist)) {
        listPlaylist.first = nodePlaylistBaru;
    } else {
        NodePlaylist* current = listPlaylist.first;
        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = nodePlaylistBaru;
    }

    std::cout << "Playlist berhasil ditambahkan" << std::endl;
}

void hapusPlaylist(ListPlaylist& listPlaylist, const std::string& namaPlaylistHapus) {
    NodePlaylist* current = listPlaylist.first;
    NodePlaylist* previous = nullptr;
    while (current != nullptr && current->playlist.judul != namaPlaylistHapus) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Playlist tidak ditemukan" << std::endl;
        return;
    }

    if (current->firstMusik != nullptr) {
        std::cout << "Playlist tidak dapat dihapus karena masih memiliki relasi musik" << std::endl;
        return;
    }

    if (previous == nullptr) {
        listPlaylist.first = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;

    std::cout << "Playlist berhasil dihapus" << std::endl;
}

void tampilkanSemuaPlaylist(const ListPlaylist& listPlaylist) {
    if (kosongPlaylist(listPlaylist)) {
        std::cout << "Belum ada playlist yang terdaftar" << std::endl;
        return;
    }

    std::cout << "========== DAFTAR PLAYLIST ==========" << std::endl;

    NodePlaylist* current = listPlaylist.first;
    while (current != nullptr) {
        std::cout << "Judul playlist: " << current->playlist.judul << std::endl;
        std::cout << "Deskripsi playlist: " << current->playlist.deskripsi << std::endl;
        std::cout << "Frekuensi akses: " << current->playlist.frekuensiAkses << std::endl;
        tampilkanSemuaPlaylistMusik(listPlaylist, current->playlist.judul);
        std::cout << "----------------------------------" << std::endl;

        current = current->next;
    }
}



unsigned int hitungTotalPlaylistMusik(const ListPlaylist& listPlaylist, const std::string& namaPlaylist) {
    NodePlaylist* currentPlaylist = listPlaylist.first;
    while (currentPlaylist != nullptr && currentPlaylist->playlist.judul != namaPlaylist) {
        currentPlaylist = currentPlaylist->next;
    }

    if (currentPlaylist == nullptr) {
        return 0;
    }

    unsigned int total = 0;
    NodeRelasiMusik* currentRelasi = currentPlaylist->firstMusik;
    while (currentRelasi != nullptr) {
        total++;
        currentRelasi = currentRelasi->next;
    }

    return total;
}

bool kosongPlaylistMusik(const ListPlaylist& listPlaylist, const std::string& namaPlaylist) {
    NodePlaylist* current = listPlaylist.first;
    while (current != nullptr && current->playlist.judul != namaPlaylist) {
        current = current->next;
    }

    if (current == nullptr) {
        return true;
    }

    return current->firstMusik == nullptr;
}

ListPlaylist cariPlaylistMusik(const ListPlaylist& listPlaylist, Musik* const musik) {
    ListPlaylist hasil = buatListPlaylist();

    if (musik == nullptr) {
        return hasil;
    }

    NodePlaylist* currentPlaylist = listPlaylist.first;
    while (currentPlaylist != nullptr) {
        NodeRelasiMusik* currentRelasi = currentPlaylist->firstMusik;
        while (currentRelasi != nullptr) {
            if (currentRelasi->musik == musik) {
                Playlist playlistBaru;
                playlistBaru.judul = currentPlaylist->playlist.judul;

                NodePlaylist* nodePlaylistBaru = new NodePlaylist;
                nodePlaylistBaru->playlist = playlistBaru;
                nodePlaylistBaru->firstMusik = nullptr;
                nodePlaylistBaru->next = nullptr;

                if (kosongPlaylist(hasil)) {
                    hasil.first = nodePlaylistBaru;
                } else {
                    NodePlaylist* current = hasil.first;
                    while (current->next != nullptr) {
                        current = current->next;
                    }

                    current->next = nodePlaylistBaru;
                }

                NodeRelasiMusik* nodeRelasiBaru = new NodeRelasiMusik;
                nodeRelasiBaru->musik = musik;
                nodeRelasiBaru->next = nullptr;

                nodePlaylistBaru->firstMusik = nodeRelasiBaru;

                break;
            }

            currentRelasi = currentRelasi->next;
        }

        currentPlaylist = currentPlaylist->next;
    }

    return hasil;
}

void tambahPlaylistMusik(ListPlaylist& listPlaylist, const std::string& namaPlaylist, Musik* const musik) {
    if (musik == nullptr) {
        std::cout << "Data musik tidak valid" << std::endl;
        return;
    }

    NodePlaylist* currentPlaylist = listPlaylist.first;
    while (currentPlaylist != nullptr && currentPlaylist->playlist.judul != namaPlaylist) {
        currentPlaylist = currentPlaylist->next;
    }

    if (currentPlaylist == nullptr) {
        std::cout << "Playlist tidak ditemukan" << std::endl;
        return;
    }

    NodeRelasiMusik* currentRelasi = currentPlaylist->firstMusik;
    while (currentRelasi != nullptr) {
        if (currentRelasi->musik == musik) {
            std::cout << "Musik sudah terdaftar pada playlist tersebut" << std::endl;
            return;
        }

        currentRelasi = currentRelasi->next;
    }

    NodeRelasiMusik* nodeRelasiBaru = new NodeRelasiMusik;
    nodeRelasiBaru->musik = musik;
    nodeRelasiBaru->next = nullptr;

    if (currentPlaylist->firstMusik == nullptr) {
        currentPlaylist->firstMusik = nodeRelasiBaru;
    } else {
        currentRelasi = currentPlaylist->firstMusik;
    
        while (currentRelasi->next != nullptr) {
            currentRelasi = currentRelasi->next;
        }
    
        currentRelasi->next = nodeRelasiBaru;
    }

    std::cout << "Relasi playlist musik berhasil ditambahkan" << std::endl;
}

void hapusPlaylistMusik(ListPlaylist& listPlaylist, const std::string& namaPlaylist, Musik* const musik) {
    if (musik == nullptr) {
        std::cout << "Data musik tidak valid" << std::endl;
        return;
    }
    
    NodePlaylist* currentPlaylist = listPlaylist.first;
    while (currentPlaylist != nullptr && currentPlaylist->playlist.judul != namaPlaylist) {
        currentPlaylist = currentPlaylist->next;
    }
    
    if (currentPlaylist == nullptr) {
        std::cout << "Playlist tidak ditemukan" << std::endl;
        return;
    }
    
    NodeRelasiMusik* currentRelasi = currentPlaylist->firstMusik;
    NodeRelasiMusik* previousRelasi = nullptr;
    while (currentRelasi != nullptr && currentRelasi->musik != musik) {
        previousRelasi = currentRelasi;
        currentRelasi = currentRelasi->next;
    }
    
    if (currentRelasi == nullptr) {
        std::cout << "Musik tidak terdaftar pada playlist tersebut" << std::endl;
        return;
    }
    
    if (previousRelasi == nullptr) {
        currentPlaylist->firstMusik = currentRelasi->next;
    } else {
        previousRelasi->next = currentRelasi->next;
    }
    
    delete currentRelasi;
    
    std::cout << "Relasi playlist musik berhasil dihapus" << std::endl;
}

void tampilkanSemuaPlaylistMusik(const ListPlaylist& listPlaylist, const std::string& namaPlaylist) {
    NodePlaylist* currentPlaylist = listPlaylist.first;
    while (currentPlaylist != nullptr && currentPlaylist->playlist.judul != namaPlaylist) {
        currentPlaylist = currentPlaylist->next;
    }

    if (currentPlaylist == nullptr) {
        std::cout << "Playlist tidak ditemukan" << std::endl;
        return;
    }

    if (currentPlaylist->firstMusik == nullptr) {
        std::cout << "Playlist belum memiliki musik" << std::endl;
        return;
    }
    
    std::cout << "Daftar musik:" << std::endl;

    NodeRelasiMusik* currentRelasi = currentPlaylist->firstMusik;
    unsigned int nomor = 1;
    while (currentRelasi != nullptr) {
        if (currentRelasi->musik != nullptr) {
            std::cout << nomor << ". " << currentRelasi->musik->judul << std::endl;
            nomor++;
        }

        currentRelasi = currentRelasi->next;
    }
}