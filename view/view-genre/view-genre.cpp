#include <iostream>
#include <string>

#include "view-genre.hpp"

void viewMenuKelolaGenre(ListGenre& listGenre, const ListMusik& listMusik) {
    std::string pilihan;

    while (true) {
        std::cout << "========== KELOLA GENRE ==========" << std::endl;
        std::cout << "1. Tambah genre" << std::endl;
        std::cout << "2. Tampilkan semua genre" << std::endl;
        std::cout << "3. Cari genre" << std::endl;
        std::cout << "4. Update genre" << std::endl;
        std::cout << "5. Hapus genre" << std::endl;
        std::cout << "6. Tambah relasi genre musik" << std::endl;
        std::cout << "7. Hapus relasi genre musik" << std::endl;
        std::cout << "0. Kembali" << std::endl;
        std::cout << "Pilih menu > ";

        std::getline(std::cin, pilihan);

        std::cout << std::endl;

        if (pilihan == "0" || std::cin.eof()) {
            break;
        }

        if (pilihan == "1") {
            viewTambahGenre(listGenre);
        } else if (pilihan == "2") {
            viewTampilkanSemuaGenre(listGenre);
        } else if (pilihan == "3") {
            viewCariGenre(listGenre);
        } else if (pilihan == "4") {
            viewUpdateGenre(listGenre);
        } else if (pilihan == "5") {
            viewHapusGenre(listGenre);
        } else if (pilihan == "6") {
            viewTambahRelasiGenreMusik(listGenre, listMusik);
        } else if (pilihan == "7") {
            viewHapusRelasiGenreMusik(listGenre, listMusik);   
        } else {
            std::cerr << "Pilihan tidak valid" << std::endl;
        }

        std::cout << std::endl;
    }
}

void viewTambahGenre(ListGenre& listGenre) {
    std::cout << "========== TAMBAH GENRE ==========" << std::endl;

    Genre genreBaru;

    std::cout << "Nama genre > ";
    std::getline(std::cin, genreBaru.nama);

    if (genreBaru.nama.empty()) {
        std::cerr << "Gagal menambah genre: Nama genre tidak boleh kosong" << std::endl;
        return;
    }

    try {
        tambahGenre(listGenre, genreBaru);
        std::cout << "Genre berhasil ditambahkan" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menambah genre: " << pesanError << std::endl;
    }
}

void viewTampilkanSemuaGenre(const ListGenre& listGenre) {
    std::cout << "========== TAMPILKAN SEMUA GENRE ==========" << std::endl;

    tampilkanSemuaGenre(listGenre);
}

void viewCariGenre(const ListGenre& listGenre) {
    std::cout << "========== CARI GENRE ==========" << std::endl;

    std::string namaGenreCari;

    std::cout << "Nama genre yang ingin dicari > ";
    std::getline(std::cin, namaGenreCari);

    std::cout << std::endl;

    Genre* genreDitemukan = cariGenre(listGenre, namaGenreCari);

    if (genreDitemukan == nullptr) {
        std::cerr << "Genre tidak ditemukan" << std::endl;
    } else {
        std::cout << "Genre berhasil ditemukan" << std::endl;
        tampilkanGenre(*genreDitemukan);
    }
}

void viewUpdateGenre(ListGenre& listGenre) {
    std::cout << "========== UPDATE GENRE ==========" << std::endl;

    std::string namaGenreUpdate;

    std::cout << "Nama genre yang ingin diupdate > ";
    std::getline(std::cin, namaGenreUpdate);

    std::cout << std::endl;

    Genre* genreDitemukan = cariGenre(listGenre, namaGenreUpdate);

    if (genreDitemukan == nullptr) {
        std::cerr << "Gagal mengupdate genre: Genre tidak ditemukan" << std::endl;
        return;
    }

    std::cout << "Genre ditemukan" << std::endl;
    tampilkanGenre(*genreDitemukan);
    std::cout << std::endl;

    Genre genreBaru;

    std::cout << "Nama genre baru > ";
    std::getline(std::cin, genreBaru.nama);

    if (genreBaru.nama.empty()) {
        std::cerr << "Gagal mengupdate genre: Nama genre tidak boleh kosong" << std::endl;
        return;
    }

    Genre* genreLain = cariGenre(listGenre, genreBaru.nama);

    if (genreLain != nullptr && genreLain != genreDitemukan) {
        std::cerr << "Gagal mengupdate genre: Genre dengan nama tersebut sudah ada" << std::endl;
        return;
    }

    *genreDitemukan = genreBaru;

    std::cout << "Genre berhasil diupdate" << std::endl;
}

void viewHapusGenre(ListGenre& listGenre) {
    std::cout << "========== HAPUS GENRE ==========" << std::endl;

    std::string namaGenreHapus;

    std::cout << "Nama genre yang ingin dihapus > ";
    std::getline(std::cin, namaGenreHapus);

    std::cout << std::endl;

    try {
        hapusGenre(listGenre, namaGenreHapus);
        std::cout << "Genre berhasil dihapus" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menghapus genre: " << pesanError << std::endl;
    }
}

void viewTambahRelasiGenreMusik(ListGenre& listGenre, const ListMusik& listMusik) {
    std::cout << "========== TAMBAH RELASI GENRE MUSIK ==========" << std::endl;

    std::string namaGenreTambah;
    std::string idMusikTambah;

    std::cout << "Nama genre yang ingin ditambahkan > ";
    std::getline(std::cin, namaGenreTambah);

    std::cout << "ID musik yang ingin ditambahkan > ";
    std::getline(std::cin, idMusikTambah);

    Musik* musikDitemukan = cariMusik(listMusik, idMusikTambah);

    if (musikDitemukan == nullptr) {
        std::cerr << "Gagal menambah relasi genre musik: Musik tidak ditemukan" << std::endl;
        return;
    }

    try {
        tambahGenreMusik(listGenre, namaGenreTambah, musikDitemukan);
        std::cout << "Relasi genre musik berhasil ditambah" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menambah relasi genre musik: " << pesanError << std::endl;
    }
}

void viewHapusRelasiGenreMusik(ListGenre& listGenre, const ListMusik& listMusik) {
    std::cout << "========== HAPUS RELASI GENRE MUSIK ==========" << std::endl;

    std::string namaGenreHapus;
    std::string idMusikHapus;

    std::cout << "Nama genre yang ingin dihapus > ";
    std::getline(std::cin, namaGenreHapus);

    std::cout << "ID musik yang ingin dihapus > ";
    std::getline(std::cin, idMusikHapus);

    Musik* musikDitemukan = cariMusik(listMusik, idMusikHapus);

    if (musikDitemukan == nullptr) {
        std::cerr << "Gagal menghapus relasi genre musik: Musik tidak ditemukan" << std::endl;
        return;
    }

    try {
        hapusGenreMusik(listGenre, namaGenreHapus, musikDitemukan);
        std::cout << "Relasi genre musik berhasil dihapus" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menghapus relasi genre musik: " << pesanError << std::endl;
    }
}