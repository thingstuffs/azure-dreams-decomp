#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u32 word0;
    u32 word1;
} Copy8 __attribute__((packed));

typedef struct {
    u8 pad0[8];
    void *child;
    void *sub;
    u8 *d81d4;
} Entry;

typedef struct S_func_800D7FB8_0 {
    s16 unk_00;
    union {
        s16 s16_value;
        u16 u16_value;
    } unk_02;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
} S_func_800D7FB8_0;

typedef struct S_func_800D7FB8_1 {
    u8 pad_00[0x4A];
    s16 unk_4A;
} S_func_800D7FB8_1;

typedef struct S_func_800D7FB8_2 {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[2];
    u16 unk_06;
    u8 pad_08[2];
    u16 unk_0A;
} S_func_800D7FB8_2;

typedef struct S_func_800D7FB8_3 {
    u8 *unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[2];
    u16 unk_14;
    u8 pad_16[6];
    s16 unk_1C;
    s16 unk_1E;
} S_func_800D7FB8_3;

typedef struct S_func_800D7FB8_4 {
    u8 pad_00[4];
    s32 unk_04;
} S_func_800D7FB8_4;

typedef struct S_func_800D7FB8_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_func_800D7FB8_5;

typedef struct S_func_800D7FB8_6 {
    s32 unk_00;
} S_func_800D7FB8_6;

typedef struct S_func_800D7FB8_7 {
    u16 unk_00;
} S_func_800D7FB8_7;

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_800DEC00[];
extern s32 D_80083460[3];
extern s32 D_800814A0[];
extern s32 D_800D81D4;

extern void *func_8003FD64(void *, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A56E0(s32);

/* Spawns effect entries and marks the controller finished after two delays. */
void func_800D7FB8(S_func_800D7FB8_0 *controller) {
    S_func_800D7FB8_1 *entry_data;
    s16 state;
    s32 spawn_index;
    u16 finish_timer;
    u16 effect_timer;
    s32 resource_word;
    S_func_800D7FB8_3 *sub_data;
    Entry *entry;
    S_func_800D7FB8_5 *counter_base;

    state = controller->unk_00;
    if (state == 1) {
        goto timer_state;
    }
    if (state >= 2) {
        goto check_ff;
    }
    if (state == 0) {
        goto init_state;
    }
    goto done;

check_ff:
    if (state == 0xFF) {
        goto ff_state;
    }
    goto done;

init_state:
    controller->unk_02.s16_value = 0x3C;
    controller->unk_00 = (s16)((u16)controller->unk_00 + 1);
    func_800A56E0(0x600);
    spawn_index = 0x96;
    do {
        entry = func_8003FD64((void *)0x312, D_80083498);
        if (entry != NULL) {
            entry_data = (S_func_800D7FB8_1 *)((u8 *)entry + 0x20);
            entry->d81d4 = (u8 *)&D_800D81D4;
            func_8004491C(entry, D_80045340);
            sub_data = entry->sub;
            ((S_func_800D7FB8_2 *)entry->child)->unk_02 = controller->unk_04;
            ((S_func_800D7FB8_2 *)entry->child)->unk_06 = controller->unk_06;
            ((S_func_800D7FB8_2 *)entry->child)->unk_0A = controller->unk_08;
            sub_data->unk_1E = 0x400;
            sub_data->unk_1C = 0x400;
            sub_data->unk_10 = 0x20;
            sub_data->unk_00 = D_800DEC00;
            sub_data->unk_14 = (u16)(sub_data->unk_14 | 0xC);
            resource_word = ((S_func_800D7FB8_4 *)D_800DEC00)->unk_04;
            sub_data->unk_04 = 0;
            sub_data->unk_05 = 0;
            sub_data->unk_0C = 0;
            sub_data->unk_08 = resource_word;
            __builtin_memcpy((u8 *)entry + 0x2C, (u8 *)controller + 4, 8);
            entry_data->unk_4A = (spawn_index & 1) ? 1 : -1;
            ((S_func_800D7FB8_2 *)entry->child)->unk_0A = controller->unk_08;
        }
        spawn_index -= 1;
    } while (spawn_index >= 0);

timer_state:
    effect_timer = (u16)(controller->unk_02.u16_value - 1);
    controller->unk_02.u16_value = effect_timer;
    if ((effect_timer << 0x10) <= 0) {
        controller->unk_02.u16_value = 8U;
        controller->unk_00 = (s16)0xFF;
    }
    goto done;

ff_state:
    finish_timer = (u16)(controller->unk_02.u16_value - 1);
    controller->unk_02.u16_value = finish_timer;
    if ((finish_timer << 0x10) <= 0) {
        counter_base = (S_func_800D7FB8_5 *)D_80083460;
        counter_base->unk_0A = (u16)(counter_base->unk_0A - 1);
        ((S_func_800D7FB8_7 *)((u8 *)controller - 2))->unk_00 = (u16)(((S_func_800D7FB8_7 *)((u8 *)controller - 2))->unk_00 | 0x8000);
        ((S_func_800D7FB8_6 *)D_800814A0)->unk_00 = ((S_func_800D7FB8_6 *)D_800814A0)->unk_00 | 0x8000;
    }

done:
    return;
}
