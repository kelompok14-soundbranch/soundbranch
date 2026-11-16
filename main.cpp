#include <iostream>
#include <limits>
#include <string>

#include "entitas/musik.hpp"
#include "entitas/artis.hpp"
#include "entitas/album.hpp"
#include "entitas/genre.hpp"
#include "entitas/playlist.hpp"

#include "abstract-data-type/list-musik/list-musik.hpp"
#include "abstract-data-type/list-artis/list-artis.hpp"
#include "abstract-data-type/list-album/list-album.hpp"
#include "abstract-data-type/list-genre/list-genre.hpp"
#include "abstract-data-type/list-playlist/list-playlist.hpp"

int bacaPilihanMenu() {
    int pilihan;

    if (!(std::cin >> pilihan)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return pilihan;
}

void pulihkanInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}



void menuMusik(ListMusik& listMusik, const ListArtis& listArtis, const ListAlbum& listAlbum, const ListGenre& listGenre, const ListPlaylist& listPlaylist) {
    int pilihan;

    do {
        std::cout << "\n========== KELOLA MUSIK ==========" << std::endl;
        std::cout << "1. Tambah musik" << std::endl;
        std::cout << "2. Tampilkan semua musik" << std::endl;
        std::cout << "3. Tampilkan semua musik lengkap" << std::endl;
        std::cout << "4. Cari musik" << std::endl;
        std::cout << "5. Hapus musik" << std::endl;
        std::cout << "0. Kembali" << std::endl;
        std::cout << "Pilih menu: ";

        pilihan = bacaPilihanMenu();

        switch (pilihan) {
            case 1: {
                Musik musikBaru;

                std::cout << "\n========== TAMBAH MUSIK ==========" << std::endl;

                std::cout << "ID musik: ";
                std::getline(std::cin, musikBaru.id);

                std::cout << "Judul musik: ";
                std::getline(std::cin, musikBaru.judul);

                std::cout << "Durasi musik (detik): ";

                if (!(std::cin >> musikBaru.durasi)) {
                    std::cout << "Durasi harus berupa angka" << std::endl;
                    pulihkanInput();
                    break;
                }

                std::cout << "Tahun rilis: ";

                if (!(std::cin >> musikBaru.tahunRilis)) {
                    std::cout << "Tahun rilis harus berupa angka" << std::endl;
                    pulihkanInput();
                    break;
                }

                pulihkanInput();

                tambahMusik(listMusik, musikBaru);
                break;
            }

            case 2: {
                std::cout << std::endl;
                tampilkanSemuaMusik(listMusik);
                break;
            }

            case 3: {
                std::cout << std::endl;
                tampilkanSemuaMusikLengkap(listMusik, listArtis, listAlbum, listGenre, listPlaylist);
                break;
            }

            case 4: {
                std::string idMusikCari;

                std::cout << "\n========== CARI MUSIK ==========" << std::endl;
                std::cout << "ID musik: ";
                std::getline(std::cin, idMusikCari);

                Musik* musikDitemukan = cariMusik(listMusik, idMusikCari);

                if (musikDitemukan != nullptr) {
                    std::cout << "\nMusik berhasil ditemukan" << std::endl;
                    std::cout << "ID musik: " << musikDitemukan->id << std::endl;
                    std::cout << "Judul: " << musikDitemukan->judul << std::endl;
                    std::cout << "Durasi: " << musikDitemukan->durasi << " detik" << std::endl;
                    std::cout << "Tahun rilis: " << musikDitemukan->tahunRilis << std::endl;
                } else {
                    std::cout << "Musik tidak ditemukan" << std::endl;
                }

                break;
            }

            case 5: {
                std::string idMusikHapus;

                std::cout << "\n========== HAPUS MUSIK ==========" << std::endl;
                std::cout << "ID musik yang ingin dihapus: ";
                std::getline(std::cin, idMusikHapus);

                Musik* musikDitemukan = cariMusik(listMusik, idMusikHapus);

                if (musikDitemukan == nullptr) {
                    std::cout << "Musik tidak ditemukan." << std::endl;
                } else {
                    hapusMusik(listMusik, idMusikHapus);
                }

                break;
            }

            case 0:
                std::cout << "Kembali ke main menu..." << std::endl;
                break;

            default:
                std::cout << "Pilihan tidak valid." << std::endl;
        }

    } while (pilihan != 0);
}

