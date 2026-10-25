#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_8016ECE4_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8016ECE4_0;   /* base in spawn_conditional_source_effect */

typedef struct S_8016ECE4_1 {
    u8 pad_00[0x12];
    s16 unk_12;
    u8 pad_14[0x4];
    s16 unk_18;
    u8 pad_1A[0xA];
    void * unk_24;
    u8 pad_28[0x1C];
    s8 unk_44;
    s8 unk_45;
    s8 unk_46;
    s8 unk_47;
    s8 unk_48;
    s8 unk_49;
    u8 pad_4A[0x2];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} S_8016ECE4_1;

typedef struct S_8016ECE4_5 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8016ECE4_5;

typedef struct S_8016ECE4_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x7E];
    s16 unk_AA;
} S_8016ECE4_6;

typedef struct {
    s16 field0;
    s16 field2;
} TableEntry;

s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
s32 rand();
extern M2C_UNK D_800777F4;
extern u8 ghosh_object_callback;
extern void *ghosh_actor_node[];
extern TableEntry ghosh_effect_direction_offsets[];

/* Spawn and initialize an effect at the source position when its mode and status allow it. */
void spawn_conditional_source_effect(void) {
    s32 rounded_x;
    s32 rounded_y;
    u8 high_byte;
    u8 low_byte;
    u16 count;
    register SpriteFrameState *sprite;
    S_8016ECE4_1 *effect_state;
    S_8016ECE4_5 *source_pos;
    S_8016ECE4_6 *source_state;
    ObjectNodeHeader *effect;
    ObjectPosition *effect_pos;
    void *source;

    source = ghosh_actor_node[0];
    {
        u8 *addr = (u8 *)0x80010000;   /* integer page, two genuine reads of the 16-bit counter at 0x80013610 (decision 44; func_8132C638 uses the same counter) */
        low_byte = addr[0x3611];
        high_byte = addr[0x3610];
    }
    count = low_byte | (high_byte << 8);
    source_pos = ((S_8016ECE4_0 *)source)->unk_08;
    source_state = source + 0x20;
    if (((count & 3) == 1) && !(rand(source) & 1)) {
        effect = allocate_flagged_object_node(0x12);
        if (effect != NULL) {
            effect_state = ((void *)effect) + 0x20;
            effect_state->unk_12 = 3;
            effect->update_callback = &ghosh_object_callback;
            register_node(effect, project_sprite_chain);
            sprite = effect->sprite;
            sprite->flags = (u16) (sprite->flags & 0xFFF3);
            effect_state->unk_24 = source_state;
            effect_pos = effect->position;
            effect_pos->x.w.i = (u16) source_pos->unk_02.s;
            effect_pos->y.w.i = (u16) source_pos->unk_06.s;
            effect_pos->z.w.i = (s16) (source_pos->unk_0A - 0x80);
            effect_state->unk_50 = 0;
            effect_state->unk_4C = 0;
            effect_state->unk_54 = 0;
            effect_state->unk_60 = 0;
            effect_state->unk_18 = (s16) (((u16) source_state->unk_2A >> 9) & 7);
            sprite = effect->sprite;
            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            sprite->depth_bias = (s16) (ghosh_effect_direction_offsets[((u16) source_state->unk_2A >> 9) & 7].field2 * 6);
            source_state->unk_AA = 0x4D;
            rounded_x = source_pos->unk_02.u;
            effect_state->unk_48 = (s8) (rounded_x / 64);
            rounded_y = source_pos->unk_06.u;
            effect_state->unk_49 = (s8) (rounded_y / 64);
            sprite->color.c.b = 0x80;
            sprite->color.c.g = 0x80;
            sprite->color.c.r = 0x80;
            sprite->source = &D_800777F4;
            sprite->flags = (u16) (sprite->flags | 0x80);
            effect_state->unk_44 = 3;
            effect_state->unk_45 = 6;
            effect_state->unk_46 = 0;
            effect_state->unk_47 = 0;
        }
    }
}
