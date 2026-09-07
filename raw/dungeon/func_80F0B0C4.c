#include "common.h"

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern u8 D_80170F74[];
extern u8 D_80173D58[];

void func_80047784(void *, u8, s32);
void func_8009C12C(void *, void *, s16, s32);
void func_800A2B04(void *, u8, u8);
void func_800A4ACC(void *);
void func_800A56E0(s32);
void func_800AD594(void *, s32);

void func_801728C4(void *arg0, void *arg1, void *arg2, void *arg3) {
    register u8 *actor ASM_REG("$18");
    u16 counter;
    u8 next_state;
    s32 state;

    actor = arg3;
    state = FIELD(arg0, u8 *, 0x9B);
    switch (state) {
        case 0:
            FIELD(arg0, u8 *, 0x9B) = 1;
        case 1:
            goto state_1;
        case 2:
            goto state_2;
        case 3:
            goto state_3;
        default:
            return;
    }

state_1:
    if (FIELD(arg2, u16 *, 0x14) & 0x8000) {
        FIELD(arg0, u8 *, 0x9B) = 3;
        FIELD(arg2, u16 *, 0x14) |= 0x6000;
        func_8009C12C(actor, arg2, FIELD(actor, s16 *, 0x2A), 1);
        goto end;
    }
    FIELD(arg1, s32 *, 0x14) = 0;
    FIELD(arg1, s32 *, 0x10) = 0;
    FIELD(arg1, s32 *, 0xC) = 0;
    FIELD(arg2, void **, 0x2C) = D_80173D58;
    func_80047784(arg2,
        D_80173D58[((D_80083228 + FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7],
        0);
    next_state = FIELD(arg0, u8 *, 0x9B);
    FIELD(arg0, u16 *, 0x96) = 0;
    goto increment_state;

state_2:
    counter = FIELD(arg0, u16 *, 0x96) + 1;
    FIELD(arg0, u16 *, 0x96) = counter;
    if ((s16)counter != 2) {
        goto end;
    }
    func_800A56E0(0x804);
    func_8009C12C(actor, arg2, FIELD(actor, s16 *, 0x2A), 1);
    next_state = FIELD(arg0, u8 *, 0x9B);

increment_state:
    next_state++;
    FIELD(arg0, u8 *, 0x9B) = next_state;
    goto end;

state_3:
    if (!(FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto end;
    }
    func_800A2B04(arg1, FIELD(arg2, u8 *, 0x24), FIELD(arg2, u8 *, 0x25));
    func_800AD594(actor, 0x100);
    FIELD(arg0, void **, 0x8C) = D_80170F74;
    D_8008346C = 0;
    func_800A4ACC(actor);
    if (FIELD(actor, s8 *, 0x6D) == 0) {
        FIELD(actor, u16 *, 0x46) &= 0x7FFF;
        goto end;
    }
    D_800E3DE8 = actor - 0x20;
    ASM_USE(actor);

end:
    return;
}
