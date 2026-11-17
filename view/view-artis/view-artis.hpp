#ifndef VIEW_ARTIS_HPP
#define VIEW_ARTIS_HPP

#include "../../abstract-data-type/list-artis/list-artis.hpp"
#include "../../abstract-data-type/list-musik/list-musik.hpp"

void viewMenuKelolaArtis(ListArtis& listArtis, const ListMusik& listMusik);
void viewTambahArtis(ListArtis& listArtis);
void viewTampilkanSemuaArtis(const ListArtis& listArtis);
void viewCariArtis(const ListArtis& listArtis);
void viewUpdateArtis(ListArtis& listArtis);
void viewHapusArtis(ListArtis& listArtis);
void viewTambahRelasiArtisMusik(ListArtis& listArtis, const ListMusik& listMusik);
void viewHapusRelasiArtisMusik(ListArtis& listArtis, const ListMusik& listMusik);

#endif