void menuArtis(ListArtis& listArtis, const ListMusik& listMusik) {
    int pilihan;

    do {
        std::cout << "\n========== KELOLA ARTIS ==========" << std::endl;
        std::cout << "1. Tambah artis" << std::endl;
        std::cout << "2. Tampilkan semua artis" << std::endl;
        std::cout << "3. Cari artis" << std::endl;
        std::cout << "4. Hapus artis" << std::endl;
        std::cout << "5. Tambah relasi musik" << std::endl;
        std::cout << "6. Hapus relasi musik" << std::endl;
        std::cout << "0. Kembali" << std::endl;
        std::cout << "Pilih menu: ";

        pilihan = bacaPilihanMenu();

        switch (pilihan) {
            case 1: {
                Artis artisBaru;

                std::cout << "\n========== TAMBAH ARTIS ==========" << std::endl;

                std::cout << "ID artis: ";
                std::getline(std::cin, artisBaru.id);

                std::cout << "Nama artis: ";
                std::getline(std::cin, artisBaru.nama);

                tambahArtis(listArtis, artisBaru);
                break;
            }

            case 2: {
                std::cout << std::endl;
                tampilkanSemuaArtis(listArtis);
                break;
            }

            case 3: {
                std::string idArtisCari;

                std::cout << "\n========== CARI ARTIS ==========" << std::endl;
                std::cout << "ID artis: ";
                std::getline(std::cin, idArtisCari);

                Artis* artisDitemukan = cariArtis(listArtis, idArtisCari);

                if (artisDitemukan != nullptr) {
                    std::cout << "\nArtis berhasil ditemukan" << std::endl;
                    std::cout << "ID artis: " << artisDitemukan->id << std::endl;
                    std::cout << "Nama artis: " << artisDitemukan->nama << std::endl;
                } else {
                    std::cout << "Artis tidak ditemukan" << std::endl;
                }

                break;
            }

            case 4: {
                std::string idArtisHapus;

                std::cout << "\n========== HAPUS ARTIS ==========" << std::endl;
                std::cout << "ID artis yang ingin dihapus: ";
                std::getline(std::cin, idArtisHapus);

                Artis* artisDitemukan = cariArtis(listArtis, idArtisHapus);

                if (artisDitemukan == nullptr) {
                    std::cout << "Artis tidak ditemukan" << std::endl;
                } else {
                    hapusArtis(listArtis, idArtisHapus);
                }

                break;
            }

            case 5: {
                std::string idArtisTambah;
                std::string idMusikTambah;

                std::cout << "\n========== TAMBAH RELASI MUSIK ==========" << std::endl;
                tampilkanSemuaArtis(listArtis);
                std::cout << "ID artis yang ingin ditambahkan: ";
                std::getline(std::cin, idArtisTambah);

                Artis* artisDitemukan = cariArtis(listArtis, idArtisTambah);

                if (artisDitemukan == nullptr) {
                    std::cout << "Artis tidak ditemukan" << std::endl;
                    break;
                }

                tampilkanSemuaMusik(listMusik);
                std::cout << "ID musik yang ingin ditambahkan: ";
                std::getline(std::cin, idMusikTambah);

                Musik* musikDitemukan = cariMusik(listMusik, idMusikTambah);

                if (musikDitemukan == nullptr) {
                    std::cout << "Musik tidak ditemukan" << std::endl;
                    break;
                }

                tambahArtisMusik(listArtis, idArtisTambah, musikDitemukan);

                break;
            }

            case 6: {
                std::string idArtisHapus;
                std::string idMusikHapus;

                std::cout << "\n========== HAPUS RELASI MUSIK ==========" << std::endl;
                tampilkanSemuaArtis(listArtis);
                std::cout << "ID artis yang ingin dihapus: ";
                std::getline(std::cin, idArtisHapus);

                Artis* artisDitemukan = cariArtis(listArtis, idArtisHapus);

                if (artisDitemukan == nullptr) {
                    std::cout << "Artis tidak ditemukan" << std::endl;
                    break;
                }

                tampilkanSemuaMusik(listMusik);
                std::cout << "ID musik yang ingin dihapus: ";
                std::getline(std::cin, idMusikHapus);

                Musik* musikDitemukan = cariMusik(listMusik, idMusikHapus);

                if (musikDitemukan == nullptr) {
                    std::cout << "Musik tidak ditemukan" << std::endl;
                    break;
                }

                hapusArtisMusik(listArtis, idArtisHapus, musikDitemukan);

                break;
            }

            case 0:
                std::cout << "Kembali ke main menu..." << std::endl;
                break;

            default:
                std::cout << "Pilihan tidak valid" << std::endl;
        }

    } while (pilihan != 0);
}

