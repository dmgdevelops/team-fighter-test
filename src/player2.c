#include "simple_logger.h"
#include "gfc_input.h"

#include "player2.h"


void player2_think(Entity *self);
void player2_update(Entity *self);
void player2_free(Entity *self);

Entity *player2_new()
{
    Entity *self;

    self = entity_new();
    if(!self)
    {
        slog("failed to spawn player entity");
        return NULL;
    }

    //self->sprite = gf2d_sprite_load_image("images/doom-stance.png");
    self->sprite = gf2d_sprite_load_all(
        "images/Kanji/kanji_idle.png",
        400,
        347,
        12,
        0);
    self->frame = 0;
    self->position = vector2d(1000,495);
    self->flip = vector2d(0,0);
    self->scale = vector2d(.5,.5);

    self->think = player2_think;
    self->update = player2_update;
    self->free = player2_free;
    self->redHealth = 100;
    self->factor = 3;
    self->isAttacking = 0;
    self->isJumping = 0;
    self->jumpStrength = 0;
    self->jumpHeight = 15;
    self->gravity = 0;
    self->activeFrames = 0;
    self->input = ButtonNeutral;
    self->state = ES_stand;

    return self;
}

void player2_update(Entity *self)
{
    if (!self)
    {
        slog("self pointer not provided");
        return;
    }
    if(self->state == ES_stand){
        //dir.x = 0;
        //dir.y = 0;
        self->gravity = 0;
        self->isJumping = 0;
        self->isAttacking = 0;
        self->frame += 0.055;
        if(self->frame >= 12)self->frame = 0;
    }
}

void player2_think(Entity *self){

}

void player2_free(Entity *self)
{
    if(!self)return;

}

/*eol@eof*/
