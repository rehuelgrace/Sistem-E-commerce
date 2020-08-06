#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cart.h"

/* Prototype manajemen memori */
void AlokasiC (address *P, infotype X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
{
    /* Algoritma */
    (*P) = (ElmtStack *) malloc (sizeof (ElmtStack));
    if ((*P) != NULL) {
        Info(*P) = X;
        Next(*P) = Nil;
    }
    else {
        (*P) = Nil;
    }
}
void DealokasiC (address P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */ 
{
    free(P);
}

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean IsEmptyC (Stack S)
/* Mengirim true jika Stack kosong: TOP(S) = Nil */
{
    return(Top(S) == Nil);
}
void CreateEmptyC (Stack * S)
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stack S yang kosong */
{
    Top(*S) = Nil;
}
void Push (Stack * S, infotype X)
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
{
    /* Kamus */
    address P;
    /* Algoritma */
    AlokasiC(&P,X);
    if (P != Nil) {
        Next(P) = Top(*S);
        Top(*S) = P;
    }
}
void Pop (Stack * S, infotype * X)
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
{
    /* Kamus */
    address P;
    /* Algoritma */
    P = Top(*S);
    Top(*S) = Next(Top(*S));
    Next(P) = Nil;
    (*X) = Info(P);
    DealokasiC(P);
}

void PrintCartStack(Stack S){
    //infoCart X;
    address P;

    if(Top(S)==Nil){
        printf("cart kosong.\n");
    } else {
        P = Top(S);
        printf("id_produk id_pembeli id_penjual harga jumlah_barang total status\n");
        do{
            printf("%s %s %s %d %d %d %s\n", Info(P).id_produk, Info(P).id_pembeli, Info(P).id_penjual, Info(P).harga, Info(P).jumlah_barang, Info(P).total, Info(P).status);
            P = Next(P);
        }while (!(P==Nil));
    }
}

void AddPesanan(Stack S){
    address P;

    FILE *pesanan = fopen("Pesanan.txt","a+");
    P = Top(S);
    while (P != Nil){
        fprintf(pesanan, "%s %s %s %d %d %d %s\n", Info(P).id_produk, Info(P).id_pembeli, Info(P).id_penjual, Info(P).harga, Info(P).jumlah_barang, Info(P).total, Info(P).status);
        P = Next(P);
    }
    fclose(pesanan);
}

void PrintPesanan(infotype X){
    printf("-----------------------------------------------------------------\n");
    printf("id_produk id_pembeli id_penjual harga jumlah_barang total\n");
    printf("%s %s %s %d %d %d\n", X.id_produk, X.id_pembeli, X.id_penjual, X.harga, X.jumlah_barang, X.total);
    printf("-----------------------------------------------------------------\n");
}

void PrintCartPembeli(char idd_pembeli[3]){
    char id_produk[3];
    char id_pembeli[3];
    char id_penjual[3];
    char harga[999];
    char jumlah_barang[999];
    char total[999];
    char status[999];

    FILE *pesanan = fopen("Pesanan.txt","r+");
    printf("id_produk id_pembeli id_penjual harga jumlah_barang total status\n");
    while (!feof(pesanan)){
        fscanf(pesanan, "%s %s %s %s %s %s %s\n", id_produk, id_pembeli, id_penjual, harga, jumlah_barang, total, status);
        if (strcmp(idd_pembeli,id_pembeli)==0){
            fflush(stdin);
            printf("%s %s %s %s %s %s %s\n", id_produk, id_pembeli, id_penjual, harga, jumlah_barang, total, status);
        }
    }
}

void PrintCartPenjual(char idd_penjual[3]){
    char id_produk[3];
    char id_pembeli[3];
    char id_penjual[3];
    char harga[999];
    char jumlah_barang[999];
    char total[999];
    char status[999];

    FILE *pesanan = fopen("Pesanan.txt","r+");
    printf("id_produk id_pembeli id_penjual harga jumlah_barang total status\n");
    while (!feof(pesanan)){
        fscanf(pesanan, "%s %s %s %s %s %s %s\n", id_produk, id_pembeli, id_penjual, harga, jumlah_barang, total, status);
        if (strcmp(idd_penjual,id_penjual)==0){
            fflush(stdin);
            printf("%s %s %s %s %s %s %s\n", id_produk, id_pembeli, id_penjual, harga, jumlah_barang, total, status);
        }
    }
}

/*void UpdateStatusPembayaran(char id[], char idd_penjual[], char idd_produk[]){
    char id_produk[3];
    char id_pembeli[3];
    char id_penjual[3];
    char harga[999];
    char jumlah_barang[999];
    char total[999];
    char status[999];
    
    FILE *in=fopen("Pesanan.txt","r");
    FILE *temp=fopen("TempPesanan.txt","a+");
    while(!feof(in)){
        fscanf(in,"%s %s %s %s %s %s %s\n", id_produk, id_pembeli, id_penjual, harga, jumlah_barang, total, status);
        if ((strcmp(id_pembeli,id)!=0)||(strcmp(id_penjual,idd_penjual)!=0)||(strcmp(id_produk,idd_produk)!=0)){
            fprintf(temp, "%s %s %s %s %s %s %s\n", id_produk, id, id_penjual, harga, jumlah_barang, total, status);
        } else if ((strcmp(id_pembeli,id)==0)&&(strcmp(id_penjual,idd_penjual)==0)&&(strcmp(id_produk,idd_produk)==0)){
            strcpy(status, "BAYAR");
            fprintf(temp, "%s %s %s %s %s %s %s\n", id_produk, id, id_penjual, harga, jumlah_barang, total, status);
            printf("Pembayaran Sukses\n");
        }
    }
    fclose(in);
    fclose(temp);
    remove("Pesanan.txt");
    rename("TempPesanan.txt","Pesanan.txt");   
}*/

void UpdateStatusPengiriman(char idd_penjual[3]){
    char status_pengiriman[999];
    char id_produk[3];
    char id_pembeli[3];
    char id_penjual[3];
    char harga[999];
    char jumlah_barang[999];
    char total[999];
    char status[999];

    FILE *pesanan = fopen("Pesanan.txt","r+");
    FILE *pengiriman = fopen("Pengiriman.txt","a+");
    while (!feof(pesanan)){
        fscanf(pesanan, "%s %s %s %s %s %s %s\n", id_produk, id_pembeli, id_penjual, harga, jumlah_barang, total, status);
        /*if ((strcmp(id_pembeli,id)!=0)||(strcmp(id_penjual,idd_penjual)!=0)||(strcmp(id_produk,idd_produk)!=0)){*/
            if(strcmp(status,"BAYAR")==0){
                strcpy(status_pengiriman, "DIKIRIM");
            } else if (strcmp(status,"TUNDA")==0){
                strcpy(status_pengiriman, "MENUNGGU PEMBAYARAN");
            }
            fprintf(pengiriman, "%s %s %s %s %s %s %s %s\n", id_produk, id_pembeli, id_penjual, harga, jumlah_barang, total, status, status_pengiriman);
        //}
    }
    fclose(pesanan);
    fclose(pengiriman);
}