void menuAlbum(ListAlbum& listAlbum, const ListArtis& listArtis, const ListMusik& listMusik) {
    int pilihan;

    do {
        std::cout << "\n========== KELOLA ALBUM ==========" << std::endl;
        std::cout << "1. Tambah album" << std::endl;
        std::cout << "2. Tampilkan semua album" << std::endl;
        std::cout << "3. Cari album" << std::endl;
        std::cout << "4. Hapus album" << std::endl;
        std::cout << "5. Tambah relasi musik" << std::endl;
        std::cout << "6. Hapus relasi musik" << std::endl;
        std::cout << "0. Kembali" << std::endl;
        std::cout << "Pilih menu: ";

        pilihan = bacaPilihanMenu();

        switch (pilihan) {
            case 1: {
                Album albumBaru;
                std::string idArtis;

                std::cout << "\n========== TAMBAH ALBUM ==========" << std::endl;

                std::cout << "ID album: ";
                std::getline(std::cin, albumBaru.id);

                std::cout << "Nama album: ";
                std::getline(std::cin, albumBaru.nama);

                std::cout << "Deskripsi album: ";
                std::getline(std::cin, albumBaru.deskripsi);

                std::cout << "Tahun rilis: ";

                if (!(std::cin >> albumBaru.tahunRilis)) {
                    std::cout << "Tahun rilis harus berupa angka" << std::endl;
                    pulihkanInput();
                    break;
                }

                pulihkanInput();

                std::cout << "ID artis pemilik album: ";
                std::getline(std::cin, idArtis);

                albumBaru.artis = cariArtis(listArtis, idArtis);

                if (albumBaru.artis == nullptr) {
                    std::cout << "Artis tidak ditemukan. Album gagal ditambahkan" << std::endl;
                } else {
                    tambahAlbum(listAlbum, albumBaru);
                }

                break;
            }

            case 2: {
                std::cout << std::endl;
                tampilkanSemuaAlbum(listAlbum);
                break;
            }

            case 3: {
                std::string idAlbumCari;

                std::cout << "\n========== CARI ALBUM ==========" << std::endl;
                std::cout << "ID album: ";
                std::getline(std::cin, idAlbumCari);

                Album* albumDitemukan = cariAlbum(listAlbum, idAlbumCari);

                if (albumDitemukan != nullptr) {
                    std::cout << "\nAlbum berhasil ditemukan" << std::endl;
                    std::cout << "ID album: " << albumDitemukan->id << std::endl;
                    std::cout << "Nama album: " << albumDitemukan->nama << std::endl;
                    std::cout << "Deskripsi: " << albumDitemukan->deskripsi << std::endl;
                    std::cout << "Tahun rilis: " << albumDitemukan->tahunRilis << std::endl;

                    if (albumDitemukan->artis != nullptr) {
                        std::cout << "Artis: " << albumDitemukan->artis->nama << std::endl;
                    } else {
                        std::cout << "Artis: Tidak diketahui" << std::endl;
                    }
                } else {
                    std::cout << "Album tidak ditemukan" << std::endl;
                }

                break;
            }

            case 4: {
                std::string idAlbumHapus;

                std::cout << "\n========== HAPUS ALBUM ==========" << std::endl;
                std::cout << "ID album yang ingin dihapus: ";
                std::getline(std::cin, idAlbumHapus);

                Album* albumDitemukan = cariAlbum(listAlbum, idAlbumHapus);

                if (albumDitemukan == nullptr) {
                    std::cout << "Album tidak ditemukan" << std::endl;
                } else {
                    hapusAlbum(listAlbum, idAlbumHapus);
                }

                break;
            }

            case 5: {
                std::string idAlbumTambah;
                std::string idMusikTambah;

                std::cout << "\n========== TAMBAH RELASI MUSIK ==========" << std::endl;
                tampilkanSemuaAlbum(listAlbum);
                std::cout << "ID album yang ingin ditambahkan: ";
                std::getline(std::cin, idAlbumTambah);

                Album* albumDitemukan = cariAlbum(listAlbum, idAlbumTambah);

                if (albumDitemukan == nullptr) {
                    std::cout << "Album tidak ditemukan" << std::endl;
                    break;
                }

                tampilkanSemuaMusik(listMusik);
                std::cout << "ID musik yang ingin ditambahkan: ";
                std::getline(std::cin, idMusikTambah);

                Musik* musikDitemukan = cariMusik(listMusik, idMusikTambah);

                if (musikDitemukan == nullptr) {
                    std::cout << "Musik tidak ditemukan" << std::endl;
                    break;
                }

                tambahAlbumMusik(listAlbum, idAlbumTambah, musikDitemukan);

                break;
            }

            case 6: {
                std::string idAlbumHapus;
                std::string idMusikHapus;

                std::cout << "\n========== HAPUS RELASI MUSIK ==========" << std::endl;
                tampilkanSemuaAlbum(listAlbum);
                std::cout << "ID album yang ingin dihapus: ";
                std::getline(std::cin, idAlbumHapus);

                Album* albumDitemukan = cariAlbum(listAlbum, idAlbumHapus);

                if (albumDitemukan == nullptr) {
                    std::cout << "Album tidak ditemukan" << std::endl;
                    break;
                }

                tampilkanSemuaMusik(listMusik);
                std::cout << "ID musik yang ingin dihapus: ";
                std::getline(std::cin, idMusikHapus);

                Musik* musikDitemukan = cariMusik(listMusik, idMusikHapus);

                if (musikDitemukan == nullptr) {
                    std::cout << "Musik tidak ditemukan" << std::endl;
                    break;
                }

                hapusAlbumMusik(listAlbum, idAlbumHapus, musikDitemukan);

                break;
            }

            case 0:
                std::cout << "Kembali ke main menu..." << std::endl;
                break;

            default:
                std::cout << "Pilihan tidak valid" << std::endl;
        }

    } while (pilihan != 0);
}

