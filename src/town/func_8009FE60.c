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

void func_8009D5C0(void **arg0) {
    s16 field18;
    void **iter;
    u8 *base;
    u8 *work;
    u8 *object;
    TownState *initial;
    TownState *state;
    InitCallback init;
    ListCallback callback;
    void *entry;

    iter = arg0;
    initial = &D_801131B8;
    field18 = D_8006ADBC.field18;
    initial->field4 = (field18 == 12);
    if (field18 == 12) {
        initial->field8 = D_8006ADBC.field1A;
    } else {
        initial->field8 = 0;
    }
    if (D_8006ADC0[0] != 0) {
        base = D_80082A80;
        work = base - 0x48;
        state = &D_801131B8;
        state->field1C = base;
        state->field20 = D_800D3CC8;
        state->field24 = D_800D401C;
        state->field30 = D_800D381C;
        state->field38 = (void *)0x80010000;
        state->field18 = (void *)0x80012D70;
        state->field40 = (void *)0x80013188;
        state->field3C = D_800D2EA4;
        TOWN_SYSTEM_SCRATCH->state = (void *)state;
        func_80034F88(work, (void *)TOWN_SYSTEM_SCRATCH->payload);
        *(s32 *)(work + 0x84) = 0;
        object = D_80082BC0;
        init = *(InitCallback *)(object + 0x10);
        init(object + 0x20, 0, 0);
        func_8008AC84(0);
        func_8008B23C(state->field34);
    }
    while ((entry = *iter) != 0) {
        callback = *(ListCallback *)((u8 *)entry + 0x10);
        if (callback != 0) callback();
        iter++;
    }
    func_80034F88(D_80082A38, *(void **)((u8 *)D_80082A38 + 0x88));
}
