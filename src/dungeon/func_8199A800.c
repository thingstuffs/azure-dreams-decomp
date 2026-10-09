#include "modules/dungeon_ovl_19ba800.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

#define U8_AT(p, off) (*(u8 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define U32_AT(p, off) (*(u32 *)((u8 *)(p) + (off)))
#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define PTR_AT(p, off) (*(void **)((u8 *)(p) + (off)))

extern u8 D_80024A64[];
extern u16 D_80024A70[];


extern s32 func_80053EF0(s32);
extern void func_800B835C(void *, void *, s32, s32);
extern u8 D_80080000[];

#define MANAGER_PTR() ((void *)(u32)U32_AT(((u8 *)(&D_800814A8)), 0))

void func_8002401C(void *state_data);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol func_80024000).  The phase table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_19ba800_entry)(void *) = func_8002401C;

/* Advances a timed effect sequence, updates the entry tint, and draws the animation. */
void func_8002401C(void *state_data)
{
    u8 *state = (u8 *)state_data;
    GameWork *effect_flags;
    s32 phase;
    s32 result;
    void *entry;
    void *child;

    U16_AT(state, 0x16)++;
    phase = S16_AT(state, 0x0A);
    effect_flags = &gameWork;
    switch (phase) {
    case 0:
        U32_AT(MANAGER_PTR(), 0xF4) = (u32)D_80024A64;
        func_800246F4((ObjectNodeHeader *)((u8 *)PTR_AT(state, 0) - 0x20), PTR_AT(state, 4));
        result = U16_AT(state, 0x0A);
        result++;
        U16_AT(state, 0x0A) = result;
    case 1:
        result = (s32)PTR_AT(state, 4);
        if ((U16_AT((void *)result, 0) & 0x80) == 0) {
            break;
        }
        {
            void *manager =
                *(void **)(D_80080000 + 0x14A8);

            U16_AT(state, 0x18) = 0x12;
            result = U16_AT(manager, 0xA6) - 1;
            U16_AT(manager, 0xA6) = result;
        }
        result = func_80053EF0(4);
        if (result != 2) {
            func_800A56E0(0x300);
        } else {
            func_800A56E0(0x4300);
        }
        U8_AT(MANAGER_PTR(), 0xA8) = U8_AT(state, 8);
        U16_AT(state, 0x14) = U16_AT(MANAGER_PTR(), 0x2A);
        U16_AT(state, 0x0A)++;
        break;

    case 2:
        U16_AT(state, 0x18)--;
        if ((s16)U16_AT(state, 0x18) > 0) {
            break;
        }
        U16_AT(state, 0x18) = 0x10;
        U16_AT(state, 0x0A)++;
        break;

    case 3:
        entry = PTR_AT(MANAGER_PTR(), 0x60);
        if (entry != 0) {
            s32 entry_flags = (s32)U32_AT(entry, 0x1C) | 0x10000000;
            u32 tint = 0;

            U32_AT(entry, 0x1C) = entry_flags;
            child = PTR_AT(entry, -0x14);
            if ((U16_AT(effect_flags, 4) & 1) != 0) {
                tint = 0x0080FF80;
            }
            U32_AT(child, 0x0C) = tint;
        }
        if ((U16_AT(((u16 *)(&D_80082E80.unk_014)), 0) & 0x8000) == 0) {
            U16_AT(state, 0x18)--;
            if ((s16)U16_AT(state, 0x18) >= 0) {
                break;
            }
        }
        entry = PTR_AT(MANAGER_PTR(), 0x60);
        if (entry != 0) {
            u32 clear_effect_mask = 0xEFFFFFFF;
            u32 tint = 0x00808080;
            s32 entry_flags;

            child = PTR_AT(entry, -0x14);
            entry_flags = (s32)U32_AT(entry, 0x1C) & clear_effect_mask;
            U32_AT(entry, 0x1C) = entry_flags;
            U32_AT(child, 0x0C) = tint;
        }
        U16_AT(state, 0x0A)++;
        break;

    case 4:
        if (S16_AT(D_80024A70, 0) == 0) {
            {
                DungeonGlobalStatus *sequence_state = &dungeonStatus;
                U16_AT(sequence_state, 0x0A)--;
                U32_AT(sequence_state, 0x0C) = 0;
            }
            U16_AT(state, -2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
    }
    if (S16_AT(state, 0x0A) >= 2) {
        u8 *draw_data = (u8 *)&D_80024A70[2];
        s32 draw_params[2];

        draw_params[0] = 0x01000360;
        draw_params[1] = 0x00200020;
        func_800B835C(draw_data, draw_params, 1, 0);
        U8_AT(draw_data, 8) += 0x10;
    }
    D_80024A70[0] = 0;
}

