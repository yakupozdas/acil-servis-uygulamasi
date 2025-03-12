#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Hasta bilgileri icin struct tan�m�
typedef struct Hasta {
    char ad[50];
    char soyad[50];
    char tcNo[12];
    int yas;
    char cinsiyet;
    char sikayet[100];
    int oncelik;   // 1: Kritik, 2: Oncelikli, 3: Normal
    char receteNo[15];
    char adres[100];
    char telefonNo[20];
    char alerji[100];
    int buyukTansiyon;
    int kucukTansiyon;
    float ates;
    char atesDerecesi[20];
    char buyukTansiyonDerecesi[20];
    char kucukTansiyonDerecesi[20];
    struct Hasta *sonraki;
} Hasta;

// Bagli listenin baslangici
Hasta *ilk = NULL;

// Triaj de�erlendirme fonksiyonu
int triajDegerlendir(char *sikayet) {
    if (strstr(sikayet, "kalp krizi") || strstr(sikayet, "nefes darli�i"))
        return 1;
    else if (strstr(sikayet, "kirik") || strstr(sikayet, "siddetli a�ri"))
        return 2;
    else
        return 3;
}

// Rastgele recete numarasi olusturma fonksiyonu
void receteNoOlustur(char *receteNo) {
    sprintf(receteNo, "RX-%d", rand() % 1000000);
}

// Ates derecesini belirleme fonksiyonu
// <38.0 => Normal, 38.0-39.9 => Yuksek, >=40.0 => Havale
void atesDerecelendir(Hasta *hasta) {
    if (hasta->ates < 38.0)
        strcpy(hasta->atesDerecesi, "Normal");
    else if (hasta->ates >= 38.0 && hasta->ates < 40.0)
        strcpy(hasta->atesDerecesi, "Yuksek");
    else
        strcpy(hasta->atesDerecesi, "Havale");
}

