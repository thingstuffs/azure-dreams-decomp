#ifndef DUNGEON_EFFECT_POPUP_BODY_H
#define DUNGEON_EFFECT_POPUP_BODY_H

#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"

/* create_actor_value_popup installs either fading callback on this body. */
typedef struct ActorValuePopupBody {
    ObjectNodeHeader *owner;
    /* UNION: src/dungeon/effect/update_anchored_fading_effect.c:56,116,119; src/dungeon/effect/update_attached_fading_effect.c:65,125,128 - the same velocity word is stored and read whole (lw/sw, >> 1) and read through its high halfword. */
    union { struct { s32 v; } at00; struct { u8 pad[2]; s16 v; } at02; } unk_04;
    s16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[2];
    ObjectPosition *anchor_position;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
} ActorValuePopupBody;

#endif
