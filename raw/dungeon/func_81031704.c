#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern u8 D_80083228[];
extern u8 D_801714B8[];
extern u8 D_801760CC[];

void func_80172F04(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *actor ASM_REG("$17");
    s32 state;
    u8 next_state;
    u16 timer;
    register u8 *table ASM_REG("$5");
    register u32 work ASM_REG("$2");
    register void *call_actor ASM_REG("$4");

    ASM_KEEP_NV(arg2);
    ASM_KEEP_NV(arg1);
    actor = arg3;
    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto end;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_0:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 3;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(actor, arg2, FIELD(actor, s16, 0x2A), 1);
        goto end;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    goto advance;

state_1:
    timer = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = timer;
    table = (u8 *)0x80170000;
    if (((s16)timer == 4) || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        ASM_KEEP(table);
        table += 0x60CC;
        work = 0x80080000;
        ASM_KEEP(work);
        FIELD(arg2, u8 *, 0x2C) = table;
        work = FIELD((u8 *)work, s16, 0x3228) + FIELD(actor, s16, 0x2A) + 0x100;
        work = ((s32)work >> 9) & 7;
        work += (u32)table;
        func_80047784(arg2,
            FIELD((u8 *)work, u8, 0),
            0);
        func_800A56E0(0x809);
        goto advance;
    }
    goto end;

state_2:
    timer = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = timer;
    if (((s16)timer == 4) || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_8009C12C(actor, arg2, FIELD(actor, s16, 0x2A), 1);
        goto advance;
    }
    goto end;

advance:
    next_state = FIELD(arg0, u8, 0x9B);
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B) = next_state + 1;
    goto end;

state_3:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        func_800AD594(actor, 0x140);
        call_actor = actor;
        ASM_KEEP(call_actor);
        work = (u32)D_801714B8;
        ASM_KEEP(work);
        FIELD(arg0, u8 *, 0x8C) = (u8 *)work;
        work = 0x80080000;
        ASM_KEEP(work);
        FIELD((u8 *)work, s32, 0x346C) = 0;
        func_800A4ACC(call_actor);
        FIELD(actor, u16, 0x46) &= 0x7FFF;
    }

end:
    return;
}
