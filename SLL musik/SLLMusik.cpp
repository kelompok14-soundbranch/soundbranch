#include "sllMusik.hpp"

/* ===================== Pengelolaan awal & akhir ===================== */

/*
 * inisialisasiMusik
 * I.S. : l sembarang (belum diinisialisasi)
 * F.S. : l adalah list kosong (l.first = nullptr)
 */
void inisialisasiMusik(ListMusik& l) {
    l.first = nullptr;
}

/*
 * bersihkanMusik
 * I.S. : l sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : seluruh node pada l dibebaskan dari node pertama satu per satu,
 *        l menjadi list kosong (l.first = nullptr)
 */
void bersihkanMusik(ListMusik& l) {
    while (l.first != nullptr) {
        NodeMusik* temp = l.first;
        l.first = temp->next;
        delete temp;
    }
}

/* ===================== Pencarian & informasi ===================== */

/*
 * cariMusik  (penelusuran linear, O(n); pencocokan id persis/huruf besar-kecil dibedakan)
 * I.S. : l sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : mengembalikan pointer ke node yang id-nya sama dengan id,
 *        atau nullptr jika tidak ditemukan; l tidak berubah
 */
NodeMusik* cariMusik(const ListMusik& l, const string& id) {
    NodeMusik* p = l.first;

    while (p != nullptr && p->data.id != id) {
        p = p->next;
    }
    return p;
}

/*
 * cariMusikByJudul  (penelusuran linear, O(n); huruf besar-kecil dibedakan)
 * I.S. : l sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : mengembalikan pointer ke node PERTAMA yang judulnya sama dengan judul,
 *        atau nullptr jika tidak ditemukan; l tidak berubah
 */
NodeMusik* cariMusikByJudul(const ListMusik& l, const string& judul) {
    NodeMusik* p = l.first;

    while (p != nullptr && p->data.judul != judul) {
        p = p->next;
    }
    return p;
}

/*
 * sudahAdaMusik
 * I.S. : l sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : mengembalikan true jika id terdaftar di l, false jika tidak;
 *        l tidak berubah
 */
bool sudahAdaMusik(const ListMusik& l, const string& id) {
    return cariMusik(l, id) != nullptr;
}

/*
 * jumlahMusik
 * I.S. : l sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : mengembalikan banyak node pada l (0 jika kosong); l tidak berubah
 */
int jumlahMusik(const ListMusik& l) {
    int jumlah = 0;
    NodeMusik* p = l.first;

    while (p != nullptr) {
        jumlah++;
        p = p->next;
    }
    return jumlah;
}

/*
 * tampilMusik
 * I.S. : l sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : seluruh musik pada l tercetak berurutan dari node pertama dengan
 *        penomoran (id, judul, durasi dalam detik, tahun rilis); jika kosong
 *        tercetak pesan bahwa list kosong; l tidak berubah
 */
void tampilMusik(const ListMusik& l) {
    if (l.first == nullptr) {
        cout << "List musik kosong.\n";
    } else {
        int no = 1;
        NodeMusik* p = l.first;
        while (p != nullptr) {
            cout << no << ". [" << p->data.id << "] " << p->data.judul
                 << " | durasi: " << p->data.durasi << " detik"
                 << " | rilis: " << p->data.tahunRilis << "\n";
            no++;
            p = p->next;
        }
    }
}

/* ===================== Penambahan (insert last) ===================== */

/*
 * tambahMusik  (insert last; O(n) karena SLL standar tidak punya pointer last)
 * I.S. : l sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : jika m.id belum ada di l -> node baru berisi m menjadi node
 *        TERAKHIR, fungsi mengembalikan true.
 *        jika m.id sudah ada -> l tidak berubah (tidak ada duplikasi),
 *        fungsi mengembalikan false
 */
bool tambahMusik(ListMusik& l, const Musik& m) {
    bool ditambah = !sudahAdaMusik(l, m.id);

    if (ditambah) {
        NodeMusik* baru = new NodeMusik;
        baru->data = m;
        baru->next = nullptr;

        if (l.first == nullptr) {
            l.first = baru;
        } else {
            NodeMusik* p = l.first;
            while (p->next != nullptr) {
                p = p->next;
            }
            p->next = baru;
        }
    }
    return ditambah;
}

/* ===================== Penghapusan ===================== */

/*
 * hapusAwalMusik  (delete first, O(1))
 * I.S. : l sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : jika l tidak kosong -> data node pertama disimpan di hasil, node
 *        pertama dihapus, node kedua menjadi first, fungsi mengembalikan true.
 *        jika l kosong -> l dan hasil tidak berubah, fungsi mengembalikan false
 */
bool hapusAwalMusik(ListMusik& l, Musik& hasil) {
    bool berhasil = (l.first != nullptr);

    if (berhasil) {
        NodeMusik* temp = l.first;
        hasil = temp->data;
        l.first = temp->next;
        delete temp;
    }
    return berhasil;
}

/*
 * hapusAkhirMusik  (delete last, O(n))
 * I.S. : l sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : jika l tidak kosong -> data node terakhir disimpan di hasil, node
 *        terakhir dihapus, fungsi mengembalikan true.
 *        jika l kosong -> l dan hasil tidak berubah, fungsi mengembalikan false
 */
bool hapusAkhirMusik(ListMusik& l, Musik& hasil) {
    bool berhasil = (l.first != nullptr);

    if (berhasil) {
        if (l.first->next == nullptr) {
            // hanya satu node: sama dengan delete first
            hasil = l.first->data;
            delete l.first;
            l.first = nullptr;
        } else {
            // berhenti di node sebelum node terakhir
            NodeMusik* prev = l.first;
            while (prev->next->next != nullptr) {
                prev = prev->next;
            }
            hasil = prev->next->data;
            delete prev->next;
            prev->next = nullptr;
        }
    }
    return berhasil;
}

/*
 * hapusSetelahMusik  (delete after, O(1))
 * I.S. : prev adalah pointer ke sebuah node pada list (boleh nullptr)
 * F.S. : jika prev tidak nullptr dan punya node sesudahnya -> node sesudah prev
 *        dihapus, datanya disimpan di hasil, fungsi mengembalikan true.
 *        selain itu -> list dan hasil tidak berubah, fungsi mengembalikan false
 */
bool hapusSetelahMusik(NodeMusik* prev, Musik& hasil) {
    bool berhasil = (prev != nullptr && prev->next != nullptr);

    if (berhasil) {
        NodeMusik* temp = prev->next;
        hasil = temp->data;
        prev->next = temp->next;
        delete temp;
    }
    return berhasil;
}

/*
 * hapusMusik  (hapus berdasarkan id, O(n))
 * I.S. : l sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : jika id ada di l -> node ber-id tersebut dihapus (di awal,
 *        tengah, atau akhir), fungsi mengembalikan true.
 *        jika tidak ada -> l tidak berubah, fungsi mengembalikan false
 */
bool hapusMusik(ListMusik& l, const string& id) {
    bool berhasil = false;
    Musik dummy;

    if (l.first != nullptr) {
        if (l.first->data.id == id) {
            berhasil = hapusAwalMusik(l, dummy);
        } else {
            NodeMusik* prev = l.first;
            while (prev->next != nullptr && prev->next->data.id != id) {
                prev = prev->next;
            }
            berhasil = hapusSetelahMusik(prev, dummy);
        }
    }
    return berhasil;
}