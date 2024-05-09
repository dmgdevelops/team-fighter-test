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
        "images/Polnareff/polnareff_idle.png",
        180,
        155,
        13,
        0);
    self->frame = 0;
    self->position = vector2d(5,450);
    self->flip = vector2d(1,0);
    self->scale = vector2d(1.5,1.5);

    self->think = player1_think;
    self->update = player1_update;
    self->free = player1_free;
    self->redHealth = 100;
    self->factor = 3;
    self->isAttacking = 0;
    self->isJumping = 0;
    self->jumpStrength = 0;
    self->jumpHeight = 15;
    self->gravity = 0;
    self->activeFrames = 0;
    self->input = ButtonNeutral;

    return self;
}

void doJoystickButtonDown(SDL_JoyButtonEvent *event, Entity *self)
{
    //Vector2D dir = {0};
    //slog("%zu] SDL_JOYBUTTONDOWN\n  Joystick:\t#%i(%i)\n  Button:\t%i\n\n", event->timestamp, 0, event->which, event->button);
    if(event->button == 11)
    {
        self->input = ButtonUp;
        if(!self->isAttacking && !self->isJumping)
        {
            slog("Jump occured");
            self->state = ES_jump;
            self->isJumping = 1;
            self->jumpStrength = self->jumpHeight;
            self->factor = 3;
        }
    }
    if(event->button == 12 && event->button == 13)
    {
        self->input = ButtonDownLeft;
        if(!self->isJumping && !self->isAttacking)
        {
            self->state = ES_chBlock;
            self->sprite = gf2d_sprite_load_all("images/Polnareff/polnareff_crouch.png",180,155,9,0);
            self->factor = 3;
        }
    }
    if(event->button == 12)
    {
        self->input = ButtonDown;
        if(!self->isJumping && !self->isAttacking)
        {
            self->state = ES_crouch;
            self->sprite = gf2d_sprite_load_all("images/Polnareff/polnareff_crouch.png",180,155,9,0);
            self->factor = 3;
        }
    }
    if(event->button == 12 && event->button == 14)
    {
        self->input = ButtonDownRight;
        if(!self->isJumping && !self->isAttacking)
        {
            self->state = ES_crouch;
            self->sprite = gf2d_sprite_load_all("images/Polnareff/polnareff_crouch.png",180,155,9,0);
            self->factor = 3;
        }
    }
    if(event->button == 14)
    {
        self->input = ButtonRight;
        if(!self->isJumping && !self->isAttacking)
        {
            //dir.x = 1; //forward walk
            self->state = ES_walk;
            self->sprite = gf2d_sprite_load_all("images/Polnareff/polnareff_walk.png",180,155,10,0);
            self->factor = 3;
        }
    }
    if(event->button == 13 && !self->isJumping && !self->isAttacking)
    {
        self->input = ButtonLeft;
        if(!self->isJumping && !self->isAttacking)
        {
            //dir.x = -1; //backward walk
            self->state = ES_backwalk;
            self->sprite = gf2d_sprite_load_all("images/Polnareff/polnareff_walk.png",180,155,10,0);
            self->factor = 1.5;
        }
    }
    if(event->button == 0)
    {
        self->input = ButtonB;

        if(!self->isJumping && !self->isAttacking)
        {
            self->state = ES_attack;
            self->isAttacking = 1;
            self->activeFrames = 11;
            self->sprite = gf2d_sprite_load_all("images/Polnareff/polnareff_b.png",180,155,11,0);
        }
    }
}

void doJoystickButtonUp(SDL_JoyButtonEvent *event, Entity *self)
{
    slog("[%zu] SDL_JOYBUTTONUP\n  Joystick:\t#%i(%i)\n  Button:\t%i\n\n", event->timestamp, 0, event->which, event->button);
    self->input = ButtonNeutral;
    if(!self->isJumping && !self->isAttacking)
    {
        self->state = ES_stand;
        self->sprite = gf2d_sprite_load_all("images/Polnareff/polnareff_idle.png",180,155,13,0);
        self->factor = 3;
    }
}

