#include "boolean.h"

#ifndef USER_H 
#define USER_H

/* Kamus Umum */

typedef struct 
{
	char id[3]; /* format 1-99*/
	char nama[5];
	int saldo;
	char password[9];
	char tipeAkun[2]; /* format 1-99*/
	int Neff;
} Tab;

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong */
void CreateEmpty (Tab *T);
/* I.S. sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */

void AddUser(Tab *T, char id[], char password[], char nama[], int saldo, char tipeAkun[]);

void AddToListUser(Tab T);

void AddToDataPribadi(Tab T);

boolean isLoginValid(char idd[], char pass[], char tipe[]);

void PrintPilihanPenjual(Tab P);

void PrintProdukPenjual(char id[]);

void TopUp(char idd[], int transaksi);

void Transaksi(char idd[], int transaksi);

void TransaksiBatal(char idd[], int transaksi);

#endif