#include "common.h"
#include "records/Rec_D_800814A8.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80172F58_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    void * unk_0C;
} S_80172F58_0;   /* state in func_80172F58 */

typedef struct S_80172F58_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
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
} S_80172F58_1;   /* arg3 in func_80172F58 */

typedef struct S_80172F58_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_80172F58_2;   /* arg2 in func_80172F58 */

typedef struct S_80172F58_3_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_80172F58_3_pre;   /* the 0x14 bytes before found in func_80172F58, addressed as found[-1] */

typedef struct S_80172F58_3 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_80172F58_3;   /* found in func_80172F58 */

typedef struct S_80172F58_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172F58_4;   /* object in func_80172F58 */


typedef struct S_80172F58_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172F58_6;   /* target in func_80172F58 */

typedef struct S_80172F58_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172F58_7;   /* retry_target in func_80172F58 */

typedef struct S_80172F58_8 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172F58_8;   /* check_target in func_80172F58 */

typedef struct S_80172F58_9 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80172F58_9;   /* kind_table + kind * 0x14 in func_80172F58 */

typedef struct S_80172F58_10 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   /* accessed as both */
} S_80172F58_10;   /* arg0 in func_80172F58 */

typedef struct S_80172F58_11 {
    u16 unk_00;
} S_80172F58_11;   /* &D_80082EA4 in func_80172F58 */

typedef struct S_80172F58_12 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_80172F58_12;   /* loop_state in func_80172F58 */

typedef struct S_80172F58_13 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80172F58_13;   /* arg3 + (((S_80172F58_1 *)arg3)->unk_71.u & 0x7F) in func_80172F58 */



extern s32 func_8009A180();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s32 func_8009A540();
extern s32 func_8009A66C();
extern s32 func_8009FD7C();
extern s16 func_800A0134();
extern void *func_800A02AC();
extern void *func_800A04F0();
extern u16 func_800A0818();
extern void func_800A0E6C();
extern void func_800A19E4();
extern s32 func_800A6D30();
extern void func_800A9A0C();
extern s16 func_800BCB04();
extern s32 func_80173734();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_8006CD00;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s32 D_80083460;
extern s8 D_800E2970[];

