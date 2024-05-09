#ifndef __INPUT_H__
#define __INPUT_H__

#include <SDL.h>
#include "gfc_text.h"
#include "gfc_list.h"

typedef enum
{
    ButtonNeutral = 0,
    ButtonA,
    ButtonB,
    ButtonC,
    ButtonD,
    ButtonTag,
    ButtonStart,
    ButtonUp,
    ButtonDown,
    ButtonLeft,
    ButtonRight,
    ButtonUpLeft,
    ButtonUpRight,
    ButtonDownLeft,
    ButtonDownRight
}InputAction;

typedef struct IBuffer
{
    Uint32 InputBufferInternal[90];
    Uint32 FrameInputted[90];
    Uint32 BufferHeld[90];
}InputBuffer;

typedef struct ValidSequences
{
    char qcf_a[4];
    char qcf_b[4];
    char chargeF_a[3];
}InputSequence;

//void tick(InputAction action, Uint32[] bufferObj);

//uint8 checkInputSequence();

#endif
