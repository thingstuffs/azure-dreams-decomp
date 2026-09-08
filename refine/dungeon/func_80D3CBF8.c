#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

typedef struct {
    u8 pad[0x24];
    u8 x;
    u8 y;
} FallbackCenter;

extern s32 func_80042900();
extern s32 func_8009A180();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s32 func_8009A540();
extern s32 func_8009A8C0();
extern s32 func_8009FD7C();
extern s16 func_800A0134();
extern void *func_800A02AC();
extern void *func_800A04F0();
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A0E6C();
extern void func_800A19E4();
extern s32 func_800A6D30();
extern void func_800A9A0C();
extern s16 func_800BCB04();
extern s32 func_80172BB0();

extern u8 D_8006CCD8[16];
extern u8 D_8006CCE8[16];
extern s16 D_8006CD00[8];
extern void *D_800814A8;
extern u8 D_80082E80[];
extern FallbackCenter D_80082E80_center[] __asm__("D_80082E80");
extern u16 D_80082EA4;
extern s32 D_80083460;
extern u8 D_800E2970[];

/* Choose a movement direction, move the actor, and update its path history and height. */
void func_801723F8(void *work_data, void *action_context, void *position_data, void *actor_data) {
    register u8 *move_work ASM_REG("$21") = work_data;
    register u8 *position ASM_REG("$20") = position_data;
    u8 *actor = actor_data;
    u8 *turn_state;
    u16 turn_flags;
    s32 movement_flags;
    s32 limit_turn;
    s32 attempt;
    register s16 *angle_step ASM_REG("$17");
    register s32 angle ASM_REG("$3");
    s32 target_x;
    s32 target_y;
    s32 candidate_angle;
    s32 call_result;
    s32 tile_mask;
    s32 direction_offset;
    s32 direction;
    s32 tile_type;
    register s32 work_value ASM_REG("$2");
    void *node;
    void *parent;

    turn_state = (u8 *)&D_80083460;
    turn_flags = U16_AT(turn_state, 2);
    ASM_KEEP(move_work);
    ASM_KEEP(position);
    limit_turn = turn_flags & 0;

    if ((turn_flags & 0x4000) || (S8_AT(actor, 0x71) >= 0)) {
        if ((U8_AT(actor, 0x12) >= 2) || U8_AT(move_work, 0xB5) ||
            ((func_80172BB0(move_work, action_context, position, actor) << 16) == 0)) {
            func_800A9A0C(actor);
            return;
        }
        if (PTR_AT(turn_state, 0xC) == actor) {
            U16_AT(actor, 0x46) = 0xC008;
        }
        return;
    }

    if ((turn_flags & 0x2000) == 0) {
        return;
    }

    func_800A19E4(position, actor, 3, 6, (u8 *)move_work + 0x9C);
    movement_flags = S32_AT(actor, 0x1C);

    if (movement_flags & 0x410) {
        if (movement_flags & 0x400) {
            node = func_800A02AC(actor, U8_AT(position, 0x24), U8_AT(position, 0x25));
            if (node != NULL) {
                u8 *node_work;
                s32 history_index;

                parent = PTR_AT(node, -0x14);
                node_work = (u8 *)move_work + 0x98;
                U16_AT(actor, 0x2A) = func_800A0818(
                    U8_AT(position, 0x24), U8_AT(position, 0x25),
                    U8_AT(parent, 0x24), U8_AT(parent, 0x25),
                    node_work);
                history_index = U8_AT(actor, 0x71);
                history_index &= 0x7F;
                ASM_KEEP_DEP_NV(history_index, move_work);
                U8_AT(actor, 0x71) = history_index;
                return;
            }

            work_value = S32_AT(actor, 0x14);
            if (work_value >= 0) {
                S32_AT(actor, 0x14) = work_value | 0x80000000;
                call_result = func_800A6D30();
                U16_AT(actor, 0x2A) += (call_result & 7) << 9;
            }
            goto loop_setup;
        }

        work_value = (s32)func_800A04F0(actor, U8_AT(position, 0x24),
                                    U8_AT(position, 0x25),
                                    S16_AT(actor, 0x2A));
        ASM_SCHED_BARRIER();
        attempt = 0;
        if (work_value == 0) {
            goto loop_ready;
        }
        goto clear_history;
    }

    if (movement_flags & 0x2000) {
        if (U16_AT(actor, 0x46) & 0x8000) {
            attempt = 0;
            goto loop_ready;
        }

        if (movement_flags & 0x20000) {
            s16 path_angle;
            u8 *path_center;
            u8 *path_work;

            path_center = D_80082E80;
            direction = (U8_AT(actor, 0x45) + (S16_AT(D_800814A8, 0x2A) >> 9)) & 7;
            target_x = U8_AT(path_center, 0x24) +
                       *(u16 *)(D_8006CCD8 + (direction * 2));
            target_y = U8_AT(path_center, 0x25) +
                       *(u16 *)(D_8006CCE8 + (direction * 2));

            if ((U8_AT(position, 0x24) == (u16)target_x) &&
                (U8_AT(position, 0x25) == (u16)target_y)) {
                goto clear_history;
            }

            path_work = (u8 *)move_work + 0x98;
            path_angle = func_800A0818(
                U8_AT(position, 0x24), U8_AT(position, 0x25),
                (s16)target_x, (s16)target_y, path_work);
            U16_AT(actor, 0x2A) = path_angle;
            call_result = func_8009A8C0(path_angle, position, actor, 0x20);
            if ((call_result << 16) <= 0) {
                U16_AT(actor, 0x2A) = func_800A0818(
                    U8_AT(position, 0x24), U8_AT(position, 0x25),
                    D_80082E80_center[0].x,
                    D_80082E80_center[0].y, path_work);
            }

            work_value = func_8009FD7C(
                U8_AT(position, 0x24), U8_AT(position, 0x25),
                D_80082E80_center[0].x,
                D_80082E80_center[0].y);
            ASM_SCHED_BARRIER();
            attempt = 0;
            if ((work_value << 16) != 0) {
                limit_turn = 1;
            }
            goto loop_ready;
        }
        goto direct_move;
    }

    tile_type = S8_AT(position, 0x26);
    if (tile_type >= 0) {
        u8 *tile_records;
        u8 *tile_record;

        tile_records = D_800E2970;
        tile_record = tile_records + tile_type * 0x14;
        if (U16_AT(tile_record, 0xC) & 2) {
            goto direct_move;
        }
    }

    attempt = 0;
    if (U16_AT(actor, 0x46) & 0x8000) {
        goto loop_ready;
    }

    node = func_800A04F0(actor, U8_AT(position, 0x24), U8_AT(position, 0x25),
                          S16_AT(actor, 0x2A));
    if ((node != NULL) && (S32_AT(node, 0x1C) & 0x2000) &&
        (func_800A0134(node, actor) < 0x81) &&
        ((func_8009A540(
              ((S16_AT(actor, 0x2A) >> 9) & 0xFFFF),
              U8_AT(position, 0x24), U8_AT(position, 0x25),
              (s16)(U16_AT(actor, 0x88) - 0x20)) << 16) != 0)) {
        goto clear_history;
    }

    if (S32_AT(actor, 0x1C) & 0x20000) {
        u8 *move_center;

        move_center = D_80082E80;
        U16_AT(actor, 0x2A) = func_800A0818(
            U8_AT(position, 0x24), U8_AT(position, 0x25),
            U8_AT(move_center, 0x24), U8_AT(move_center, 0x25),
            (u8 *)move_work + 0x98);

        if ((func_8009FD7C(
                U8_AT(position, 0x24), U8_AT(position, 0x25),
                U8_AT(move_center, 0x24), U8_AT(move_center, 0x25)) << 16) != 0) {
            if (func_800A0134(D_800814A8, actor) >= 0x81) {
                goto loop_setup;
            }
            if ((func_8009A540(
                    ((S16_AT(actor, 0x2A) >> 9) & 0xFFFF),
                    U8_AT(position, 0x24), U8_AT(position, 0x25),
                    (s16)(U16_AT(actor, 0x88) - 0x20)) << 16) == 0) {
                goto loop_setup;
            }
            goto clear_history;
        }
        goto loop_setup;
    }

direct_move:
    func_800A0E6C(position, S8_AT(move_work, 0x9C), actor, (u8 *)move_work + 0x98);

loop_setup:
    attempt = 0;

loop_ready:
    work_value = (s32)0x80070000;
    ASM_KEEP(work_value);
    angle_step = (s16 *)(work_value - 0x3300);

loop_head:
    angle = S16_AT(actor, 0x2A);
    if (U16_AT(move_work, 0x98) & 2) {
        candidate_angle = angle - *angle_step;
    } else {
        candidate_angle = angle + *angle_step;
    }

    call_result = func_8009A8C0((s16)candidate_angle, position, actor, 0x20);
    if ((call_result << 16) > 0) {
        if (attempt >= 3) {
            work_value = limit_turn;
            if (work_value != 0) {
                goto clear_history;
            }
        }

        U16_AT(actor, 0x2A) = candidate_angle;
        U8_AT((u8 *)actor + (U8_AT(actor, 0x71) & 0x7F), 0x74) =
            U8_AT(position, 0x24);
        U8_AT((u8 *)actor + (U8_AT(actor, 0x71) & 0x7F), 0x7C) =
            U8_AT(position, 0x25);
        U8_AT(actor, 0x71)++;

        call_result = func_80042900(actor, 0x1B);
        if ((call_result << 16) == 0) {
            s32 old_x;
            s32 old_y;

            old_x = U8_AT(position, 0x24);
            old_y = U8_AT(position, 0x25);
            tile_mask = 0x3000;
            if (S32_AT(actor, 0x1C) & 0x2000) {
                tile_mask = 0x300;
            }
            func_8009A3D0(old_x, old_y, tile_mask);
        }

        {
            register s32 position_x ASM_REG("$2");

            direction_offset = (U16_AT(actor, 0x2A) >> 8) & 0xE;
            position_x = U8_AT(position, 0x24);
            position_x += D_8006CCD8[direction_offset];
            U8_AT(position, 0x24) = position_x;
            U8_AT(position, 0x25) += D_8006CCE8[direction_offset];
        }

        if ((call_result << 16) == 0) {
            s32 new_x;
            s32 new_y;

            new_x = U8_AT(position, 0x24);
            new_y = U8_AT(position, 0x25);
            tile_mask = 0x3000;
            if (S32_AT(actor, 0x1C) & 0x2000) {
                tile_mask = 0x300;
            }
            func_8009A21C(new_x, new_y, tile_mask);
        }
        goto loop_done;
    }

    if (attempt != 0) {
        goto loop_increment;
    }
    if (D_80082EA4 == U16_AT(position, 0x24)) {
        goto loop_increment;
    }
    if ((func_8009A180(actor, S32_AT(D_800814A8, 0x58) + 0x20) << 16) != 0) {
        return;
    }

loop_increment:
    attempt++;
    angle_step++;
    if (attempt < 8) {
        goto loop_head;
    }

loop_done:
    if (attempt >= 8) {
        U8_AT(actor, 0x71) &= 0x7F;
        U16_AT(actor, 0x46) &= 0x7FFF;
        func_800A9A0C(actor);
        return;
    }

    U16_AT(actor, 0x46) &= 0x7FFF;
    S8_AT(move_work, 0x9C) = U8_AT(position, 0x26);
    U8_AT(actor, 0x6D)--;
    {
        u8 *turn_state_tail = (u8 *)&D_80083460;

        U16_AT(turn_state_tail, 8)++;
    }
    if (S8_AT(actor, 0x6D) != 0) {
        goto update_height;
    }

clear_history:
    U8_AT(actor, 0x71) &= 0x7F;
    return;

update_height:
    attempt = func_800BCB04(
        (U8_AT(position, 0x24) << 6) | 0x20,
        (U8_AT(position, 0x25) << 6) | 0x20,
        (s16)(U16_AT(actor, 0x88) - 0x20));
    if (attempt < 0x200) {
        U16_AT(actor, 0x88) = attempt;
    }
    return;
}

