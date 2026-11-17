#include <iostream>
#include <limits>
#include <string>

#include "view-playlist.hpp"

void viewMenuKelolaPlaylist(ListPlaylist& listPlaylist, const ListMusik& listMusik) {
    std::string pilihan;

    while (true) {
        std::cout << "========== KELOLA PLAYLIST ==========" << std::endl;
        std::cout << "1. Tambah playlist" << std::endl;
        std::cout << "2. Tampilkan semua playlist" << std::endl;
        std::cout << "3. Cari playlist" << std::endl;
        std::cout << "4. Update playlist" << std::endl;
        std::cout << "5. Hapus playlist" << std::endl;
        std::cout << "6. Tambah relasi playlist musik" << std::endl;
        std::cout << "7. Hapus relasi playlist musik" << std::endl;
        std::cout << "0. Kembali" << std::endl;
        std::cout << "Pilih menu > ";

        std::getline(std::cin, pilihan);

        std::cout << std::endl;

        if (pilihan == "0" || std::cin.eof()) {
            break;
        }

        if (pilihan == "1") {
            viewTambahPlaylist(listPlaylist);
        } else if (pilihan == "2") {
            viewTampilkanSemuaPlaylist(listPlaylist);
        } else if (pilihan == "3") {
            viewCariPlaylist(listPlaylist);
        } else if (pilihan == "4") {
            viewUpdatePlaylist(listPlaylist);
        } else if (pilihan == "5") {
            viewHapusPlaylist(listPlaylist);
        } else if (pilihan == "6") {
            viewTambahRelasiPlaylistMusik(listPlaylist, listMusik);
        } else if (pilihan == "7") {
            viewHapusRelasiPlaylistMusik(listPlaylist, listMusik);
        } else {
            std::cerr << "Pilihan tidak valid" << std::endl;
        }

        std::cout << std::endl;
    }
}

void viewTambahPlaylist(ListPlaylist& listPlaylist) {
    std::cout << "========== TAMBAH PLAYLIST ==========" << std::endl;

    Playlist playlistBaru;

    std::cout << "Judul playlist > ";
    std::getline(std::cin, playlistBaru.judul);

    if (playlistBaru.judul.empty()) {
        std::cerr << "Gagal menambah playlist: Judul playlist tidak boleh kosong" << std::endl;
        return;
    }

    std::cout << "Deskripsi playlist > ";
    std::getline(std::cin, playlistBaru.deskripsi);

    playlistBaru.frekuensiAkses = 0;

    try {
        tambahPlaylist(listPlaylist, playlistBaru);
        std::cout << "Playlist berhasil ditambahkan" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menambah playlist: " << pesanError << std::endl;
    }
}

void viewTampilkanSemuaPlaylist(const ListPlaylist& listPlaylist) {
    std::cout << "========== TAMPILKAN SEMUA PLAYLIST ==========" << std::endl;

    tampilkanSemuaPlaylist(listPlaylist);
}

void viewCariPlaylist(const ListPlaylist& listPlaylist) {
    std::cout << "========== CARI PLAYLIST ==========" << std::endl;

    std::string judulPlaylistCari;

    std::cout << "Judul playlist yang ingin dicari > ";
    std::getline(std::cin, judulPlaylistCari);

    std::cout << std::endl;

    Playlist* playlistDitemukan = cariPlaylist(listPlaylist, judulPlaylistCari);

    if (playlistDitemukan == nullptr) {
        std::cerr << "Playlist tidak ditemukan" << std::endl;
    } else {
        std::cout << "Playlist berhasil ditemukan" << std::endl;
        tampilkanPlaylist(*playlistDitemukan);
    }
}

