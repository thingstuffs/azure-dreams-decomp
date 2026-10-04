#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
extern int abs(int);

void *func_8003FD64();
s32 func_8004491C();
s32 func_80069EF8();
void func_8009CE1C();
void *func_800A05A4();
s16 func_800A3820();
s32 func_800A4688();
s32 func_800A56E0();
s16 func_800BCB04();
extern M2C_UNK D_800245B4;
extern M2C_UNK D_80024A1C;


typedef struct S_func_81820800_1 {
    void *unk_00;
    u16 *unk_04;
    u8 pad_08[1];
    u8 unk_09;
    s16 unk_0A;
    u8 pad_0C[0x44];
    u16 unk_50;
    s16 unk_52;
} S_func_81820800_1;

typedef struct S_func_81820800_2 {
    union {
        s32 unk_00;
        struct {
            u8 pad_00[2];
            u16 unk_02;
        } unk_02;
    } unk_00;
    union {
        s32 unk_04;
        struct {
            u8 pad_04[2];
            u16 unk_06;
        } unk_06;
    } unk_04;
    u8 pad_08[2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_81820800_2;

typedef struct S_func_81820800_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void *unk_60;
    u8 pad_64[0xE];
    u8 unk_72;
    u8 unk_73;
} S_func_81820800_3;

typedef struct S_func_81820800_4 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
} S_func_81820800_4;

typedef struct S_func_81820800_5 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_func_81820800_5;

typedef struct S_func_81820800_6 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0xC];
    void *unk_20;
} S_func_81820800_6;

typedef struct S_func_81820800_7 {
    u8 pad_00[4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0x24];
    s16 unk_4C;
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
    s16 unk_54;
    s16 unk_56;
} S_func_81820800_7;

typedef struct S_func_81820800_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_func_81820800_8;

void func_80024020(void *state, S_func_81820800_2 *motion, void *source_data);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol func_80024000).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const module_entry)(void *, S_func_81820800_2 *, void *) __asm__("func_80024000") = func_80024020;

