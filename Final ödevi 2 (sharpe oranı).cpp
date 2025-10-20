#include <stdio.h>

int main() {
    double getiri, risksiz_oran, standart_sapma, sharpe;

    printf("Sharpe Orani Hesaplama Programina Hosgeldiniz!\n");

    // Kullanýcýdan deðerleri al
    printf("Yatirimin getirisi (%% olarak): ");
    scanf("%lf", &getiri);

    printf("Risksiz faiz orani (%% olarak): ");
    scanf("%lf", &risksiz_oran);

    printf("Portfoyun standart sapmasi (%% olarak): ");
    scanf("%lf", &standart_sapma);

    // Yüzde deðerlerini ondalýk forma çevir
    getiri /= 100.0;
    risksiz_oran /= 100.0;
    standart_sapma /= 100.0;

    // Sharpe oranýný hesapla
    if (standart_sapma == 0) {
        printf("Hata: Standart sapma sifir olamaz!\n");
        return 1;
    }

    sharpe = (getiri - risksiz_oran) / standart_sapma;

    // Sonucu yazdýr
    printf("\nSharpe Orani: %.2f\n", sharpe);

    // Yorumu yazdýr
    if (sharpe < 1) {
        printf("Genel olarak dusuk bir oran. Yatirim verimsiz olabilir.\n");
    } else if (sharpe < 2) {
        printf("Fena degil, kabul edilebilir bir performans.\n");
    } else if (sharpe < 3) {
        printf("Cok iyi bir oran! Yatirim basarili gorunuyor.\n");
    } else {
        printf("Mukemmel bir oran! Yatirim cok guclu.\n");
    }

    return 0;
}


