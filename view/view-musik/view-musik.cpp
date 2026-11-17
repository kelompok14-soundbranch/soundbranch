#include <iostream>
#include <limits>
#include <string>

#include "view-musik.hpp"

void viewMenuKelolaMusik(ListMusik& listMusik, ListArtis& listArtis, ListAlbum& listAlbum, ListGenre& listGenre, ListPlaylist& listPlaylist) {
    std::string pilihan;

    while (true) {
        std::cout << "========== KELOLA MUSIK ==========" << std::endl;
        std::cout << "1. Tambah musik" << std::endl;
        std::cout << "2. Tampilkan semua musik" << std::endl;
        std::cout << "3. Cari musik" << std::endl;
        std::cout << "4. Update musik" << std::endl;
        std::cout << "5. Hapus musik" << std::endl;
        std::cout << "0. Kembali" << std::endl;
        std::cout << "Pilih menu > ";

        std::getline(std::cin, pilihan);

        std::cout << std::endl;

        if (pilihan == "0" || std::cin.eof()) {
            break;
        }

        if (pilihan == "1") {
            viewTambahMusik(listMusik);
        } else if (pilihan == "2") {
            viewTampilkanSemuaMusik(listMusik, listArtis, listAlbum, listGenre, listPlaylist);
        } else if (pilihan == "3") {
            viewCariMusik(listMusik);
        } else if (pilihan == "4") {
            viewUpdateMusik(listMusik);
        } else if (pilihan == "5") {
            viewHapusMusik(listMusik, listArtis, listAlbum, listGenre, listPlaylist);  
        } else {
            std::cerr << "Pilihan tidak valid" << std::endl;
        }

        std::cout << std::endl;
    }
}

void viewTambahMusik(ListMusik& listMusik) {
    std::cout << "========== TAMBAH MUSIK ==========" << std::endl;

    Musik musikBaru;

    std::cout << "ID musik > ";
    std::getline(std::cin, musikBaru.id);

    if (musikBaru.id.empty()) {
        std::cerr << "Gagal menambah musik: ID musik tidak boleh kosong" << std::endl;
        return;
    }

    std::cout << "Judul musik > ";
    std::getline(std::cin, musikBaru.judul);

    if (musikBaru.judul.empty()) {
        std::cerr << "Gagal menambah musik: Judul musik tidak boleh kosong" << std::endl;
        return;
    }

    std::cout << "Durasi musik (detik) > ";

    if (!(std::cin >> musikBaru.durasi)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Gagal menambah musik: Durasi harus berupa angka" << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Tahun rilis > ";

    if (!(std::cin >> musikBaru.tahunRilis)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Gagal menambah musik: Tahun rilis harus berupa angka" << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    try {
        tambahMusik(listMusik, musikBaru);
        std::cout << "Musik berhasil ditambahkan" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menambah musik: " << pesanError << std::endl;
    }
}

void viewTampilkanSemuaMusik(ListMusik& listMusik, ListArtis& listArtis, ListAlbum& listAlbum, ListGenre& listGenre, ListPlaylist& listPlaylist) {
    std::cout << "========== TAMPILKAN SEMUA MUSIK ==========" << std::endl;

    tampilkanSemuaMusik(listMusik, listArtis, listAlbum, listGenre, listPlaylist);
}

void viewCariMusik(const ListMusik& listMusik) {
    std::cout << "========== CARI MUSIK ==========" << std::endl;

    std::string idMusikCari;

    std::cout << "ID musik yang ingin dicari > ";
    std::getline(std::cin, idMusikCari);

    std::cout << std::endl;

    Musik* musikDitemukan = cariMusik(listMusik, idMusikCari);

    if (musikDitemukan == nullptr) {
        std::cerr << "Musik tidak ditemukan" << std::endl;
    } else {
        std::cout << "Musik berhasil ditemukan" << std::endl;
        tampilkanMusik(*musikDitemukan);
    }
}

void viewUpdateMusik(ListMusik& listMusik) {
    std::cout << "========== UPDATE MUSIK ==========" << std::endl;

    std::string idMusikUpdate;

    std::cout << "ID musik yang ingin diupdate > ";
    std::getline(std::cin, idMusikUpdate);

    std::cout << std::endl;

    Musik* musikDitemukan = cariMusik(listMusik, idMusikUpdate);

    if (musikDitemukan == nullptr) {
        std::cerr << "Gagal mengupdate musik: Musik tidak ditemukan" << std::endl;
        return;
    }

    std::cout << "Musik ditemukan" << std::endl;
    tampilkanMusik(*musikDitemukan);
    std::cout << std::endl;

    Musik musikBaru = *musikDitemukan;

    std::cout << "Judul musik baru > ";
    std::getline(std::cin, musikBaru.judul);

    if (musikBaru.judul.empty()) {
        std::cerr << "Gagal mengupdate musik: Judul musik tidak boleh kosong" << std::endl;
        return;
    }

    std::cout << "Durasi musik baru (detik) > ";

    if (!(std::cin >> musikBaru.durasi)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Gagal mengupdate musik: Durasi harus berupa angka" << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Tahun rilis baru > ";

    if (!(std::cin >> musikBaru.tahunRilis)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Gagal mengupdate musik: Tahun rilis harus berupa angka" << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    *musikDitemukan = musikBaru;

    std::cout << "Musik berhasil diupdate" << std::endl;
}

void viewHapusMusik(ListMusik& listMusik, ListArtis& listArtis, ListAlbum& listAlbum, ListGenre& listGenre, ListPlaylist& listPlaylist) {
    std::cout << "========== HAPUS MUSIK ==========" << std::endl;

    std::string idMusikHapus;

    std::cout << "ID musik yang ingin dihapus > ";
    std::getline(std::cin, idMusikHapus);

    std::cout << std::endl;

    Musik* musikDihapus = cariMusik(listMusik, idMusikHapus);

    if (musikDihapus == nullptr) {
        std::cerr << "Gagal menghapus musik: Musik tidak ditemukan" << std::endl;
        return;
    }

    try {
        hapusMusik(listMusik, listArtis, listAlbum, listGenre, listPlaylist, idMusikHapus);
        std::cout << "Musik berhasil dihapus" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menghapus musik: " << pesanError << std::endl;
    }
}