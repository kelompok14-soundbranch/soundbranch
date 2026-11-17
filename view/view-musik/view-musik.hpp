#ifndef VIEW_MUSIK_HPP
#define VIEW_MUSIK_HPP

#include "../../abstract-data-type/list-musik/list-musik.hpp"
#include "../../abstract-data-type/list-artis/list-artis.hpp"
#include "../../abstract-data-type/list-album/list-album.hpp"
#include "../../abstract-data-type/list-genre/list-genre.hpp"
#include "../../abstract-data-type/list-playlist/list-playlist.hpp"

void viewMenuKelolaMusik(ListMusik& listMusik, ListArtis& listArtis, ListAlbum& listAlbum, ListGenre& listGenre, ListPlaylist& listPlaylist);

void viewTambahMusik(ListMusik& listMusik);
void viewTampilkanSemuaMusik(ListMusik& listMusik, ListArtis& listArtis, ListAlbum& listAlbum, ListGenre& listGenre, ListPlaylist& listPlaylist);
void viewCariMusik(const ListMusik& listMusik);
void viewUpdateMusik(ListMusik& listMusik);
void viewHapusMusik(ListMusik& listMusik, ListArtis& listArtis, ListAlbum& listAlbum, ListGenre& listGenre, ListPlaylist& listPlaylist);

#endif