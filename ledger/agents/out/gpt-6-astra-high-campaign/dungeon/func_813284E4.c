#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800814A8.h"
#ifdef NON_MATCHING
#include <stdint.h>
typedef uintptr_t uptr;
#else
typedef u32 uptr;
#endif

typedef struct S_8016FCE4_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
} S_8016FCE4_0;   /* arg3 in func_8016FCE4 */

typedef struct S_8016FCE4_1 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
} S_8016FCE4_1;   /* arg2 in func_8016FCE4 */

typedef struct S_8016FCE4_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8016FCE4_2_pre;   /* the 0x14 bytes before temp_v0 in func_8016FCE4, addressed as temp_v0[-1] */

typedef struct S_8016FCE4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016FCE4_3;   /* temp_v0_2 in func_8016FCE4 */

typedef struct S_8016FCE4_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8016FCE4_4;   /* heading_base in func_8016FCE4 */



typedef struct S_8016FCE4_7 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8016FCE4_7;   /* counter_base in func_8016FCE4 */

typedef struct S_8016FCE4_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016FCE4_8;   /* (arg3 + ((u8) ((S_8016FCE4_0 *)arg3)->unk_71.s & 0x7F)) in func_8016FCE4 */


s32 func_8009A180(void *, void *);
void func_8009A21C(s32, s32, s32);
void func_8009A3D0(s32, s32, s32);
s32 func_8009A66C(s32, void *, void *, s32);
s32 func_8009FD7C(s32, s32, s32, s32);
void *func_800A02AC(void *, s32, s32);
s32 func_800A04F0(void *, s32, s32, s32);
s16 func_800A0818(s32, s32, s32, s32, void *);
void func_800A0E6C(void *, s32, void *, void *);
void func_800A19E4(void *, void *, s32, s32, void *);
s32 func_800A6D30(void);
void func_800A9A0C(void *);
extern void call_800A9A0C_top(void *) __asm__("func_800A9A0C");
s16 func_800BCB04(s32, s32, s32);
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s16 D_8006CD00[];
extern u8 *D_800814A8;
extern u8 D_80082E80[];
extern u8 D_80082E80_b[] __asm__("D_80082E80");
extern u8 D_80082E80_c[] __asm__("D_80082E80");
extern u16 D_80082EA4;
extern u16 D_80083462;
extern u8 D_80083460[];

