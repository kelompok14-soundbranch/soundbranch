#ifndef VIEW_PLAYLIST_HPP
#define VIEW_PLAYLIST_HPP

#include "../../abstract-data-type/list-playlist/list-playlist.hpp"
#include "../../abstract-data-type/list-musik/list-musik.hpp"

void viewMenuKelolaPlaylist(ListPlaylist& listPlaylist, const ListMusik& listMusik);

void viewTambahPlaylist(ListPlaylist& listPlaylist);
void viewTampilkanSemuaPlaylist(const ListPlaylist& listPlaylist);
void viewCariPlaylist(const ListPlaylist& listPlaylist);
void viewUpdatePlaylist(ListPlaylist& listPlaylist);
void viewHapusPlaylist(ListPlaylist& listPlaylist);

void viewTambahRelasiPlaylistMusik(ListPlaylist& listPlaylist, const ListMusik& listMusik);
void viewHapusRelasiPlaylistMusik(ListPlaylist& listPlaylist, const ListMusik& listMusik);

#endif