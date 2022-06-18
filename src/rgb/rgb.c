#include <stdlib.h>
#include <stdio.h>
#include "rgb.h"


void swap(RGB *a, RGB *b){
    RGB aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

RGB** get_pixel_matrix(FILE* file, int *width, int *height){
    char aux[5]; // Vom citi P6
    unsigned short max_val; // Deja 256
    fgets(aux, 5, file); // P6 skipped
    fscanf(file, "%d%d", width, height); // Aflam inaltimea/latimea
    fgetc(file); // Trecem peste un whitespace
    fscanf(file, "%hd", &max_val); // Luam val maxima = 255
    fgetc(file); // Trecem peste whitespace
    RGB** matrix; // Matricea unde vor fi retinuti pixelii imaginii

    matrix = (RGB**)malloc(*height * sizeof(RGB*)); // Se aloca spatiul pentru matrice
    for(int i = 0; i < *height; i++)
        matrix[i] = (RGB*)malloc(*width * sizeof(RGB));

    for(int i = 0; i < *height; i++) // Se citeste matricea efectiva
        fread(matrix[i], sizeof(RGB), (*width), file);
    return matrix;
}

void print_pixel_matrix(RGB** matrix, int width, int height, FILE* file){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++)
            fprintf(file, "%d %d %d  ", matrix[i][j].red, matrix[i][j].green, matrix[i][j].blue);
        fprintf(file, "\n");
    }
}

void make_ppm(RGB** matrix, int width, int height, FILE* file){
    fprintf(file, "%s\n", "P6");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "%s\n", "255");
    for(int i = 0; i < height; i++)
        fwrite(matrix[i], sizeof(RGB), width, file);
}

RGB get_average_color(RGB** matrix, int startX, int startY, int width, int height){
    BIG_RGB temp; // Variabila temporara pentru a stoca suma tuturor culorilor
    RGB answer;
    temp.red = temp.green = temp.blue = 0;
    for(int y = startY; y < startY + height; y++)
        for(int x = startX; x < startX + width; x++){
            temp.red += matrix[y][x].red;
            temp.green += matrix[y][x].green;
            temp.blue += matrix[y][x].blue;
        }
    answer.red = temp.red / (width * height);
    answer.green = temp.green / (width * height);
    answer.blue = temp.blue / (width * height);
    return answer;
}

RGB get_sepia_color(RGB color){
    BIG_RGB temp;
    temp.red = color.red;
    temp.green = color.green;
    temp.blue = color.blue;

    temp.red = 0.393 * temp.red + 0.769 * temp.green + 0.189 * temp.blue;
    temp.green = 0.349 * temp.red + 0.686 * temp.green + 0.168 * temp.blue;
    temp.blue = 0.272 * temp.red + 0.534 * temp.green + 0.131 * temp.blue;

    RGB sepia_color;
    sepia_color.red = (temp.red > 255) ? 255 : temp.red;
    sepia_color.green = (temp.green > 255) ? 255 : temp.green;
    sepia_color.blue = (temp.blue > 255) ? 255 : temp.blue;

    return sepia_color;

}

void apply_sepia(RGB*** matrix, int startX, int startY, int width, int height){
    for(int y = startY; y < startY + height; y++)
        for(int x = startX; x < startX + width; x++)
            (*matrix)[y][x] = get_sepia_color((*matrix)[y][x]);
}

RGB get_gray_color(RGB color){
    BIG_RGB temp;
    temp.red = color.red;
    temp.green = color.green;
    temp.blue = color.blue;

    temp.red = 0.299 * temp.red + 0.587 * temp.green + 0.114 * temp.blue;
    temp.green = temp.red;
    temp.blue = temp.red;

    RGB gray_color;
    gray_color.red = (temp.red > 255) ? 255 : temp.red;
    gray_color.green = (temp.green > 255) ? 255 : temp.green;
    gray_color.blue = (temp.blue > 255) ? 255 : temp.blue;

    return gray_color;

}

void apply_grayscale(RGB*** matrix, int startX, int startY, int width, int height){
    for(int y = startY; y < startY + height; y++)
        for(int x = startX; x < startX + width; x++)
            (*matrix)[y][x] = get_gray_color((*matrix)[y][x]);
}

RGB** cut_rgb_matrix(RGB** matrix, int width, int height, int percent, int *newW, int *newH){
    (*newH) = height * percent / 100;
    (*newW) = width * percent / 100;
    RGB** new_matrix = calloc(*newH, sizeof(RGB*));
    for(int i = 0; i < *newH; i++)
        new_matrix[i] = calloc(*newW, sizeof(RGB));
    for(int y = 0; y < *newH; y++)
        for(int x = 0; x < *newW; x++)
            new_matrix[y][x] = matrix[y][x];
    return new_matrix;
}

