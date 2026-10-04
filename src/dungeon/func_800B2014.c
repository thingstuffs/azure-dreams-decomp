#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Coord;

extern s32 D_800835E8[];
M2C_UNK func_8003E188();
M2C_UNK func_80042640();
void func_800424E0(); /* extern */
s32 func_800990FC();
s32 func_80099194();
void *func_80099290();
s32 func_8009929C();
s32 func_80099734();
void func_800997FC(); /* extern */
s32 func_8009B88C();
s32 *(*func_800A0B94())(s32, s16, s16, s16); /* extern */
s32 func_800A1618();
s32 func_800A1D4C(); /* extern */
s32 func_800A384C();
s32 func_800A3D18();
s16 func_800A48F0(); /* extern */
s32 func_800A5720(); /* extern */
void func_800A90E8();
void func_8009A180(s32 *, u8 *);
extern M2C_UNK D_800E0A42;
extern M2C_UNK D_800E0A56;
extern M2C_UNK D_800E0A6A;


typedef struct S_800B7774_0_pre {
    u16 unk_00;
} S_800B7774_0_pre;   /* the 0x2 bytes before arg0 in func_800B7774, addressed as arg0[-1] */

typedef struct S_800B7774_0 {
    u8 unk_00;
    u8 pad_01[0x3];
    s32 * unk_04;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u16 unk_0C;
    s16 unk_0E;
} S_800B7774_0;   /* arg0 in func_800B7774 */

typedef struct S_800B7774_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_800B7774_1;   /* controls_base in func_800B7774 */

typedef struct S_800B7774_2_pre {
    s32 unk_00;
    u8 pad_04[0x10];
} S_800B7774_2_pre;   /* the 0x14 bytes before temp_v0 in func_800B7774, addressed as temp_v0[-1] */

typedef struct S_800B7774_2 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x1];
    u8 unk_13;
    u8 pad_14[0x4];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x17];
    u8 unk_43;
    u8 pad_44[0x2];
    union { u16 u; s16 s; } unk_46;   /* accessed as both */
    u8 pad_48[0x18];
    s32 unk_60;
} S_800B7774_2;   /* temp_v0 in func_800B7774 */


typedef struct S_800B7774_4 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800B7774_4;   /* arg2 in func_800B7774 */

typedef struct S_800B7774_5 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800B7774_5;   /* state_base in func_800B7774 */

typedef struct S_800B7774_6_pre {
    u16 unk_00;
} S_800B7774_6_pre;   /* the 0x2 bytes before temp_v0_6 in func_800B7774, addressed as temp_v0_6[-1] */

