#include "common.h"
#include "records/Rec_D_800814A8.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8016B230_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    void * unk_0C;
} S_8016B230_0;   /* state in func_8016B230 */

typedef struct S_8016B230_1 {
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
} S_8016B230_1;   /* arg3 in func_8016B230 */

typedef struct S_8016B230_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_8016B230_2;   /* arg2 in func_8016B230 */

typedef struct S_8016B230_3_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_8016B230_3_pre;   /* the 0x14 bytes before found in func_8016B230, addressed as found[-1] */

typedef struct S_8016B230_3 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_8016B230_3;   /* found in func_8016B230 */

typedef struct S_8016B230_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016B230_4;   /* object in func_8016B230 */

typedef struct S_8016B230_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   /* accessed as both */
    u8 pad_9D[0x12];
    u8 unk_AF;
} S_8016B230_5;   /* arg0 in func_8016B230 */


typedef struct S_8016B230_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016B230_7;   /* target in func_8016B230 */

typedef struct S_8016B230_8 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016B230_8;   /* retry_target in func_8016B230 */

typedef struct S_8016B230_9 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016B230_9;   /* check_target in func_8016B230 */

typedef struct S_8016B230_10 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_8016B230_10;   /* kind_table + kind * 0x14 in func_8016B230 */

typedef struct S_8016B230_11 {
    u16 unk_00;
} S_8016B230_11;   /* &D_80082EA4 in func_8016B230 */

typedef struct S_8016B230_12 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8016B230_12;   /* loop_state in func_8016B230 */

typedef struct S_8016B230_13 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016B230_13;   /* arg3 + (((S_8016B230_1 *)arg3)->unk_71.u & 0x7F) in func_8016B230 */



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
extern s32 func_8016B954();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_8006CD00;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s32 D_80083460;
extern s8 D_800E2970[];