void player1_think(Entity *self)
{
    if(!self)return;

    //Vector2D dir = {0};

    SDL_Joystick *joystick;
    joystick = SDL_JoystickOpen(0);
    //slog("Open Buttons: %i", SDL_JoystickNumButtons(joystick));
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_JOYBUTTONDOWN:
                doJoystickButtonDown(&event.jbutton, self);
                break;
            case SDL_JOYBUTTONUP:
                doJoystickButtonUp(&event.jbutton, self);
                break;
            default:
                break;
        }
    }
    /*
    if((SDL_JoystickGetAxis(joystick, 1) < -32700 || SDL_JoystickGetButton(joystick, 11) == 1) && self->state != ES_attack && self-> isJumping == 0)
    {
        slog("Jump occured");
        self->state = ES_jump;
        self->isJumping = 1;
        self->jumpStrength = self->jumpHeight;
        self->factor = 3;
        //slog("Current y: %f", self->position.y);
    }
    else if((SDL_JoystickGetAxis(joystick, 1) > 32700 || SDL_JoystickGetButton(joystick, 12) == 1) && self->state != ES_attack && self->state != ES_jump)
    {
        //dir.y = 1;
        self->state = ES_crouch;
        self->sprite = gf2d_sprite_load_all("images/Polnareff/polnareff_crouch.png",180,155,9,0);
        self->factor = 3;
    }
    else if((SDL_JoystickGetAxis(joystick, 0) > 32700 || SDL_JoystickGetButton(joystick, 14) == 1) && self->state != ES_attack && self->state != ES_jump)
    {
        dir.x = 1; //forward walk
        self->state = ES_walk;
        self->sprite = gf2d_sprite_load_all("images/Polnareff/polnareff_walk.png",180,155,10,0);
        self->factor = 3;
    }
    else if((SDL_JoystickGetAxis(joystick, 0) < -32700 || SDL_JoystickGetButton(joystick, 13) == 1) && self->state != ES_attack && self->state != ES_jump)
    {
        dir.x = -1; //backward walk
        self->state = ES_walk;
        self->sprite = gf2d_sprite_load_all("images/Polnareff/polnareff_walk.png",180,155,10,0);
        self->factor = 1.5;
    }
    else if (self->state != ES_attack && self->state != ES_jump)
    {
        self->state = ES_stand;
        self->sprite = gf2d_sprite_load_all("images/Polnareff/polnareff_idle.png",180,155,13,0);
        self->factor = 3;
    }

    if(SDL_JoystickGetButton(joystick, 0) == 1 && self->state != ES_crouch && self->isAttacking == 0)
    {
        self->state = ES_attack;
        self->isAttacking = 1;
        self->activeFrames = 11;
        self->sprite = gf2d_sprite_load_all("images/Polnareff/polnareff_b.png",180,155,11,0);
    }

    else if (self->isAttacking == 0){
       self->state = ES_stand;
    }

    vector2d_normalize(&dir);
    //self->state = ES_stand;
    vector2d_scale(self->moveSpeed,dir,self->factor);*/
}

void player1_update(Entity *self)
{
    if(!self)return;
    Vector2D dir = {0};
    if(self->state == ES_stand && self->position.y == 450){
        dir.x = 0;
        dir.y = 0;
        self->gravity = 0;
        self->isJumping = 0;
        self->isAttacking = 0;
        self->frame += 0.02;
        if(self->frame >= 13)self->frame = 0;
    }
    if(self->state == ES_crouch){
        self->frame += 0.025;
        if(self->frame >= 8)self->frame = 4;
    }
    if(self->state == ES_walk){
        dir.x = 1;
        self->frame += 0.1;
        if(self->frame >= 10)self->frame = 0;
    }
    if(self->state == ES_backwalk){
        dir.x = -1;
        self->frame += 0.1;
        if(self->frame >= 10)self->frame = 0;
    }
    if(self->state == ES_attack){
        self->frame += 0.04;
        if(self->frame >= self->activeFrames)
        {
            self->frame = 0;
            self->isAttacking = 0;
            self->activeFrames = 0;
        }
    }
    if(self->state == ES_jump){
        vector2d_add(self->position, self->position, vector2d(0, -self->jumpStrength));
        self->jumpStrength--;
        self-> gravity = 1;
        if (self->jumpStrength <= 0)
        {
            self->isJumping = 0;
            self->state = ES_stand;
        }
    }

    vector2d_add(self->position, self->position, vector2d(0, self->gravity));

    vector2d_normalize(&dir);
    vector2d_scale(self->moveSpeed,dir,self->factor);

    vector2d_add(self->position,self->position,self->moveSpeed);
}

void player1_free(Entity *self)
{
    if(!self)return;

}


/*eol@eof*/
