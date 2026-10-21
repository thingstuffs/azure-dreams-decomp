/* Relinked copy of dungeon/func_80D65C5C (func_80D65C5C.c); retail differs only at relocation sites. */
#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"



typedef struct S_80D65C5C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80D65C5C_0;   /* node in spawn_baloon_directional_puff_slot_a */

typedef struct S_80D65C5C_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80D65C5C_1;   /* arg0 in spawn_baloon_directional_puff_slot_a */

typedef struct S_80D65C5C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} S_80D65C5C_2;   /* sprite in spawn_baloon_directional_puff_slot_a */

typedef struct S_80D65C5C_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80D65C5C_3;   /* part in spawn_baloon_directional_puff_slot_a */

typedef struct S_80D65C5C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80D65C5C_4;   /* ((S_80D65C5C_0 *)node)->unk_08 in spawn_baloon_directional_puff_slot_a */

typedef struct S_80D65C5C_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D65C5C_5;   /* ((S_80D65C5C_1 *)arg0)->unk_08 in spawn_baloon_directional_puff_slot_a */

typedef struct S_80D65C5C_6 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80D65C5C_6;   /* ((S_80D65C5C_0 *)node)->unk_0C in spawn_baloon_directional_puff_slot_a */


extern s32 rand(void);
extern void register_node(void *, void *);
extern void func_8003DB94(void *, void *, s32);

extern s32 effect_sprite_sources;
extern s16 actor_direction_step_pairs[];
extern u8 D_8014D384[];

/* Spawns a directional sprite effect near the source with randomized velocity. */
void spawn_baloon_directional_puff_slot_a(S_80D65C5C_1 *source, s32 angle)
{
    void *node;
    S_80D65C5C_2 *sprite;
    s16 *direction_step;

    node = func_8003FC64(0x212);
    if (node != 0) {
        ((S_80D65C5C_0 *)node)->unk_10 = D_8014D384;

        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_02 =
            ((S_80D65C5C_5 *)(source->unk_08))->unk_02;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_06 =
            ((S_80D65C5C_5 *)(source->unk_08))->unk_06;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_0A =
            ((S_80D65C5C_5 *)(source->unk_08))->unk_0A - 0x58;

        direction_step = (s16 *)((u8 *)actor_direction_step_pairs + (((u32)angle >> 7) & 0x1C));
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_02 += direction_step[0] * 0x12;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_06 += direction_step[1] * 0x12;

        ((S_80D65C5C_6 *)(((S_80D65C5C_0 *)node)->unk_0C))->unk_06 = 6;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_0C =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_10 =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_14 =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;

        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_0C +=
            direction_step[0] * 0x1C0000;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_10 +=
            direction_step[1] * 0x1C0000;

        sprite = (u8 *)node + 0x20;
        sprite->unk_0A = angle;
        sprite->unk_0C = 0xC;
        sprite->unk_0E = 0xC;
        register_node(node, project_sprite_chain);

        {
            S_80D65C5C_3 *part = ((S_80D65C5C_0 *)node)->unk_0C;

            part->unk_14 |= 0xC;
            part->unk_10 = 0x60;
            part->unk_14 |= 2;
            part->unk_1C = 0x800;
            part->unk_1E = 0x800;
            part->unk_0E = 0x80;
            part->unk_0D = 0x80;
            part->unk_0C = 0x80;
            part->unk_14 |= 0x100;
            part->unk_12 = 0x7DCF;
            func_8003DB94(part, &effect_sprite_sources, 0);
        }
    }
}