/* Select a movement direction, move the actor, and update its path history and height. */
void func_80172F58(u8 *move_input, void *action_context, u8 *position_input, u8 *actor_input) {
    register u8 *move_state ASM_REG("$21") = move_input;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register u8 *position ASM_REG("$20") = position_input;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *actor ASM_REG("$18") = actor_input;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 near_target ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 attempt ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s16 *angle_offset;
    register u8 *x_offsets;
    u8 *dungeon_state;
    u8 *turn_state;
    u32 state_flags;
    u32 actor_flags;
    s32 direction_clear;
    register s32 direction_offset ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 move_found ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 tile_mask;
    s32 base_angle;
    s16 move_angle;
    u8 next_x;
    u8 next_y;
    void *found_target;
    u8 *object;

    dungeon_state = (u8 *)&D_80083460;
    state_flags = ((S_80172F58_0 *)dungeon_state)->unk_02;
    ASM_KEEP(move_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(position);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    near_target = 0;

    if ((state_flags & 0x4000) || (((S_80172F58_1 *)actor)->unk_71.s >= 0)) {
        if ((((S_80172F58_1 *)actor)->unk_12 >= 2) ||
            ((func_80173734(move_state, action_context, position, actor) << 16) == 0)) {
            func_800A9A0C(actor);
            goto end;
        }
        if (((S_80172F58_0 *)dungeon_state)->unk_0C != actor) {
            goto end;
        }
        ((S_80172F58_1 *)actor)->unk_46 = 0xC008;
        goto end;
    }
    if (!(state_flags & 0x2000)) {
        goto end;
    }

    func_800A19E4(position, actor, 3, 6, move_state + 0x9C);
    actor_flags = ((S_80172F58_1 *)actor)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            found_target = func_800A02AC(actor, ((S_80172F58_2 *)position)->unk_24.at00.v, ((S_80172F58_2 *)position)->unk_24.at01.v);
            if (found_target != NULL) {
                object = ((S_80172F58_3_pre *)found_target)[-1].unk_00;
                ((S_80172F58_1 *)actor)->unk_2A.u = func_800A0818(
                    ((S_80172F58_2 *)position)->unk_24.at00.v, ((S_80172F58_2 *)position)->unk_24.at01.v,
                    ((S_80172F58_4 *)object)->unk_24, ((S_80172F58_4 *)object)->unk_25, move_state + 0x98);
                ((S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
                goto end;
            }
            {
                s32 object_status;

                s32 random_turn;

                object_status = ((S_80172F58_1 *)actor)->unk_14;
                if (!(object_status & 0x80000000)) {
                    object_status |= 0x80000000;
                    ((S_80172F58_1 *)actor)->unk_14 = object_status;
                    random_turn = func_800A6D30();
                    ((S_80172F58_1 *)actor)->unk_2A.u += (random_turn & 7) << 9;
                }
            }
            goto init_loop;
        }
        found_target = func_800A04F0(actor, ((S_80172F58_2 *)position)->unk_24.at00.v, ((S_80172F58_2 *)position)->unk_24.at01.v,
                              ((S_80172F58_1 *)actor)->unk_2A.s);
        attempt = 0;
        if (found_target == NULL) {
            goto setup_loop;
        }
        goto clear_history;
    }

    if (actor_flags & 0x2000) {
        if (((S_80172F58_1 *)actor)->unk_46 & 0x8000) {
            attempt = 0;
            goto setup_loop;
        }
        if (actor_flags & 0x20000) {
            s32 direction;
            s16 target_x;
            s32 target_y;
            s16 new_angle;
            u8 *target;

            target = (u8 *)&D_80082EA4 - 0x24;
            direction = (((S_80172F58_1 *)actor)->unk_45 +
                         ((s32)(((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_u16 << 16) >> 25)) & 7;
            target_x = ((S_80172F58_6 *)target)->unk_24 +
                       ((u16 *)&D_8006CCD8)[direction];
            target_y = ((S_80172F58_6 *)target)->unk_25 +
                       ((u16 *)&D_8006CCE8)[direction];
            if ((((S_80172F58_2 *)position)->unk_24.at00.v == (u16)target_x) &&
                (((S_80172F58_2 *)position)->unk_24.at01.v == (u16)target_y)) {
                goto clear_history;
            }
            new_angle = func_800A0818(((S_80172F58_2 *)position)->unk_24.at00.v, ((S_80172F58_2 *)position)->unk_24.at01.v,
                                      target_x, (s16)target_y, move_state + 0x98);
            ((S_80172F58_1 *)actor)->unk_2A.u = new_angle;
            if ((func_8009A66C(new_angle, position, actor, 0x20) << 16) <= 0) {
                u8 *retry_target = D_80082E80;

                ((S_80172F58_1 *)actor)->unk_2A.u = func_800A0818(
                    ((S_80172F58_2 *)position)->unk_24.at00.v, ((S_80172F58_2 *)position)->unk_24.at01.v,
                    ((S_80172F58_7 *)retry_target)->unk_24, ((S_80172F58_7 *)retry_target)->unk_25,
                    move_state + 0x98);
            }
            {
                u8 *check_target = D_80082E80;

                if ((func_8009FD7C(((S_80172F58_2 *)position)->unk_24.at00.v, ((S_80172F58_2 *)position)->unk_24.at01.v,
                                   ((S_80172F58_8 *)check_target)->unk_24,
                                   ((S_80172F58_8 *)check_target)->unk_25) << 16) != 0) {
                    near_target = 1;
                }
            }
            attempt = 0;
            goto setup_loop;
        }
        goto use_target;
    }

    {
        s32 kind;

        kind = ((S_80172F58_2 *)position)->unk_26.s;
        if (kind >= 0) {
            u8 *kind_table = (u8 *)D_800E2970;

            if (((S_80172F58_9 *)(kind_table + kind * 0x14))->unk_0C & 2) {
                goto use_target;
            }
        }
    }
    attempt = 0;
    if (((S_80172F58_1 *)actor)->unk_46 & 0x8000) {
        goto setup_loop;
    }
    found_target = func_800A04F0(actor, ((S_80172F58_2 *)position)->unk_24.at00.v, ((S_80172F58_2 *)position)->unk_24.at01.v,
                          ((S_80172F58_1 *)actor)->unk_2A.s);
    if ((found_target != NULL) && (((S_80172F58_3 *)found_target)->unk_1C & 0x2000) &&
        (func_800A0134(found_target, actor) < 0x81) &&
        ((func_8009A540(((s32)(((S_80172F58_1 *)actor)->unk_2A.u << 16) >> 25) & 0xFFFF,
                        ((S_80172F58_2 *)position)->unk_24.at00.v, ((S_80172F58_2 *)position)->unk_24.at01.v,
                        (s16)(((S_80172F58_1 *)actor)->unk_88 - 0x20)) << 16) != 0)) {
        goto clear_history;
    }
    if (((S_80172F58_1 *)actor)->unk_1C & 0x20000) {
        u8 *target = D_80082E80;
        ((S_80172F58_1 *)actor)->unk_2A.u = func_800A0818(
            ((S_80172F58_2 *)position)->unk_24.at00.v, ((S_80172F58_2 *)position)->unk_24.at01.v,
            ((S_80172F58_6 *)target)->unk_24, ((S_80172F58_6 *)target)->unk_25, move_state + 0x98);
        if ((func_8009FD7C(((S_80172F58_2 *)position)->unk_24.at00.v, ((S_80172F58_2 *)position)->unk_24.at01.v,
                           ((S_80172F58_6 *)target)->unk_24, ((S_80172F58_6 *)target)->unk_25) << 16) != 0) {
            if (func_800A0134(D_800814A8, actor) < 0x81) {
                direction_clear = func_8009A540(
                    ((s32)(((S_80172F58_1 *)actor)->unk_2A.u << 16) >> 25) & 0xFFFF,
                    ((S_80172F58_2 *)position)->unk_24.at00.v, ((S_80172F58_2 *)position)->unk_24.at01.v,
                    (s16)(((S_80172F58_1 *)actor)->unk_88 - 0x20));
                attempt = 0;
                if ((direction_clear << 16) == 0) {
                    goto setup_loop;
                }
                goto clear_history;
            }
            attempt = 0;
            goto setup_loop;
        }
        goto init_loop;
    }

use_target:
    func_800A0E6C(position, ((S_80172F58_10 *)move_state)->unk_9C.s, actor, move_state + 0x98);
init_loop:
    attempt = 0;
setup_loop:
    x_offsets = (u8 *)&D_8006CCD8;
    angle_offset = &D_8006CD00;

loop:
    base_angle = (s32)((S_80172F58_1 *)actor)->unk_2A.s;
    if (((S_80172F58_10 *)move_state)->unk_98 & 2) {
        {
            s32 angle_delta = (s32)*angle_offset;

            move_angle = (s16)(base_angle - angle_delta);
        }
    } else {
        {
            s32 angle_delta = (s32)*angle_offset;

            move_angle = (s16)(base_angle + angle_delta);
        }
    }
    if ((func_8009A66C(move_angle, position, actor, 0x20) << 16) > 0) {
        if (attempt >= 3) {
            s32 target_nearby = near_target;

            ASM_KEEP(target_nearby);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if (target_nearby) {
                goto clear_history;
            }
        }
        ((S_80172F58_1 *)actor)->unk_2A.u = move_angle;
        ((S_80172F58_13 *)(actor + (((S_80172F58_1 *)actor)->unk_71.u & 0x7F)))->unk_74 =
            ((S_80172F58_2 *)position)->unk_24.at00.v;
        ((S_80172F58_13 *)(actor + (((S_80172F58_1 *)actor)->unk_71.u & 0x7F)))->unk_7C =
            ((S_80172F58_2 *)position)->unk_24.at01.v;
        ((S_80172F58_1 *)actor)->unk_71.u++;
        func_8009A3D0(((S_80172F58_2 *)position)->unk_24.at00.v, ((S_80172F58_2 *)position)->unk_24.at01.v,
                      (((S_80172F58_1 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000);
        direction_offset = (((S_80172F58_1 *)actor)->unk_2A.u >> 8) & 0xE;
        ((S_80172F58_2 *)position)->unk_24.at00.v +=
            *((u8 *)((u32)direction_offset + (u32)x_offsets));
        ((S_80172F58_2 *)position)->unk_24.at01.v += *((u8 *)&D_8006CCE8 + direction_offset);
        next_x = ((S_80172F58_2 *)position)->unk_24.at00.v;
        next_y = *(volatile u8 *)((u8 *)position + 0x25);
        tile_mask = 0x3000;
        if (((S_80172F58_1 *)actor)->unk_1C & 0x2000) {
            tile_mask = 0x300;
        }
        func_8009A21C(next_x, next_y, tile_mask);
        goto after_loop;
    }

    if (attempt == 0) {
        if ((((S_80172F58_11 *)(&D_80082EA4))->unk_00 != ((S_80172F58_2 *)position)->unk_24.at00u.v) &&
            ((s16)func_8009A180(actor, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) != 0)) {
            goto end;
        }
    }
    attempt++;
    angle_offset++;
    if (attempt < 8) {
        goto loop;
    }

after_loop:
    move_found = attempt < 8;
    if (!move_found) {
        ((S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
        ((S_80172F58_1 *)actor)->unk_46 &= 0x7FFF;
        func_800A9A0C(actor);
        goto end;
    }
    turn_state = (u8 *)&D_80083460;
    ((S_80172F58_1 *)actor)->unk_46 &= 0x7FFF;
    ((S_80172F58_10 *)move_state)->unk_9C.u = ((S_80172F58_2 *)position)->unk_26.u;
    ((S_80172F58_1 *)actor)->unk_6D.u--;
    ((S_80172F58_12 *)turn_state)->unk_08++;
    if (((S_80172F58_1 *)actor)->unk_6D.s != 0) {
        goto update_height;
    }

clear_history:
    ((S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
    goto end;

update_height:
    attempt = func_800BCB04((((S_80172F58_2 *)position)->unk_24.at00.v << 6) | 0x20,
                      (((S_80172F58_2 *)position)->unk_24.at01.v << 6) | 0x20,
                      (s16)(((S_80172F58_1 *)actor)->unk_88 - 0x20));
    if (attempt < 0x200) {
        ((S_80172F58_1 *)actor)->unk_88 = attempt;
    }
    goto end;

end:
    ASM_KEEP(move_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    return;
}
