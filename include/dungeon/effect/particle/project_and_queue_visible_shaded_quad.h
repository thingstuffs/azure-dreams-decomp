#ifndef DUNGEON_OVL_1990800_H
#define DUNGEON_OVL_1990800_H

#include "common.h"
#include "dungeon/effect/spell_effect.h"

/* State for the fading sprite sequence advanced by advance_effect_sequence. */
typedef struct FadingSpriteSequenceBody {
    SpellEffectHeader spell;
    u8 pad_0C[0x20];
    union { u16 s; s16 u; } unk_2C;   /* accessed as both */
    union { s16 s; u16 u; } unk_2E;   /* accessed as both */
    union { s16 s; u16 u; } unk_30;   /* accessed as both */
    union { s16 s; u16 u; } unk_32;   /* accessed as both */
    u16 unk_34;
    u8 pad_36[0x2];
    u16 unk_38;
    u8 pad_3A[0x12];
    union { u16 s; s16 u; } unk_4C;   /* accessed as both */
    union { u16 s; s16 u; } unk_4E;   /* accessed as both */
    union { u16 s; s16 u; } unk_50;   /* accessed as both */
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    union { u16 s; s16 u; } unk_58;   /* accessed as both */
    union { u16 s; s16 u; } unk_5A;   /* accessed as both */
    union { u16 s; s16 u; } unk_5C;   /* accessed as both */
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    union { u16 s; s16 u; } unk_64;   /* accessed as both */
    union { u16 s; s16 u; } unk_66;   /* accessed as both */
    union { u16 s; s16 u; } unk_68;   /* accessed as both */
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
    union { u16 s; s16 u; } unk_70;   /* accessed as both */
    union { u16 s; s16 u; } unk_72;   /* accessed as both */
    union { u16 s; s16 u; } unk_74;   /* accessed as both */
    u16 unk_76;
    u16 unk_78;
    u16 unk_7A;
    union { u16 s; s16 u; } unk_7C;   /* accessed as both */
    union { u16 s; s16 u; } unk_7E;   /* accessed as both */
    union { u16 s; s16 u; } unk_80;   /* accessed as both */
} FadingSpriteSequenceBody;

#include "modules/dungeon_native_abi.h"
#include "common.h"

/* Timer, origin, and local offset stored by follow_origin_and_fade_sprite. */
typedef struct OriginFollowingFadeSpriteBody {
    u8 pad_00[0x38];
    union { u16 u; s16 s; } ticks_remaining;
    s16 fade_divisor;
    u8 pad_3C[0x4];
    void *base_position;
    u16 offset_x;
    u16 offset_y;
    u16 offset_z;
} OriginFollowingFadeSpriteBody;

/* Bank flag: scalar declaration matches retail scheduling; following tail views remain external. */
extern s16 fading_quad_effect_updated;
void advance_effect_sequence(void *, void *, void *);
#endif
