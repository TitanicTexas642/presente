#include "entity.h"

#include <math.h>
#include <stdio.h>

int entity_physics(const level *lvl, entity *ent){
    
    // Update position
    float limitex_der= ent->x + ent->rad;
    float limitey_abajo= ent->y + ent->rad;
    float limitex_izq= ent->x - ent->rad;
    float limitey_arriba=ent->y - ent->rad;
    // Check if the center is inside a solid cell
    int tile_x = (int) floor(limitex_der/TILE_SIZE);
    int tile_y = (int) floor(limitey_abajo/TILE_SIZE);
    int tile_x2= (int) floor(limitex_izq/TILE_SIZE);
    int tile_y2= (int) floor(limitey_arriba/TILE_SIZE);
    char cell = level_get(lvl,tile_x,tile_y);

    if(cell=='#'){
        if(tile_x<0){
            if (ent->x-ent->vx < ent->x){
                ent->x-=ent->vx;
                ent->y+=ent->vy;
            }
            else{
                ent->x += ent->vx;
                ent->y += ent->vy;
            }
        }
        if(tile_y<0){
            if(ent->y-ent->vy < ent->y){
                ent->x += ent->vx;
                ent->y -= ent->vy;
            }
            else{
                ent->x += ent->vx;
                ent->y += ent->vy;
            }
        }
        if(tile_x>=lvl->size_x){
            if (ent->x + ent->vx > ent->x){
                ent->x-=ent->vx;
                ent->y-=ent->vy;
            }
            else{
                ent->x += ent->vx;
                ent->y += ent->vy;
            }        
        }
        if(tile_y>=lvl->size_y){
            if(ent->y+ent->vy > ent->y){
                ent->x+=ent->vx;
                ent->y-=ent->vy;
            }
            else{
                ent->x += ent->vx;
                ent->y += ent->vy;
            }
        }
        else{
            ent->x-=(ent->vx);
            ent->y-=(ent->vy);
        }
        return 1;
    }
    else{
        char cell = level_get(lvl,tile_x2,tile_y2);
        if(cell=='#'){
            if(tile_x2<0){
                if (ent->x-ent->vx > ent->x){
                    ent->x-=ent->vx;
                    ent->y+=ent->vy;
                }
                else{
                    ent->x += ent->vx;
                    ent->y += ent->vy;
                }
            }
            if(tile_y2<0){
                if(ent->y-ent->vy > ent->y){
                    ent->x += ent->vx;
                    ent->y -= ent->vy;
                }
                else{
                    ent->x += ent->vx;
                    ent->y += ent->vy;
                }
            }
            if(tile_x2>=lvl->size_x){
                if (ent->x + ent->vx < ent->x){
                    ent->x-=ent->vx;
                    ent->y-=ent->vy;
                }
                else{
                    ent->x += ent->vx;
                    ent->y += ent->vy;
                }        
            }
            if(tile_y2>=lvl->size_y){
                if(ent->y+ent->vy < ent->y){
                    ent->x+=ent->vx;
                    ent->y-=ent->vy;
                }
                else{
                    ent->x += ent->vx;
                    ent->y += ent->vy;
                }
            }
            else{
                ent->x-=(ent->vx);
                ent->y-=(ent->vy);
            } 
            return 1;
        }
    }
    // Update position
    ent->x += ent->vx;
    ent->y += ent->vy;
    return 0;
}

int entity_collision(const entity *ent1, const entity *ent2){
    // If one of the enitities is dead, there is no collision
    if(ent1->dead || ent2->dead) return 0;

    // Compute the distance between the two centers
    float delta_x = ent1->x - ent2->x;
    float delta_y = ent1->y - ent2->y;
    float delta_mag = sqrt(delta_x*delta_x+delta_y*delta_y);

    // Return 1 if the distance is smaller than the sum of both radious
    return (delta_mag < ent1->rad + ent2->rad);
}
