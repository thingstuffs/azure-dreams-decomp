#include "common.h"
#include "m2c_compat.h"

typedef struct S_800F65CC_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x10];
    s16 unk_24;
} S_800F65CC_0;   /* temp_v0_2 in func_800F65CC */

typedef struct S_800F65CC_1 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_800F65CC_1;   /* s1 in func_800F65CC */

typedef struct S_800F65CC_2 {
    u8 pad_00[0x4];
    union { u16 s; s16 u; } unk_04;   /* accessed as both */
} S_800F65CC_2;   /* temp_v1 in func_800F65CC */


struct S_8003E2D8 {
    u8 pad0[0x1DC];
    s32 *field_1DC;
    s16 pad_1E0[8];
    s16 field_1F0;
};
typedef struct S_8003E2D8 S_8003E2D8;
struct S_80082E60 {
    u8 pad0[0x10];
    s16 field_10;
    s16 field_12;
    s16 field_14;
    s16 field_16;
};
typedef struct S_80082E60 S_80082E60;
extern s16 *D_800F8A44[];
extern struct S_8003E2D8 D_80083160;
extern struct S_80082E60 D_80082E60;
extern volatile s16 D_80013714[8];
extern u8 D_80013720[];
extern u8 D_800F6544[];
extern u8 D_800F8A4C[];
struct S_10 {
    u8 data[10];
};
void *func_8003FC64(s32, s32, s16 **, s32);

/* Initializes effect state and sets the high flag bit on three adjacent entries. */
void func_800F65CC(void) {
    s16 **state_slot;
    s16 *state_value;
    s32 entries_base;
    s32 index;
    S_8003E2D8 *world_state;
    s16 *entry_info;
    S_80082E60 *effect_state;
    s16 **state_table;
    s32 state_code;
    u16 entry_flags;
    S_800F65CC_0 *effect;
    S_800F65CC_2 *entry;

    world_state = &D_80083160;
    entry_info = (s16 *)((u8 *)world_state + 0x1DC);
    entries_base = world_state->field_1DC;
    index = 1;
    state_code = 0x11;
    state_table = D_800F8A44;
    state_slot = state_table + 1;
    effect_state = &D_80082E60;
    effect_state->field_10 = 0x1F;
    effect_state->field_12 = 0x3E;
    effect_state->field_16 = (u16)(effect_state->field_16 | 1);
    do {
        state_value = *state_slot;
        if (state_value != NULL) {
            *state_value = state_code;
        }
        index -= 1;
        state_slot -= 1;
    } while (index >= 0);
    effect = func_8003FC64(0x12, index, state_slot, state_code);
    if (effect != NULL) {
        s16 *status_base;

        effect->unk_10 = &D_800F6544;
        effect->unk_24 = 0x38;
        status_base = (s16 *)0x80010000;
        if (!((u16)status_base[0x3714 / 2] & 1)) {
            *(struct S_10 *)((u32)0x80010000 | 0x3720) = *(struct S_10 *)D_800F8A4C;
            status_base[0x371A / 2] = 0;
            status_base[0x3718 / 2] = 0;
            status_base[0x3716 / 2] = 4;
            status_base[0x3714 / 2] = (u16)(status_base[0x3714 / 2] | 1);
        }
    }
    index = 0x1E;
    do {
        entry = ((index + (0x3E << ((S_800F65CC_1 *)entry_info)->unk_14)) * 6) + entries_base;
        entry_flags = entry->unk_04.s;
        index += 1;
        entry->unk_04.u = (s16)(entry_flags | 0x8000);
    } while (index < 0x21);
}
