#include <stdio.h>
#include <stdlib.h>

int main() {
    char ch1, ch2;
    int num1, num2;
    int sum;

    printf("=== 6-Bit Karakter Tabanli Toplama Simulasyonu (ASCII Eklentili) ===\n");
    printf("Iki rakam giriniz (ornek: '4' ve '7'):\n");

    printf("Birinci rakam: ");
    // Karakter okurken önceki newline (enter) karakterini atlamak için ' ' kullanýlýr
    if (scanf(" %c", &ch1) != 1) {
        // Okuma hatasý kontrolü
        return 1;
    }

    printf("Ikinci rakam: ");
    if (scanf(" %c", &ch2) != 1) {
        // Okuma hatasý kontrolü
        return 1;
    }

    // --- Girilen Karakterlerin ASCII Bilgisi ---
    printf("\n--- ASCII Bilgisi ---\n");
    printf("Girilen karakter 1 ('%c') ASCII degeri: %d\n", ch1, ch1);
    printf("Girilen karakter 2 ('%c') ASCII degeri: %d\n", ch2, ch2);
    printf("---------------------\n\n");

    if (ch1 < '0' || ch1 > '9' || ch2 < '0' || ch2 > '9') {
        printf("Hata: Gecersiz karakter girdiniz! (Sadece 0-9 arasi olmali)\n");
        return 1;
    }

    // Karakterden rakam degerine donusum
    num1 = ch1 - '0';
    num2 = ch2 - '0';
    sum = num1 + num2;

    // '0' karakterinin ASCII degeri
    printf("!!! Not: '0' karakterinin ASCII degeri %d'dir. !!!\n", '0');
    printf("Karakterden rakama donusum:\n");
    printf("num1 = '%c' - '0' = %d - %d = %d\n", ch1, ch1, '0', num1);
    printf("num2 = '%c' - '0' = %d - %d = %d\n", ch2, ch2, '0', num2);
    printf("--------------------------------\n");


    if (sum > 9) {
        printf("Hata: Toplama sonucu 9'dan buyuk! (Simulasyon kisitlamasi: %d + %d = %d)\n", num1, num2, sum);
    } else {
        printf("Toplama sonucu: %d + %d = %d\n", num1, num2, sum);
        
        // Toplam tek haneli oldugu icin, sonucu tekrar karaktere cevirebiliriz.
        char result_ch = sum + '0';
        printf("Toplama sonucu karakteri ('%c') ASCII degeri: %d\n", result_ch, result_ch);
    }

    return 0;
}
