#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CB9DC_0_pre {
    u16 unk_00;
} S_800CB9DC_0_pre;   /* the 0x2 bytes before arg0 in func_800CB9DC, addressed as arg0[-1] */

typedef struct S_800CB9DC_0 {
    void * unk_00;
    u8 pad_04[0x2];
    u16 unk_06;
} S_800CB9DC_0;   /* arg0 in func_800CB9DC */

typedef struct S_800CB9DC_1_pre {
    void * unk_00;
    M2C_UNK * unk_04;
    u8 pad_08[0xE];
    u16 unk_16;
} S_800CB9DC_1_pre;   /* the 0x18 bytes before temp_s1 in func_800CB9DC, addressed as temp_s1[-1] */

typedef struct S_800CB9DC_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800CB9DC_1;   /* temp_s1 in func_800CB9DC */

typedef struct S_800CB9DC_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x21C];
    s32 unk_234;
    u8 pad_238[0x34DC];
    u16 unk_3714;
} S_800CB9DC_2;   /* arg1 in func_800CB9DC */

typedef struct S_800CB9DC_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800CB9DC_3;   /* temp_a0 in func_800CB9DC */

typedef struct S_800CB9DC_4 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800CB9DC_4;   /* arg2 in func_800CB9DC */

typedef struct S_800CB9DC_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800CB9DC_5;   /* counts in func_800CB9DC */

typedef struct S_800CB9DC_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CB9DC_6;   /* temp_a1 in func_800CB9DC */

typedef struct S_800CB9DC_7 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800CB9DC_7;   /* page14 in func_800CB9DC */

typedef struct S_800CB9DC_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CB9DC_8;   /* base34 in func_800CB9DC */

typedef struct S_800CB9DC_9 {
    u8 pad_00[0x14A0];
    union { volatile s32 s; s32 u; } unk_14A0;   /* accessed as both */
} S_800CB9DC_9;   /* page14_again in func_800CB9DC */


M2C_UNK func_80040AA0();               /* extern */
M2C_UNK func_800478B8();                      /* extern */
M2C_UNK func_800481E0();                            /* extern */
M2C_UNK func_800945E8();           /* extern */
M2C_UNK func_800948BC();                            /* extern */
M2C_UNK func_8009A028();                      /* extern */
M2C_UNK func_8009A3D0();             /* extern */
M2C_UNK func_800A32A4();                      /* extern */
M2C_UNK func_800A6780();                            /* extern */
extern s32 D_80010234;
extern M2C_UNK D_80013714;
extern s16 D_80081468[3];
extern M2C_UNK D_800814A0;
extern u8 D_80082E6B;
extern M2C_UNK D_80083460;
extern u8 *D_800E3D7C;

/* Updates go-up trap motion, then advances the player or removes the affected actor. */
void func_800CB9DC(void *trap_state_in, void *motion_state_in, void *animation_in) {
    void *trap_state = trap_state_in;
    S_800CB9DC_2 *motion_state = motion_state_in;
    register S_800CB9DC_4 *animation ASM_REG("$18") = animation_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    M2C_UNK *actor_data;
    M2C_UNK tile_mask;
    s32 vertical_speed;
    u16 elapsed_frames;
    S_800CB9DC_3 *position;
    void *actor;

    func_800478B8(animation);
    ASM_KEEP(trap_state); /* MATCH: preserve the trap-state save order after sharing the final update. */
    actor = ((S_800CB9DC_0 *)trap_state)->unk_00;
    actor_data = ((S_800CB9DC_1_pre *)actor)[-1].unk_04;
    position = ((S_800CB9DC_1_pre *)actor)[-1].unk_00;
    vertical_speed = motion_state->unk_14 + 0xFFFA0000;
    motion_state->unk_14 = vertical_speed;
    position->unk_08 = (s32) (position->unk_08 + vertical_speed);
    elapsed_frames = ((S_800CB9DC_0 *)trap_state)->unk_06 + 1;
    ((S_800CB9DC_0 *)trap_state)->unk_06 = elapsed_frames;
    if (((s16) elapsed_frames >= 0x41) || ((animation->unk_14 & 0x8000) != 0)) {
        if (actor == D_800E3D7C) {
            s16 *trap_counts;
            u8 transition_id;
            register u8 *transition_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            register s32 floors_ascended ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            u16 go_up_trap_count;

            motion_state = (void *)0x80010000;
            ASM_KEEP(motion_state);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            if (motion_state->unk_3714 & 4) {
                func_80040AA0(3U, actor_data);
            } else {
                func_800945E8(actor, actor_data);
                func_800948BC();
                func_800A6780();
                transition_page = (u8 *)0x80080000;
                ASM_KEEP(transition_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                trap_counts = D_80081468;
                transition_id = transition_page[0x2E6B];
                floors_ascended = motion_state->unk_234;
                go_up_trap_count = ((S_800CB9DC_5 *)trap_counts)->unk_04;
                floors_ascended++;
                go_up_trap_count++;
                motion_state->unk_234 = floors_ascended;
                ((S_800CB9DC_5 *)trap_counts)->unk_04 = go_up_trap_count;
                func_80040AA0(transition_id, trap_counts);
                func_800481E0();
            }
        } else {
            {
                s32 tile_x;
                s32 tile_y;
                s32 actor_flags;

                actor_flags = ((S_800CB9DC_1 *)actor)->unk_1C;
                tile_x = ((S_800CB9DC_6 *)actor_data)->unk_24;
                tile_y = ((S_800CB9DC_6 *)actor_data)->unk_25;
                tile_mask = 0x3000;
                if (actor_flags & 0x2000) {
                    tile_mask = 0x300;
                }
                func_8009A3D0(tile_x, tile_y, tile_mask);
            }
            func_800A32A4(actor);
            func_8009A028(actor);
            {
                register u8 *status_page ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                u8 *actor_counts;
                register s32 global_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                u16 actor_count;
                u16 removal_flags;

                status_page = (u8 *)0x80080000;
                actor_counts = (u8 *)&D_80083460;
                removal_flags = ((S_800CB9DC_1_pre *)actor)[-1].unk_16;
                ((S_800CB9DC_1_pre *)actor)[-1].unk_16 = removal_flags | 0x8000;
                global_flags = ((S_800CB9DC_7 *)status_page)->unk_14A0;
                actor_count = ((S_800CB9DC_8 *)actor_counts)->unk_0A;
                global_flags |= 0x8000;
                actor_count--;
                ((S_800CB9DC_7 *)status_page)->unk_14A0 = global_flags;
                ((S_800CB9DC_8 *)actor_counts)->unk_0A = actor_count;
                ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            }
        }
        {
            s32 global_flags;
            u8 *status_page_again;
            u16 removal_flags;

            removal_flags = ((S_800CB9DC_0_pre *)trap_state)[-1].unk_00;
            status_page_again = (u8 *)0x80080000;
            ((S_800CB9DC_0_pre *)trap_state)[-1].unk_00 = removal_flags | 0x8000;
            global_flags = ((S_800CB9DC_9 *)status_page_again)->unk_14A0.s;
            global_flags |= 0x8000;
            ((S_800CB9DC_9 *)status_page_again)->unk_14A0.u = global_flags;
        }
    }
}
/* MECHANISM: Pinned long-lived args reproduce the s3/s0/s2 prologue, with keeps after the first call.
   Split RMW locals and ABI-pinned call args recover both interleaved load/store schedules.
   Held page bases plus a symbolic D_80083460 base and dead-$a1 clobber force the final rematerialization. */
