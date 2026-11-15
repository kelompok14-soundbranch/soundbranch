#include "MLLPlaylist.hpp"

/* ===================== Pengelolaan awal & akhir ===================== */

/*
 * inisialisasiMLLPlaylist
 * I.S. : m sembarang (belum diinisialisasi)
 * F.S. : m adalah MLL Playlist kosong (m.first = nullptr)
 */
void inisialisasiMLLPlaylist(MLLPlaylist& m) {
    m.first = nullptr;
}

/*
 * bersihChildPlaylist  (prosedur bantu)
 * I.S. : p sudah ada, list child milik p boleh kosong atau berisi
 * F.S. : seluruh node child milik p dibebaskan, p->firstChild = nullptr.
 *        Node musik di SLL TIDAK ikut dihapus (child hanya menunjuk).
 */
static void bersihChildPlaylist(NodeParentPlaylist* p) {
    while (p->firstChild != nullptr) {
        NodeChildPlaylist* temp = p->firstChild;
        p->firstChild = temp->next;
        delete temp;
    }
}

/*
 * bersihkanMLLPlaylist
 * I.S. : m sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : seluruh playlist beserta node child-nya dibebaskan, m menjadi kosong.
 *        SLL musik tidak tersentuh.
 */
void bersihkanMLLPlaylist(MLLPlaylist& m) {
    while (m.first != nullptr) {
        NodeParentPlaylist* temp = m.first;
        bersihChildPlaylist(temp);
        m.first = temp->next;
        delete temp;
    }
}

/* ===================== Pencarian & informasi ===================== */

/*
 * cariPlaylist  (penelusuran linear, O(n))
 * I.S. : m sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : mengembalikan pointer ke parent yang data.judul-nya sama dengan
 *        judul, atau nullptr jika tidak ditemukan; m tidak berubah
 */
NodeParentPlaylist* cariPlaylist(const MLLPlaylist& m, const string& judul) {
    NodeParentPlaylist* p = m.first;

    while (p != nullptr && p->data.judul != judul) {
        p = p->next;
    }
    return p;
}

/*
 * cariMusikPlaylist  (penelusuran linear, O(n))
 * I.S. : p sudah ada (tidak nullptr)
 * F.S. : mengembalikan pointer ke child yang musiknya ber-id id pada p,
 *        atau nullptr jika tidak ditemukan; list child tidak berubah
 */
NodeChildPlaylist* cariMusikPlaylist(const NodeParentPlaylist* p, const string& id) {
    NodeChildPlaylist* c = p->firstChild;

    while (c != nullptr && c->musik->data.id != id) {
        c = c->next;
    }
    return c;
}

/*
 * cariMusikPlaylistByJudul  (penelusuran linear, O(n))
 * I.S. : p sudah ada (tidak nullptr)
 * F.S. : mengembalikan pointer ke child PERTAMA yang musiknya berjudul judul
 *        pada p, atau nullptr jika tidak ditemukan; list child tidak berubah
 */
NodeChildPlaylist* cariMusikPlaylistByJudul(const NodeParentPlaylist* p, const string& judul) {
    NodeChildPlaylist* c = p->firstChild;

    while (c != nullptr && c->musik->data.judul != judul) {
        c = c->next;
    }
    return c;
}

/*
 * cariMusikDiPlaylist  (pencarian dua tingkat, O(n + k))
 * I.S. : m sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : mengembalikan pointer ke node musik (di SLL) yang berjudul judulMusik
 *        dan terdaftar pada playlist judulPlaylist; mengembalikan nullptr jika
 *        playlist tidak ada atau musik tidak ada di playlist tersebut;
 *        m tidak berubah
 */
NodeMusik* cariMusikDiPlaylist(const MLLPlaylist& m, const string& judulPlaylist,
                               const string& judulMusik) {
    NodeMusik* hasil = nullptr;
    NodeParentPlaylist* p = cariPlaylist(m, judulPlaylist);

    if (p != nullptr) {
        NodeChildPlaylist* c = cariMusikPlaylistByJudul(p, judulMusik);
        if (c != nullptr) {
            hasil = c->musik;
        }
    }
    return hasil;
}

/*
 * tampilCariMusikDiPlaylist
 * I.S. : m sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : jika ditemukan -> data musik (id, judul, durasi, tahun rilis) dan nama
 *        playlist tercetak; jika playlist tidak ada atau musik tidak ada di
 *        playlist tersebut -> tercetak pesan yang sesuai; m tidak berubah
 */
void tampilCariMusikDiPlaylist(const MLLPlaylist& m, const string& judulPlaylist,
                               const string& judulMusik) {
    NodeParentPlaylist* p = cariPlaylist(m, judulPlaylist);

    if (p == nullptr) {
        cout << "Playlist \"" << judulPlaylist << "\" tidak ditemukan.\n";
    } else {
        NodeMusik* nm = cariMusikDiPlaylist(m, judulPlaylist, judulMusik);
        if (nm == nullptr) {
            cout << "Musik \"" << judulMusik << "\" tidak ada di playlist \""
                 << judulPlaylist << "\".\n";
        } else {
            cout << "Ditemukan di playlist \"" << judulPlaylist << "\": ["
                 << nm->data.id << "] " << nm->data.judul
                 << " | durasi: " << nm->data.durasi << " detik"
                 << " | rilis: " << nm->data.tahunRilis << "\n";
        }
    }
}

