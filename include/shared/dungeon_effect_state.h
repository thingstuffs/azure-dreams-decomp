#ifndef SHARED_DUNGEON_EFFECT_STATE_H
#define SHARED_DUNGEON_EFFECT_STATE_H

#include "common.h"
#include "shared/entity.h"

/* The shared 0x98-byte dungeon effect body. Named union views retain each access width. */
typedef struct B22_81893474_EffectState {
    union { ActorRecord *actor; void *address; } owner; /* +0x00: borrowed owner, also passed through generic effect callbacks */
    union { void *address; u16 *flags; } image; /* +0x04: image address and its leading flag halfword */
    u8 unk8;
    u8 id;
    union { s16 s; u16 u; } state;
    union { s16 s; u16 u; } unkC;
    union { s16 s; u16 u; } direction;
    union { s16 s; u16 u; u8 low_byte; } timer;
    union { s16 s; u16 u; } duration;
    union { s16 s; u16 u; } field_14;
    union { s16 s; u16 u; } x;
    union { s16 s; u16 u; } y;
    union { s16 s; u16 u; } z;
    u8 status;
    u8 pad1D[3];
    union { s16 s; u16 u; } unk_20; /* +0x20 */
    u8 pad22[0x2E];
    union { s16 s; u16 u; } unk_50; /* +0x50 */
    union { s16 s; u16 u; } unk_52; /* +0x52 */
    u8 pad54[0x24];
    union { s16 s; u16 u; } unk_78; /* +0x78 */
    u8 pad7A[4];
    union { s16 s; u16 u; } unk_7E; /* +0x7E */
    u8 pad80[2];
    union { s16 s; u16 u; } unk_82; /* +0x82 */
    u8 pad84[0x14];
} B22_81893474_EffectState;

#endif
