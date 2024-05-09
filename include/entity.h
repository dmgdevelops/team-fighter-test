#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gfc_types.h"
#include "gf2d_sprite.h"
#include "input.h"

/**
 *      This is the entity system for my 2d project
 */

typedef enum
{
    ES_stand = 0,
    ES_stBlock,
    ES_crouch,
    ES_chBlock,
    ES_attack,
    ES_special,
    ES_knockd,
    ES_dash,
    ES_walk,
    ES_backwalk,
    ES_jump,
    ES_jumpBlock,
    ES_hitstun,
    ES_blockstun,
    ES_recovery,
    ES_ko
}EntityState;

typedef enum
{
    ENT_PROJ = 0,
    ENT_ATTACK,
    ENT_P1_ACTIVE,
    ENT_P2_ACTIVE,
    ENT_P1_TAG,
    ENT_P2_TAG
}EntityType;

typedef struct Entity_S
{
    Uint8       _inuse;         //Flag for memory usage
    Sprite      *sprite;        //Entity sprite (if needed)
    float      frame;          //Current frame of animation for sprite
    Vector2D    position;       //Where to draw entity
    Vector2D    flip;
    Vector2D    scale;
    float         factor;
    void   (*think)(struct Entity_S *self);
    void   (*update)(struct Entity_S *self);
    void   (*free)(struct Entity_S *self);
    void *data;

    float redHealth;            //Current Health
    float greyHealth;           //Recoverable Health
    Vector2D moveSpeed;         //Movement moveSpeed
    Vector2D jumpSpeed;
    float activeFrames;         //Keeps track of how long a move is active for

    int jumps;                  //How many jumps does the character have

    Uint8 canAirdash;           //Flag to define if a character can canAirdash
    Uint8 isFloat;              //Flag to define if a character can currently fly
    Uint8 xFactor;              //Flag to define if x-factor is active
    Uint8 isAttacking;          //Flag to define if a character is currently attacking

    Uint8 isJumping;
    float jumpStrength;
    float jumpHeight;
    float gravity;
    //Vector2D direction;

    EntityState state;
    EntityType type;
    InputAction input;
    //Rect bounds;
}Entity;


void entity_system_initialize(Uint32 max);

void entity_clear_all(Entity *ignore);

Entity *entity_new();

void entity_free(Entity *self);

void entity_system_think();

void entity_system_update();

void entity_system_draw();

#endif
