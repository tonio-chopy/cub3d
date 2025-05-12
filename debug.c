/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:19:13 by alaualik          #+#    #+#             */
/*   Updated: 2025/05/12 15:05:04 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define MINIMAP_SCALE 10  // Nouvelle constante pour le zoom de la minimap

int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
} ColorRGB;

// Couleurs prédéfinies
const ColorRGB RGB_Red = {255, 0, 0};
const ColorRGB RGB_Green = {0, 255, 0};
const ColorRGB RGB_Blue = {0, 0, 255};
const ColorRGB RGB_White = {255, 255, 255};
const ColorRGB RGB_Yellow = {255, 255, 0};
const ColorRGB RGB_TransparentYellow = {255, 255, 0, 100};

// Fonction pour diviser une couleur par 2 (assombrir)
ColorRGB color_div2(ColorRGB color) {
    ColorRGB result;
    result.r = color.r / 2;
    result.g = color.g / 2;
    result.b = color.b / 2;
    return result;
}

// Fonction pour dessiner une ligne verticale
void verLine(SDL_Renderer* renderer, int x, int y1, int y2, ColorRGB color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, x, y1, x, y2);
}

// Nouvelle fonction pour dessiner la minimap
void drawMinimap(SDL_Renderer* renderer, double posX, double posY) {
    // Dessiner la carte
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            if (worldMap[x][y] != 0) {
                SDL_Rect rect = {
                    x * MINIMAP_SCALE,
                    y * MINIMAP_SCALE,
                    MINIMAP_SCALE,
                    MINIMAP_SCALE
                };
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    
    // Dessiner le joueur
    SDL_Rect playerRect = {
        (int)(posX * MINIMAP_SCALE) - 2,
        (int)(posY * MINIMAP_SCALE) - 2,
        5,
        5
    };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &playerRect);
}

int main(int argc, char* argv[]) {
    double posX = 22, posY = 12;  // position de départ
    double dirX = -1, dirY = 0;   // vecteur direction
    double planeX = 0, planeY = 0.66; // plan de la caméra
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Raycaster + Minimap Debug", 
                                         SDL_WINDOWPOS_CENTERED, 
                                         SDL_WINDOWPOS_CENTERED, 
                                         SCREEN_WIDTH, 
                                         SCREEN_HEIGHT, 
                                         SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    bool running = true;
    SDL_Event event;
    Uint32 oldTime = SDL_GetTicks();
    
    while (running) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        
        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        
        // Raycasting
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            // Calcul de la position et direction du rayon
            double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
            
            // Position dans la carte
            int mapX = (int)posX;
            int mapY = (int)posY;
            
            // Longueur du rayon jusqu'au prochain côté x ou y
            double sideDistX, sideDistY;
            
            // Longueur du rayon entre les côtés x ou y
            double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
            double perpWallDist;
            
            // Direction des pas
            int stepX, stepY;
            
            int hit = 0; // a-t-on touché un mur ?
            int side; // côté NS ou EW touché ?
            
            // Calcul du pas et de la distance initiale
            if (rayDirX < 0) {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            } else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            
            if (rayDirY < 0) {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            } else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }
            
            // Algorithme DDA
            while (hit == 0) {
                if (sideDistX < sideDistY) {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                } else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                
                // Vérifier si on a touché un mur
                if (worldMap[mapX][mapY] > 0) hit = 1;
            }
            
            // Dessiner le rayon sur la minimap (debug visuel)
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 100); // Jaune transparent
            SDL_RenderDrawLine(renderer, 
                             posX * MINIMAP_SCALE, posY * MINIMAP_SCALE,
                             mapX * MINIMAP_SCALE, mapY * MINIMAP_SCALE);
            
            // Calcul de la distance projetée sur la direction de la caméra
            if (side == 0) perpWallDist = (sideDistX - deltaDistX);
            else perpWallDist = (sideDistY - deltaDistY);
            
            // Hauteur de la ligne à dessiner
            int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
            
            // Calcul des pixels à dessiner
            int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawStart < 0) drawStart = 0;
            int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;
            
            // Choix de la couleur en fonction du type de mur
            ColorRGB color;
            switch (worldMap[mapX][mapY]) {
                case 1: color = RGB_Red; break;
                case 2: color = RGB_Green; break;
                case 3: color = RGB_Blue; break;
                case 4: color = RGB_White; break;
                default: color = RGB_Yellow; break;
            }
            
            // Assombrir les côtés y
            if (side == 1) color = color_div2(color);
            
            // Dessiner la ligne verticale
            verLine(renderer, x, drawStart, drawEnd, color);
        }
        
        // Dessiner la minimap
        drawMinimap(renderer, posX, posY);
        
        // Calcul du temps et FPS
        Uint32 currentTime = SDL_GetTicks();
        double frameTime = (currentTime - oldTime) / 1000.0;
        oldTime = currentTime;
        
        // Vitesse de déplacement
        double moveSpeed = frameTime * 5.0;
        double rotSpeed = frameTime * 3.0;
        
        // Gestion des touches
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        
        // Avancer
        if (keystate[SDL_SCANCODE_UP]) {
            if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0) posX += dirX * moveSpeed;
            if (worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
        }
        
        // Reculer
        if (keystate[SDL_SCANCODE_DOWN]) {
            if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == 0) posX -= dirX * moveSpeed;
            if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
        }
        
        // Rotation à droite
        if (keystate[SDL_SCANCODE_RIGHT]) {
            double oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        }
        
        // Rotation à gauche
        if (keystate[SDL_SCANCODE_LEFT]) {
            double oldDirX = dirX;
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
            
            double oldPlaneX = planeX;
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        }
        
        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);
    }
    
    // Nettoyage
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
