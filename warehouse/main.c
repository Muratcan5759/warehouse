#include <stdio.h>
#include <stdlib.h>



float maliyetHesapla(int depoSayisi, int musteriSayisi, int val[], float wt[], float seyahatMasraflari[][depoSayisi], int MurunAdet[])
{
    int musteridepolari[musteriSayisi];
    int depodurumlar[depoSayisi];

    memset(depodurumlar, 0, depoSayisi * sizeof(depodurumlar[0]));
    memset(musteridepolari, -1, musteriSayisi * sizeof(musteridepolari[0]));



    float optimumHesap = 0;

    for(int m = 0; m< musteriSayisi; m++)
    {
        int alinanDepo = -1;
        float olanMaliyet = 1000000000.0f;

        for (int d = 0; d<depoSayisi; d++)
        {

            if(val[d] < MurunAdet[m])
                continue;


            float tempMaliyet = 0;

            if(depodurumlar[d] == 0)
                tempMaliyet += wt[d];

            tempMaliyet += seyahatMasraflari[m][d];

            if( tempMaliyet < olanMaliyet)
            {
                olanMaliyet = tempMaliyet;
                alinanDepo = d;
            }

        }

        musteridepolari[m] = alinanDepo;

        optimumHesap += seyahatMasraflari[m][alinanDepo];
        val[alinanDepo] -= MurunAdet[m];


        if(depodurumlar[alinanDepo] == 0){
             depodurumlar[alinanDepo] = 1;
             optimumHesap += wt[alinanDepo];

        }

    }

    printf("\nSONUC: %f\n\n", optimumHesap);
    for(int m=0; m<musteriSayisi; m++)
    {
        printf("  %d", musteridepolari[m]);

    }


}


void CalistirHesaplayici(char* dosyaYolu)
{
    FILE* file = fopen (dosyaYolu, "r");

    if (file == NULL)
    {
      printf ("Dosya Bulunamadi.");
      return 1;
    }

    int depSayisi, musteriSayisi;
    int i = 0;
    /*ilk satirin ilk sutununu */
    fscanf (file, "%d", &i);
    depSayisi = i;
    /*ilk satirin ikinci sutunu  */
    fscanf(file, "%d\n", &i);
    musteriSayisi = i;

    int val[depSayisi]; //depo kapasieleri
    //int *val = calloc(depSayisi+1, sizeof*val);
    float wt[depSayisi]; // depo maliyetleri
    //float *wt = calloc(depSayisi+1, sizeof*wt);
    //float seyahatMasraflari[musteriSayisi][depSayisi];
    //float (*seyahatMasraflari)[musteriSayisi] = calloc(depSayisi+1, sizeof*seyahatMasraflari);
    int (*seyahatMasraflari)[depSayisi] = calloc(musteriSayisi, sizeof*seyahatMasraflari);

    int MurunAdet[musteriSayisi]; //musteri talepleri
    //int *MurunAdet = calloc(musteriSayisi+1, sizeof*MurunAdet);
    int j = 0;


    for (j = 0; j<depSayisi; j++)
    {
        fscanf(file, "%d", &i);
        val[j] = i;

        float tmp =0;
        fscanf(file, "%f", &tmp);
        wt[j] = tmp;

        //printf("%d\n");
    }


    float temp=0;
    for(int m = 0; m < musteriSayisi ; m++){

        fscanf(file, "%f", &temp);
        MurunAdet[m] = temp;


        for (int d =0; d< depSayisi; d++)
        {
            fscanf(file,"%f", &seyahatMasraflari[m][d]);
        }


    }



    fclose(file);



    maliyetHesapla(depSayisi, musteriSayisi, val, wt, seyahatMasraflari,MurunAdet);
}

int main()
{

    CalistirHesaplayici("wl_50_1");
    printf("\n\n----------\n\n");

    CalistirHesaplayici("wl_200_5");
    printf("\n\n----------\n\n");

    CalistirHesaplayici("wl_1000_1");
    printf("\n\n----------\n\n");
    // ----------------------------------------------------------------- //





    return 0;
}
