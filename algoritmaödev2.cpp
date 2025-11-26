#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- DURUM DEÐÝÞKENLERÝ ---
// Global deðiþkenler yerine main içinde tutulmasý daha temiz bir yaklaþýmdýr, 
// ancak simülasyon akýþýný sadeleþtirmek için burada tanýmlanmýþtýr.

int saglik = 100;    // 0-100 aralýðýnda
int enerji = 100;    // 0-100 aralýðýnda
int yemek = 5;       // Baþlangýç yemeði
int siginak_var = 0; // 0: Yok, 1: Var
char komut;          // Oyuncudan alýnan komut

// --- FONKSÝYON PROTOTÝPLERÝ ---
void durumu_goster();
void avlan();
void siginak_ara();
void dinlen();
void tehlike_simule_et();
void sifreli_ilerleme();

// --- ANA PROGRAM ---
int main() {
    // Rastgele sayý üretimi için baþlatma (Zorunlu olmasa da rastgeleliði saðlar)
    srand(time(NULL)); 

    printf("--- KARAKTER TABANLI HAYATTA KALMA SIMULATORU ---\n");
    printf("Amaciniz saglik ve enerjinizi koruyarak hayatta kalmak.\n");

    // ANA DÖNGÜ (DO-WHILE ZORUNLU)
    // Oyuncu 'X' komutunu vermedikçe simülasyon devam eder.
    do {
        durumu_goster();
        printf("Yapmak istediginiz eylemi secin (A, S, R, E, F, P, X): ");
        scanf(" %c", &komut); // Baþtaki boþluk (' ') önceki '\n' karakterini yutar.
        
        // Komut Yönetimi (SWITCH-CASE ZORUNLU)
        switch (komut) {
            case 'A':
            case 'a':
                avlan();
                break;
            case 'S':
            case 's':
                siginak_ara();
                break;
            case 'R':
            case 'r':
                dinlen();
                break;
            case 'E':
            case 'e':
                // Envanter zaten durumu_goster() içinde gösteriliyor.
                printf("Envanter gorüntulendi (yukaridaki tabloya bakiniz).\n");
                break;
            case 'F':
            case 'f':
                tehlike_simule_et();
                break;
            case 'P':
            case 'p':
                sifreli_ilerleme();
                break;
            case 'X':
            case 'x':
                printf("\nSimulasyon Sonlaniyor... Hayatta kaldiniz (veya en azindan kacabildiniz).\n");
                break;
            default:
                printf("Gecersiz komut. Lutfen A, S, R, E, F, P veya X secin.\n");
        }
        
        // Her tur sonunda karakterin durumunu kontrol et
        if (saglik <= 0 || enerji <= 0) {
            printf("\n--- KARAKTER VEFAT ETTI ---\n");
            printf("Saglik: %d, Enerji: %d. Simulasyon Sonlandi.\n", saglik, enerji);
            komut = 'X'; // Döngüden çýkýþý zorlar
        }

    } while (komut != 'X' && komut != 'x');

    return 0;
}

// --- FONKSÝYON TANIMLARI ---

// Durumlarý gösterir
void durumu_goster() {
    printf("\n--- DURUM GORUNTUSU ---\n");
    printf("Saglik: %d/100\n", saglik);
    printf("Enerji: %d/100\n", enerji);
    printf("Yemek Sayisi: %d\n", yemek);
    printf("Siginak Durumu: %s\n", siginak_var ? "Bulundu" : "Bulunmadi");
    printf("--------------------------\n");
}

// 'A' Komutu: Avlanma
void avlan() {
    int enerji_kaybi = 10;
    int sans = rand() % 100 + 1; // 1 ile 100 arasýnda rastgele sayý

    // ARITMETÝK ÝÞLEM ZORUNLULUÐU: Enerji kaybý
    enerji -= enerji_kaybi; 
    
    printf("Avlanmaya calisiliyor... Enerji: -%d\n", enerji_kaybi);

    // MANTIK: Yemek kazanma ve yaralanma þansý (&&, || zorunlu)
    // Yemek kazanma þansý %50 VE enerji > 10 ise yemek bulunur.
    if ((sans <= 50) && (enerji > 10)) { 
        yemek += 2;
        printf("Basari! 2 yemek kazandiniz.\n");
    } 
    // VEYA %10 ihtimalle canavar saldýrýr (Yaralanma)
    else if (sans >= 90 || enerji <= 10) { 
        saglik -= 15;
        printf("Yaralandiniz! Saglik: -15. Yemek bulunamadi.\n");
    }
    else {
        printf("Basarisiz. Yemek bulunamadi.\n");
    }
}

