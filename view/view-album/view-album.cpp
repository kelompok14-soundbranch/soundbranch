#include <iostream>
#include <limits>
#include <string>

#include "view-album.hpp"

void viewMenuKelolaAlbum(ListAlbum& listAlbum, const ListArtis& listArtis, const ListMusik& listMusik) {
    std::string pilihan;

    while (true) {
        std::cout << "========== KELOLA ALBUM ==========" << std::endl;
        std::cout << "1. Tambah album" << std::endl;
        std::cout << "2. Tampilkan semua album" << std::endl;
        std::cout << "3. Cari album" << std::endl;
        std::cout << "4. Update album" << std::endl;
        std::cout << "5. Hapus album" << std::endl;
        std::cout << "6. Tambah relasi album musik" << std::endl;
        std::cout << "7. Hapus relasi album musik" << std::endl;
        std::cout << "0. Kembali" << std::endl;
        std::cout << "Pilih menu > ";

        std::getline(std::cin, pilihan);

        std::cout << std::endl;

        if (pilihan == "0" || std::cin.eof()) {
            break;
        }

        if (pilihan == "1") {
            viewTambahAlbum(listAlbum, listArtis);
        } else if (pilihan == "2") {
            viewTampilkanSemuaAlbum(listAlbum);
        } else if (pilihan == "3") {
            viewCariAlbum(listAlbum);
        } else if (pilihan == "4") {
            viewUpdateAlbum(listAlbum, listArtis);
        } else if (pilihan == "5") {
            viewHapusAlbum(listAlbum);
        } else if (pilihan == "6") {
            viewTambahRelasiAlbumMusik(listAlbum, listMusik);
        } else if (pilihan == "7") {
            viewHapusRelasiAlbumMusik(listAlbum, listMusik);
        } else {
            std::cerr << "Pilihan tidak valid" << std::endl;
        }

        std::cout << std::endl;
    }
}

