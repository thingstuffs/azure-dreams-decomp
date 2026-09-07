#include "common.h"

typedef struct S_80172290_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} S_80172290_0;   /* arg0 in func_80172290 */

typedef struct S_80172290_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172290_1;   /* arg1 in func_80172290 */

typedef struct S_80172290_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172290_2;   /* arg3 in func_80172290 */

typedef struct S_80172290_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172290_3;   /* arg2 in func_80172290 */

typedef struct S_80172290_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_80172290_4;   /* global_state in func_80172290 */

typedef struct S_80172290_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172290_5;   /* map_state in func_80172290 */



extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s32 D_80083460;
extern s32 D_80170E5C;

/* Advance arcing movement toward the destination tile and finalize the landing. */
void func_80172290(S_80172290_0 *animation, S_80172290_1 *motion, S_80172290_3 *destination, S_80172290_2 *entity) {
    s32 query_output;
    s32 frames_left;
    s32 entity_flags;
    s32 phase;

    phase = animation->unk_9B;
    if (phase == 1) {
        goto movement;
    }
    if (phase >= 2) {
        goto high_state;
    }
    if (phase == 0) {
        goto initialize;
    }
    goto countdown;

high_state:
    if (phase == 2) {
        goto check_flag;
    }
    goto countdown;

initialize:
    animation->unk_98 |= 8;
    motion->unk_14 = 0xFFEE0000;
    entity->unk_1C &= 0xF7FFFFFF;
    animation->unk_A0 = 0;
    animation->unk_9B++;

movement:
    frames_left = animation->unk_96.s;
    animation->unk_90 -= animation->unk_A0;
    if (frames_left != 0) {
        {
            s32 target_x = destination->unk_24 << 6;
            s32 current_x = motion->unk_02 - 0x20;

            motion->unk_0C = ((target_x - current_x) << 16) / frames_left;
        }
        {
            s32 target_y = destination->unk_25 << 6;
            s32 current_y = motion->unk_06 - 0x20;

            motion->unk_10 =
                ((target_y - current_y) << 16) / animation->unk_96.s;
        }
        animation->unk_A0 += motion->unk_14;
        motion->unk_14 += 0x40000;
    }

    animation->unk_90 += animation->unk_A0;
    if (animation->unk_96.s < 2) {
        animation->unk_90 = 0;
        animation->unk_98 &= 0xFFF7;
        entity->unk_1C |= 0x08000000;
        animation->unk_9B++;
    }

check_flag:
    if (entity->unk_1C & 0x08000000) {
        animation->unk_98 &= 0xFFF7;
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, destination->unk_24, destination->unk_25);
        animation->unk_9B++;
    }

countdown:
    if ((s16)--animation->unk_96.u <= 0) {
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, destination->unk_24, destination->unk_25);
        func_800AD594(entity, 4);
        func_800A4ACC(entity);

        {
            u8 *global_state = (u8 *)&D_80083460;

            if (((S_80172290_4 *)global_state)->unk_08.s != 0) {
                ((S_80172290_4 *)global_state)->unk_08.u--;
            }
        }

        entity_flags = entity->unk_1C;
        if (!(entity_flags & 0x2000)) {
            goto low_flags;
        }
        if (entity->unk_46 & 0x8000) {
            entity->unk_46 &= 0x7FFF;
        }
        goto call_entity;

low_flags:
        if (entity_flags & 0x410) {
            goto call_entity;
        }
        if (entity_flags & 0x20000) {
            u8 *map_state = D_80082E80;

            entity->unk_2A = func_800A0818(
                destination->unk_24, destination->unk_25,
                ((S_80172290_5 *)map_state)->unk_24, ((S_80172290_5 *)map_state)->unk_25, &query_output);
        }

call_entity:
        if ((func_800AD9B4(destination, entity) << 16) > 0) {
            animation->unk_8C = &D_80170E5C;
            func_800A9A04(entity);
        }
    }

done:
    return;
}
