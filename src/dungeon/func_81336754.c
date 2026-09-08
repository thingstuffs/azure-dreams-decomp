#include "common.h"

typedef union {
    u16 unsigned_value;
    s16 signed_value;
} DungeonTimer;

typedef struct {
    u8 pad_00[0x8C];
    u8 *unk_8C;
    u8 pad_90[6];
    DungeonTimer timer;
    u8 pad_98[3];
    u8 state;
    u8 pad_9C[0x10];
    u8 mode;
} DungeonState;

typedef struct {
    u8 pad_00[0x0C];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} DungeonWork;

typedef struct {
    u8 pad_00[0x14];
    u16 flags;
    u8 pad_16[0x0E];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[6];
    u8 *unk_2C;
} DungeonObject;

typedef struct {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x2A];
    u8 unk_72;
    u8 unk_73;
} DungeonInput;

extern u8 D_801739E0[];
extern u8 D_801739E8[];
extern u8 D_801739F0[];
extern u8 D_801739A0[];
extern u8 D_801739A8[];
extern u8 D_801739B0[];
extern u8 D_8016A36C[];
extern s16 D_80083228[5];
extern u8 D_80083780[12];
extern s32 D_8008346C[];
extern void *D_80164998[];

extern void func_80047784(DungeonObject *, u8, s32);
extern void func_800A2B04(DungeonWork *, u8, u8);
extern void func_800A56E0(s32);
extern void func_801676CC(DungeonWork *);
extern void func_801685CC(DungeonState *, DungeonWork *, DungeonObject *, u8 *, s32);

/* Advance the timed dungeon object sequence and update its direction table. */
void func_8016D754(DungeonState *state, DungeonWork *work,
                  DungeonObject *object, DungeonInput *input) {
    u32 state_index;
    static void *const state_labels[] = {
        &&case0, &&case1, &&case2, &&case3, &&case4, &&case5, &&case6
    };
    state_index = state->state;
    if (state_index >= 7)
        goto done;
    (void)state_labels;
    goto *D_80164998[state_index];

case1:
    {
        s32 mode;
        register u8 *direction_table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u32 direction_index;

        mode = state->mode;
        switch (mode) {
        case 0:
            direction_table = D_801739E0;
            break;
        case 1:
            direction_table = D_801739E8;
            break;
        case 2:
            direction_table = D_801739F0;
            break;
        case 3:
            direction_table = D_801739E0 + 0x18;
            break;
        default:
            goto case1_common;
        }
        object->unk_2C = direction_table;
        direction_index = ((s32)(D_80083228[0] + input->unk_2A + 0x100) >> 9) & 7;
        func_80047784(object,
            *((u8 *)((u32)direction_index + (u32)direction_table)), 0);
    }
case1_common:
    func_801676CC(work);
    state->timer.unsigned_value = 6;
    state->state = state->state + 1;
    func_800A56E0(0x703);
    goto done;

case2:
    {
        u16 timer;

        timer = state->timer.unsigned_value - 1;
        state->timer.unsigned_value = timer;
        if ((timer << 16) > 0) {
            if (object->flags & 0xE000)
                goto case0;
            goto done;
        }
        goto case0;
    }

case3:
    {
        u16 timer;
        s16 current_timer;

        timer = state->timer.unsigned_value + 1;
        state->timer.unsigned_value = timer;
        if ((s16)timer == 1) {
            func_801685CC(state, work, object, D_80083780, 0);
            current_timer = state->timer.signed_value;
            if (current_timer == (s16)timer) {
                func_801685CC(state, work, object, D_80083780, current_timer);
                if (state->timer.signed_value == current_timer)
                    func_801685CC(state, work, object, D_80083780, 2);
            }
        }
        if (state->timer.signed_value != 0xB)
            goto done;
        goto case0;
    }

case4:
    {
        s32 mode;
        u8 *direction_table;
        u8 *previous_table;
        u32 direction_index;

        if (!(object->flags & 0xE000))
            goto done;
        work->unk_14 = 0;
        work->unk_10 = 0;
        work->unk_0C = 0;
        func_800A2B04(work, object->unk_24, object->unk_25);
        mode = state->mode;
        switch (mode) {
        case 0:
            previous_table = object->unk_2C;
            direction_table = D_801739A0;
            break;
        case 1:
            previous_table = object->unk_2C;
            direction_table = D_801739A8;
            break;
        case 2:
            previous_table = object->unk_2C;
            direction_table = D_801739B0;
            break;
        case 3:
            previous_table = object->unk_2C;
            direction_table = D_801739A0 + 0x18;
            break;
        default:
            goto case0;
        }
        if (previous_table != direction_table) {
            object->unk_2C = direction_table;
            direction_index = ((s32)(D_80083228[0] + input->unk_2A + 0x100) >> 9) & 7;
            func_80047784(object,
                *((u8 *)((u32)direction_index + (u32)direction_table)), 0);
        }
        goto case0;
    }

case5:
    {
        u16 timer;

        timer = state->timer.unsigned_value;
        state->timer.unsigned_value = timer + 1;
        if ((s16)timer < 0x3C)
            goto done;
        goto case0;
    }

case0:
    state->timer.unsigned_value = 0;
    state->state = state->state + 1;
    goto done;

case6:
    input->unk_73 = 0;
    input->unk_72 = 0;
    state->unk_8C = D_8016A36C;
    D_8008346C[0] = 0;
    input->unk_46 = input->unk_46 & 0x7FFF;

done:
    return;
}
