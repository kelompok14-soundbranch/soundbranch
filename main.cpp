#include <iostream>
#include <string>

#include "view/view-musik/view-musik.hpp"
#include "view/view-artis/view-artis.hpp"
#include "view/view-album/view-album.hpp"
#include "view/view-genre/view-genre.hpp"
#include "view/view-playlist/view-playlist.hpp"

int main() {
    ListMusik listMusik = buatListMusik();
    ListArtis listArtis = buatListArtis();
    ListAlbum listAlbum = buatListAlbum();
    ListGenre listGenre = buatListGenre();
    ListPlaylist listPlaylist = buatListPlaylist();

    std::string pilihan;

    while (true) {
        std::cout << "====================================" << std::endl;
        std::cout << "           SOUNDBRANCH              " << std::endl;
        std::cout << "====================================" << std::endl;
        std::cout << "1. Kelola musik" << std::endl;
        std::cout << "2. Kelola artis" << std::endl;
        std::cout << "3. Kelola album" << std::endl;
        std::cout << "4. Kelola genre" << std::endl;
        std::cout << "5. Kelola playlist" << std::endl;
        std::cout << "0. Keluar" << std::endl;
        std::cout << "Pilih menu > ";
        
        std::getline(std::cin, pilihan);

        std::cout << std::endl;

        if (pilihan == "0" || std::cin.eof()) {
            std::cout << "Terima kasih telah menggunakan SoundBranch" << std::endl;
            break;
        }

        if (pilihan == "1") {
            viewMenuKelolaMusik(listMusik, listArtis, listAlbum, listGenre, listPlaylist);
        } else if (pilihan == "2") {
            viewMenuKelolaArtis(listArtis, listMusik);
        } else if (pilihan == "3") {
            viewMenuKelolaAlbum(listAlbum, listArtis, listMusik);
        } else if (pilihan == "4") {
            viewMenuKelolaGenre(listGenre, listMusik);
        } else if (pilihan == "5") {
            viewMenuKelolaPlaylist(listPlaylist, listMusik);
        } else {
            std::cerr << "Pilihan tidak valid" << std::endl;
        }

        if (pilihan == "0" || std::cin.eof()) {
            std::cout << "Terima kasih telah menggunakan SoundBranch" << std::endl;
            break;
        }

        std::cout << std::endl;
    }

    return 0;
}