void menuGenre(ListGenre& listGenre, const ListMusik& listMusik) {
    int pilihan;

    do {
        std::cout << "\n========== KELOLA GENRE ==========" << std::endl;
        std::cout << "1. Tambah genre" << std::endl;
        std::cout << "2. Tampilkan semua genre" << std::endl;
        std::cout << "3. Cari genre" << std::endl;
        std::cout << "4. Hapus genre" << std::endl;
        std::cout << "5. Tambah relasi musik" << std::endl;
        std::cout << "6. Hapus relasi musik" << std::endl;
        std::cout << "0. Kembali" << std::endl;
        std::cout << "Pilih menu: ";

        pilihan = bacaPilihanMenu();

        switch (pilihan) {
            case 1: {
                Genre genreBaru;

                std::cout << "\n========== TAMBAH GENRE ==========" << std::endl;
                std::cout << "Nama genre: ";
                std::getline(std::cin, genreBaru.nama);

                tambahGenre(listGenre, genreBaru);
                break;
            }

            case 2: {
                std::cout << std::endl;
                tampilkanSemuaGenre(listGenre);
                break;
            }

            case 3: {
                std::string namaGenreCari;

                std::cout << "\n========== CARI GENRE ==========" << std::endl;
                std::cout << "Nama genre: ";
                std::getline(std::cin, namaGenreCari);

                Genre* genreDitemukan = cariGenre(listGenre, namaGenreCari);

                if (genreDitemukan != nullptr) {
                    std::cout << "\nGenre berhasil ditemukan" << std::endl;
                    std::cout << "Nama genre: " << genreDitemukan->nama << std::endl;
                } else {
                    std::cout << "Genre tidak ditemukan" << std::endl;
                }

                break;
            }

            case 4: {
                std::string namaGenreHapus;

                std::cout << "\n========== HAPUS GENRE ==========" << std::endl;
                std::cout << "Nama genre yang ingin dihapus: ";
                std::getline(std::cin, namaGenreHapus);

                Genre* genreDitemukan = cariGenre(listGenre, namaGenreHapus);

                if (genreDitemukan == nullptr) {
                    std::cout << "Genre tidak ditemukan" << std::endl;
                } else {
                    hapusGenre(listGenre, namaGenreHapus);
                }

                break;
            }

             case 5: {
                std::string namaGenreTambah;
                std::string idMusikTambah;

                std::cout << "\n========== TAMBAH RELASI MUSIK ==========" << std::endl;
                tampilkanSemuaGenre(listGenre);
                std::cout << "Nama genre yang ingin ditambahkan: ";
                std::getline(std::cin, namaGenreTambah);

                Genre* genreDitemukan = cariGenre(listGenre, namaGenreTambah);

                if (genreDitemukan == nullptr) {
                    std::cout << "Genre tidak ditemukan" << std::endl;
                    break;
                }

                tampilkanSemuaMusik(listMusik);
                std::cout << "ID musik yang ingin ditambahkan: ";
                std::getline(std::cin, idMusikTambah);

                Musik* musikDitemukan = cariMusik(listMusik, idMusikTambah);

                if (musikDitemukan == nullptr) {
                    std::cout << "Musik tidak ditemukan" << std::endl;
                    break;
                }

                tambahGenreMusik(listGenre, namaGenreTambah, musikDitemukan);

                break;
            }

            case 6: {
                std::string namaGenreHapus;
                std::string idMusikHapus;

                std::cout << "\n========== HAPUS RELASI MUSIK ==========" << std::endl;
                tampilkanSemuaGenre(listGenre);
                std::cout << "Nama genre yang ingin dihapus: ";
                std::getline(std::cin, namaGenreHapus);

                Genre* genreDitemukan = cariGenre(listGenre, namaGenreHapus);

                if (genreDitemukan == nullptr) {
                    std::cout << "Genre tidak ditemukan" << std::endl;
                    break;
                }

                tampilkanSemuaMusik(listMusik);
                std::cout << "ID musik yang ingin dihapus: ";
                std::getline(std::cin, idMusikHapus);

                Musik* musikDitemukan = cariMusik(listMusik, idMusikHapus);

                if (musikDitemukan == nullptr) {
                    std::cout << "Musik tidak ditemukan" << std::endl;
                    break;
                }

                hapusGenreMusik(listGenre, namaGenreHapus, musikDitemukan);

                break;
            }

            case 0:
                std::cout << "Kembali ke main menu..." << std::endl;
                break;

            default:
                std::cout << "Pilihan tidak valid" << std::endl;
        }

    } while (pilihan != 0);
}

