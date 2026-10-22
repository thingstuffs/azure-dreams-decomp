#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_particle_template.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x20];
    s32 field_20;
} EffectFieldView_8132E83C;


typedef struct Copy12 {
    s32 word[3];
} __attribute__((packed)) Copy12;

void register_node(void *, void *);
s32 rand(void);
extern u8 D_801654F0[];


typedef struct S_8016583C_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8016583C_0;   /* arg0 in create_short_lived_colored_particle */

typedef struct S_8016583C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0xC];
    u16 unk_42;
    u16 unk_44;
    u16 unk_46;
} S_8016583C_1;

typedef struct S_8016583C_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8016583C_2;

typedef struct S_8016583C_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8016583C_3;

   /* ((S_8016583C_0 *)arg0)->unk_08 in create_short_lived_colored_particle */

/* Spawn an effect at an offset from the source with randomized horizontal velocity. */
void create_short_lived_colored_particle(S_8016583C_0 *source, s16 duration, s32 scale, s16 offset_x, s16 offset_y, s16 offset_z,
    s32 velocity_z) {
    S_8016583C_2 *sprite;
    S_8016583C_1 *effect_state;
    ObjectNodeHeader *effect;
    s32 held_scale ;

    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        held_scale = scale;
        (effect->unk_10) = &D_801654F0;
        ((S_8016583C_3 *)((effect->position)))->unk_02 =
            (s16) (((MovingPosition *)(source->unk_08))->unk_02 + offset_x);
        ((S_8016583C_3 *)((effect->position)))->unk_06 =
            (s16) (((MovingPosition *)(source->unk_08))->unk_06 + offset_y);
        ((S_8016583C_3 *)((effect->position)))->unk_0A =
            (s16) (((MovingPosition *)(source->unk_08))->unk_0A + offset_z);
        effect_state = ((void *)effect) + 0x20;
        effect_state->unk_42 = (u16) ((MovingPosition *)(source->unk_08))->unk_02;
        effect_state->unk_44 = (u16) ((MovingPosition *)(source->unk_08))->unk_06;
        effect_state->unk_46 = (u16) ((MovingPosition *)(source->unk_08))->unk_0A;
        ((S_8016583C_3 *)((effect->position)))->unk_0C = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((S_8016583C_3 *)((effect->position)))->unk_10 = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((S_8016583C_3 *)((effect->position)))->unk_14 = velocity_z;
        effect_state->unk_14 = duration;
        effect_state->unk_32 = 8;
        effect_state->unk_34 = 8;
        register_node(effect, project_sprite_chain);
        sprite = (effect->sprite);
        sprite->unk_1E = 0x200;
        sprite->unk_1C = 0x200;
        sprite->unk_0C = held_scale;
        sprite->unk_14 = (u16) (sprite->unk_14 & 0xFFF3);
        (((EffectFieldView_8132E83C *)effect)->field_20) = held_scale;
        effect_state->unk_04 = held_scale;
        effect_state->unk_08 = held_scale;
        (*(Copy12 *)((u8 *)effect + 0x56)) =
            (*(Copy12 *)((u8 *)&particle_sprite_template + 0));
        sprite->unk_08 = (void *) (((void *)effect) + 0x56);
    }
}

/* MECHANISM: The stack-passed offsets and duration are declared s16, so assign_parms
   holds each entry value through a narrowing conversion instead of sinking a single-use
   stack load to its use; offset_y/offset_z stay in $s3/$s4 across func_8003FC64,
   giving the 0x30 frame and save order. One packed 12-byte assignment emits the
   retail lwl/lwr plus swl/swr copy sequence. */
