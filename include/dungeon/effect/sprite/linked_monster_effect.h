#ifndef DUNGEON_EFFECT_SPRITE_LINKED_MONSTER_EFFECT_H
#define DUNGEON_EFFECT_SPRITE_LINKED_MONSTER_EFFECT_H

#include "common.h"
#include "shared/object_node.h"

/* Body of a node allocated by create_linked_object_chain. */
typedef struct LinkedObjectChainBody {
    u8 pad_00[0x20];
    ObjectNodeHeader *head;
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    s16 unk_2E;
    union { s16 n; u16 v; } unk_30;   /* accessed as both */
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    s16 unk_38;
    u16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    union { u16 u; s16 s; } unk_40;   /* accessed as both */
    u16 unk_42;
} LinkedObjectChainBody;

#endif