/* Select a movement direction, record the previous tile, and update the actor position and height. */
void func_8016B230(u8 *movement_in, void *action_ctx, u8 *position_in, u8 *actor_in) {
    register u8 *movement ASM_REG("$21") = movement_in;   /* MATCH pin: retail delay-slot fill depends on it */
    register u8 *position ASM_REG("$20") = position_in;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 *actor ASM_REG("$18") = actor_in;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 near_target ASM_REG("$22");   /* MATCH pin: retail register colouring depends on it */
    register s32 attempt ASM_REG("$19");   /* MATCH pin: keeps a constant in a register as retail does */
    register s16 *angle_offset;
    register u8 *x_offsets;
    u8 *dungeon_state;
    u8 *turn_state;
    u32 dungeon_flags;
    u32 actor_flags;
    s32 path_result;
    s32 random_bits;
    register s32 direction_offset ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 moved ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 tile_mask;
    s32 base_angle;
    s16 move_angle;
    u8 next_x;
    u8 next_y;
    void *found;
    u8 *object;

    dungeon_state = (u8 *)&D_80083460;
    dungeon_flags = ((S_8016B230_0 *)dungeon_state)->unk_02;
    ASM_KEEP(movement);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_KEEP(position);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_KEEP(actor);   /* MATCH pin: retail keeps a computation the compiler would drop */
    near_target = 0;

    if ((dungeon_flags & 0x4000) || (((S_8016B230_1 *)actor)->unk_71.s >= 0)) {
        if ((((S_8016B230_1 *)actor)->unk_12 >= 2) ||
            ((func_8016B954(movement, action_ctx, position, actor) << 16) == 0)) {
            func_800A9A0C(actor);
            goto end;
        }
        if (((S_8016B230_0 *)dungeon_state)->unk_0C != actor) {
            goto end;
        }
        ((S_8016B230_1 *)actor)->unk_46 = 0xC008;
        goto end;
    }
    if (!(dungeon_flags & 0x2000)) {
        goto end;
    }

    func_800A19E4(position, actor, 3, 6, movement + 0x9C);
    actor_flags = ((S_8016B230_1 *)actor)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            found = func_800A02AC(actor, ((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v);
            if (found != NULL) {
                object = ((S_8016B230_3_pre *)found)[-1].unk_00;
                ((S_8016B230_1 *)actor)->unk_2A.u = func_800A0818(
                    ((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                    ((S_8016B230_4 *)object)->unk_24, ((S_8016B230_4 *)object)->unk_25, movement + 0x98);
                ((S_8016B230_1 *)actor)->unk_71.u &= 0x7F;
                goto end;
            }
            {
                register s32 object_status ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

                object_status = ((S_8016B230_1 *)actor)->unk_14;
                if (object_status >= 0) {
                    ((S_8016B230_1 *)actor)->unk_14 = object_status | 0x80000000;
                    random_bits = func_800A6D30();
                    ((S_8016B230_1 *)actor)->unk_2A.u += (random_bits & 7) << 9;
                }
            }
            goto init_loop;
        }
        found = func_800A04F0(actor, ((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                              ((S_8016B230_1 *)actor)->unk_2A.s);
        attempt = 0;
        if (found == NULL) {
            goto setup_loop;
        }
        goto clear_history;
    }

    if (((S_8016B230_5 *)movement)->unk_AF) {
        if (((S_8016B230_1 *)actor)->unk_46 & 0x8000) {
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
            direction = (((S_8016B230_1 *)actor)->unk_45 +
                         ((s32)(((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_u16 << 16) >> 25)) & 7;
            target_x = ((S_8016B230_7 *)target)->unk_24 +
                       ((u16 *)&D_8006CCD8)[direction];
            target_y = ((S_8016B230_7 *)target)->unk_25 +
                       ((u16 *)&D_8006CCE8)[direction];
            if ((((S_8016B230_2 *)position)->unk_24.at00.v == (u16)target_x) &&
                (((S_8016B230_2 *)position)->unk_24.at01.v == (u16)target_y)) {
                goto clear_history;
            }
            new_angle = func_800A0818(((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                                      target_x, (s16)target_y, movement + 0x98);
            ((S_8016B230_1 *)actor)->unk_2A.u = new_angle;
            if ((func_8009A66C(new_angle, position, actor, 0x20) << 16) <= 0) {
                u8 *retry_target = D_80082E80;

                ((S_8016B230_1 *)actor)->unk_2A.u = func_800A0818(
                    ((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                    ((S_8016B230_8 *)retry_target)->unk_24, ((S_8016B230_8 *)retry_target)->unk_25,
                    movement + 0x98);
            }
            {
                u8 *check_target = D_80082E80;

                if ((func_8009FD7C(((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                                   ((S_8016B230_9 *)check_target)->unk_24,
                                   ((S_8016B230_9 *)check_target)->unk_25) << 16) != 0) {
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

        kind = ((S_8016B230_2 *)position)->unk_26.s;
        if (kind >= 0) {
            u8 *kind_table = (u8 *)D_800E2970;

            if (((S_8016B230_10 *)(kind_table + kind * 0x14))->unk_0C & 2) {
                goto use_target;
            }
        }
    }
    attempt = 0;
    if (((S_8016B230_1 *)actor)->unk_46 & 0x8000) {
        goto setup_loop;
    }
    found = func_800A04F0(actor, ((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                          ((S_8016B230_1 *)actor)->unk_2A.s);
    if ((found != NULL) && (((S_8016B230_3 *)found)->unk_1C & 0x2000) &&
        (func_800A0134(found, actor) < 0x81) &&
        ((func_8009A540(((s32)(((S_8016B230_1 *)actor)->unk_2A.u << 16) >> 25) & 0xFFFF,
                        ((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                        (s16)(((S_8016B230_1 *)actor)->unk_88 - 0x20)) << 16) != 0)) {
        goto clear_history;
    }
    if (((S_8016B230_1 *)actor)->unk_1C & 0x20000) {
        u8 *target = D_80082E80;
        ((S_8016B230_1 *)actor)->unk_2A.u = func_800A0818(
            ((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
            ((S_8016B230_7 *)target)->unk_24, ((S_8016B230_7 *)target)->unk_25, movement + 0x98);
        if ((func_8009FD7C(((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                           ((S_8016B230_7 *)target)->unk_24, ((S_8016B230_7 *)target)->unk_25) << 16) != 0) {
            if (func_800A0134(D_800814A8, actor) < 0x81) {
                path_result = func_8009A540(
                    ((s32)(((S_8016B230_1 *)actor)->unk_2A.u << 16) >> 25) & 0xFFFF,
                    ((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                    (s16)(((S_8016B230_1 *)actor)->unk_88 - 0x20));
                attempt = 0;
                if ((path_result << 16) == 0) {
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
    func_800A0E6C(position, ((S_8016B230_5 *)movement)->unk_9C.s, actor, movement + 0x98);
init_loop:
    attempt = 0;
setup_loop:
    x_offsets = (u8 *)&D_8006CCD8;
    angle_offset = &D_8006CD00;
    ASM_KEEP(attempt);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_KEEP(x_offsets);   /* MATCH pin: retail schedule: same instructions, different order without it */

loop:
    base_angle = (s32)((S_8016B230_1 *)actor)->unk_2A.s;
    if (((S_8016B230_5 *)movement)->unk_98 & 2) {
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

            ASM_KEEP(target_nearby);   /* MATCH pin: load-bearing for the whole function shape */
            if (target_nearby) {
                goto clear_history;
            }
        }
        ((S_8016B230_1 *)actor)->unk_2A.u = move_angle;
        ((S_8016B230_13 *)(actor + (((S_8016B230_1 *)actor)->unk_71.u & 0x7F)))->unk_74 =
            ((S_8016B230_2 *)position)->unk_24.at00.v;
        ((S_8016B230_13 *)(actor + (((S_8016B230_1 *)actor)->unk_71.u & 0x7F)))->unk_7C =
            ((S_8016B230_2 *)position)->unk_24.at01.v;
        ((S_8016B230_1 *)actor)->unk_71.u++;
        func_8009A3D0(((S_8016B230_2 *)position)->unk_24.at00.v, ((S_8016B230_2 *)position)->unk_24.at01.v,
                      (((S_8016B230_1 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000);
        direction_offset = (((S_8016B230_1 *)actor)->unk_2A.u >> 8) & 0xE;
        ((S_8016B230_2 *)position)->unk_24.at00.v +=
            *((u8 *)((u32)direction_offset + (u32)x_offsets));
        ((S_8016B230_2 *)position)->unk_24.at01.v += *((u8 *)&D_8006CCE8 + direction_offset);
        next_x = ((S_8016B230_2 *)position)->unk_24.at00.v;
        next_y = *(volatile u8 *)((u8 *)position + 0x25);
        tile_mask = 0x3000;
        if (((S_8016B230_1 *)actor)->unk_1C & 0x2000) {
            tile_mask = 0x300;
        }
        func_8009A21C(next_x, next_y, tile_mask);
        goto after_loop;
    }

    if (attempt == 0) {
        if ((((S_8016B230_11 *)(&D_80082EA4))->unk_00 != ((S_8016B230_2 *)position)->unk_24.at00u.v) &&
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
    moved = attempt < 8;
    if (!moved) {
        ((S_8016B230_1 *)actor)->unk_71.u &= 0x7F;
        ((S_8016B230_1 *)actor)->unk_46 &= 0x7FFF;
        func_800A9A0C(actor);
        goto end;
    }
    turn_state = (u8 *)&D_80083460;
    ((S_8016B230_1 *)actor)->unk_46 &= 0x7FFF;
    ((S_8016B230_5 *)movement)->unk_9C.u = ((S_8016B230_2 *)position)->unk_26.u;
    ((S_8016B230_1 *)actor)->unk_6D.u--;
    ((S_8016B230_12 *)turn_state)->unk_08++;
    if (((S_8016B230_1 *)actor)->unk_6D.s != 0) {
        goto update_height;
    }

clear_history:
    ((S_8016B230_1 *)actor)->unk_71.u &= 0x7F;
    goto end;

update_height:
    attempt = func_800BCB04((((S_8016B230_2 *)position)->unk_24.at00.v << 6) | 0x20,
                      (((S_8016B230_2 *)position)->unk_24.at01.v << 6) | 0x20,
                      (s16)(((S_8016B230_1 *)actor)->unk_88 - 0x20));
    if (attempt < 0x200) {
        ((S_8016B230_1 *)actor)->unk_88 = attempt;
    }
    goto end;

end:
    ASM_KEEP(movement);   /* MATCH pin: retail basic-block layout depends on it */
    return;
}
