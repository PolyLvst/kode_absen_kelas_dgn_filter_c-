#include <iostream>
#include<windows.h>
using namespace std;
string KelasPilihan;
string namaKelas[][3]={{"Jotaro","10","RPL"},{"Joestar","10","RPL"},{"Jonathan","11","RPL"},{"Josuke","10","RPL"},{"Joe","11","RPL"},{"Kujo","11","RPL"},{"Jeremy","12","RPL"},{"Josua","12","RPL"},{"Joker","12","RPL"},{"Jokowi","11","RPL"}};
int absen[]={1,2,3,4,5,6,7,8,9,10};
int nilaiA_B[][2]={{80,85},{79,75},{92,89},{80,85},{79,75},{92,89},{90,80},{88,86},{70,77},{100,100}};
int lengthArray=sizeof(nilaiA_B)/sizeof(nilaiA_B[0]);
int i,j,k,PosAkhirY;
//ASCII code Horizontal = 205 Vertikal = 186
int H=205,V=186,AtasKiri=201,BawahKiri=200,AtasKanan=187,BawahKanan=188,SimpangTigaAtas=203,SimpangTigaBawah=202;

//Gotoxy untuk menaruh posisi cursor
void gotoxy(short x, short y){
	//set cursor position at certain coordinate
	COORD coord={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
//Untuk menaruh kode ASCII
void PutChar(byte porosX,byte porosY,int KodeASCII){
	gotoxy(porosX,porosY);printf("%c",KodeASCII);
}
//Untuk mencetak tabel
void cetakTabel(){
	i=1;
	while(i<=59){//Saat posisi tabel telah mencapai 59 maka berhenti mencetak garis horizontal
		PutChar(i,1,H);
		PutChar(i,PosAkhirY,H);
		i++;
	}
	j=1;
	while(j<=PosAkhirY){//Saat posisi tabel telah mencapai posisi paling bawah maka berhenti mencetak garis vertikal
		PutChar(i,j,V);
		PutChar(1,j,V);
		PutChar(6,j,V);PutChar(18,j,V);PutChar(27,j,V);PutChar(38,j,V);PutChar(48,j,V);
		j++;
	}
	//Mencetak pojok tabel
	PutChar(1,1,AtasKiri);PutChar(1,PosAkhirY,BawahKiri);
	PutChar(i,1,AtasKanan);PutChar(i,PosAkhirY,BawahKanan);
	//Mencetak persimpangan tabel
	PutChar(6,1,SimpangTigaAtas);PutChar(18,1,SimpangTigaAtas);PutChar(27,1,SimpangTigaAtas);PutChar(38,1,SimpangTigaAtas);PutChar(48,1,SimpangTigaAtas);
	PutChar(6,PosAkhirY,SimpangTigaBawah);PutChar(18,PosAkhirY,SimpangTigaBawah);PutChar(27,PosAkhirY,SimpangTigaBawah);PutChar(38,PosAkhirY,SimpangTigaBawah);PutChar(48,PosAkhirY,SimpangTigaBawah);
}
//Untuk mencetak judul
void header(){
	gotoxy(3,2);cout<<"No";
	gotoxy(8,2);cout<<"Nama";
	gotoxy(20,2);cout<<"Kelas";
	gotoxy(30,2);cout<<"Nilai 1";
	gotoxy(40,2);cout<<"Nilai 2";
	gotoxy(50,2);cout<<"Rata-rata";
}
//Menghitung rata rata
int hitungRataRata(int indexSiswa){
	float hasilRerata;
	for (j=0;j<2;j++){
		hasilRerata+=nilaiA_B[indexSiswa][j];//Menjumlahkan semua nilai
	}
	return hasilRerata/2;//Jumlah dibagi dua, hasilnya dibagi dua lalu di return alias di kembalikan kepada pemanggil fungsi
}
//Menampilkan isi tabel
void tampilkanData(string Filter){
	PosAkhirY=3;//Memberi tahu kalau posisi terakhir yang ingin dicetak adalah sekian
	int PosY_DalamTabel=3;//Untuk menempatkan posisi akhir data yang dicetak
		for (i=0;i<lengthArray;i++){
			if(Filter=="all"||Filter==namaKelas[i][1]){//Jika filternya all atau sesuai dengan nama kelas maka tampilkan data
				int DataPorosX=8;
				for (j=0;j<3;j++){		
					gotoxy(DataPorosX,PosY_DalamTabel);cout<<namaKelas[i][j];
					if (j==1)DataPorosX+=3;	//Menaruh posisi kursor ke depan nama dan seterusnya
					else DataPorosX+=12;
				}
				DataPorosX=30;
				for (k=0;k<2;k++){
					gotoxy(DataPorosX,PosY_DalamTabel);cout<<nilaiA_B[i][k];
					DataPorosX+=10;//Menaruh posisi kursor ke depan nama dan seterusnya
				}
				gotoxy(DataPorosX,PosY_DalamTabel);cout<<hitungRataRata(i);//Menampilkan rata rata nilai siswa tersebut
				gotoxy(2,PosY_DalamTabel);cout<<absen[i]<<".";//Tampilkan absen
				PosAkhirY++;//Memberi tahu kalau posisi terakhir cursor sekian
				PosY_DalamTabel++;	//Menaruh posisi cursor di bawah data siswa yang telah di tampilkan
			} else if (Filter!=namaKelas[i][1]){//Jika filter tidak cocok maka skip pengulangan kali ini
				continue;
			}	
		}
}
//Menghapus semua yang telah ditampilkan
void clearTabel(){
	for(i=0;i<=66;i++){//Menghapus sampai posisi paling kanan dengan batas sekian
		for(j=0;j<=PosAkhirY+2;j++){//Menghapus sampai posisi paling bawah dengan batas sekian
			PutChar(i,j,0);
		}
	}	
}
int main(){
	header();//Memanggil fungsi tersebut untuk menampilkan judul
	tampilkanData("all");//Memanggil fungsi tersebut untuk menampilkan semua data yang tersedia
	cetakTabel();//Memanggil fungsi tersbut untuk mencetak tabel
	gotoxy(0,PosAkhirY+1);cout<<"[* untuk keluar] Pilih kelas diatas yang hanya ingin ditampilkan : ";
	gotoxy(0,PosAkhirY+2);cout<<"[ketik all untuk mereset]";
	do{
		gotoxy(67,PosAkhirY+1);cin>>KelasPilihan;
		gotoxy(67,PosAkhirY+1);cout<<"     ";
		for (i=0;i<lengthArray;i++){
			if (KelasPilihan==namaKelas[i][1]){
				clearTabel();
				header();
				tampilkanData(KelasPilihan);
				cetakTabel();
				gotoxy(0,PosAkhirY+1);cout<<"[* untuk keluar] Pilih kelas diatas yang hanya ingin ditampilkan : ";	
				gotoxy(0,PosAkhirY+2);cout<<"[ketik all untuk mereset]";
			} else if (KelasPilihan=="all"){
				clearTabel();
				header();
				tampilkanData("all");
				cetakTabel();
				gotoxy(0,PosAkhirY+1);cout<<"[* untuk keluar] Pilih kelas diatas yang hanya ingin ditampilkan : ";	
				gotoxy(0,PosAkhirY+2);cout<<"[ketik all untuk mereset]";
			}
		}
	}while(KelasPilihan!="*");  
	gotoxy(0,PosAkhirY+3);cout<<"By Hudman H.A.";
}		