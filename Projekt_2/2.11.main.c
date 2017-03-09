/**

Autor: Mateusz Findeisen G2I3/1I3
Program DODAJE liczby zespolone zapisane w postaci kanonicznej lub wykladniczej (poprzednio: mnozy)
Po konsultacji, w wyniku niespojnosci na kartce z zadanie (raz 'iloczyn', raz 'zsumowac') uzgodnione, ze sumowanie.

Uruchamianie:
wpisanie "make" w konsoli, nastêpnie "./2.11.o"
W celu usuniêcia pliku wynikowego, mo¿na u¿yæ komendy "make clean"

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "2.11.spis.h"
#define pi 3.141592653589793
int main(){
    char s[10][60], *pEnd;
    int n, i, znak;
    double liczba_a=-1, liczba_b=-1, suma_a=0, suma_b=0, temp;
/** WCZYTYWANIE */
    puts("Program ten sluzy do sumowania n liczb zespolonych zapisancyh w postaci A+Bj lub Aexp(Bjpi)");
    printf("Ile liczb chcesz zsumowac: ");
    while(scanf("%d", &n) != 1){
        printf("Upewnij sie, ze podales/as liczbe calkowita!\nIle liczb chcesz zsumowac: ");
        /* Czyszczenie bufora jesli uzytkownik poda zla dana */
        while(getchar()!='\n');
    }
    for(;getchar()!='\n';){}
    for(i=0;i<n;i++){ /* n-ta liczba */
        printf("Liczba %d: ", i+1);
        fgets(s[i],59,stdin);
        liczba_a = strtod(s[i], &pEnd);
        znak=pEnd-s[i];
/** ANALIZOWANIE */
        if(s[i][znak]=='j'){ /* liczba formatu Bj */
                if(s[i][++znak]!='\n') {blad(znak); return 0;}
                if(liczba_a==0)
                    liczba_b=1;
                else{
                    liczba_b=liczba_a;
                    liczba_a=0;
                }
        }else{
            if(s[i][znak]=='+' || s[i][znak]=='-'){ /* liczba formatu A+Bj */
                liczba_b=strtod(s[i]+znak, &pEnd);
                znak=pEnd-s[i];
                if(liczba_b==0){
                    if(s[i][znak]=='+')
                        liczba_b=1;
                    else
                        liczba_b=-1;
                    znak++;
                }
                if(s[i][znak]!='j') {blad(znak); return 0;}
                if(s[i][++znak]!='\n') {blad(znak); return 0;}
            }else{
                if(s[i][znak]=='e'){ /* liczba formatu Aexp(Bjpi) */
                    if(liczba_a<0) {blad(0); return 0;}
                    if(s[i][++znak]!='x') {blad(znak); return 0;}
                    if(s[i][++znak]!='p') {blad(znak); return 0;}
                    if(s[i][++znak]!='(') {blad(znak); return 0;}
                    liczba_b=strtod(s[i]+znak+1, &pEnd);
                    if(liczba_b==0) liczba_b=pi; else liczba_b*=pi;
                    znak=pEnd-s[i];
                    if(s[i][znak]!='j') {blad(znak); return 0;}
                    if(s[i][++znak]!='p') {blad(znak); return 0;}
                    if(s[i][++znak]!='i') {blad(znak); return 0;}
                    if(s[i][++znak]!=')') {blad(znak); return 0;}
                    if(s[i][++znak]!='\n') {blad(znak); return 0;}
                    if(liczba_a==0){
                        liczba_a=liczba_b=0;
                        continue;
                    }else{
/** POST_WYKL -> POST_KAN */
                        temp=liczba_a;
                        liczba_a=cos(liczba_b)*temp;
                        liczba_b=sin(liczba_b)*temp;
                    }
                }else{
                    if(s[i][znak]=='\n'){
                        liczba_b=0;
                    }else{
                        blad(znak); return 0;
                    }
                }
            }
        }
        suma_a+=liczba_a;	suma_b+=liczba_b;
        liczba_a = liczba_b = -1;
    }
/** WYPISYWANIE */
    if(suma_b>0)
        printf("Wynik (postac kanoniczna):  %.4f+%.4fj\n",suma_a,suma_b);
    else
        if(suma_b==0)
            printf("Wynik (postac kanoniczna):  %.4f+0j\n",suma_a);
        else
            printf("Wynik (postac kanoniczna):  %.4f%.4fj\n",suma_a,suma_b);
/** POST_KAN -> POST_WYKL */
    postac_wykl(&suma_a,&suma_b);
/** WYPISYWANIE */
    if(suma_b==0)
        printf("Wynik (postac wykladnicza): %.4fexp(0jpi)\n",suma_a);
    else
        printf("Wynik (postac wykladnicza): %.4fexp(%.4fjpi)\n",suma_a,suma_b);

    return 0;
}
