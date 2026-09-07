#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))
#define VFIELD(ptr, type, off) (*(type volatile *)((u8 *)(ptr) + (off)))

extern s32 func_80042900();
extern void func_80170F50() __attribute__((noreturn));
extern void func_80170F54(void *) __attribute__((noreturn));
extern s32 D_800814A0;
extern u8 D_800E23F8[];
extern u8 D_800E2408[];
extern u8 *D_800E3D7C[3];

void func_80170CEC(void *arg0, void *arg1, void *arg2) {
    void *entity;
    register void *entity_saved ASM_REG("$10");
    void *copy_source;
    void *entity_base;
    void *record;
    u16 old_angle;
    u16 new_angle;
    u16 record_angle;
    s16 state;
    u16 state_u;
    void *kind;

    entity = FIELD(arg0, void *, 0x40);
    copy_source = VFIELD(arg0, void *, 0x44);
    old_angle = VFIELD(arg2, u16, 0x1A);
    entity_base = (u8 *)entity - 0x20;
    record = FIELD(entity_base, void *, 0xC);
    record_angle = FIELD(record, u16, 6);
    new_angle = old_angle + 0x190;
    ASM_SCHED_BARRIER();
    entity_saved = entity;
    FIELD(arg2, u16, 0x1A) = new_angle;
    FIELD(arg2, u16, 6) = record_angle;
    if (new_angle >= 0x1001) {
        FIELD(arg2, u16, 0x1A) = old_angle - 0xE70;
    }

    state = FIELD(arg0, s16, 0x2C);
    state_u = FIELD(arg0, u16, 0x2C);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        {
            register void *tail_arg ASM_REG("$4");

            tail_arg = entity_saved;
            ASM_KEEP(tail_arg);
            func_80170F54(tail_arg);
        }
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    {
        register void *tail_arg ASM_REG("$4");

        tail_arg = entity_saved;
        ASM_KEEP(tail_arg);
        func_80170F54(tail_arg);
    }

state_0:
{
    u16 fade0;
    s32 quotient0;

    fade0 = FIELD(arg0, u16, 0x36) + 1;
    quotient0 = ((s32)(s16)fade0 << 7) / FIELD(arg0, s16, 0x38);
    FIELD(arg0, u16, 0x36) = fade0;
    FIELD(arg2, s8, 0xC) = quotient0;
    FIELD(arg2, s8, 0xD) = quotient0;
    FIELD(arg2, s8, 0xE) = quotient0;
    if (FIELD(arg0, s16, 0x36) < 5) {
        goto do_call;
    }
    FIELD(arg0, u16, 0x2C)++;
    func_80170F54(entity_saved);
    return;
}

state_1:
    if ((FIELD(entity_saved, u8, 0x9A) == 0x19) ||
        (FIELD(entity_saved, u8, 0xB5) == 0)) {
        FIELD(arg0, u16, 0x2C) = state_u + 1;
        FIELD(arg0, s16, 0x38) = 0x14;
        FIELD(arg0, u16, 0x36) = 0x14;
    }
    if (FIELD(entity, u8, 0x9A) == 1) {
        FIELD(arg0, s16, 0x2C) = 3;
        FIELD(arg0, s16, 0x38) = 0x14;
        FIELD(arg0, u16, 0x36) = 0x14;
    }
    if ((FIELD(entity_saved, s32, 0x14) & 0x100000) &&
        (D_800E3D7C[0][0x9A] != 0x28)) {
        FIELD(arg0, s16, 0x2C) = 3;
        FIELD(arg0, s16, 0x38) = 0x14;
        FIELD(arg0, u16, 0x36) = 0x14;
    }
    if (FIELD(entity_base, u16, 0x1E) & 0x8000) {
        FIELD(arg0, s16, 0x2C) = 3;
        FIELD(arg0, s16, 0x38) = 0x14;
        FIELD(arg0, u16, 0x36) = 0x14;
    }
    kind = FIELD(record, void *, 0x2C);
    if ((kind == D_800E23F8) || (kind == D_800E2408)) {
        FIELD(arg0, s16, 0x2C) = 3;
        FIELD(arg0, s16, 0x38) = 0x14;
        FIELD(arg0, u16, 0x36) = 0x14;
    }
    FIELD(arg1, s32, 0) = FIELD(copy_source, s32, 0);
    FIELD(arg1, s32, 4) = FIELD(copy_source, s32, 4);
    FIELD(arg1, s32, 8) = FIELD(copy_source, s32, 8);
    func_80170F50();
    return;

state_3:
    FIELD(arg1, s32, 0) = FIELD(copy_source, s32, 0);
    FIELD(arg1, s32, 4) = FIELD(copy_source, s32, 4);
    FIELD(arg1, s32, 8) = FIELD(copy_source, s32, 8);
    FIELD(arg2, u16, 0x1C) = FIELD(record, u16, 0x1C);
    FIELD(arg2, u16, 0x1E) = FIELD(record, u16, 0x1E);

state_2:
{
    u16 fade2;
    s32 quotient2;

    fade2 = FIELD(arg0, u16, 0x36) - 1;
    quotient2 = ((s32)(s16)fade2 << 7) / FIELD(arg0, s16, 0x38);
    FIELD(arg0, u16, 0x36) = fade2;
    FIELD(arg2, s8, 0xC) = quotient2;
    FIELD(arg2, s8, 0xD) = quotient2;
    FIELD(arg2, s8, 0xE) = quotient2;
    if (FIELD(arg0, s16, 0x36) <= 0) {
        goto set_flags;
    }
}

    ASM_KEEP(entity_saved);
do_call:
    if ((func_80042900(entity_saved, 0xA) << 16) == 0) {
        return;
    }

set_flags:
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
}