void menuPlaylist(ListPlaylist& listPlaylist, const ListMusik& listMusik) {
    int pilihan;

    do {
        std::cout << "\n========== KELOLA PLAYLIST ==========" << std::endl;
        std::cout << "1. Tambah playlist" << std::endl;
        std::cout << "2. Tampilkan semua playlist" << std::endl;
        std::cout << "3. Cari playlist" << std::endl;
        std::cout << "4. Hapus playlist" << std::endl;
        std::cout << "5. Tambah relasi musik" << std::endl;
        std::cout << "6. Hapus relasi musik" << std::endl;
        std::cout << "0. Kembali" << std::endl;
        std::cout << "Pilih menu: ";

        pilihan = bacaPilihanMenu();

        switch (pilihan) {
            case 1: {
                Playlist playlistBaru;

                std::cout << "\n========== TAMBAH PLAYLIST ==========" << std::endl;

                std::cout << "Judul playlist: ";
                std::getline(std::cin, playlistBaru.judul);

                std::cout << "Deskripsi playlist: ";
                std::getline(std::cin, playlistBaru.deskripsi);

                playlistBaru.frekuensiAkses = 0;

                tambahPlaylist(listPlaylist, playlistBaru);
                break;
            }

            case 2: {
                std::cout << std::endl;
                tampilkanSemuaPlaylist(listPlaylist);
                break;
            }

            case 3: {
                std::string judulPlaylistCari;

                std::cout << "\n========== CARI PLAYLIST ==========" << std::endl;
                std::cout << "Judul playlist: ";
                std::getline(std::cin, judulPlaylistCari);

                Playlist* playlistDitemukan = cariPlaylist(listPlaylist, judulPlaylistCari);

                if (playlistDitemukan != nullptr) {
                    std::cout << "\nPlaylist berhasil ditemukan" << std::endl;
                    std::cout << "Judul playlist: " << playlistDitemukan->judul << std::endl;
                    std::cout << "Deskripsi: " << playlistDitemukan->deskripsi << std::endl;
                    std::cout << "Frekuensi akses: " << playlistDitemukan->frekuensiAkses << std::endl;
                } else {
                    std::cout << "Playlist tidak ditemukan" << std::endl;
                }

                break;
            }

            case 4: {
                std::string judulPlaylistHapus;

                std::cout << "\n========== HAPUS PLAYLIST ==========" << std::endl;
                std::cout << "Judul playlist yang ingin dihapus: ";
                std::getline(std::cin, judulPlaylistHapus);

                Playlist* playlistDitemukan = cariPlaylist(listPlaylist, judulPlaylistHapus);

                if (playlistDitemukan == nullptr) {
                    std::cout << "Playlist tidak ditemukan." << std::endl;
                } else {
                    hapusPlaylist(listPlaylist, judulPlaylistHapus);
                }

                break;
            }

             case 5: {
                std::string namaPlaylist;
                std::string idMusikTambah;

                std::cout << "\n========== TAMBAH RELASI MUSIK ==========" << std::endl;
                tampilkanSemuaPlaylist(listPlaylist);
                std::cout << "Nama playlist yang ingin ditambahkan: ";
                std::getline(std::cin, namaPlaylist);

                Playlist* playlistDitemukan = cariPlaylist(listPlaylist, namaPlaylist);

                if (playlistDitemukan == nullptr) {
                    std::cout << "Playlist tidak ditemukan" << std::endl;
                    break;
                }

                tampilkanSemuaMusik(listMusik);
                std::cout << "ID musik yang ingin ditambahkan: ";
                std::getline(std::cin, idMusikTambah);

                Musik* musikDitemukan = cariMusik(listMusik, idMusikTambah);

                if (musikDitemukan == nullptr) {
                    std::cout << "Musik tidak ditemukan" << std::endl;
                    break;
                }

                tambahPlaylistMusik(listPlaylist, namaPlaylist, musikDitemukan);

                break;
            }

            case 6: {
                std::string namaPlaylistHapus;
                std::string idMusikHapus;

                std::cout << "\n========== HAPUS RELASI MUSIK ==========" << std::endl;
                tampilkanSemuaPlaylist(listPlaylist);
                std::cout << "Nama playlist yang ingin dihapus: ";
                std::getline(std::cin, namaPlaylistHapus);

                Playlist* playlistDitemukan = cariPlaylist(listPlaylist, namaPlaylistHapus);

                if (playlistDitemukan == nullptr) {
                    std::cout << "Playlist tidak ditemukan" << std::endl;
                    break;
                }

                tampilkanSemuaMusik(listMusik);
                std::cout << "ID musik yang ingin dihapus: ";
                std::getline(std::cin, idMusikHapus);

                Musik* musikDitemukan = cariMusik(listMusik, idMusikHapus);

                if (musikDitemukan == nullptr) {
                    std::cout << "Musik tidak ditemukan" << std::endl;
                    break;
                }

                hapusPlaylistMusik(listPlaylist, namaPlaylistHapus, musikDitemukan);

                break;
            }

            case 0:
                std::cout << "Kembali ke main menu..." << std::endl;
                break;

            default:
                std::cout << "Pilihan tidak valid." << std::endl;
        }

    } while (pilihan != 0);
}