// 'S' Komutu: Sýðýnak Arama
void siginak_ara() {
    int sans = rand() % 100 + 1;

    printf("Siginak araniyor...\n");

    // IF-ELSE ZORUNLULUÐU: Sýðýnak bulma ihtimali
    if (siginak_var == 1) {
        printf("Zaten bir siginaginiz var. Bosa zaman kaybettiniz.\n");
    } 
    // MANTIK: Saðlýk iyiyse VE þans yaver giderse sýðýnak bulma ihtimali artar.
    else if ((saglik > 50 && enerji > 50) || (sans > 70)) { 
        siginak_var = 1;
        printf("Tebrikler! Guvenli bir siginak buldunuz.\n");
    }
    else {
        printf("Bir siginak bulunamadi. Aramaya devam etmelisiniz.\n");
    }
}

// 'R' Komutu: Dinlenme
void dinlen() {
    int enerji_artisi = 20;
    int saglik_artisi = 10;
    
    // YEMEK KONTROLÜ
    if (yemek <= 0) {
        printf("Yemeginiz yok! Dinlenmek icin yemek yiyemediniz. Sadece %d enerji kazandiniz.\n", enerji_artisi / 2);
        enerji += enerji_artisi / 2;
        saglik -= 5; // Açlýk cezasý
        printf("Acliktan dolayi 5 saglik kaybettiniz.\n");
    } else {
        // ARÝTMETÝK ÝÞLEMLER ZORUNLULUÐU
        enerji += enerji_artisi;
        saglik += saglik_artisi;
        yemek -= 1;
        printf("Dinlendiniz ve yemek yediniz. Enerji: +%d, Saglik: +%d, Yemek: -1.\n", enerji_artisi, saglik_artisi);
    }
    
    // Max 100 limitini aþmama
    if (enerji > 100) enerji = 100;
    if (saglik > 100) saglik = 100;
}

// 'F' Komutu: Tehlike Serisi Simülasyonu
void tehlike_simule_et() {
    int tehlike_suresi = 4; // 4 adýmlýk tehlike dalgasý

    printf("--- TEHLIKE DALGASI BASLIYOR ---\n");

    // FOR DÖNGÜSÜ ZORUNLULUÐU: Tehlike dalgasýný simüle eder
    for (int i = 1; i <= tehlike_suresi; i++) {
        int sans = rand() % 100;
        printf("Tehlike Adimi %d: ", i);

        // Siginak varsa tehlikeden korunma ihtimali yüksek
        if (siginak_var == 1 && sans < 80) {
            printf("Siginak sayesinde korunuyorsunuz.\n");
        } 
        // Siginak yoksa can kaybý ihtimali
        else if (siginak_var == 0 && sans < 50) {
            int hasar = 10 + (rand() % 10);
            saglik -= hasar;
            printf("Yaralandiniz! Saglik -%d. Kacin!\n", hasar);
        }
        else {
            printf("Tehlikeden kactiniz.\n");
            enerji -= 5; // Kaçmak enerji harcar
        }
        
        // Her adýmda can/enerji kontrolü
        if (saglik <= 0 || enerji <= 0) break; 
    }

    printf("--- TEHLIKE DALGASI SONA ERDI ---\n");
}

// 'P' Komutu: Þifreli Ýlerleme
void sifreli_ilerleme() {
    char gizli_sifre = 'Z'; // Aþýlmasý gereken þifre (Engel)
    char girilen_karakter;
    int deneme_sayisi = 0;

    printf("--- GIZEMLI KAPI ENGELI ---\n");
    printf("Kapiyi acmak icin dogru sifreyi (tek karakter) girin.\n");

    // DO-WHILE DÖNGÜSÜ ZORUNLULUÐU: Doðru karakteri girene kadar devam eder
    do {
        printf("Deneme %d. Karakteri girin: ", ++deneme_sayisi);
        scanf(" %c", &girilen_karakter);

        if (girilen_karakter == gizli_sifre) {
            printf("Sifre dogru! Kapi acildi. Ilerliyorsunuz.\n");
        } else {
            printf("Yanlis sifre. Tekrar deneyin.\n");
            // Yanlýþ deneme cezasý
            enerji -= 5; 
            if (enerji <= 0) {
                printf("Enerjiniz bitti. Kapiyi acmaya gucunuz kalmadi.\n");
                break;
            }
        }

    } while (girilen_karakter != gizli_sifre);
}
