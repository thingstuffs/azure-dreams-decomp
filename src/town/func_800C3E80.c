#include "common.h"

typedef struct {
    u8 pad0[0x18];
    s16 state;
    s16 index;
} TownState;

extern TownState D_8006ADBC;
extern u8 D_800D4094[];
extern u16 D_800D4244[];
extern u16 D_800D4268[];

extern s32 func_800C0F60(s16 arg0);
extern s32 func_800B28A0(void);
extern void func_8004437C(s32 arg0, s32 arg1);
extern void SD_Call(s32 arg0);

/* town_sd_sq_callagain_sub: replay and record the town or fallback sequence with the supplied flags. */
s32 town_sd_sq_callagain_sub(s32 sequence_flags) {
    s32 entry_index;
    u16 town_effect;
    u16 town_sequence;
    u16 fallback_effect;
    u16 fallback_sequence;
    u8 *town_entry;
    u8 *town_entries;
    u16 *fallback_entries;
    u16 *fallback_entry;
    s32 fallback_index;
    /* MATCH: Keep the merged sequence argument in a0 through each arm. */
    register s32 sequence ASM_REG("$4");

    entry_index = func_800C0F60(D_8006ADBC.index);
    if (D_8006ADBC.state == 12) {
        u16 *current_sound;

        current_sound = D_800D4268;
        town_entries = D_800D4094;
        town_entry = town_entries + (entry_index * 10);
        town_effect = *(volatile u16 *)(town_entry + 6);
        current_sound[2] = town_effect;
        if ((s16)town_effect != -1) {
            func_8004437C(*(s16 *)(town_entry + 6), 0);
        }
        town_sequence = *(u16 *)(town_entry + 8);
        current_sound[3] = town_sequence;
        if ((s16)town_sequence == -1) {
            return 1;
        }
        sequence = *(u16 *)(town_entry + 8);
        sequence |= sequence_flags;
        sequence = (u16)sequence;
    } else {
        fallback_index = func_800B28A0();
        fallback_entries = D_800D4244;
        fallback_entry = fallback_entries + (fallback_index * 2);
        fallback_effect = fallback_entry[0];
        D_800D4268[2] = fallback_effect;
        func_8004437C((s16)fallback_effect, 0);
        fallback_sequence = fallback_entry[1];
        ((volatile u16 *)D_800D4268)[3] = fallback_sequence;
        sequence = fallback_sequence | sequence_flags;
        sequence = (u16)sequence;
        /* MATCH: Complete argument preparation before the shared call. */
        ASM_SCHED_BARRIER();
    }
    SD_Call(sequence);
    return 1;
}
