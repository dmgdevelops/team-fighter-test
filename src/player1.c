#include "simple_logger.h"
#include "gfc_input.h"

#include "player1.h"


void player1_think(Entity *self);
void player1_update(Entity *self);
void player1_free(Entity *self);

Entity *player1_new()
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
        "images/ed210.png",
        128,
        128,
        16,
        0);
    self->frame = 0;
    self->position = vector2d(5,5);

    self->think = player1_think;
    self->update = player1_update;
    self->free = player1_free;
    self->redHealth = 100;

    return self;
}

void player1_think(Entity *self)
{
    if(!self)return;

    Vector2D dir = {0};

    SDL_Joystick *joystick;
    joystick = SDL_JoystickOpen(0);

    if(SDL_JoystickGetAxis(joystick, 1) < -32700 || SDL_JoystickGetHat(joystick, 0) == 1)
    {
        dir.y = -1;
        self->state = ES_crouch;
    }
    if(SDL_JoystickGetAxis(joystick, 1) > 32700 || SDL_JoystickGetHat(joystick, 0) == 4)
    {
        dir.y = 1;
        self->state = ES_jump;
    }
    if(SDL_JoystickGetAxis(joystick, 0) > 32700 || SDL_JoystickGetHat(joystick, 0) == 2)
    {
        dir.x = 1;
        self->state = ES_walk;
    }
    if(SDL_JoystickGetAxis(joystick, 0) < -32700 || SDL_JoystickGetHat(joystick, 0) == 8)
    {
        dir.x = -1;
        self->state = ES_stBlock;
    }

    vector2d_normalize(&dir);
    vector2d_scale(self->moveSpeed,dir,3);
}

void player1_update(Entity *self)
{
    if(!self)return;

    vector2d_add(self->position,self->position,self->moveSpeed);
}

void player1_free(Entity *self)
{
    if(!self)return;

}


/*eol@eof*/
