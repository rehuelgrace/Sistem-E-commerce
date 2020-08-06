#ifndef PRODUK_H
#define PRODUK_H

typedef struct {
	char id_produk[3]; /* format P1-P9*/
	char id_penjual[3]; /* format 01-99*/
	char nama_produk[5];
	char kategori[3]; /* format K1-K9 */
	int harga;
	int Neff;
} Produk;

void CreateEmptyP (Produk *P);
/* I.S. sembarang */
/* F.S. Terbentuk tabel P kosong dengan kapasitas IdxMax-IdxMin+1 */

void AddProduk(Produk *P, char id_produk[], char id_penjual[], char nama_produk[], int harga, char kategori[]);

void AddToDataProduk(Produk P);

void PrintProduk(Produk P, char id[]);

void PrintAllProduk(Produk P);

#endif