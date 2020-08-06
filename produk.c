#include "boolean.h"
#include "produk.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void CreateEmptyP (Produk *P){
	(*P).Neff = 0;
}
/* I.S. sembarang */
/* F.S. Terbentuk tabel P kosong dengan kapasitas IdxMax-IdxMin+1 */

void AddProduk(Produk *P, char id_produk[], char id_penjual[], char nama_produk[], int harga, char kategori[]){
	strcpy(P->id_produk, id_produk);
	strcpy(P->id_penjual, id_penjual);
	strcpy(P->nama_produk, nama_produk);
	strcpy(P->kategori, kategori);
	P->harga = harga;
}

void AddToDataProduk(Produk P){
	char id_produk[3]; /* format P1-P9*/
	char id_penjual[3]; /* format 01-99*/
	char nama_produk[5];
	char kategori[3]; /* format K1-K9 */
	char harga[100];

	strcpy(id_produk, P.id_produk);
	strcpy(id_penjual, P.id_penjual);
	strcpy(nama_produk, P.nama_produk);
	strcpy(kategori, P.kategori);
	sprintf(harga, "%d", P.harga); // mengubah tipe integer produk.harga ke array of char.
	//itoa(P.stock, stock, 10);
	//sprintf(stock, "%d", P.stock); // mengubah tipe integer produk.stock ke array of char.

	FILE *filename = fopen("DataProduk.txt","a+");
	fprintf(filename, "%s %s %s %s %s\n", id_produk, id_penjual, nama_produk, harga, kategori);
	fclose(filename);
}

void PrintProduk(Produk P, char id[]){
	char id_produk[3]; /* format P1-P9*/
	char id_penjual[3]; /* format 01-99*/
	char nama_produk[5];
	char kategori[3]; /* format K1-K9 */
	char harga[100];

	FILE *filename = fopen("DataProduk.txt","a+");
	printf("id_produk id_penjual nama_produk harga kategori\n");	
	while (!feof(filename)){
		fscanf(filename, "%s %s %s %s %s\n", id_produk, id_penjual, nama_produk, harga, kategori);
		if(strcmp(id, id_penjual)==0){
			fflush(stdin);
			printf("%s %s %s %s %s\n", id_produk, id_penjual, nama_produk, harga, kategori);
		}
		fflush(stdin);
	}
}

void PrintAllProduk(Produk P){
	char id_produk[3]; /* format P1-P9*/
	char id_penjual[3]; /* format 01-99*/
	char nama_produk[5];
	char kategori[3]; /* format K1-K9 */
	char harga[100];

	FILE *filename = fopen("DataProduk.txt","a+");
	printf("id_produk id_penjual nama_produk harga kategori\n");	
	while (!feof(filename)){
		fscanf(filename, "%s %s %s %s %s\n", id_produk, id_penjual, nama_produk, harga, kategori);
		fflush(stdin);
		printf("%s %s %s %s %s\n", id_produk, id_penjual, nama_produk, harga, kategori);
	}
}