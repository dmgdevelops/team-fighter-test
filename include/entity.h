#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <gfc_types.h>
#include <gf2d_sprite.h>

/**
 *      This is the entity system for my 2d project
 */

typedef struct Entity_S
{
    Uint8       _inuse;         //Flag for memory usage
    Sprite      *sprite;        //Entity sprite (if needed)
    float      frame;          //Current frame of animation for sprite
    Vector2D    position;       //Where to draw entity
    void   (*think)(struct Entity_S *self);
    void   (*update)(struct Entity_S *self);
    void   (*free)(struct Entity_S *self);
    void *data;
}Entity;


void entity_system_initialize(Uint32 max);

void entity_clear_all(Entity *ignore);

Entity *entity_new();

void entity_free(Entity *self);

void entity_system_think();

void entity_system_update();

void entity_system_draw();

#endif