void viewUpdatePlaylist(ListPlaylist& listPlaylist) {
    std::cout << "========== UPDATE PLAYLIST ==========" << std::endl;

    std::string judulPlaylistUpdate;

    std::cout << "Judul playlist yang ingin diupdate > ";
    std::getline(std::cin, judulPlaylistUpdate);

    std::cout << std::endl;

    Playlist* playlistDitemukan = cariPlaylist(listPlaylist, judulPlaylistUpdate);

    if (playlistDitemukan == nullptr) {
        std::cerr << "Gagal mengupdate playlist: Playlist tidak ditemukan" << std::endl;
        return;
    }

    std::cout << "Playlist ditemukan" << std::endl;
    tampilkanPlaylist(*playlistDitemukan);
    std::cout << std::endl;

    Playlist playlistBaru = *playlistDitemukan;

    std::cout << "Judul playlist baru > ";
    std::getline(std::cin, playlistBaru.judul);

    if (playlistBaru.judul.empty()) {
        std::cerr << "Gagal mengupdate playlist: Judul playlist tidak boleh kosong" << std::endl;
        return;
    }

    Playlist* playlistLain = cariPlaylist(listPlaylist, playlistBaru.judul);

    if (playlistLain != nullptr && playlistLain != playlistDitemukan) {
        std::cerr << "Gagal mengupdate playlist: Playlist dengan judul tersebut sudah ada" << std::endl;
        return;
    }

    std::cout << "Deskripsi playlist baru > ";
    std::getline(std::cin, playlistBaru.deskripsi);

    *playlistDitemukan = playlistBaru;

    std::cout << "Playlist berhasil diupdate" << std::endl;
}

void viewHapusPlaylist(ListPlaylist& listPlaylist) {
    std::cout << "========== HAPUS PLAYLIST ==========" << std::endl;

    std::string judulPlaylistHapus;

    std::cout << "Judul playlist yang ingin dihapus > ";
    std::getline(std::cin, judulPlaylistHapus);

    std::cout << std::endl;

    try {
        hapusPlaylist(listPlaylist, judulPlaylistHapus);
        std::cout << "Playlist berhasil dihapus" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menghapus playlist: " << pesanError << std::endl;
    }
}

void viewTambahRelasiPlaylistMusik(ListPlaylist& listPlaylist, const ListMusik& listMusik) {
    std::cout << "========== TAMBAH RELASI PLAYLIST MUSIK ==========" << std::endl;

    std::string judulPlaylistTambah;
    std::string idMusikTambah;

    std::cout << "Judul playlist yang ingin ditambahkan > ";
    std::getline(std::cin, judulPlaylistTambah);

    std::cout << "ID musik yang ingin ditambahkan > ";
    std::getline(std::cin, idMusikTambah);

    Musik* musikDitemukan = cariMusik(listMusik, idMusikTambah);

    if (musikDitemukan == nullptr) {
        std::cerr << "Gagal menambah relasi playlist musik: Musik tidak ditemukan" << std::endl;
        return;
    }

    try {
        tambahPlaylistMusik(listPlaylist, judulPlaylistTambah, musikDitemukan);
        std::cout << "Relasi playlist musik berhasil ditambah" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menambah relasi playlist musik: " << pesanError << std::endl;
    }
}

void viewHapusRelasiPlaylistMusik(ListPlaylist& listPlaylist, const ListMusik& listMusik) {
    std::cout << "========== HAPUS RELASI PLAYLIST MUSIK ==========" << std::endl;

    std::string judulPlaylistHapus;
    std::string idMusikHapus;

    std::cout << "Judul playlist yang ingin dihapus > ";
    std::getline(std::cin, judulPlaylistHapus);

    std::cout << "ID musik yang ingin dihapus > ";
    std::getline(std::cin, idMusikHapus);

    Musik* musikDitemukan = cariMusik(listMusik, idMusikHapus);

    if (musikDitemukan == nullptr) {
        std::cerr << "Gagal menghapus relasi playlist musik: Musik tidak ditemukan" << std::endl;
        return;
    }

    try {
        hapusPlaylistMusik(listPlaylist, judulPlaylistHapus, musikDitemukan);
        std::cout << "Relasi playlist musik berhasil dihapus" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menghapus relasi playlist musik: " << pesanError << std::endl;
    }
}