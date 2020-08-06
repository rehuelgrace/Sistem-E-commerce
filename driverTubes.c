#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user.h"
#include "boolean.h"
#include "produk.h"
#include "cart.h"
//#include "pengiriman.h"

void Menu(){
/* Menampilkan menu awal. */
	printf("********************************************************************\n");
	printf("Selamat datang!\n");
	printf("Silahkan LOGIN atau DAFTAR terlebih dahulu.\n");
	printf("1. Ketik LOGIN untuk login ke akun Anda.\n");
	printf("2. Ketik DAFTAR jika Anda belum memiliki akun.\n");
	printf("3. Ketik EXIT jika Anda ingin keluar dari program.\n");
	printf("********************************************************************\n");
}

void PilihanTipeAkun(){
	printf("Mau login/daftar sebagai apa?\n");
	printf("1. Ketik PEMBELI untuk login / daftar sebagai pembeli.\n");
	printf("2. Ketik PENJUAL untuk login / daftar sebagai penjual.\n");
}

void MenuPenjual(){
	/* Menampilkan tampilan menu di penjual. */
	printf("********************************************************************\n");
	printf("Selamat datang di toko Anda!\n");
	printf("Anda dapat melakukan hal dibawah ini.\n");
	printf("1. ADD PRODUK untuk menambahkan produk ke akun Anda.\n");
	printf("2. DAFTAR PRODUK untuk mengecek list produk Anda.\n");
	printf("3. DAFTAR PESANAN untuk mengecek list pembayaran produk Anda.\n");
	printf("4. EXIT jika Anda ingin logout dari akun Anda.\n");
	printf("********************************************************************\n");
}

void MenuPembeli(){
	/* Menampilkan tampilan menu di pembeli. */
	printf("********************************************************************\n");
	printf("Selamat datang di akun Anda!\n");
	printf("Anda dapat melakukan hal dibawah ini.\n");
	printf("1. ADD PRODUK untuk menambahkan produk ke keranjang Anda.\n");
	printf("2. CHECKOUT untuk mengecek list pesanan Anda.\n");
	printf("3. TOPUP jika Anda ingin topup saldo akun Anda.\n");
	printf("4. EXIT jika Anda ingin logout dari akun Anda.\n");
	printf("********************************************************************\n");
}