int main() {
    ListMusik listMusik = buatListMusik();
    ListArtis listArtis = buatListArtis();
    ListAlbum listAlbum = buatListAlbum();
    ListGenre listGenre = buatListGenre();
    ListPlaylist listPlaylist = buatListPlaylist();

    int pilihan;

    do {
        std::cout << "\n========== MAIN MENU ==========" << std::endl;
        std::cout << "1. Kelola musik" << std::endl;
        std::cout << "2. Kelola artis" << std::endl;
        std::cout << "3. Kelola album" << std::endl;
        std::cout << "4. Kelola genre" << std::endl;
        std::cout << "5. Kelola playlist" << std::endl;
        std::cout << "0. Keluar" << std::endl;
        std::cout << "Pilih menu: ";

        pilihan = bacaPilihanMenu();

        switch (pilihan) {
            case 1:
                menuMusik(listMusik, listArtis, listAlbum, listGenre, listPlaylist);
                break;

            case 2:
                menuArtis(listArtis, listMusik);
                break;

            case 3:
                menuAlbum(listAlbum, listArtis, listMusik);
                break;

            case 4:
                menuGenre(listGenre, listMusik);
                break;

            case 5:
                menuPlaylist(listPlaylist, listMusik);
                break;

            case 0:
                std::cout << "Terima kasih sudah menggunakan aplikasi SoundBranch" << std::endl;
                break;

            default:
                std::cout << "Pilihan tidak valid" << std::endl;
        }

    } while (pilihan != 0);

    return 0;
}