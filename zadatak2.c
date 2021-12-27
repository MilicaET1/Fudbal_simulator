#include <stdio.h>
#include <string.h>
#define BR_KLUBOVA 10 //instancirali 10 elemenata tj da mozemo imati 10 klubova

struct Klub
{
	char ime_kluba [21];
	int tr_br_bodova;
	int br_d_golova;
	int br_p_golova;
	int br_o_ut;
	
};
struct Klub klubovi[BR_KLUBOVA]; //niz klubova i definisana vrednost koju koristimo
int br_klubova = 0; //broj unetih klubova


//da na osnovu imena pronadjemo indeks kluba
int nadji(char* ime_kluba) //funkcija nadji pronalazi klub sa odredjenim imenom
{
	for(int i=0; i<br_klubova ;i++)
	{
		if(strcasecmp(ime_kluba ,klubovi[i].ime_kluba)==0)
			return i;
	}

}
//funkcija odigraj utakmicu - za unos informacija o klubovima i golovima
void odigraj_utakmicu ()
{
	char klub_d[20];
	char klub_g[20];
	int d_golovi;
	int p_golovi;
	
	printf("Utakmica je odigrana. Unesi klubove \n");
	printf("Domacin: \n");
	scanf("%s",klub_d);
	printf("Gost: \n");
	scanf("%s", klub_g);
	printf("Broj datih golova domacina: \n");
	scanf("%d",&d_golovi);
	printf("Broj primljenih golova domacina: \n");
	scanf("%d",&p_golovi);
	

	int index_gosta;
	int index_domacina;
	
	//da bi pristupili odredjenim klubovima iz tabele
	index_gosta = nadji(klub_g);
	index_domacina = nadji(klub_d);
	
	//menjamo vrednosti golova za klubove
	klubovi[index_domacina].br_d_golova += d_golovi; //domacin
	klubovi[index_domacina].br_p_golova += p_golovi;

	klubovi[index_gosta].br_d_golova += p_golovi; //gost
	klubovi[index_gosta].br_p_golova += d_golovi;
	
	klubovi[index_domacina].br_o_ut += 1; //racuna broj odigranih utakmica
	klubovi[index_gosta].br_o_ut += 1;

	
	if(d_golovi > p_golovi)//racuna broj osvojenih bodova
	{
		klubovi[index_domacina].tr_br_bodova += 3;
		klubovi[index_gosta].tr_br_bodova += 0;
	}
	else if (d_golovi == p_golovi)
	{
		klubovi[index_domacina].tr_br_bodova += 1;
		klubovi[index_gosta].tr_br_bodova += 1;
	}
	else if (d_golovi <  p_golovi)
	{
		klubovi[index_domacina].tr_br_bodova += 0;
		klubovi[index_gosta].tr_br_bodova += 3;
	}

	
}

void sortiraj () // prati dva odvojena kluba i uporedjuje njihove bodove i/ili golove
{
	for (int i=0; i<br_klubova; i++)
	{
		for(int j=i+1; j<br_klubova; j++)
		{
			char zameniti = 0;
			int raz_golova_i = 0;
			int raz_golova_j = 0;
			//izdracunavanje golova za respektivne klubove
			raz_golova_i = klubovi[i].br_d_golova - klubovi[i].br_p_golova;
			raz_golova_j = klubovi[j].br_d_golova - klubovi[j].br_p_golova;
			
			//racuna da li treba da se zamene mesta klubova 
			if(zameniti == 0 && klubovi[i].tr_br_bodova < klubovi[j].tr_br_bodova)
			{
				zameniti = 1;
			}
			if(zameniti == 0 && klubovi[i].tr_br_bodova == klubovi[j].tr_br_bodova && raz_golova_i < raz_golova_j )
			{
				zameniti = 1;
			}

 			//zameni im mesta ako treba
			if(zameniti == 1)
			{
				struct Klub temp;
				temp = klubovi[i];
				klubovi[i] = klubovi[j];
				klubovi[j] = temp;
			}
		}
	}

}


void filtriraj()
{
	int granicni_br;
	char znak;
	printf("Unesi br boda od kojeg se pretrazuje tabela i oznaku za manje ili vece:\n");
	printf("broj, znak\n");
	scanf("%d, %c", &granicni_br, &znak);
	printf("%16s %3s %4s    %3s\n","TIM", "OS", "G", "B");
	for(int i=0; i<br_klubova ;i++)
	{
		if(znak == '<' && klubovi[i].tr_br_bodova <= granicni_br)
		{
			printf("%16s %3d %3d:%-3d %3d\n",klubovi[i].ime_kluba, klubovi[i].br_o_ut, klubovi[i].br_d_golova, klubovi[i].br_p_golova, klubovi[i].tr_br_bodova);
		}
		else if(znak == '>' && klubovi[i].tr_br_bodova >= granicni_br)
		{
			printf("%16s %3d %3d:%-3d %3d\n",klubovi[i].ime_kluba, klubovi[i].br_o_ut, klubovi[i].br_d_golova, klubovi[i].br_p_golova, klubovi[i].tr_br_bodova);
		}
		else if(znak != '<' && znak != '>')
		{
			printf("Pogresan unos!\n");
		}
	}



}




int main()
{
	// provera da li fajl postoji 
	FILE *fp; 
	fp = fopen("file.bin", "r");
	if(fp == NULL)
	{
		printf("Fajl nije napravljen.\n");
		
	}
	else
	{
		fread(klubovi,sizeof(struct Klub),BR_KLUBOVA, fp);
		fread(&br_klubova, sizeof(br_klubova), 1, fp);
		fclose(fp);
	}


	//izbor menija
	while(1)
	{	
		int izbor;
	
		printf("Opcije programa:\n");
		printf("1.Unos novog kluba\n");
		printf("2.Izlistaj podatke o klubovima\n");
		printf("3.Odigraj utakmicu\n");
		printf("4.Izadji iz programa\n");
		printf("5.Filtriranje po broju bodova\n");
		printf("------------------------------------\n");
		scanf("%d",&izbor);
		
		if(izbor == 1)
		{
			if(br_klubova == BR_KLUBOVA) // ispitujemo da li smo dosli do maksimuma
			{
				printf("------------------------------------\n");
				printf("*****Tabela je popunjena!*****\n");
				printf("------------------------------------\n");
			}
			else 
			{
				printf("Unesi ime kluba:\n");
				scanf("%s", klubovi[br_klubova].ime_kluba);
				br_klubova++;
				printf("-------------------------------------\n");
			}
		}
		else if(izbor == 2)
		{
			sortiraj();
			printf("Svi uneti klubovi:\n");
			printf("--------------------------------------\n");
			printf("%s %11s %3s %4s    %3s\n","POREDAK","TIM", "OS", "G", "B");
			for(int i = 0; i<br_klubova ;i++)
			{
				
				printf("%d. %16s %3d %3d:%-3d %3d\n",i+1,klubovi[i].ime_kluba, klubovi[i].br_o_ut, klubovi[i].br_d_golova, klubovi[i].br_p_golova, klubovi[i].tr_br_bodova);
			}
		}
		
		else if(izbor == 3)
		{
			odigraj_utakmicu();

		}
		else if(izbor == 4)
		{
			fp =fopen("file.bin", "w");
			fwrite(klubovi, sizeof(struct Klub), BR_KLUBOVA, fp);
			fwrite(&br_klubova, sizeof(br_klubova), 1, fp);
			fclose(fp);
			break;
		}
		else if(izbor == 5)
		{
			filtriraj();
		}
	}


return 0;
}


