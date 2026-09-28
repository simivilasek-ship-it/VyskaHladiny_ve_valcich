#include <stdio.h>
#include <stdlib.h>
#define VSTUPNI_SOUBOR "cisla.txt"
#define VYSTUPNI_SOUBOR "vystup.txt"
#define PI 3.14


void Kontrola_otevreni(FILE *soubor, const char* SOUBOR) {
    if (soubor == NULL) {
        printf("Soubor %s se nepodarilo spravne otevrit.\n", SOUBOR);
        exit(EXIT_FAILURE);
    }

}

void Kontrola_uzavreni(FILE *soubor, const char* SOUBOR) {
    if (fclose(soubor) == EOF) {
        printf("Soubor %s se nepodarilo zavrit.\n", SOUBOR);
        exit(EXIT_FAILURE);
    }
}

void Tisk_hlavicky_obrazovka(void) {
    printf("=====================================================================\n");
    printf("| Poradi | Polomer | Vyska |Objem valce | Mnozstvi vody | Vejde se? |\n");
    printf("=====================================================================\n");
}

void Tisk_hlavicky_soubor(FILE *f) {

    fprintf(f, "VALCE S VYHOVUJICIM OBJEMEM\n");
    fprintf(f, "=============================================================================\n");
    fprintf(f, "| Poradi | Polomer | Vyska | Objem valce | Mnozstvi vody | Vyska hladiny |\n");
    fprintf(f, "=============================================================================\n");
}

float objemValce(int polomer, int vyska) {
    return (PI * polomer * polomer * vyska) / 1000.0f;
}


float vyskaHladiny(int polomer, int vodaLitry) {
    return (vodaLitry * 1000.0f) / (PI * polomer * polomer);
}

void Tisk_paticky_obrazovka(void) {
    printf("=======================================================================\n");
}

void Tisk_paticky_soubor(FILE *f) {
    fprintf(f, "=============================================================================\n");
}


int main(void) {
    FILE *souborvstup = fopen(VSTUPNI_SOUBOR, "r");
    FILE *souborvystup = fopen(VYSTUPNI_SOUBOR, "w");

    Kontrola_otevreni(souborvstup, VSTUPNI_SOUBOR);
    Kontrola_otevreni(souborvystup, VYSTUPNI_SOUBOR);

    Tisk_hlavicky_obrazovka();
    Tisk_hlavicky_soubor(souborvystup);

    int polomer,vyska, voda;
    int poradoveCislo = 1;
    int vyhovujiciCislo = 1;

    while (fscanf(souborvstup,"%d  %d %d",&polomer, & vyska, &voda) ==3) {
        float objem=objemValce(polomer,vyska);
        int vejdeSe = (voda<=objem);
        fprintf(stdout, "|%7d | %7d | %5d | %7.2f dm3 | %8d l | %9s |\n",
                   poradoveCislo, polomer, vyska, objem, voda, vejdeSe ? "ANO" : "NE");

        // Do souboru zapisujeme pouze kompletní řádek, pokud se voda vejde
        if (vejdeSe) {
            float hladina = vyskaHladiny(polomer, voda);

            // PERFEKTNÍ ZAROVNÁNÍ: Šířky polí přesně odpovídají nové hlavičce souboru
            fprintf(souborvystup, "| %6d | %4d cm | %4d cm | %8.2f dm3 | %11d l | %11.2f cm |\n",
                    vyhovujiciCislo, polomer, vyska, objem, voda, hladina);
            vyhovujiciCislo++;
        }
        poradoveCislo++;
    }


    Tisk_paticky_obrazovka();
    Tisk_paticky_soubor(souborvystup);


    Kontrola_uzavreni(souborvstup, VSTUPNI_SOUBOR);
    Kontrola_uzavreni(souborvystup, VYSTUPNI_SOUBOR);



    return 0;
}
