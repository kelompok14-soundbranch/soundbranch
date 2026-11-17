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
        throw std::string("Sudah ada playlist lain dengan judul yang sama");
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
}

void hapusPlaylist(ListPlaylist& listPlaylist, const std::string& namaPlaylistHapus) {
    NodePlaylist* current = listPlaylist.first;
    NodePlaylist* previous = nullptr;
    while (current != nullptr && current->playlist.judul != namaPlaylistHapus) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        throw std::string("Playlist tidak ditemukan");
    }

    if (current->firstMusik != nullptr) {
        throw std::string("Playlist tidak dapat dihapus karena masih memiliki relasi musik");
    }

    if (previous == nullptr) {
        listPlaylist.first = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;
}

void tampilkanSemuaPlaylist(const ListPlaylist& listPlaylist) {
    if (kosongPlaylist(listPlaylist)) {
        std::cout << "Belum ada playlist yang terdaftar" << std::endl;
        return;
    }

    unsigned int nomor = 1;

    NodePlaylist* current = listPlaylist.first;
    while (current != nullptr) {
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Playlist " << nomor << std::endl;
        tampilkanPlaylist(current->playlist);
        std::cout << std::endl;
        tampilkanSemuaPlaylistMusik(listPlaylist, current->playlist.judul);
        std::cout << "----------------------------------" << std::endl;

        nomor++;
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

ListPlaylist cariSemuaPlaylistMusik(const ListPlaylist& listPlaylist, Musik* const musik) {
    ListPlaylist hasil = buatListPlaylist();

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
    NodePlaylist* currentPlaylist = listPlaylist.first;
    while (currentPlaylist != nullptr && currentPlaylist->playlist.judul != namaPlaylist) {
        currentPlaylist = currentPlaylist->next;
    }

    if (currentPlaylist == nullptr) {
        throw std::string("Playlist tidak ditemukan");
    }

    NodeRelasiMusik* currentRelasi = currentPlaylist->firstMusik;
    while (currentRelasi != nullptr) {
        if (currentRelasi->musik == musik) {
            throw std::string("Musik sudah terdaftar pada playlist tersebut sebelumnya");
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
}

void hapusPlaylistMusik(ListPlaylist& listPlaylist, const std::string& namaPlaylist, Musik* const musik) {    
    NodePlaylist* currentPlaylist = listPlaylist.first;
    while (currentPlaylist != nullptr && currentPlaylist->playlist.judul != namaPlaylist) {
        currentPlaylist = currentPlaylist->next;
    }
    
    if (currentPlaylist == nullptr) {
        throw std::string("Playlist tidak ditemukan");
    }
    
    NodeRelasiMusik* currentRelasi = currentPlaylist->firstMusik;
    NodeRelasiMusik* previousRelasi = nullptr;
    while (currentRelasi != nullptr && currentRelasi->musik != musik) {
        previousRelasi = currentRelasi;
        currentRelasi = currentRelasi->next;
    }
    
    if (currentRelasi == nullptr) {
        throw std::string("Musik tidak terdaftar pada playlist tersebut");
    }
    
    if (previousRelasi == nullptr) {
        currentPlaylist->firstMusik = currentRelasi->next;
    } else {
        previousRelasi->next = currentRelasi->next;
    }
    
    delete currentRelasi;
}

void hapusSemuaPlaylistMusik(ListPlaylist& listPlaylist, Musik* const musik) {
    NodePlaylist* currentPlaylist = listPlaylist.first;

    while (currentPlaylist != nullptr) {
        NodeRelasiMusik* currentRelasi = currentPlaylist->firstMusik;
        NodeRelasiMusik* previousRelasi = nullptr;

        while (currentRelasi != nullptr) {
            if (currentRelasi->musik == musik) {
                NodeRelasiMusik* hapus = currentRelasi;

                if (previousRelasi == nullptr) {
                    currentPlaylist->firstMusik = currentRelasi->next;
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

        currentPlaylist = currentPlaylist->next;
    }
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
    
    std::cout << "DAFTAR MUSIK" << std::endl;

    unsigned int nomor = 1;
    NodeRelasiMusik* currentRelasi = currentPlaylist->firstMusik;
    while (currentRelasi != nullptr) {
        if (currentRelasi->musik != nullptr) {
            std::cout << "----------" << std::endl;
            std::cout << "Relasi playlist musik " << nomor << std::endl;
            tampilkanMusik(*currentRelasi->musik);
            std::cout << "----------" << std::endl;

            nomor++;
        }

        currentRelasi = currentRelasi->next;
    }
}