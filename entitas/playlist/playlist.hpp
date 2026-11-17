#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <string>

struct Playlist {
    std::string judul;
    std::string deskripsi;
    int frekuensiAkses;
};

// mengembalikan pointer ke playlist baru valid jika judul dan deskripsi yang diberikan valid, atau nullptr jika salah satunya tidak valid
Playlist* buatPlaylist(const std::string& judul, const std::string& deskripsi);

// I.S.: terdefinisi playlist valid
// F.S.: ditampilkan seluruh data playlist. playlist tidak mengalami perubahan
void tampilkanPlaylist(const Playlist& playlist);

#endif