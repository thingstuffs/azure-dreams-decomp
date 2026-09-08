#include "common.h"

typedef struct GlobalADBC { u8 pad0[0x18]; s16 field18; s16 field1A; } GlobalADBC;
typedef struct TownState {
    s32 field0; s32 field4; s32 field8; u8 pad0C[0xC];
    void *field18; void *field1C; void *field20; void *field24;
    u8 pad28[8]; void *field30; void *field34; void *field38; void *field3C; void *field40;
} TownState;

/* Fixed application scratch arena below the PS-X EXE load image.  Resident
 * func_8004B568 decodes data starting at this exact base; TOWN publishes its
 * state in the leading word and passes the following payload to the init. */
typedef struct TownSystemScratch {
    void *state;
    u8 payload[1];
} TownSystemScratch;

#define TOWN_SYSTEM_SCRATCH ((TownSystemScratch *)0x80016000U)

typedef void (*InitCallback)(void *, s32, s32);
typedef void (*ListCallback)(void);
extern GlobalADBC D_8006ADBC;
extern void *D_8006ADC0[];
extern s32 D_80082A38[];
extern u8 D_80082A80[];
extern u8 D_80082BC0[];
extern u8 D_800D2EA4[];
extern u8 D_800D381C[];
extern u8 D_800D3CC8[];
extern u8 D_800D401C[];
extern TownState D_801131B8;
extern void func_80034F88(void *, void *);
extern void func_8008AC84(s32);
extern void func_8008B23C(void *);

/* Sets up town state and runs initialization and list callbacks. */
void func_8009D5C0(void **entries) {
    s16 mode;
    void **entry_cursor;
    u8 *state_buffer;
    u8 *system_work;
    u8 *init_object;
    TownState *town_state;
    TownState *state;
    InitCallback init_callback;
    ListCallback entry_callback;
    void *entry;

    entry_cursor = entries;
    town_state = &D_801131B8;
    mode = D_8006ADBC.field18;
    town_state->field4 = (mode == 12);
    if (mode == 12) {
        town_state->field8 = D_8006ADBC.field1A;
    } else {
        town_state->field8 = 0;
    }
    if (D_8006ADC0[0] != 0) {
        state_buffer = D_80082A80;
        system_work = state_buffer - 0x48;
        state = &D_801131B8;
        state->field1C = state_buffer;
        state->field20 = D_800D3CC8;
        state->field24 = D_800D401C;
        state->field30 = D_800D381C;
        state->field38 = (void *)0x80010000;
        state->field18 = (void *)0x80012D70;
        state->field40 = (void *)0x80013188;
        state->field3C = D_800D2EA4;
        TOWN_SYSTEM_SCRATCH->state = (void *)state;
        func_80034F88(system_work, (void *)TOWN_SYSTEM_SCRATCH->payload);
        *(s32 *)(system_work + 0x84) = 0;
        init_object = D_80082BC0;
        init_callback = *(InitCallback *)(init_object + 0x10);
        init_callback(init_object + 0x20, 0, 0);
        func_8008AC84(0);
        func_8008B23C(state->field34);
    }
    while ((entry = *entry_cursor) != 0) {
        entry_callback = *(ListCallback *)((u8 *)entry + 0x10);
        if (entry_callback != 0) entry_callback();
        entry_cursor++;
    }
    func_80034F88(D_80082A38, *(void **)((u8 *)D_80082A38 + 0x88));
}
