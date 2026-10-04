#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct S_807AE960_1 {
    union { u16 s; s16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    union { s16 s; s16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0x4];
    s16 unk_0A;
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
    u16 unk_0E;
    s16 unk_10;
} S_807AE960_1;   /* state in func_807AE960 */

typedef struct S_807AE960_2 {
    u8 pad_00[0x1A];
    s16 unk_1A;
} S_807AE960_2;   /* target in func_807AE960 */

typedef struct S_807AE960_3 {
    u8 pad_00[0x2090];
    s32 unk_2090;
} S_807AE960_3;   /* global in func_807AE960 */

typedef struct S_807AE960_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_807AE960_4;   /* actor in func_807AE960 */

typedef struct S_807AE960_5 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_807AE960_5;   /* global_end in func_807AE960 */

typedef struct S_807AE960_6 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_807AE960_6;   /* entry in func_807AE960 */


extern void *D_800F6000[];
M2C_UNK Control_CD();
s32 func_8003F270();
void func_8003F540();
int func_800445E0();
s32 func_80053EF0();
s32 func_800A56E0();
extern M2C_UNK D_80010000;
extern u16 D_8001371A;
extern s32 D_8006CD58;

/* Dispatch the CD-audio fade state machine, then step the actor's shake counter and raise the finished flag. */
void func_807AE960(u8 *state, u8 *actor, u8 *target) {
    s16 steps;
    s32 dispatch_index;
    s16 remaining;
    s32 countdown;
    u16 countdown_u;
    s32 actor_pos;
    u8 *global;
    u32 cd_mode;
    s32 table_base;
    u8 *global_end;
    GameWork *dungeon_data;
    S_807AE960_6 *entry;

    dungeon_data = &gameWork;
    global_end = (u8 *)dungeon_data + 0x1DC;
    table_base = ((s32)dungeon_data->map.cells);
    dispatch_index = (s16)(((S_807AE960_1 *)state)->unk_00.s - 1);
    switch (dispatch_index + 1) {
    case 1:
    case 2:
        if (func_8003F270() != 0) {
            return;
        }
        if (((S_807AE960_1 *)state)->unk_10 == 0) {
            func_800A56E0(0x300);
        }
        ((S_807AE960_1 *)state)->unk_00.u = 3;
        break;
    case 17:
        ((S_807AE960_1 *)state)->unk_0A = 0x400;
        ((S_807AE960_2 *)target)->unk_1A = (s16) (u16) ((S_807AE960_1 *)state)->unk_0A;
        ((S_807AE960_1 *)state)->unk_00.u = 0;
        break;
    case 3:
        steps = ((S_807AE960_1 *)state)->unk_04.s;
        if (steps > 0) {
            ((S_807AE960_2 *)target)->unk_1A = (s16) ((u16) ((S_807AE960_2 *)target)->unk_1A
                + ((s32) (((S_807AE960_1 *)state)->unk_0A - ((S_807AE960_2 *)target)->unk_1A) / steps));
        }
        remaining = (u16) ((S_807AE960_1 *)state)->unk_04.s - 1;
        ((S_807AE960_1 *)state)->unk_04.u = remaining;
        do {
            global = (u8 *)0x80010000;
        } while (0);
        if (*(u16 *)(global + 0x371A) < 4U) {
            if (remaining < 0) {
                ((S_807AE960_1 *)state)->unk_04.s = 0;
            }
            break;
        }
        if (((S_807AE960_3 *)global)->unk_2090 == 1) {
            dungeonStatus.unk_0A = 1;
        }
        if (((S_807AE960_1 *)state)->unk_04.s > 0) {
            break;
        }
        cd_mode = ((S_807AE960_3 *)global)->unk_2090;
        if (cd_mode == 1) {
            if (func_80053EF0(4) != 0) {
                ((S_807AE960_1 *)state)->unk_04.s = 0;
                break;
            }
            if (((S_807AE960_3 *)global)->unk_2090 == cd_mode) {
                dungeonStatus.unk_0A = 0;
            }
        }
        ((S_807AE960_2 *)target)->unk_1A = (s16) (u16) ((S_807AE960_1 *)state)->unk_0A;
        ((S_807AE960_1 *)state)->unk_00.u = 0;
        break;
    case 4:
        if (((S_807AE960_1 *)state)->unk_10 == 0) {
            func_8003F540(0, D_8006CD58, 0x0600065E, 0x030008B6);
            Control_CD(0x15, func_800445E0(), 0);
        }
        ((S_807AE960_1 *)state)->unk_04.s = 0x60;
        ((S_807AE960_1 *)state)->unk_0C.s = 0x60;
    case 20:
        ((S_807AE960_1 *)state)->unk_00.s = 2U;
        ((S_807AE960_1 *)state)->unk_0A = (s16) ((S_807AE960_1 *)state)->unk_02;
        break;
    default:
        break;
    }
    countdown = ((S_807AE960_1 *)state)->unk_0C.s;
    countdown_u = ((S_807AE960_1 *)state)->unk_0C.u;
    if (countdown != 0) {
        countdown = countdown_u - 1;
        ((S_807AE960_1 *)state)->unk_0C.s = countdown;
        actor_pos = ((S_807AE960_4 *)actor)->unk_0A;
        if (countdown & 1) {
            countdown = actor_pos + 1;
        } else {
            countdown = actor_pos - 1;
        }
        ((S_807AE960_4 *)actor)->unk_0A = countdown;
        if (((S_807AE960_1 *)state)->unk_0C.s == 0) {
            ((S_807AE960_4 *)actor)->unk_0A = (s16) ((S_807AE960_1 *)state)->unk_0E;
        }
    }
    if (((S_807AE960_1 *)state)->unk_00.u != 0) {
        return;
    }
    if ((u8) D_80082E80.tileY >= 0x3DU) {
        return;
    }
    if (((S_807AE960_1 *)state)->unk_0A == (s16) ((S_807AE960_1 *)state)->unk_02) {
        return;
    }
    ((S_807AE960_1 *)state)->unk_00.s = 4U;
    entry = ((0x3E << ((S_807AE960_5 *)global_end)->unk_14) * 6) + table_base + 0xBA;
    entry->unk_04 = (u16) (entry->unk_04 | 0x8000);
    return;
}
