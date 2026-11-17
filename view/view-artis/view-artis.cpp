#include <iostream>
#include <string>

#include "view-artis.hpp"

void viewMenuKelolaArtis(ListArtis& listArtis, const ListMusik& listMusik) {
    std::string pilihan;

    while (true) {
        std::cout << "========== KELOLA ARTIS ==========" << std::endl;
        std::cout << "1. Tambah artis" << std::endl;
        std::cout << "2. Tampilkan semua artis" << std::endl;
        std::cout << "3. Cari artis" << std::endl;
        std::cout << "4. Update artis" << std::endl;
        std::cout << "5. Hapus artis" << std::endl;
        std::cout << "6. Tambah relasi artis musik" << std::endl;
        std::cout << "7. Hapus relasi artis musik" << std::endl;
        std::cout << "0. Kembali" << std::endl;
        std::cout << "Pilih menu > ";

        std::getline(std::cin, pilihan);

        std::cout << std::endl;

        if (pilihan == "0" || std::cin.eof()) {
            break;
        }

        if (pilihan == "1") {
            viewTambahArtis(listArtis);
        } else if (pilihan == "2") {
            viewTampilkanSemuaArtis(listArtis);
        } else if (pilihan == "3") {
            viewCariArtis(listArtis);
        } else if (pilihan == "4") {
            viewUpdateArtis(listArtis);
        } else if (pilihan == "5") {
            viewHapusArtis(listArtis);
        } else if (pilihan == "6") {
            viewTambahRelasiArtisMusik(listArtis, listMusik);
        } else if (pilihan == "7") {
            viewHapusRelasiArtisMusik(listArtis, listMusik);
        } else {
            std::cerr << "Pilihan tidak valid" << std::endl;
        }

        std::cout << std::endl;
    }
}

void viewTambahArtis(ListArtis& listArtis) {
    std::cout << "========== TAMBAH ARTIS ==========" << std::endl;

    Artis artisBaru;

    std::cout << "ID artis > ";
    std::getline(std::cin, artisBaru.id);

    if (artisBaru.id.empty()) {
        std::cerr << "Gagal menambah artis: ID artis tidak boleh kosong" << std::endl;
        return;
    }

    std::cout << "Nama artis > ";
    std::getline(std::cin, artisBaru.nama);

    if (artisBaru.nama.empty()) {
        std::cerr << "Gagal menambah artis: Nama artis tidak boleh kosong" << std::endl;
        return;
    }

    try {
        tambahArtis(listArtis, artisBaru);
        std::cout << "Artis berhasil ditambahkan" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menambah artis: " << pesanError << std::endl;
    }
}

void viewTampilkanSemuaArtis(const ListArtis& listArtis) {
    std::cout << "========== TAMPILKAN SEMUA ARTIS ==========" << std::endl;

    tampilkanSemuaArtis(listArtis);
}

void viewCariArtis(const ListArtis& listArtis) {
    std::cout << "========== CARI ARTIS ==========" << std::endl;

    std::string idArtisCari;

    std::cout << "ID artis yang ingin dicari > ";
    std::getline(std::cin, idArtisCari);

    std::cout << std::endl;

    Artis* artisDitemukan = cariArtis(listArtis, idArtisCari);

    if (artisDitemukan == nullptr) {
        std::cerr << "Artis tidak ditemukan" << std::endl;
    } else {
        std::cout << "Artis berhasil ditemukan" << std::endl;
        tampilkanArtis(*artisDitemukan);
    }
}

void viewUpdateArtis(ListArtis& listArtis) {
    std::cout << "========== UPDATE ARTIS ==========" << std::endl;

    std::string idArtisUpdate;

    std::cout << "ID artis yang ingin diupdate > ";
    std::getline(std::cin, idArtisUpdate);

    std::cout << std::endl;

    Artis* artisDitemukan = cariArtis(listArtis, idArtisUpdate);

    if (artisDitemukan == nullptr) {
        std::cerr << "Gagal mengupdate artis: Artis tidak ditemukan" << std::endl;
        return;
    }

    std::cout << "Artis ditemukan" << std::endl;
    tampilkanArtis(*artisDitemukan);
    std::cout << std::endl;

    Artis artisBaru = *artisDitemukan;

    std::cout << "Nama artis baru > ";
    std::getline(std::cin, artisBaru.nama);

    if (artisBaru.nama.empty()) {
        std::cerr << "Gagal mengupdate artis: Nama artis tidak boleh kosong" << std::endl;
        return;
    }

    *artisDitemukan = artisBaru;

    std::cout << "Artis berhasil diupdate" << std::endl;
}

void viewHapusArtis(ListArtis& listArtis) {
    std::cout << "========== HAPUS ARTIS ==========" << std::endl;

    std::string idArtisHapus;

    std::cout << "ID artis yang ingin dihapus > ";
    std::getline(std::cin, idArtisHapus);

    std::cout << std::endl;

    try {
        hapusArtis(listArtis, idArtisHapus);
        std::cout << "Artis berhasil dihapus" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menghapus artis: " << pesanError << std::endl;
    }
}

void viewTambahRelasiArtisMusik(ListArtis& listArtis, const ListMusik& listMusik) {
    std::cout << "========== TAMBAH RELASI ARTIS MUSIK ==========" << std::endl;

    std::string idArtisTambah;
    std::string idMusikTambah;

    std::cout << "ID artis yang ingin ditambahkan > ";
    std::getline(std::cin, idArtisTambah);

    std::cout << "ID musik yang ingin ditambahkan > ";
    std::getline(std::cin, idMusikTambah);

    Musik* musikDitemukan = cariMusik(listMusik, idMusikTambah);

    if (musikDitemukan == nullptr) {
        std::cerr << "Gagal menambah relasi artis musik: Musik tidak ditemukan" << std::endl;
        return;
    }

    try {
        tambahArtisMusik(listArtis, idArtisTambah, musikDitemukan);
        std::cout << "Relasi artis musik berhasil ditambah" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menambah relasi artis musik: " << pesanError << std::endl;
    }
}

void viewHapusRelasiArtisMusik(ListArtis& listArtis, const ListMusik& listMusik) {
    std::cout << "========== HAPUS RELASI ARTIS MUSIK ==========" << std::endl;

    std::string idArtisHapus;
    std::string idMusikHapus;

    std::cout << "ID artis yang ingin dihapus > ";
    std::getline(std::cin, idArtisHapus);

    std::cout << "ID musik yang ingin dihapus > ";
    std::getline(std::cin, idMusikHapus);

    Musik* musikDitemukan = cariMusik(listMusik, idMusikHapus);

    if (musikDitemukan == nullptr) {
        std::cerr << "Gagal menghapus relasi artis musik: Musik tidak ditemukan" << std::endl;
        return;
    }

    try {
        hapusArtisMusik(listArtis, idArtisHapus, musikDitemukan);
        std::cout << "Relasi artis musik berhasil dihapus" << std::endl;
    } catch (const std::string& pesanError) {
        std::cerr << "Gagal menghapus relasi artis musik: " << pesanError << std::endl;
    }
}