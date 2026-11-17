#ifndef VIEW_ALBUM_HPP
#define VIEW_ALBUM_HPP

#include "../../abstract-data-type/list-album/list-album.hpp"
#include "../../abstract-data-type/list-artis/list-artis.hpp"
#include "../../abstract-data-type/list-musik/list-musik.hpp"

void viewMenuKelolaAlbum(ListAlbum& listAlbum, const ListArtis& listArtis, const ListMusik& listMusik);

void viewTambahAlbum(ListAlbum& listAlbum, const ListArtis& listArtis);
void viewTampilkanSemuaAlbum(const ListAlbum& listAlbum);
void viewCariAlbum(const ListAlbum& listAlbum);
void viewUpdateAlbum(ListAlbum& listAlbum, const ListArtis& listArtis);
void viewHapusAlbum(ListAlbum& listAlbum);

void viewTambahRelasiAlbumMusik(ListAlbum& listAlbum, const ListMusik& listMusik);
void viewHapusRelasiAlbumMusik(ListAlbum& listAlbum, const ListMusik& listMusik);

#endif