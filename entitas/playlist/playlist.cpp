#include <iostream>
#include "playlist.hpp"

Playlist* buatPlaylist(const std::string& judul, const std::string& deskripsi) {
    if (judul == "" || deskripsi == "") {
        return nullptr;
    }

    Playlist* playlist = new Playlist;
    playlist->judul = judul;
    playlist->deskripsi = deskripsi;
    playlist->frekuensiAkses = 0;

    return playlist;
}

void tampilkanPlaylist(const Playlist& playlist) {
    std::cout << "Judul playlist: " << playlist.judul << std::endl;
    std::cout << "Deskripsi playlist: " << playlist.deskripsi << std::endl;
    std::cout << "Frekuensi akses playlist: " << playlist.frekuensiAkses << std::endl;
}