/* Choose a movement heading, advance the actor, and update its movement state. */
void func_8016FCE4(void *move_state, void *unused, void *position_in, void *actor_in) {
    M2C_UNK tile_mask;
    register void *position ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *actor ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 *turn_offsets;
    s32 target_y;
    s32 target_x;
    s32 trial_heading;
    s16 target_heading;
    register s32 step_coord ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 tile_y;
    s32 heading_state;
    register s32 move_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 move_flags;
    register s32 heading ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *counter_base;
    register s32 turn_index ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 limit_turns;
    u8 *x_offsets;
    void *target;
    S_8016FCE4_3 *target_position;

    position = position_in;
    actor = actor_in;
    limit_turns = 0;
    if ((D_80083462 & 0x4000) || (((S_8016FCE4_0 *)actor)->unk_71.s >= 0)) {
        call_800A9A0C_top(actor);
        return;
    }
    if (D_80083462 & 0x2000) {
        func_800A19E4(position, actor, 3, 6, move_state + 0x9C);
        ASM_KEEP_NV(position);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP_NV(actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        move_flags = ((S_8016FCE4_0 *)actor)->unk_1C;
        if (move_flags & 0x410) {
            if (move_flags & 0x400) {
                target = func_800A02AC(actor, ((S_8016FCE4_1 *)position)->unk_24.at00.v, ((S_8016FCE4_1 *)position)->unk_24.at01.v);
                if (target != NULL) {
                    target_position = ((S_8016FCE4_2_pre *)target)[-1].unk_00;
                    ((S_8016FCE4_0 *)actor)->unk_2A.u = func_800A0818(((S_8016FCE4_1 *)position)->unk_24.at00.v, ((S_8016FCE4_1 *)position)->unk_24.at01.v, target_position->unk_24, target_position->unk_25, move_state + 0x98);
                    ((S_8016FCE4_0 *)actor)->unk_71.u = ((S_8016FCE4_0 *)actor)->unk_71.u & 0x7F;
                    return;
                }
                move_result = ((S_8016FCE4_0 *)actor)->unk_14;
                if (move_result >= 0) {
                    ((S_8016FCE4_0 *)actor)->unk_14 = (s32) (move_result | 0x80000000);
                    ((S_8016FCE4_0 *)actor)->unk_2A.u += (func_800A6D30() & 7) << 9;
                    goto reset_turn_index;
                }
                goto reset_turn_index;
            }
            move_result = func_800A04F0(actor, ((S_8016FCE4_1 *)position)->unk_24.at00.v, ((S_8016FCE4_1 *)position)->unk_24.at01.v, (s16) ((S_8016FCE4_0 *)actor)->unk_2A.u);
            turn_index = 0;
            if (move_result != 0) {
                ASM_SCHED_BARRIER(); /* MATCH: retain the forward jump to shared cleanup. */
                goto finish_move;
            }
            goto start_turn_search;
        }
        turn_index = 0;
        if (!(((S_8016FCE4_0 *)actor)->unk_46 & 0x8000)) {
            if (move_flags & 0x20000) {
                u8 **heading_ref = &D_800814A8;
                register u8 *position_base = D_80082E80;
                u8 *heading_base;
                u8 *x_table_base;
                s32 dir_index;

                x_table_base = D_8006CCD8;
                heading_base = *heading_ref;
                dir_index = ((((S_8016FCE4_0 *)actor)->unk_45 + ((s32) (((S_8016FCE4_4 *)heading_base)->unk_2A << 0x10) >> 0x19)) & 7) * 2;
                target_x = position_base[0x24] + *(u16 *)(x_table_base + dir_index);
                target_y = D_80082E80[0x25] + *(u16 *)(D_8006CCE8 + dir_index);
                if ((((S_8016FCE4_1 *)position)->unk_24.at00.v != (target_x & 0xFFFF)) || (((S_8016FCE4_1 *)position)->unk_24.at01.v != (target_y & 0xFFFF))) {
                    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    heading_state = move_state + 0x98;
                    target_heading = func_800A0818(((S_8016FCE4_1 *)position)->unk_24.at00.v, ((S_8016FCE4_1 *)position)->unk_24.at01.v, (s16) target_x, (s16) target_y, heading_state);
                    ((S_8016FCE4_0 *)actor)->unk_2A.u = (u16) target_heading;
                    if ((func_8009A66C(target_heading, position, actor, 0x20) << 0x10) <= 0) {
                        ((S_8016FCE4_0 *)actor)->unk_2A.u = func_800A0818(((S_8016FCE4_1 *)position)->unk_24.at00.v, ((S_8016FCE4_1 *)position)->unk_24.at01.v, D_80082E80_b[0x24], D_80082E80_b[0x25], heading_state);
                    }
                    move_result = func_8009FD7C(((S_8016FCE4_1 *)position)->unk_24.at00.v, ((S_8016FCE4_1 *)position)->unk_24.at01.v, D_80082E80_b[0x24], D_80082E80_b[0x25]);
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                    turn_index = 0;
                    if ((move_result << 0x10) != 0) {
                        limit_turns = 1;
                        goto start_turn_search;
                    }
                    goto start_turn_search;
                }
                goto finish_move;
            }
            func_800A0E6C(position, ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_s8, actor, move_state + 0x98);
reset_turn_index:
            turn_index = 0;
            goto start_turn_search;
        }
start_turn_search:
        x_offsets = D_8006CCD8;
        turn_offsets = D_8006CD00;
try_heading:
        heading = ((S_8016FCE4_0 *)actor)->unk_2A.s;
        if (((Rec_func_800A9E70_arg0 *)move_state)->unk_98 & 2) {
            move_result = *turn_offsets;
            trial_heading = heading - move_result;
        } else {
            move_result = *turn_offsets;
            trial_heading = heading + move_result;
        }
        if ((func_8009A66C((s16) trial_heading, position, actor, 0x20) << 0x10) > 0) {
            if (turn_index < 3) {
                goto take_step;
            }
            move_result = limit_turns;
            if (move_result != 0) {
                goto finish_move;
            }
take_step:
            {
                ((S_8016FCE4_0 *)actor)->unk_2A.u = (u16) trial_heading;
                ((S_8016FCE4_8 *)((actor + ((u8) ((S_8016FCE4_0 *)actor)->unk_71.s & 0x7F))))->unk_74 = (u8) ((S_8016FCE4_1 *)position)->unk_24.at00.v;
                ((S_8016FCE4_8 *)((actor + ((u8) ((S_8016FCE4_0 *)actor)->unk_71.s & 0x7F))))->unk_7C = (u8) ((S_8016FCE4_1 *)position)->unk_24.at01.v;
                ((S_8016FCE4_0 *)actor)->unk_71.s = (s8) ((u8) ((S_8016FCE4_0 *)actor)->unk_71.s + 1);
                func_8009A3D0(((S_8016FCE4_1 *)position)->unk_24.at00.v, ((S_8016FCE4_1 *)position)->unk_24.at01.v,
                              (((S_8016FCE4_0 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000);
                step_coord = ((u16) ((S_8016FCE4_0 *)actor)->unk_2A.u >> 8) & 0xE;
                ((S_8016FCE4_1 *)position)->unk_24.at00.v = (u8) (((S_8016FCE4_1 *)position)->unk_24.at00.v + *(u8 *) ((uptr) step_coord + (uptr) x_offsets));
                ((S_8016FCE4_1 *)position)->unk_24.at01.v = (u8) (((S_8016FCE4_1 *)position)->unk_24.at01.v + D_8006CCE8[step_coord]);
                step_coord = ((S_8016FCE4_1 *)position)->unk_24.at00.v;
                tile_y = ((S_8016FCE4_1 *)position)->unk_24.at01.v;
                if (((S_8016FCE4_0 *)actor)->unk_1C & 0x2000) {
                    tile_mask = 0x300;
                } else {
                    tile_mask = 0x3000;
                }
                func_8009A21C(step_coord, tile_y, tile_mask);
                move_result = turn_index < 8;
                goto check_step;
            }
        }
        if ((turn_index != 0) || (D_80082EA4 == ((S_8016FCE4_1 *)position)->unk_24.at00u.v) || ((func_8009A180(actor, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 0x10) == 0)) {
            turn_index += 1;
            turn_offsets += 1;
            if (turn_index >= 8) {
finish_search:
                ASM_KEEP_NV(turn_index);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                move_result = turn_index < 8;
check_step:
                if (move_result == 0) {
                    ((S_8016FCE4_0 *)actor)->unk_71.s = (s8) ((u8) ((S_8016FCE4_0 *)actor)->unk_71.s & 0x7F);
                    ((S_8016FCE4_0 *)actor)->unk_46 = (u16) (((S_8016FCE4_0 *)actor)->unk_46 & 0x7FFF);
                    func_800A9A0C(actor);
                    return;
                }
                ((S_8016FCE4_0 *)actor)->unk_46 = (u16) (((S_8016FCE4_0 *)actor)->unk_46 & 0x7FFF);
                ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_s8 = (s8) ((S_8016FCE4_1 *)position)->unk_26;
                ((S_8016FCE4_0 *)actor)->unk_6D.u = (u8) (((S_8016FCE4_0 *)actor)->unk_6D.u - 1);
                counter_base = D_80083460;
                ((S_8016FCE4_7 *)counter_base)->unk_08 = (u16) (((S_8016FCE4_7 *)counter_base)->unk_08 + 1);
                if (((S_8016FCE4_0 *)actor)->unk_6D.s != 0) {
                    goto update_height;
                }
finish_move:
                ((S_8016FCE4_0 *)actor)->unk_71.s = (s8) ((u8) ((S_8016FCE4_0 *)actor)->unk_71.s & 0x7F);
                return;
update_height:
                turn_index = (s16) func_800BCB04((((S_8016FCE4_1 *)position)->unk_24.at00.v << 6) | 0x20, (((S_8016FCE4_1 *)position)->unk_24.at01.v << 6) | 0x20, (s16) (((S_8016FCE4_0 *)actor)->unk_88 - 0x20));
                if (turn_index < 0x200) {
                    ((S_8016FCE4_0 *)actor)->unk_88 = (u16) turn_index;
                }
            } else {
                goto try_heading;
            }
        }
    }
}
