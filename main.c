#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct YardimTalebi {
    int id;
    char sehir[30];
    char ihtiyac[50];
    char ad[50];
    char aciklama[200];
    char durum[50];
};

struct Gonullu {
    int id;
    char ad[50];
    char sehir[50];
};

// Global diziler
struct YardimTalebi yardimlar[MAX];
struct Gonullu gonulluler[MAX];

// Global sayaçlar
int yardimSayisi = 0;
int gonulluSayisi = 0;

// Dosyalardan verileri yükle
void verileri_yukle() {
    // Yardým taleplerini yükle
    FILE *yardimDosya = fopen("yardim_talepleri.txt", "r");
    if (yardimDosya) {
        yardimSayisi = 0;
        while (fscanf(yardimDosya, "%d\n", &yardimlar[yardimSayisi].id) == 1) {
            fgets(yardimlar[yardimSayisi].ad, sizeof(yardimlar[yardimSayisi].ad), yardimDosya);
            yardimlar[yardimSayisi].ad[strcspn(yardimlar[yardimSayisi].ad, "\n")] = '\0';

            fgets(yardimlar[yardimSayisi].sehir, sizeof(yardimlar[yardimSayisi].sehir), yardimDosya);
            yardimlar[yardimSayisi].sehir[strcspn(yardimlar[yardimSayisi].sehir, "\n")] = '\0';

            fgets(yardimlar[yardimSayisi].ihtiyac, sizeof(yardimlar[yardimSayisi].ihtiyac), yardimDosya);
            yardimlar[yardimSayisi].ihtiyac[strcspn(yardimlar[yardimSayisi].ihtiyac, "\n")] = '\0';

            fgets(yardimlar[yardimSayisi].aciklama, sizeof(yardimlar[yardimSayisi].aciklama), yardimDosya);
            yardimlar[yardimSayisi].aciklama[strcspn(yardimlar[yardimSayisi].aciklama, "\n")] = '\0';

            fgets(yardimlar[yardimSayisi].durum, sizeof(yardimlar[yardimSayisi].durum), yardimDosya);
            yardimlar[yardimSayisi].durum[strcspn(yardimlar[yardimSayisi].durum, "\n")] = '\0';

            yardimSayisi++;
            if (yardimSayisi >= MAX) break;
        }
        fclose(yardimDosya);
    }

    // Gönüllüleri yükle
    FILE *gonulluDosya = fopen("gonulluler.txt", "r");
    if (gonulluDosya) {
        gonulluSayisi = 0;
        while (fscanf(gonulluDosya, "%d\n", &gonulluler[gonulluSayisi].id) == 1) {
            fgets(gonulluler[gonulluSayisi].ad, sizeof(gonulluler[gonulluSayisi].ad), gonulluDosya);
            gonulluler[gonulluSayisi].ad[strcspn(gonulluler[gonulluSayisi].ad, "\n")] = '\0';

            fgets(gonulluler[gonulluSayisi].sehir, sizeof(gonulluler[gonulluSayisi].sehir), gonulluDosya);
            gonulluler[gonulluSayisi].sehir[strcspn(gonulluler[gonulluSayisi].sehir, "\n")] = '\0';

            gonulluSayisi++;
            if (gonulluSayisi >= MAX) break;
        }
        fclose(gonulluDosya);
    }
}

// Yardým talebi ekleme
void yardim_talebi_ekle() {
    FILE *dosya = fopen("yardim_talepleri.txt", "a");
    if (!dosya) {
        printf("Dosya acilamadi!\n");
        return;
    }

    struct YardimTalebi yeni;

    printf("\nTalep ID: ");
    scanf("%d", &yeni.id);
    getchar();

    printf("Ad: ");
    fgets(yeni.ad, sizeof(yeni.ad), stdin);
    yeni.ad[strcspn(yeni.ad, "\n")] = '\0';

    printf("Sehir: ");
    fgets(yeni.sehir, sizeof(yeni.sehir), stdin);
    yeni.sehir[strcspn(yeni.sehir, "\n")] = '\0';

    printf("Ihtiyac: ");
    fgets(yeni.ihtiyac, sizeof(yeni.ihtiyac), stdin);
    yeni.ihtiyac[strcspn(yeni.ihtiyac, "\n")] = '\0';

    printf("Aciklama: ");
    fgets(yeni.aciklama, sizeof(yeni.aciklama), stdin);
    yeni.aciklama[strcspn(yeni.aciklama, "\n")] = '\0';

    printf("Durum (Beklemede/Onaylandi/Reddedildi): ");
    fgets(yeni.durum, sizeof(yeni.durum), stdin);
    yeni.durum[strcspn(yeni.durum, "\n")] = '\0';

    fprintf(dosya, "%d\n%s\n%s\n%s\n%s\n%s\n", yeni.id, yeni.ad, yeni.sehir,
            yeni.ihtiyac, yeni.aciklama, yeni.durum);
    fclose(dosya);

    printf("Yeni yardim talebi basariyla eklendi!\n");
    verileri_yukle(); // Verileri yeniden yükle
}