// Tansiyon derecelendirmesi fonksiyonu
// Kucuk tansiyon: <6.0 => Dusuk, 6.0-8.0 => Normal, >8.0 => Yuksek
// Buyuk tansiyon: <9.0 => Dusuk, 9.0-12.0 => Normal, >12.0 => Yuksek
void tansiyonDerecelendir(Hasta *hasta) {
    if (hasta->kucukTansiyon < 6.0)
        strcpy(hasta->kucukTansiyonDerecesi, "Du�uk");
    else if (hasta->kucukTansiyon <= 8.0)
        strcpy(hasta->kucukTansiyonDerecesi, "Normal");
    else
        strcpy(hasta->kucukTansiyonDerecesi, "Yuksek");

    if (hasta->buyukTansiyon < 9.0)
        strcpy(hasta->buyukTansiyonDerecesi, "Du�uk");
    else if (hasta->buyukTansiyon <= 12.0)
        strcpy(hasta->buyukTansiyonDerecesi, "Normal");
    else
        strcpy(hasta->buyukTansiyonDerecesi, "Yuksek");
}
// Yeni hasta ekleme fonksiyonu
void hastaEkle(char *ad, char *soyad, char *tcNo, int yas, char cinsiyet, char *sikayet, char *adres, 
               char *telefonNo, char *alerji, int buyukTansiyon, int kucukTansiyon, float ates) {
    Hasta *yeni = (Hasta *)malloc(sizeof(Hasta));
    strcpy(yeni->ad, ad);
    strcpy(yeni->soyad, soyad);
    strcpy(yeni->tcNo, tcNo);
    yeni->yas = yas;
    yeni->cinsiyet = cinsiyet;
    strcpy(yeni->sikayet, sikayet);
    yeni->oncelik = triajDegerlendir(sikayet);
    receteNoOlustur(yeni->receteNo);
    strcpy(yeni->adres, adres);
    strcpy(yeni->telefonNo, telefonNo);
    strcpy(yeni->alerji, alerji);
    yeni->buyukTansiyon = buyukTansiyon;
    yeni->kucukTansiyon = kucukTansiyon;
    yeni->ates = ates;
    atesDerecelendir(yeni);
    tansiyonDerecelendir(yeni);
    yeni->sonraki = NULL;
    
    // Triaj oncelik sirasina g�re ekleme
    if (ilk == NULL || yeni->oncelik < ilk->oncelik) {
        yeni->sonraki = ilk;
        ilk = yeni;
    } else {
        Hasta *temp = ilk;
        while (temp->sonraki != NULL && temp->sonraki->oncelik <= yeni->oncelik)
            temp = temp->sonraki;
        yeni->sonraki = temp->sonraki;
        temp->sonraki = yeni;
    }
}
int main() {
    srand(time(NULL));  // Rastgele sayi ureticisini ba�lat
    
    char devam = 'E';  // Hasta ekleme dongusunu kontrol eder
    
    while (devam == 'E' || devam == 'e') {
        char ad[50], soyad[50], tcNo[12], sikayet[100], adres[100], telefonNo[20], alerji[100];
        int yas, buyukTansiyon, kucukTansiyon;
        char cinsiyet;
        float ates;
        
        // Kullanicidan hasta bilgilerini al
        printf("\nHasta bilgilerini girin:\n");
        
        printf("Ad: ");
        fgets(ad, sizeof(ad), stdin);
        ad[strcspn(ad, "\n")] = '\0';  // Yeni satir karakterini kaldir
        
        printf("Soyad: ");
        fgets(soyad, sizeof(soyad), stdin);
        soyad[strcspn(soyad, "\n")] = '\0';  // Yeni sat�r karakterini kaldir
        
        printf("TC Kimlik No: ");
        fgets(tcNo, sizeof(tcNo), stdin);
        tcNo[strcspn(tcNo, "\n")] = '\0';  // Yeni sat�r karakterini kaldir
        
        printf("Yas: ");
        scanf("%d", &yas);
        getchar();  // Fazladan giris karakterini temizle
        
        printf("Cinsiyet (E/K): ");
        scanf("%c", &cinsiyet);
        getchar();  // Fazladan giris karakterini temizle
        
        printf("Sikayet: ");
        fgets(sikayet, sizeof(sikayet), stdin);
        sikayet[strcspn(sikayet, "\n")] = '\0';  // Yeni sat�r karakterini kald�r
        
        printf("Adres: ");
        fgets(adres, sizeof(adres), stdin);
        adres[strcspn(adres, "\n")] = '\0';  // Yeni sat�r karakterini kald�r
        
        printf("Telefon Numarasi: ");
        fgets(telefonNo, sizeof(telefonNo), stdin);
        telefonNo[strcspn(telefonNo, "\n")] = '\0';  // Yeni sat�r karakterini kald�r
        
        printf("Alerjisi var mi? (Evet/Hayir): ");
        fgets(alerji, sizeof(alerji), stdin);
        alerji[strcspn(alerji, "\n")] = '\0';  // Yeni sat�r karakterini kald�r
        
        printf("Kucuk Tansiyon: ");
        scanf("%d", &kucukTansiyon);
        getchar();  // Fazladan giris karakterini temizle
        
        printf("Buyuk Tansiyon: ");
        scanf("%d", &buyukTansiyon);
        getchar();  // Fazladan giris karakterini temizle
        
        printf("Ates: ");
        scanf("%f", &ates);
        getchar();  // Fazladan giris karakterini temizle
        
        // Hasta bilgilerini ekle
        hastaEkle(ad, soyad, tcNo, yas, cinsiyet, sikayet, adres, telefonNo, alerji, buyukTansiyon, kucukTansiyon, ates);
        
        // Yeni hasta eklenmek istenip istenmedi�ini sor
        printf("\nBaska bir hasta eklemek ister misiniz? (E/H): ");
        scanf("%c", &devam);
        getchar();  // Fazladan giri� karakterini temizle
    }
    
    // Hasta listesini yazdir
    Hasta *temp = ilk;
    printf("\n--- Acil Servis Hasta Listesi ---\n");
    while (temp != NULL) {
        printf("Ad: %s %s, TC Kimlik No: %s, Yas: %d, Cinsiyet: %c, Sikayet: %s, Oncelik: %d, Recete No: %s\n",
               temp->ad, temp->soyad, temp->tcNo, temp->yas, temp->cinsiyet, temp->sikayet, temp->oncelik, temp->receteNo);
        printf("Adres: %s, Telefon: %s\n", temp->adres, temp->telefonNo);
        printf("Alerji: %s, Buyuk Tansiyon: %d (%s), Kucuk Tansiyon: %d (%s), Ates: %.1f (%s)\n",
               temp->alerji,
               temp->buyukTansiyon, temp->buyukTansiyonDerecesi,
               temp->kucukTansiyon, temp->kucukTansiyonDerecesi,
               temp->ates, temp->atesDerecesi);
        temp = temp->sonraki;
    }
    
    return 0;
}

