#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define VSTUPNI_SOUBOR "cisla.txt"
#define VYSTUPNI_SOUBOR "vystup.txt"
#define PI 3.14159265358979323846

// Kontrola otevření souboru
void kontrolaOtevreni(FILE *soubor) {
    if (soubor == NULL) {
        printf("[CHYBA] - Soubor se nepodařilo otevřít.\n");
        exit(EXIT_FAILURE);
    }
}

// Kontrola uzavření souboru
void kontrolaUzavreni(FILE *soubor) {
    if (fclose(soubor) != 0) {
        printf("[CHYBA] - Soubor se nepodařilo správně uzavřít.\n");
        exit(EXIT_FAILURE);
    }
}

// Výpočet objemu válce v dm3
float objemValce(int polomer, int vyska) {
    return (float)(PI * polomer * polomer * vyska / 1000.0);
}

// Výpočet hladiny vody v cm
float hladinaVody(int polomer, int mnozstvi) {
    if (polomer <= 0) return 0.0f;
    return (mnozstvi * 1000.0) / (PI * polomer * polomer);
}

// Hlavička pro výpis na obrazovku
void hlavickaObrazovka(FILE *f) {
    fprintf(f, "=====================================================\n");
    fprintf(f, "=================== Válce =========================\n");
    fprintf(f, "=====================================================\n");
    fprintf(f, "|-Pořadí-|-Poloměr-|-Výška-|--Objem----|-Voda---|\n");
    fprintf(f, "=====================================================\n");
}

// Paticka pro obrazovku
void patickaObrazovka(FILE *f) {
    fprintf(f, "=====================================================\n\n\n");
}

// Hlavička pro výstupní soubor
void hlavickaSoubor(FILE *f) {
    fprintf(f, "===============================================================\n");
    fprintf(f, "======================== Válce ===============================\n");
    fprintf(f, "===============================================================\n");
    fprintf(f, "|-Pořadí-|-Poloměr-|-Výška-|---Objem---|-Voda---|-Hladina-|\n");
    fprintf(f, "===============================================================\n");
}

// Paticka pro soubor
void patickaSoubor(FILE *f) {
    fprintf(f, "===============================================================\n\n\n");
}

int main(void) {
    FILE *souborVstup = fopen(VSTUPNI_SOUBOR, "r");
    FILE *souborVystup = fopen(VYSTUPNI_SOUBOR, "w");

    kontrolaOtevreni(souborVstup);
    kontrolaOtevreni(souborVystup);

    int polomer, vyska, mnozstvi;
    int poradoveCislo = 0;
    int poradoveCisloPlatne = 0;

    hlavickaSoubor(souborVystup);
    hlavickaObrazovka(stdout);

    while (fscanf(souborVstup, "%d %d %d", &polomer, &vyska, &mnozstvi) == 3) {
        poradoveCislo++;

        if (polomer <= 0 || vyska <= 0 || mnozstvi < 0) {
            printf("[VAROVÁNÍ] - Neplatný vstup u záznamu %d (r=%d, h=%d, voda=%d).\n", poradoveCislo, polomer, vyska, mnozstvi);
            continue;
        }

        float objem = objemValce(polomer, vyska);

        if (objem >= mnozstvi) {
            poradoveCisloPlatne++;
            float hladina = hladinaVody(polomer, mnozstvi);
            fprintf(souborVystup, "| %3d. | %3d cm | %3d cm | %8.2f dm3 | %6d l | %7.2f cm |\n",
                    poradoveCisloPlatne, polomer, vyska, objem, mnozstvi, hladina);
        }

        fprintf(stdout, "| %3d. | %3d cm | %3d cm | %8.2f dm3 | %6d l |\n", poradoveCislo, polomer, vyska, objem, mnozstvi);
    }

    patickaSoubor(souborVystup);
    patickaObrazovka(stdout);

    printf("[INFO] - Soubor %s byl vytvořen.\n\n", VYSTUPNI_SOUBOR);

    kontrolaUzavreni(souborVstup);
    kontrolaUzavreni(souborVystup);

    return 0;
}