void viewTambahAlbum(ListAlbum& listAlbum, const ListArtis& listArtis) {
    std::cout << "========== TAMBAH ALBUM ==========" << std::endl;

    Album albumBaru;
    std::string idArtis;

    std::cout << "ID album > ";
    std::getline(std::cin, albumBaru.id);

    if (albumBaru.id.empty()) {
        std::cerr << "Gagal menambah album: ID album tidak boleh kosong" << std::endl;
        return;
    }

    std::cout << "Nama album > ";
    std::getline(std::cin, albumBaru.nama);

    if (albumBaru.nama.empty()) {
        std::cerr << "Gagal menambah album: Nama album tidak boleh kosong" << std::endl;
        return;
    }

    std::cout << "Deskripsi album > ";
    std::getline(std::cin, albumBaru.deskripsi);

    std::cout << "Tahun rilis > ";

    if (!(std::cin >> albumBaru.tahunRilis)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Gagal menambah album: Tahun rilis harus berupa angka" << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "ID artis > ";
    std::getline(std::cin, idArtis);

    albumBaru.artis = cariArtis(listArtis, idArtis);

    if (albumBaru.artis == nullptr) {
        std::cerr << "Gagal menambah album: Artis tidak ditemukan" << std::endl;
        return;
    }

    try {
        tambahAlbum(listAlbum, albumBaru);
        std::cout << "Album berhasil ditambahkan" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menambah album: " << pesanError << std::endl;
    }
}

void viewTampilkanSemuaAlbum(const ListAlbum& listAlbum) {
    std::cout << "========== TAMPILKAN SEMUA ALBUM ==========" << std::endl;

    tampilkanSemuaAlbum(listAlbum);
}

void viewCariAlbum(const ListAlbum& listAlbum) {
    std::cout << "========== CARI ALBUM ==========" << std::endl;

    std::string idAlbumCari;

    std::cout << "ID album yang ingin dicari > ";
    std::getline(std::cin, idAlbumCari);

    std::cout << std::endl;

    Album* albumDitemukan = cariAlbum(listAlbum, idAlbumCari);

    if (albumDitemukan == nullptr) {
        std::cerr << "Album tidak ditemukan" << std::endl;
    } else {
        std::cout << "Album berhasil ditemukan" << std::endl;
        tampilkanAlbum(*albumDitemukan);
    }
}

void viewUpdateAlbum(ListAlbum& listAlbum, const ListArtis& listArtis) {
    std::cout << "========== UPDATE ALBUM ==========" << std::endl;

    std::string idAlbumUpdate;
    std::string idArtisBaru;

    std::cout << "ID album yang ingin diupdate > ";
    std::getline(std::cin, idAlbumUpdate);

    std::cout << std::endl;

    Album* albumDitemukan = cariAlbum(listAlbum, idAlbumUpdate);

    if (albumDitemukan == nullptr) {
        std::cerr << "Gagal mengupdate album: Album tidak ditemukan" << std::endl;
        return;
    }

    std::cout << "Album ditemukan" << std::endl;
    tampilkanAlbum(*albumDitemukan);
    std::cout << std::endl;

    Album albumBaru = *albumDitemukan;

    std::cout << "Nama album baru > ";
    std::getline(std::cin, albumBaru.nama);

    if (albumBaru.nama.empty()) {
        std::cerr << "Gagal mengupdate album: Nama album tidak boleh kosong" << std::endl;
        return;
    }

    std::cout << "Deskripsi album baru > ";
    std::getline(std::cin, albumBaru.deskripsi);

    std::cout << "Tahun rilis baru > ";

    if (!(std::cin >> albumBaru.tahunRilis)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Gagal mengupdate album: Tahun rilis harus berupa angka" << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "ID artis baru > ";
    std::getline(std::cin, idArtisBaru);

    Artis* artisBaru = cariArtis(listArtis, idArtisBaru);

    if (artisBaru == nullptr) {
        std::cerr << "Gagal mengupdate album: Artis tidak ditemukan" << std::endl;
        return;
    }

    albumBaru.artis = artisBaru;

    *albumDitemukan = albumBaru;

    std::cout << "Album berhasil diupdate" << std::endl;
}

void viewHapusAlbum(ListAlbum& listAlbum) {
    std::cout << "========== HAPUS ALBUM ==========" << std::endl;

    std::string idAlbumHapus;

    std::cout << "ID album yang ingin dihapus > ";
    std::getline(std::cin, idAlbumHapus);

    std::cout << std::endl;

    try {
        hapusAlbum(listAlbum, idAlbumHapus);
        std::cout << "Album berhasil dihapus" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menghapus album: " << pesanError << std::endl;
    }
}

void viewTambahRelasiAlbumMusik(ListAlbum& listAlbum, const ListMusik& listMusik) {
    std::cout << "========== TAMBAH RELASI ALBUM MUSIK ==========" << std::endl;

    std::string idAlbumTambah;
    std::string idMusikTambah;

    std::cout << "ID album yang ingin ditambahkan > ";
    std::getline(std::cin, idAlbumTambah);

    std::cout << "ID musik yang ingin ditambahkan > ";
    std::getline(std::cin, idMusikTambah);

    Musik* musikDitemukan = cariMusik(listMusik, idMusikTambah);

    if (musikDitemukan == nullptr) {
        std::cerr << "Gagal menambah relasi album musik: Musik tidak ditemukan" << std::endl;
        return;
    }

    try {
        tambahAlbumMusik(listAlbum, idAlbumTambah, musikDitemukan);
        std::cout << "Relasi album musik berhasil ditambah" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menambah relasi album musik: " << pesanError << std::endl;
    }
}

void viewHapusRelasiAlbumMusik(ListAlbum& listAlbum, const ListMusik& listMusik) {
    std::cout << "========== HAPUS RELASI ALBUM MUSIK ==========" << std::endl;

    std::string idAlbumHapus;
    std::string idMusikHapus;

    std::cout << "ID album yang ingin dihapus > ";
    std::getline(std::cin, idAlbumHapus);

    std::cout << "ID musik yang ingin dihapus > ";
    std::getline(std::cin, idMusikHapus);

    Musik* musikDitemukan = cariMusik(listMusik, idMusikHapus);

    if (musikDitemukan == nullptr) {
        std::cerr << "Gagal menghapus relasi album musik: Musik tidak ditemukan" << std::endl;
        return;
    }

    try {
        hapusAlbumMusik(listAlbum, idAlbumHapus, musikDitemukan);
        std::cout << "Relasi album musik berhasil dihapus" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menghapus relasi album musik: " << pesanError << std::endl;
    }
}