/*
 * jumlahPlaylist
 * I.S. : m sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : mengembalikan banyak playlist pada m (0 jika kosong); m tidak berubah
 */
int jumlahPlaylist(const MLLPlaylist& m) {
    int jumlah = 0;
    NodeParentPlaylist* p = m.first;

    while (p != nullptr) {
        jumlah++;
        p = p->next;
    }
    return jumlah;
}

/*
 * jumlahMusikPlaylist
 * I.S. : p sudah ada (tidak nullptr)
 * F.S. : mengembalikan banyak musik milik p (0 jika kosong); list tidak berubah
 */
int jumlahMusikPlaylist(const NodeParentPlaylist* p) {
    int jumlah = 0;
    NodeChildPlaylist* c = p->firstChild;

    while (c != nullptr) {
        jumlah++;
        c = c->next;
    }
    return jumlah;
}

/*
 * tampilMLLPlaylist
 * I.S. : m sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : seluruh playlist (judul, deskripsi, frekuensi akses) beserta
 *        musiknya tercetak berurutan dari parent pertama. Data musik dibaca
 *        langsung dari node SLL, sehingga selalu sesuai data terbaru.
 *        Jika kosong tercetak pesan bahwa data kosong; m tidak berubah
 */
void tampilMLLPlaylist(const MLLPlaylist& m) {
    if (m.first == nullptr) {
        cout << "Data playlist kosong.\n";
    } else {
        int noP = 1;
        NodeParentPlaylist* p = m.first;
        while (p != nullptr) {
            cout << noP << ". " << p->data.judul;
            if (!p->data.deskripsi.empty()) {
                cout << " | deskripsi: " << p->data.deskripsi;
            }
            cout << " | diakses: " << p->data.frekuensiAkses << "x\n";
            if (p->firstChild == nullptr) {
                cout << "     (belum ada musik)\n";
            } else {
                int noC = 1;
                NodeChildPlaylist* c = p->firstChild;
                while (c != nullptr) {
                    cout << "     " << noP << "." << noC << " ["
                         << c->musik->data.id << "] " << c->musik->data.judul
                         << " | durasi: " << c->musik->data.durasi << " detik"
                         << " | rilis: " << c->musik->data.tahunRilis << "\n";
                    noC++;
                    c = c->next;
                }
            }
            noP++;
            p = p->next;
        }
    }
}

/* ===================== Penambahan & perubahan ===================== */

/*
 * tambahPlaylist  (insert first)
 * I.S. : m sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : jika judul belum ada -> parent baru berjudul judul (deskripsi kosong,
 *        frekuensiAkses = 0, child kosong) menjadi parent PERTAMA, fungsi
 *        mengembalikan true.
 *        jika sudah ada -> m tidak berubah, fungsi mengembalikan false
 */
bool tambahPlaylist(MLLPlaylist& m, const string& judul) {
    bool ditambah = (cariPlaylist(m, judul) == nullptr);

    if (ditambah) {
        NodeParentPlaylist* baru = new NodeParentPlaylist;
        baru->data.judul = judul;
        baru->data.deskripsi = "";
        baru->data.frekuensiAkses = 0;
        baru->firstChild = nullptr;
        baru->next = m.first;
        m.first = baru;
    }
    return ditambah;
}

/*
 * tambahChildPlaylist  (insert last, O(n))
 * I.S. : p sudah ada (tidak nullptr), nodeMusik menunjuk ke node valid di SLL,
 *        list child boleh kosong atau berisi
 * F.S. : jika musik ber-id tersebut belum ada pada p -> child baru yang
 *        menunjuk ke nodeMusik menjadi child TERAKHIR, fungsi mengembalikan true.
 *        jika sudah ada (atau nodeMusik nullptr) -> list child tidak berubah,
 *        fungsi mengembalikan false
 */
bool tambahChildPlaylist(NodeParentPlaylist* p, NodeMusik* nodeMusik) {
    bool ditambah = (nodeMusik != nullptr &&
                     cariMusikPlaylist(p, nodeMusik->data.id) == nullptr);

    if (ditambah) {
        NodeChildPlaylist* baru = new NodeChildPlaylist;
        baru->musik = nodeMusik;
        baru->next = nullptr;

        if (p->firstChild == nullptr) {
            p->firstChild = baru;
        } else {
            NodeChildPlaylist* c = p->firstChild;
            while (c->next != nullptr) {
                c = c->next;
            }
            c->next = baru;
        }
    }
    return ditambah;
}

