#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern s32 func_800AD9B4(void *, void *);
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u8 D_8016B778[];
extern u8 D_8017467C[];
extern u8 D_80174684[];

typedef struct S_8016CB80_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    s32 unk_A0;
    u8 pad_A4[0xF];
    u8 unk_B3;
} S_8016CB80_0;   /* arg0 in func_8016CB80 */


typedef struct S_8016CB80_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { void * p; u8 * p2; } unk_2C;   /* accessed as both */
} S_8016CB80_2;   /* arg2 in func_8016CB80 */


typedef struct S_8016CB80_4 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_8016CB80_4;   /* temp_a0_2 in func_8016CB80 */

/* Updates movement, directional animation, and action completion. */
void func_8016CB80(void *state, void *motion_arg, void *actor_arg, void *entity_arg) {
    void *motion = motion_arg;
    register void *actor ASM_REG("$17") = actor_arg;
    void *entity = entity_arg;
    M2C_UNK direction_info;
    s32 move_ticks;
    s32 next_move_ticks;
    s32 tile_x;
    s32 pixel_offset;
    s32 entity_flags;
    u16 action_ticks;
    u16 status_flags;
    s32 phase;
    u8 *action_counter;
    register void *current_anims;
    u8 *anims;

    phase = ((S_8016CB80_0 *)state)->unk_9B;
    if (phase == 1) {
        goto update_move;
    }
    if ((s32) phase < 2) {
        if (phase == 0) {
            goto start_move;
        }
        goto update_timer;
    }
    if (phase == 2) {
        goto finish_move;
    }
    if (phase == 3) {
        goto update_animation;
    }
    goto update_timer;
start_move:
    ((S_8016CB80_0 *)state)->unk_98 = (u16) (((S_8016CB80_0 *)state)->unk_98 | 8);
    ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0xF7FFFFFF);
    ((S_8016CB80_0 *)state)->unk_9E = 5;
    ((S_8016CB80_0 *)state)->unk_A0 = 0;
    ((S_8016CB80_0 *)state)->unk_9B = (u8) (((S_8016CB80_0 *)state)->unk_9B + 1);
update_move:
    move_ticks = ((S_8016CB80_0 *)state)->unk_9E;
    ((S_8016CB80_0 *)state)->unk_90 = (s32) (((S_8016CB80_0 *)state)->unk_90 - ((S_8016CB80_0 *)state)->unk_A0);
    if (move_ticks != 0) {
        tile_x = ((S_8016CB80_2 *)actor)->unk_24;
        ASM_KEEP(tile_x);
        pixel_offset = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (s32) ((s32) (((tile_x << 6) - pixel_offset) << 0x10) / move_ticks);
        pixel_offset = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (s32) ((s32) (((((S_8016CB80_2 *)actor)->unk_25 << 6) - pixel_offset) << 0x10) / (s16) ((S_8016CB80_0 *)state)->unk_9E);
        ((S_8016CB80_0 *)state)->unk_A0 = (s32) ((0 - func_800644B8(((S_8016CB80_0 *)state)->unk_9E * 0x199)) << 0xA);
    }
    ((S_8016CB80_0 *)state)->unk_90 = (s32) (((S_8016CB80_0 *)state)->unk_90 + ((S_8016CB80_0 *)state)->unk_A0);
    next_move_ticks = (u16) ((S_8016CB80_0 *)state)->unk_9E - 1;
    ((S_8016CB80_0 *)state)->unk_9E = next_move_ticks;
    if ((next_move_ticks << 0x10) < 0) {
        ((S_8016CB80_0 *)state)->unk_90 = 0;
        ((S_8016CB80_0 *)state)->unk_98 = (u16) (((S_8016CB80_0 *)state)->unk_98 & 0xFFF7);
        ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 | 0x08000000);
        ((S_8016CB80_0 *)state)->unk_9B = (u8) (((S_8016CB80_0 *)state)->unk_9B + 1);
    }
finish_move:
    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x08000000) {
        ((S_8016CB80_0 *)state)->unk_98 = (u16) (((S_8016CB80_0 *)state)->unk_98 & 0xFFF7);
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((S_8016CB80_2 *)actor)->unk_24, ((S_8016CB80_2 *)actor)->unk_25);
        ((S_8016CB80_0 *)state)->unk_9B = (u8) (((S_8016CB80_0 *)state)->unk_9B + 1);
        goto update_timer;
    }
    goto update_timer;
update_animation:
    if (((S_8016CB80_0 *)state)->unk_B3 == 0) {
        current_anims = ((S_8016CB80_2 *)actor)->unk_2C.p;
        anims = (u8 *)&D_8017467C;
    } else {
        current_anims = ((S_8016CB80_2 *)actor)->unk_2C.p;
        anims = D_80174684;
    }
    if (current_anims != anims) {
        (*(u8 **)((u8 *)actor + 0x2C)) = anims;
        func_80047784(actor, *(u8 *)((((s32) (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7) + (u32)anims), 0);
    }
update_timer:
    action_ticks = ((S_8016CB80_0 *)state)->unk_96 - 1;
    ((S_8016CB80_0 *)state)->unk_96 = action_ticks;
    if ((action_ticks << 0x10) <= 0) {
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((S_8016CB80_2 *)actor)->unk_24, ((S_8016CB80_2 *)actor)->unk_25);
        func_800A4ACC(entity);
        action_counter = D_80083460;
        if (((S_8016CB80_4 *)action_counter)->unk_08 != 0) {
            ((S_8016CB80_4 *)action_counter)->unk_08 = (s16) ((u16) ((S_8016CB80_4 *)action_counter)->unk_08 - 1);
        }
        entity_flags = ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32;
        if (entity_flags & 0x2000) {
            status_flags = ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v;
            if (!(status_flags & 0x8000)) {
                goto finish_action;
            }
            ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v = status_flags & 0x7FFF;
            goto finish_action;
        }
        if (entity_flags & 0x410) {
            goto finish_action;
        }
        if (!(entity_flags & 0x20000)) {
            goto finish_action;
        }
        ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = func_800A0818(((S_8016CB80_2 *)actor)->unk_24, ((S_8016CB80_2 *)actor)->unk_25, D_80082E80[0x24], D_80082E80[0x25], &direction_info);
finish_action:
        if ((func_800AD9B4(actor, entity) << 0x10) > 0) {
            ((S_8016CB80_0 *)state)->unk_8C = D_8016B778;
            func_800A9A04(entity);
        }
    }
}

