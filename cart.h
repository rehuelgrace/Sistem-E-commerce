/* File : stacklist.h */
#ifndef _CART_H
#define _CART_H

#include "boolean.h"
#include <stdlib.h>

/* Konstanta */
#define Nil NULL

/* Deklarasi infotype */
typedef struct{
	char id_produk[3];
	char id_pembeli[3];
	char id_penjual[3];
	int harga;
	int jumlah_barang;
	int total;
	char status[999];
}infotype;

/* Stack dengan representasi berkait dengan pointer */
typedef struct tElmtStack * address;
typedef struct tElmtStack { 
  infotype Info;
  address Next; 
} ElmtStack; 

/* Type stack dengan ciri TOP : */
typedef struct { 
  address TOP;  /* alamat TOP: elemen puncak */
} Stack;

/* Selektor */
#define Top(S) (S).TOP
#define InfoTop(S) (S).TOP->Info 
#define Next(P) (P)->Next
#define Info(P) (P)->Info

/* Prototype manajemen memori */
void AlokasiC (address *P, infotype X);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void DealokasiC (address P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */ 

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean IsEmptyC (Stack S);
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
void CreateEmptyC (Stack * S);
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stack S yang kosong */
void Push (Stack * S, infotype X);
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
void Pop (Stack * S, infotype * X);
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
void PrintCartStack(Stack S);

void AddPesanan(Stack S);

void PrintPesanan(infotype X);

void PrintCartPembeli(char idd_pembeli[3]);

void PrintCartPenjual(char idd_penjual[3]);
/*
void UpdateStatusPembayaran(char id[], char idd_penjual[], char idd_produk[]);*/

void UpdateStatusPengiriman(char idd_penjual[3]);

#endif
