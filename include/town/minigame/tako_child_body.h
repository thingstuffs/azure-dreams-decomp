#ifndef TOWN_MINIGAME_TAKO_CHILD_BODY_H
#define TOWN_MINIGAME_TAKO_CHILD_BODY_H

#include "common.h"

/* Body of a Tako child allocated and linked by initialize_tako_minigame. */
typedef struct TakoChildBody {
    /* 0x00 */ void *parent;
    /* 0x04 */ u8 pad_04[0x48];
    /* 0x4C */ void *resource;
    /* 0x50 */ u8 pad_50[6];
    /* 0x56 */ s16 column_index;
} TakoChildBody;

#endif
