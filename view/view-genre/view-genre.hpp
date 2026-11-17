#ifndef VIEW_GENRE_HPP
#define VIEW_GENRE_HPP

#include "../../abstract-data-type/list-genre/list-genre.hpp"
#include "../../abstract-data-type/list-musik/list-musik.hpp"

void viewMenuKelolaGenre(ListGenre& listGenre, const ListMusik& listMusik);

void viewTambahGenre(ListGenre& listGenre);
void viewTampilkanSemuaGenre(const ListGenre& listGenre);
void viewCariGenre(const ListGenre& listGenre);
void viewUpdateGenre(ListGenre& listGenre);
void viewHapusGenre(ListGenre& listGenre);

void viewTambahRelasiGenreMusik(ListGenre& listGenre, const ListMusik& listMusik);
void viewHapusRelasiGenreMusik(ListGenre& listGenre, const ListMusik& listMusik);

#endif