/* Moves an attack toward its target, spawns trailing effects, and applies the hit. */
void func_80024020(void *state, S_func_81820800_2 *motion, void *source_data) {
    S_func_81820800_1 *state_obj;
    S_func_81820800_4 *owner;
    S_func_81820800_5 *source;
    S_func_81820800_3 *actor;
    u32 header_raw;
    S_func_81820800_5 *target_data;
    S_func_81820800_7 *effect_data;
    S_func_81820800_6 *effect;
    S_func_81820800_5 *actor_data;
    s32 step_x;
    s32 step_y;
    s32 offset_x;
    s32 offset_y;
    M2C_UNK distance_or_script;
    s32 abs_y;
    s32 dir_offset;
    s32 coord_x;
    s32 velocity_x;
    s32 velocity_y;
    s32 phase;
    s32 start_y;
    s32 end_x;
    s32 coord_y;
    u16 duration;
    state_obj = state;
    source = source_data;
    actor = state_obj->unk_00;
    owner = (void *) ((u8 *) actor - 0x20);
    header_raw = actor->unk_2A;
    coord_x = header_raw >> 8;
    dir_offset = coord_x & 0xE;
    actor_data = ((S_func_81820800_4 *) ((u8 *) actor - 0x20))->unk_0C;
    step_x = *(s16 *)((u8 *)dirStepX + dir_offset);
    step_y = *(s16 *)((u8 *)dirStepY + dir_offset);
    if (state_obj->unk_0A == 1) {
        motion->unk_00.unk_00 = (s32) (motion->unk_00.unk_00 + motion->unk_0C);
        motion->unk_04.unk_04 = (s32) (motion->unk_04.unk_04 + motion->unk_10);
        coord_x = func_800BCB04(motion->unk_00.unk_02.unk_02, motion->unk_04.unk_06.unk_06,
            (s16) (((S_func_81820800_8 *) owner->unk_08)->unk_0A - 0x30));
        if (coord_x < 0x200) {
            motion->unk_0A = coord_x;
        }
    }
    phase = state_obj->unk_0A;
    state_obj->unk_50 = (u16) (state_obj->unk_50 - 1);
    switch (phase) {
    case 0:
    if (!(*state_obj->unk_04 & 0x80)) {
        return;
    }
    {
        S_func_81820800_5 *tile_data;
        s32 search_mode;
        start_y = func_800A3820(3);
        search_mode = start_y << 0x10;
        tile_data = actor_data;
        end_x = tile_data->unk_24;
        header_raw = (u32)func_800A05A4(actor, end_x, tile_data->unk_25, (s16) actor->unk_2A, search_mode >> 0x10);
    }
    actor->unk_60 = (S_func_81820800_3 *)header_raw;
    if (((S_func_81820800_3 *)header_raw) != NULL) {
        goto use_target;
    }
    distance_or_script = 0;
    offset_y = 0;
    offset_x = 0;
    do {
        {
            S_func_81820800_5 *tile_data = actor_data;
            s32 tile_left;
            s32 tile_left_2;
            s32 tile_top;
            tile_left_2 = (tile_data->unk_24 + offset_x) << 6;
            coord_x = tile_left_2 + 0x20;
            tile_top = (tile_data->unk_25 + offset_y) << 6;
            coord_y = tile_top + 0x20;
        }
        effect = (S_func_81820800_6 *)(u32)(u16)coord_x;
        if ((func_800A4688((u32)effect, (u16)coord_y, func_800BCB04((u32)effect, (u16)coord_y, -0x400),
            (s16)actor->unk_2A, actor->unk_60) << 0x10) != 0) {
            break;
        }
        distance_or_script += 1;
        offset_y += step_y;
        offset_x += step_x;
    } while (distance_or_script < 2);
    {
        S_func_81820800_5 *tile_data = actor_data;
        actor->unk_72 = (u8) (tile_data->unk_24 + (step_x * distance_or_script));
        actor->unk_73 = (u8) (tile_data->unk_25 + (step_y * distance_or_script));
    }
    goto start_motion;
use_target:
    target_data = ((S_func_81820800_4 *) ((u8 *) ((S_func_81820800_3 *)header_raw) - 0x20))->unk_0C;
    actor->unk_72 = (u8) target_data->unk_24;
    actor->unk_73 = (u8) target_data->unk_25;
    if (target_data->unk_14 & 0x8000) {
        if (source->unk_14 & 0x8000) {
            goto start_hit;
        }
    }
start_motion:
    {
        S_func_81820800_5 *tile_data;

        tile_data = actor_data;
        end_x = (s8)actor->unk_72;
        abs_y = (s8)actor->unk_73;
        phase = tile_data->unk_24;
        start_y = tile_data->unk_25;
        coord_x = end_x - phase;
        coord_y = abs_y - start_y;
    }
    distance_or_script = abs(coord_x);
    abs_y = coord_y;
    abs_y = abs(abs_y);
    if (distance_or_script < abs_y) {
        distance_or_script = abs_y;
    }
    state_obj->unk_50 = (u16) (distance_or_script * 0xC);
    motion->unk_00.unk_00 = (s32) (((actor_data->unk_24 << 6) + 0x20) << 0x10);
    motion->unk_04.unk_04 = (s32) (((actor_data->unk_25 << 6) + 0x20) << 0x10);
    motion->unk_0C = (s32) ((step_x << 0x16) / 12);
    motion->unk_10 = (s32) ((step_y << 0x16) / 12);
    func_800A56E0(0x300);
    state_obj->unk_0A = (s16) ((u16) state_obj->unk_0A + 1);
    return;

    case 1:
    case 2:
    motion->unk_14 = (s32) (motion->unk_14 + 0x100);
    coord_y = 0;
    if (actor->unk_60 == NULL) {
        coord_y = -1;
    }
    coord_x = 2;
    distance_or_script = (s32)&D_800245B4;
next_effect:
    effect = func_8003FD64(0x201, ((M2C_UNK *)&D_80083498.next));
    if (effect != NULL) {
        effect->unk_10 = distance_or_script;
        func_8004491C(effect, &D_80024A1C);
        duration = state_obj->unk_50;
        effect_data = (S_func_81820800_7 *) ((u8 *) effect + 0x20);
        effect_data->unk_54 = coord_y;
        effect_data->unk_52 = duration;
        effect_data->unk_4C = (s16) (func_80069EF8() & 0xFFF);
        effect_data->unk_4E = (u16) motion->unk_14;
        effect_data->unk_04 = (s32) motion->unk_00.unk_00;
        effect_data->unk_08 = (s32) motion->unk_04.unk_04;
        effect_data->unk_0C = 0;
        velocity_x = motion->unk_0C;
        effect_data->unk_1C = velocity_x;
        effect_data->unk_10 = velocity_x;
        velocity_y = motion->unk_10;
        effect_data->unk_24 = 0xFFFD0000;
        effect_data->unk_18 = 0xFFFD0000;
        effect_data->unk_20 = velocity_y;
        effect_data->unk_14 = velocity_y;
        effect_data->unk_50 = (u16) motion->unk_0A;
        effect->unk_20 = state_obj;
        effect_data->unk_56 = (s16) ((u16) state_obj->unk_0A - 1);
    }
    coord_x -= 1;
    if (coord_x >= 0) {
        goto next_effect;
    }
    if ((s16) state_obj->unk_50 > 0) {
        return;
    }
    state_obj->unk_50 = 5U;
    state_obj->unk_0A = (s16) ((u16) state_obj->unk_0A + 1);
    if (actor->unk_60 != NULL) {
        return;
    }
start_hit:
    state_obj->unk_0A = 3;
    return;
    case 3:
    if (actor->unk_60 != NULL) {
        func_8009CE1C(actor->unk_60, 0x10, state_obj->unk_09, 4, (s32) (s16) actor->unk_2A, actor, 2);
    }
    state_obj->unk_50 = 0x10U;
    state_obj->unk_0A = (s16) ((u16) state_obj->unk_0A + 1);
    return;
    case 4:
    if ((s16) state_obj->unk_50 > 0) {
        return;
    }
    state_obj->unk_0A = (s16) ((u16) state_obj->unk_0A + 1);
    return;
    case 5:
    if (state_obj->unk_52 & 0x8000) {
        state_obj->unk_52 = (s16) ((u16) state_obj->unk_52 & 0x7FFF);
        return;
    }
    dungeonStatus.unk_0C = 0;
    *(u16 *)((u8 *)state_obj - 2) = (u16) (*(u16 *)((u8 *)state_obj - 2) | 0x8000);
    objectFlagBlock.flags = (s32) (objectFlagBlock.flags | 0x8000);
    return;
    }
}
