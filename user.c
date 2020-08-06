#include "boolean.h"
#include "user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void CreateEmpty (Tab *T){
	(*T).Neff = 0;
}

void AddUser(Tab *T, char id[], char password[], char nama[], int saldo, char tipeAkun[]){
	strcpy(T->id, id);
	strcpy(T->nama, nama);
	T->saldo = saldo;
	strcpy(T->tipeAkun, tipeAkun);
	strcpy(T->password, password);
}

void AddToListUser(Tab T){
	char id[3]; /* format 01-99*/
	char nama[5];
	char saldo[100];
	char password[9];
	char tipeAkun[2]; // tipe akun pembeli atau penjual, format T (penjual) dan B (pembeli)

	strcpy(id, T.id);
	strcpy(nama, T.nama);
	sprintf(saldo, "%d", T.saldo); // mengubah tipe integer user.saldo ke array of char.
	strcpy(password, T.password);
	strcpy(tipeAkun, T.tipeAkun);

	FILE *ListUser = fopen("ListUser.txt","a+");
	fprintf(ListUser, "%s %s %s %s %s\n", id, password, nama, saldo, tipeAkun);
	fclose(ListUser);
}

void AddToDataPribadi(Tab T){
	char id[3]; /* format 01-99*/
	char password[9];
	char tipeAkun[2];

	strcpy(id, T.id);
	strcpy(password, T.password);
	strcpy(tipeAkun, T.tipeAkun);

	FILE *filename = fopen("DataPribadi.txt","a+");
	fprintf(filename, "%s %s %s\n", id, password, tipeAkun);
	fclose(filename);
}

boolean isLoginValid(char idd[], char pass[], char tipe[]){
	boolean valid;
	char id[3]; /* format 01-99*/
	char password[9];
	char tipeAkun[2];
	FILE *filename = fopen("DataPribadi.txt","r");
	
	valid = false;
	while ((!feof(filename))&&(!valid)){
		fscanf(filename, "%s %s %s\n", id, password, tipeAkun);
		if((strcmp(idd, id)==0) && (strcmp(pass, password)==0) && (strcmp(tipeAkun, tipe)==0)) {
    		valid = true;
    	}
		fflush(stdin);
		//printf("%s %s\n", id, password); 
	}
	fclose(filename);
	return (valid);
}

void PrintPilihanPenjual(Tab P){
	char id[3]; /* format 01-99*/
	char nama[5];
	char saldo[100];
	char password[9];
	char tipeAkun[2];

	FILE *ListUser = fopen("ListUser.txt","a+");
	printf("id nama\n");
	while (!feof(ListUser)){
		fscanf(ListUser, "%s %s %s %s %s\n", id, password, nama, saldo, tipeAkun);
		if(strcmp(tipeAkun, "T")==0){
			fflush(stdin);
			printf("%s %s\n", id, nama);
		} else {
			fflush(stdin);
		}
	}
}

void PrintProdukPenjual(char id[]){
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
		} else {
			fflush(stdin);
		}
	}
}

void TopUp(char idd[], int transaksi){
	Tab T;
	char saldo[100];
	char nama[5];
	char password[9];
	char tipeAkun[2];
	char id[3];
	
	FILE *in=fopen("ListUser.txt","r+");
	FILE *temp=fopen("TempData.txt","a+");
	while(!feof(in)){
		fscanf(in,"%s %s %s %s %s\n", id, password, nama, saldo, tipeAkun);
    	if (strcmp(idd,id)!=0){
      		fprintf(temp, "%s %s %s %s %s\n", id, password, nama, saldo, tipeAkun);
    	} else {
      		strcpy(T.id, id);
      		strcpy(T.password, password);
      		strcpy(T.nama, nama);
      		strcpy(T.tipeAkun, tipeAkun);
      		T.saldo = atoi(saldo);
      		T.saldo = T.saldo + transaksi;
      		sprintf(saldo, "%d", T.saldo);
      		fprintf(temp, "%s %s %s %s %s\n", T.id, T.password, T.nama, saldo, T.tipeAkun);
      		printf("TOP UP SUCCESSFULLY\n");
    	}
  	}
	fclose(in);
  	fclose(temp);
  	remove("ListUser.txt");
  	rename("TempData.txt","ListUser.txt");   
}

void Transaksi(char idd[], int transaksi){
	Tab T;
	char saldo[100];
	char nama[5];
	char password[9];
	char tipeAkun[2];
	char id[3];
	
	FILE *in=fopen("ListUser.txt","r+");
	FILE *temp=fopen("TempData.txt","a+");
	while(!feof(in)){
		fscanf(in,"%s %s %s %s %s\n", id, password, nama, saldo, tipeAkun);
		if (strcmp(idd,id)!=0){
      			fprintf(temp, "%s %s %s %s %s\n", id, password, nama, saldo, tipeAkun);
    	} else {
			T.saldo = atoi(saldo);
			if (T.saldo < transaksi){
				printf("Saldo tidak mencukupi, silahkan TOP UP terlebih dahulu\n");
				printf("ketik TUNDA untuk menunda pembayaran\n");
				sprintf(saldo, "%d", T.saldo);
      			fprintf(temp, "%s %s %s %s %s\n", id, password, nama, saldo, tipeAkun);
			} else if (T.saldo >= transaksi){
				T.saldo = T.saldo - transaksi;
				strcpy(T.id, id);
      			strcpy(T.password, password);
      			strcpy(T.nama, nama);
      			strcpy(T.tipeAkun, tipeAkun);
      			sprintf(saldo, "%d", T.saldo);
      			fprintf(temp, "%s %s %s %s %s\n", T.id, T.password, T.nama, saldo, T.tipeAkun);
      			printf("PEMBAYARAN BERHASIL\n");
      			printf("ketik BAYAR untuk menyimpan status pembayaran\n");
			}
		}
  	}
	fclose(in);
  	fclose(temp);
  	remove("ListUser.txt");
  	rename("TempData.txt","ListUser.txt");   
}

void TransaksiBatal(char idd[], int transaksi){
	Tab T;
	char saldo[100];
	char nama[5];
	char password[9];
	char tipeAkun[2];
	char id[3];
	
	FILE *in=fopen("ListUser.txt","r+");
	FILE *temp=fopen("TempData.txt","a+");
	while(!feof(in)){
		fscanf(in,"%s %s %s %s %s\n", id, password, nama, saldo, tipeAkun);
		if (strcmp(idd,id)!=0){
      			fprintf(temp, "%s %s %s %s %s\n", id, password, nama, saldo, tipeAkun);
    	} else {
			T.saldo = atoi(saldo);
			T.saldo = T.saldo + transaksi;
			strcpy(T.id, id);
   			strcpy(T.password, password);
   			strcpy(T.nama, nama);
   			strcpy(T.tipeAkun, tipeAkun);
   			sprintf(saldo, "%d", T.saldo);
   			fprintf(temp, "%s %s %s %s %s\n", T.id, T.password, T.nama, saldo, T.tipeAkun);
			}
		}
	fclose(in);
  	fclose(temp);
  	remove("ListUser.txt");
  	rename("TempData.txt","ListUser.txt");   
}