int main(){
	Tab LU;
	Produk LP;
	char inputLOGIN[] = "LOGIN";
	char inputDAFTAR[] = "DAFTAR";
	char inputEXIT[] = "EXIT";
	char inputPEMBELI[] = "PEMBELI";
	char inputPENJUAL[] = "PENJUAL";
	//char inputY[] = "Y";
	//char inputN[] = "N";
	char state[100];
	char id[100];
	char pass[100];
	char nama[100];
	int saldo, harga, stock, nominal;
	char tipeAkun[2];
	boolean exit;
	char id_produk[100];
	char id_penjual[100];
	char nama_produk[100];
	char kategori[100];
	infotype X;
	Stack C;

	CreateEmpty(&LU);
	CreateEmptyP(&LP);
	CreateEmptyC(&C);
	Menu();
	while (!exit){
		do {
			printf(">>> DAFTAR / LOGIN / EXIT: ");
			scanf("%s", &state);
		} while ((strcmp(state,inputLOGIN)!=0)&&(strcmp(state,inputDAFTAR)!=0)&&(strcmp(state,inputEXIT)!=0));
		//(strcmp(state,inputLOGIN)==0) or (strcmp(state,inputDAFTAR)==0) or (strcmp(state,inputEXIT)==0)
		if(strcmp(state,inputLOGIN)==0){ //login
			PilihanTipeAkun(); //pilihan login sebagai penjual atau pembeli
			do {
				printf(">>> PEMBELI / PENJUAL: ");
				scanf("%s", &state);
			} while ((strcmp(state,inputPEMBELI)!=0)&&(strcmp(state,inputPENJUAL)!=0)); //bakal diulang minta input kalau tidak sesuai
			if(strcmp(state,inputPEMBELI)==0){
				printf("id: ");
				scanf("%s", &id);
				printf("password: ");
				scanf("%s", &pass);
				if((isLoginValid(id,pass,"P"))){
					printf("Login sebagai pembeli berhasil.\n");
					MenuPembeli();
					do {
						printf(">>> INPUT 1 / 2 / 3 / 4: ");
						scanf("%s", &state);
						if (strcmp(state,"1")==0){
							PrintAllProduk(LP);
							do{
								printf("Tambahkan ke keranjang / Hapus barang / Simpan pesanan? (TAMBAH / HAPUS / SIMPAN): "); //JIKA MILIH HAPUS, ASUMSI LISTCART SUDAH TERISI
								scanf("%s", &state);
								if (strcmp(state,"TAMBAH")==0) {
									printf("Input ID Produk yang ingin ditambahkan ke keranjang: ");
									scanf("%s", &X.id_produk);
									printf("Input ID penjual: ");
									scanf("%s", &X.id_penjual);
									printf("Harga per satuan: ");
									scanf("%d", &X.harga);
									printf("Jumlah yang ingin dibeli: ");
									scanf("%d", &X.jumlah_barang);
									X.total = (X.harga * X.jumlah_barang);
									printf("Total Pesanan: %d\n", X.total);
									printf("Input ID Anda: ");
									scanf("%s", &X.id_pembeli);
									PrintPesanan(X);
									do{
										printf("Ketik BAYAR untuk melanjutkan: ");
										scanf("%s", &state);
									} while (strcmp(state, "BAYAR")!=0);
									if (strcmp(state, "BAYAR")==0){
										Transaksi(id, X.total);
										scanf("%s", &X.status);
									}
									Push(&C, X);
									printf("Belanjaan berhasil di tambahkan.\n");
								} else if (strcmp(state,"HAPUS")==0){ //HAPUS ATAU UNDO BISA JUGA MEMBATALKAN PESANAN
									Pop(&C,&X);
									printf("Input ID Anda: ");
									scanf("%s", &id);
									printf("Total transaksi: ");
									scanf("%d", &nominal);
									TransaksiBatal(id, nominal);
									printf("Belanjaan berhasil di hapus.\n");
								} else if (strcmp(state,"SIMPAN")==0){
									AddPesanan(C);
									printf("Daftar belanjaan berhasil di simpan. Silahkan tunggu pengiriman apabila sudah membayar\n");
								}
							} while ((strcmp(state,"TAMBAH")!=0)&&(strcmp(state,"HAPUS")!=0)&&(strcmp(state,"SIMPAN")!=0));
						} else if (strcmp(state,"2")==0){
							PrintCartPembeli(id);
							/*do{
								printf("Ingin melakukan pembayaran? (Y/N): ");
								scanf("%s", &state);
							}while ((strcmp(state,"Y")==0)&&(strcmp(state,"N")==0));
							if (strcmp(state,"Y")==0){
								printf("Input ID Anda: ");
								scanf("%s", &id);
								printf("Input ID penjual: ");
								scanf("%s", &id_penjual);
								printf("Input ID produk yang dipesan: ");
								scanf("%s", &id_produk);
								printf("Total transaksi: ");
								scanf("%d", &nominal);
								Transaksi(id, nominal);
								UpdateStatusPembayaran(id, id_penjual, id_produk);
							} else if (strcmp(state,"N")==0){
								break;
							}*/
						} else if (strcmp(state,"3")==0){
							//Dapat melakukan topup
							printf("ID Anda: ");
							scanf("%s", &id);
							printf("Nominal: ");
							scanf("%d", &nominal);
							TopUp(id, nominal);
						} else if (strcmp(state,"4")==0){
							printf("Terima kasih!");
							exit = true;
						}
					} while ((strcmp(state,"1")!=0)&&(strcmp(state,"2")!=0)&&(strcmp(state,"3")!=0)&&(strcmp(state,"4")!=0));
				} else
					printf("Cek ulang id dan password Anda.\n");
			} else if(strcmp(state,inputPENJUAL)==0){ //penjual
				printf("id: ");
				scanf("%s", &id);
				printf("password: ");
				scanf("%s", &pass);
				if((isLoginValid(id,pass,"T"))){
						printf("Login sebagai penjual berhasil.\n");
						MenuPenjual();
						do {
							printf(">>> INPUT 1 / 2 / 3 / 4 : ");
							scanf("%s", &state);
							if (strcmp(state,"1")==0) {
								printf("Masukkan id produk (2 digit, format P1-P9): ");
								scanf("%s", &id_produk);
								printf("Masukkan id penjual (2 digit angka, format 01-99): ");
								scanf("%s", &id);
								printf("Masukkan nama produk (max 4 karakter): ");
								scanf("%s", &nama_produk);
								printf("Masukkan kategori produk (2 digit, format K1-K9): ");
								scanf("%s", &kategori);
								printf("Masukkan harga produk: ");
								scanf("%d", &harga);
								AddProduk(&LP, id_produk, id, nama_produk, harga, kategori); 
								AddToDataProduk(LP);
								printf("Produk berhasil ditambahkan.\n");
							} else if (strcmp(state,"2")==0) {
								PrintProduk(LP, id);
							} else if (strcmp(state,"3")==0) {
								UpdateStatusPengiriman(id);
							} else if (strcmp(state,"4")==0) {
								printf("Terima kasih!");
								exit = true;
							}
						} while ((strcmp(state,"1")!=0)&&(strcmp(state,"2")!=0)&&(strcmp(state,"3")!=0)&&(strcmp(state,"4")!=0));
				} else
					printf("Cek ulang id dan password Anda.\n");
			}
		} else if(strcmp(state,inputDAFTAR)==0){ //daftar
				printf("Masukkan id (2 digit angka, format 01-99): ");
				scanf("%s", &id);
				printf("Masukkan password (8 karakter): ");
				scanf("%s", &pass);
				printf("Masukkan nama (max 4 karakter): ");
				scanf("%s", &nama);
				printf("Masukkan saldo awal: ");
				scanf("%d", &saldo);
				printf("Mendaftar sebagai apa? P (Pembeli) / T (Penjual): ");
				scanf("%s", &tipeAkun);
				AddUser(&LU, id, pass, nama, saldo, tipeAkun); 
				AddToListUser(LU); //masukin data ke file eksternal List User sebagai backup seluruh data format id, password, nama, saldo, tipeAkun
				AddToDataPribadi(LU);
				printf("Pendaftaran akun sukses.\n");
		} else if(strcmp(state,inputEXIT)==0){
			printf("Terima kasih!");
			exit = true;
		}
	}
	return 0;
}