void yardim_talep_listele() {
    if (yardimSayisi == 0) {
        printf("Henuz kaydedilmis bir yardim talebi yok.\n");
        return;
    }

    printf("\n-----Kaydedilen Yardim Talepleri-----\n");
    for (int i = 0; i < yardimSayisi; i++) {
        printf("ID: %d | Ad: %s | Sehir: %s | Ihtiyac: %s | Aciklama: %s | Durum: %s\n",
               yardimlar[i].id, yardimlar[i].ad, yardimlar[i].sehir,
               yardimlar[i].ihtiyac, yardimlar[i].aciklama, yardimlar[i].durum);
    }
}

void gonullu_kaydi_olustur() {
    FILE *dosya = fopen("gonulluler.txt", "a");
    if (!dosya) {
        printf("Dosya acilamadi!\n");
        return;
    }

    struct Gonullu g;

    printf("\nGonullu ID: ");
    scanf("%d", &g.id);
    getchar();

    printf("Ad: ");
    fgets(g.ad, sizeof(g.ad), stdin);
    g.ad[strcspn(g.ad, "\n")] = '\0';

    printf("Sehir: ");
    fgets(g.sehir, sizeof(g.sehir), stdin);
    g.sehir[strcspn(g.sehir, "\n")] = '\0';

    fprintf(dosya, "%d\n%s\n%s\n", g.id, g.ad, g.sehir);
    fclose(dosya);
    printf("Yeni gonullu basariyla eklendi!\n");
    verileri_yukle(); // Verileri yeniden yükle
}

void gonulluleri_listele() {
    if (gonulluSayisi == 0) {
        printf("Henuz kaydedilmis bir gonullu yok.\n");
        return;
    }

    printf("\n-----Kaydedilen Gonulluler-----\n");
    for (int i = 0; i < gonulluSayisi; i++) {
        printf("ID: %d | Ad: %s | Sehir: %s\n",
               gonulluler[i].id, gonulluler[i].ad, gonulluler[i].sehir);
    }
}

void yardim_taleplerini_eslestir() {
    if (yardimSayisi == 0 || gonulluSayisi == 0) {
        printf("Once yardim talebi ve gonullu ekleyin.\n");
        return;
    }

    printf("\n-----Yardim Talepleri ile Gonulluleri Eslestirme-----\n");
    for (int i = 0; i < yardimSayisi; i++) {
        int eslesenVar = 0;
        printf("\nYardim Talebi ID: %d, Sehir: %s, Ihtiyac: %s\n",
               yardimlar[i].id, yardimlar[i].sehir, yardimlar[i].ihtiyac);

        for (int j = 0; j < gonulluSayisi; j++) {
            if (strcmp(yardimlar[i].sehir, gonulluler[j].sehir) == 0) {
                printf(" -> Eslesen Gonullu: %s, Sehir: %s\n",
                       gonulluler[j].ad, gonulluler[j].sehir);
                eslesenVar = 1;
            }
        }
        if (!eslesenVar)
            printf(" -> Bu talep icin uygun gonullu bulunamadi.\n");
    }
}

int main() {
    int secim;

    // Program baþlangýcýnda verileri yükle
    verileri_yukle();

    while (1) {
        printf("\n-------Afet Yardim Takip Sistemine Hosgeldiniz---------\n");
        printf("1. Yardim talebi olustur\n");
        printf("2. Gonullu kaydi olustur\n");
        printf("3. Yardim taleplerini listele\n");
        printf("4. Gonulluleri listele\n");
        printf("5. Yardim talepleri ile gonulluleri eslestir\n");
        printf("6. Cikis\n");
        printf("\nSeciminiz: ");
        scanf("%d", &secim);
        getchar();

        switch (secim) {
            case 1:
                yardim_talebi_ekle();
                break;
            case 2:
                gonullu_kaydi_olustur();
                break;
            case 3:
                yardim_talep_listele();
                break;
            case 4:
                gonulluleri_listele();
                break;
            case 5:
                yardim_taleplerini_eslestir();
                break;
            case 6:
                printf("Sistemden cikiliyor...\n");
                exit(0);
            default:
                printf("Lutfen gecerli bir secim yapiniz!\n");
        }
    }

    return 0;
}