/* Spawns and levels the egg bomb monster, then advances its activation and cleanup. */
void func_800B7774(void *egg_bomb, Coord *position, void *effect) {
    s16 spawn_x;
    s16 spawn_y;
    s32 held_x;
    s32 held_y;
    u16 action_parameter;
    s16 phase;
    s32 *monster;
    s32 *tracked_monster;
    s32 action_data;
    s32 message_id;
    s32 action_id;
    s32 target_experience;
    s16 egg_bomb_level;
    u16 remaining_frames;
    GameWork *state_base;
    Coord *coord_arg = position;

    state_base = &gameWork;
    phase = ((S_800B7774_0 *)egg_bomb)->unk_0A.s;
    switch (phase) {
    case 0:
        if ((func_8009B88C(0, (u16) coord_arg->x >> 6, (u16) coord_arg->y >> 6, &spawn_x, &spawn_y) << 0x10) == 0) {
            {
                dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
            }
            func_800997FC(&D_800E0A42);
            (*(u16 *)((u8 *)egg_bomb + (-2))) = (u16) (((S_800B7774_0_pre *)egg_bomb)[-1].unk_00 | 0x8000);
            objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
            return;
        }
        held_x = spawn_x;
        held_y = spawn_y;
        monster = func_800A0B94(((S_800B7774_0 *)egg_bomb)->unk_00,
            func_800A1618(((S_800B7774_0 *)egg_bomb)->unk_00, 2), 1)(2, held_x, held_y, (s16) (coord_arg->z - 0x20));
        ((S_800B7774_0 *)egg_bomb)->unk_04 = monster;
        if (monster != NULL) {
            func_8003E188(((S_800B7774_2 *)monster)->unk_13, 0);
            func_800A90E8(egg_bomb);
            func_80042640(monster, ((S_800B7774_2 *)monster)->unk_13);
            func_800424E0(monster, ((S_800B7774_2 *)monster)->unk_13, 0);
            ((S_800B7774_2 *)monster)->unk_43 = 0xFE;
            func_800A48F0(monster, 0x1B, 0);
            {
                s32 clamp_value;
                u32 first_call_arg;
                s32 first_call_mode;
                s32 raw_first_result;
                clamp_value = (*(u8 *)((u8 *)&((EntityRec *)((u8 *)D_800E3D7C))->unk_10 + 1)) + 0x32;
                egg_bomb_level = clamp_value;
                if (clamp_value >= 0x64) {
                    egg_bomb_level = 0x63;
                }
                {
                    s32 *scan_arg = D_800835E8;
                    target_experience = D_800835E8[egg_bomb_level];
                    ((S_800B7774_2 *)monster)->unk_18 = target_experience;
                    if ((u32) target_experience >= (u32) D_800835E8[((S_800B7774_2 *)monster)->unk_11]) {
                        s32 *loop_base = D_800835E8;
                        do {
                            func_800A1D4C(monster, 0);
                        } while ((u32) loop_base[((S_800B7774_2 *)monster)->unk_11]
                            <= (u32) ((S_800B7774_2 *)monster)->unk_18);
                        scan_arg = monster;
                    }
                    raw_first_result = func_800990FC(scan_arg);
                }
                first_call_mode = 8;
                first_call_arg = raw_first_result;
                message_id = first_call_arg;
                raw_first_result = func_8009929C(first_call_mode, first_call_arg);
                func_80099290(func_80099194(&D_800E0A6A, func_8009929C(0xA, func_80099734(monster,
                    func_80099194(&D_800E0A56, raw_first_result)))));
            }
            func_800A5720(message_id);
            {
                s32 *call_obj;
                u8 *call_state;
                call_obj = monster;
                call_state = ((u8 *)D_800E3D7C);
                ((S_800B7774_0 *)egg_bomb)->unk_0C = 0x10U;
                func_8009A180(call_obj, call_state);
            }
            ((S_800B7774_0 *)egg_bomb)->unk_0A.u = (u16) (((S_800B7774_0 *)egg_bomb)->unk_0A.u + 1);
        }

        break;
    case 1:
        remaining_frames = ((S_800B7774_0 *)egg_bomb)->unk_0C - 1;
        ((S_800B7774_0 *)egg_bomb)->unk_0C = remaining_frames;
        if (((remaining_frames << 0x10) > 0) && !(((S_800B7774_4 *)effect)->unk_14 & 0x8000)
            && (((s32)state_base->unk_010) == 0)) {
            break;
        }
        ((S_800B7774_0 *)egg_bomb)->unk_0A.u = (u16) (((S_800B7774_0 *)egg_bomb)->unk_0A.u + 1);
        break;
    case 2:
        monster = ((S_800B7774_0 *)egg_bomb)->unk_04;
        if (((S_800B7774_0 *)egg_bomb)->unk_0E == 0) {
            ((S_800B7774_2 *)monster)->unk_60 = func_800A3D18(((S_800B7774_2_pre *)monster)[-1].unk_00, monster, 2);
            {
                dungeonStatus.flags = (u16) (dungeonStatus.flags | 2);
            }
            action_data = ((S_800B7774_2 *)monster)->unk_60;
            ((S_800B7774_2 *)monster)->unk_46.u = 0x800C;
            if (action_data != 0) {
                action_id = func_800A384C(monster, action_data, &action_parameter, 1);
                ((S_800B7774_2 *)monster)->unk_2A = action_parameter;
                if ((s16) action_id >= 0) {
                    ((S_800B7774_2 *)monster)->unk_46.s = (s16) (action_id | 0x8000);
                }
            }
        }
        ((EntityRec *)((u8 *)D_800E3D7C))->unk_110 = 0;
        (*(s32 *)((u8 *)monster + (0x1C))) = (s32) (((S_800B7774_2 *)monster)->unk_1C | 0x400000);
        {
            dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
        }
        (*(u16 *)((u8 *)egg_bomb + (-2))) = (u16) (((S_800B7774_0_pre *)egg_bomb)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
        break;
    }
    tracked_monster = ((S_800B7774_0 *)egg_bomb)->unk_04;
    if ((tracked_monster != NULL) && (((S_800B7774_6_pre *)tracked_monster)[-1].unk_00 & 0x8000)) {
        ((S_800B7774_0 *)egg_bomb)->unk_0E = 1;
    }
}
