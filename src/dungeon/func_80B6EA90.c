#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

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
void func_80172290(S_80172290_0 *animation, Rec_D_800E3D7C *motion, Rec_D_80082E80 *destination, Rec_D_800E3D7C *entity) {
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
    motion->unk_14.as_s32 = 0xFFEE0000;
    entity->unk_1C.as_s32 &= 0xF7FFFFFF;
    animation->unk_A0 = 0;
    animation->unk_9B++;

movement:
    frames_left = animation->unk_96.s;
    animation->unk_90 -= animation->unk_A0;
    if (frames_left != 0) {
        {
            s32 target_x = destination->unk_24 << 6;
            s32 current_x = motion->unk_00.at02_s16.v - 0x20;

            motion->unk_0C.as_s32 = ((target_x - current_x) << 16) / frames_left;
        }
        {
            s32 target_y = destination->unk_25 << 6;
            s32 current_y = motion->unk_04.at02_s16.v - 0x20;

            motion->unk_10.at00_s32.v =
                ((target_y - current_y) << 16) / animation->unk_96.s;
        }
        animation->unk_A0 += motion->unk_14.as_s32;
        motion->unk_14.as_s32 += 0x40000;
    }

    animation->unk_90 += animation->unk_A0;
    if (animation->unk_96.s < 2) {
        animation->unk_90 = 0;
        animation->unk_98 &= 0xFFF7;
        entity->unk_1C.as_s32 |= 0x08000000;
        animation->unk_9B++;
    }

check_flag:
    if (entity->unk_1C.as_s32 & 0x08000000) {
        animation->unk_98 &= 0xFFF7;
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800A2B04(motion, destination->unk_24, destination->unk_25);
        animation->unk_9B++;
    }

countdown:
    if ((s16)--animation->unk_96.u <= 0) {
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800A2B04(motion, destination->unk_24, destination->unk_25);
        func_800AD594(entity, 4);
        func_800A4ACC(entity);

        {
            u8 *global_state = (u8 *)&D_80083460;

            if (((S_80172290_4 *)global_state)->unk_08.s != 0) {
                ((S_80172290_4 *)global_state)->unk_08.u--;
            }
        }

        entity_flags = entity->unk_1C.as_s32;
        if (!(entity_flags & 0x2000)) {
            goto low_flags;
        }
        if (entity->unk_44.at02_u16.v & 0x8000) {
            entity->unk_44.at02_u16.v &= 0x7FFF;
        }
        goto call_entity;

low_flags:
        if (entity_flags & 0x410) {
            goto call_entity;
        }
        if (entity_flags & 0x20000) {
            u8 *map_state = D_80082E80;

            entity->unk_2A.as_s16 = func_800A0818(
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