/*
 * tambahMusikKePlaylist  (sinkronisasi ke SLL utama + child berupa pointer)
 * I.S. : m dan sll sudah diinisialisasi
 * F.S. : jika playlist judulPlaylist ada -> musik didaftarkan ke sll jika
 *        id-nya belum terdaftar (jika sudah, tidak diduplikasi), lalu child
 *        baru yang menunjuk ke node musik di sll disisipkan ke playlist
 *        (insert last). Mengembalikan true jika child berhasil ditambahkan.
 *        jika playlist tidak ada -> m dan sll tidak berubah, mengembalikan false.
 *        jika musik sudah ada di playlist tersebut -> mengembalikan false.
 */
bool tambahMusikKePlaylist(MLLPlaylist& m, ListMusik& sll,
                           const string& judulPlaylist, const Musik& musik) {
    bool berhasil = false;
    NodeParentPlaylist* p = cariPlaylist(m, judulPlaylist);

    if (p != nullptr) {
        // tambahMusik sudah mengecek duplikasi id di SLL (dilewati jika sudah ada)
        tambahMusik(sll, musik);
        NodeMusik* nodeSll = cariMusik(sll, musik.id);
        berhasil = tambahChildPlaylist(p, nodeSll);
    }
    return berhasil;
}

/*
 * aksesPlaylist
 * I.S. : m sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : jika playlist judulPlaylist ada -> frekuensiAkses bertambah 1,
 *        fungsi mengembalikan true.
 *        jika tidak ada -> m tidak berubah, fungsi mengembalikan false
 */
bool aksesPlaylist(MLLPlaylist& m, const string& judulPlaylist) {
    NodeParentPlaylist* p = cariPlaylist(m, judulPlaylist);
    bool berhasil = (p != nullptr);

    if (berhasil) {
        p->data.frekuensiAkses++;
    }
    return berhasil;
}

/* ===================== Penghapusan ===================== */

/*
 * hapusMusikPlaylist  (hapus berdasarkan id, O(n))
 * I.S. : p sudah ada (tidak nullptr), list child boleh kosong atau berisi
 * F.S. : jika musik ber-id id ada pada p -> node child-nya dihapus
 *        (awal/tengah/akhir), fungsi mengembalikan true. Node musik di SLL
 *        tidak ikut dihapus.
 *        jika tidak ada -> list child tidak berubah, fungsi mengembalikan false
 */
bool hapusMusikPlaylist(NodeParentPlaylist* p, const string& id) {
    bool berhasil = false;

    if (p->firstChild != nullptr) {
        if (p->firstChild->musik->data.id == id) {
            NodeChildPlaylist* temp = p->firstChild;
            p->firstChild = temp->next;
            delete temp;
            berhasil = true;
        } else {
            NodeChildPlaylist* prev = p->firstChild;
            while (prev->next != nullptr && prev->next->musik->data.id != id) {
                prev = prev->next;
            }
            if (prev->next != nullptr) {
                NodeChildPlaylist* temp = prev->next;
                prev->next = temp->next;
                delete temp;
                berhasil = true;
            }
        }
    }
    return berhasil;
}

/*
 * hapusPlaylist  (hapus berdasarkan judul, O(n))
 * I.S. : m sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : jika judul ada di m -> playlist tersebut beserta seluruh node
 *        child-nya dihapus, fungsi mengembalikan true. SLL tidak tersentuh.
 *        jika tidak ada -> m tidak berubah, fungsi mengembalikan false
 */
bool hapusPlaylist(MLLPlaylist& m, const string& judul) {
    bool berhasil = false;

    if (m.first != nullptr) {
        if (m.first->data.judul == judul) {
            NodeParentPlaylist* temp = m.first;
            bersihChildPlaylist(temp);
            m.first = temp->next;
            delete temp;
            berhasil = true;
        } else {
            NodeParentPlaylist* prev = m.first;
            while (prev->next != nullptr && prev->next->data.judul != judul) {
                prev = prev->next;
            }
            if (prev->next != nullptr) {
                NodeParentPlaylist* temp = prev->next;
                bersihChildPlaylist(temp);
                prev->next = temp->next;
                delete temp;
                berhasil = true;
            }
        }
    }
    return berhasil;
}

/*
 * hapusReferensiMusik
 * I.S. : m sudah diinisialisasi, boleh kosong atau berisi
 * F.S. : seluruh child yang menunjuk ke musik ber-id id dihapus dari
 *        semua playlist di m; mengembalikan banyak child yang dihapus
 *        (0 jika tidak ada). Dipanggil sebelum musik dihapus dari SLL agar
 *        tidak ada pointer yang menggantung.
 */
int hapusReferensiMusik(MLLPlaylist& m, const string& id) {
    int terhapus = 0;
    NodeParentPlaylist* p = m.first;

    while (p != nullptr) {
        if (hapusMusikPlaylist(p, id)) {
            terhapus++;
        }
        p = p->next;
    }
    return terhapus;
}