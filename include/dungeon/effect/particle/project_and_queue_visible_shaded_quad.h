#ifndef DUNGEON_OVL_1990800_H
#define DUNGEON_OVL_1990800_H

#include "common.h"
#include "dungeon/effect/spell_effect.h"

/* State for the fading sprite sequence advanced by advance_effect_sequence. */
typedef struct FadingSpriteSequenceBody {
    SpellEffectHeader spell;
    u8 pad_0C[0x20];
    u16 unk_2C;
    u16 unk_2E;
    u16 unk_30;
    s16 unk_32;
    u16 unk_34;
    u8 pad_36[0x2];
    u16 unk_38;
    u8 pad_3A[0x12];
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    s16 unk_64;
    s16 unk_66;
    s16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
    u16 unk_76;
    u16 unk_78;
    u16 unk_7A;
    s16 unk_7C;
    s16 unk_7E;
    s16 unk_80;
} FadingSpriteSequenceBody;

#include "modules/dungeon_native_abi.h"

/* Timer, origin, and local offset stored by follow_origin_and_fade_sprite. */
typedef struct OriginFollowingFadeSpriteBody {
    u8 pad_00[0x38];
    u16 ticks_remaining;
    s16 fade_divisor;
    u8 pad_3C[0x4];
    void *base_position;
    u16 offset_x;
    u16 offset_y;
    u16 offset_z;
} OriginFollowingFadeSpriteBody;

/* Bank flag: scalar declaration matches retail scheduling; following tail views remain external. */
extern s16 fading_quad_effect_updated;
void advance_effect_sequence(FadingSpriteSequenceBody *, void *, void *);
#endif
