#ifndef __RGB__
#define __RGB__
#include <stdlib.h>
#include <stdio.h>


/**
 * @brief Structura de pixel care stocheaza cei 3 parametri de culoare (R, G, B) 
 */
typedef struct RGB{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
}__attribute__((packed)) RGB;

/**
 * @brief Structura auxiliara de pixel 
 */
typedef struct BIG_RGB{
    unsigned long long red;
    unsigned long long green;
    unsigned long long blue;
}__attribute__((packed)) BIG_RGB;

/**
 * @brief Functia returneaza o matrice de pixeli
 * 
 * @param file Fisierul din care se va citi matricea
 * @param width Parametru care va fi transmis prin referinta pentru a lua latimea imaginii
 * @param height Parametru care va fi transmis prin referinta pentru a lua latimea imaginii
 * @return Matricea pixelilor fisierului .ppm
 */
RGB** get_pixel_matrix(FILE* file, int *width, int *height);
/**
 * @brief Functie care va afisa matricea de pixeli (folosita pentru debugging)
 * 
 * @param matrix Matricea de pixeli
 * @param width Latimea
 * @param height Inaltimea
 * @param file Fisierul unde se doreste a fi afisata
 */
void print_pixel_matrix(RGB** matrix, int width, int height, FILE* file);
/**
 * @brief Functia care creeaza fisierul ppm in functie de matricea de pixeli
 * 
 * @param matrix Matricea pe baza careia sa creeaza fisierul
 * @param width Latimea matricii
 * @param height Inaltimea matricii
 * @param file Fisierul ppm
 */
void make_ppm(RGB** matrix, int width, int height, FILE* file);
/**
 * @brief Functie care returneaza culoarea medie a unei zone din matricea de pixeli
 * 
 * @param matrix Matricea de pixeli 
 * @param startX Pozitia initiala de pe axa Ox
 * @param startY Pozitia initiala de pe axa Oy
 * @param width Latimea zonei
 * @param height Inaltimea zonei
 * @return Culoarea medie 
 */
RGB get_average_color(RGB** matrix, int startX, int startY, int width, int height);

/**
 * @brief Functie de interschimbare a doi pixeli
 * 
 * @param a Pixelul 1
 * @param b Pixelul 2
 */
void swap(RGB *a, RGB *b);

/**
 * @brief Functie de aflare a pixelului sepia in functie de un pixel
 * 
 * @param color Pixelul
 * @return Pixelul sepia
 */
RGB get_sepia_color(RGB color);

/**
 * @brief Aplica filtrul sepia asupra unei poze
 * 
 * @param matrix Matricea de pixeli a pozei
 * @param startX Pozitia de start de pe axa Ox de unde se aplica filtrul de sepia
 * @param startY Pozitia de start de pe axa Oy de unde se aplica filtrul de sepia
 * @param width Latimea zonei pe care se aplica filtrul sepia
 * @param height Inaltimea zonei pe care se aplica filtrul sepia
 */
void apply_sepia(RGB*** matrix, int startX, int startY, int width, int height);

/**
 * @brief Functie de aflare a pixelului gray in functie de un pixel
 * 
 * @param color Pixelul
 * @return Pixelul gray
 */
RGB get_gray_color(RGB color);

/**
 * @brief Aplica filtrul grayscale asupra unei poze
 * 
 * @param matrix Matricea de pixeli a pozei
 * @param startX Pozitia de start de pe axa Ox de unde se aplica filtrul de grayscale
 * @param startY Pozitia de start de pe axa Oy de unde se aplica filtrul de grayscale
 * @param width Latimea zonei pe care se aplica filtrul grayscale
 * @param height Inaltimea zonei pe care se aplica filtrul grayscale
 */
void apply_grayscale(RGB*** matrix, int startX, int startY, int width, int height);

/**
 * @brief Functie care taie un procent dintr-o matrice rgb, plecand din coltul stanga sus
 * 
 * @param matrix Matricea
 * @param width Latimea imaginii originale
 * @param height Inaltimea imaginii originale
 * @param percent Procent de taiere
 * @param newW Noua latime a imaginii
 * @param newH Noua inaltime a imaginii
 * @return RGB** Matricea noua
 */
RGB** cut_rgb_matrix(RGB** matrix, int width, int height, int percent, int *newW, int *newH);
#endif