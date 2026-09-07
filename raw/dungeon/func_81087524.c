#include "common.h"

typedef struct {
    s32 words[6];
} Copy24;

extern s32 D_800814A0;
extern s32 D_80175F38;

s32 func_8003DE58(s32, void *, s16 *, s32);
void func_80047784(void *, s32, s32);
void func_800478B8(void *);

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_80174D24(void *arg0, void *arg1, void *arg2)
{
    u16 local[3];
    void *object;
    Copy24 *source;
    register s32 copy0 ASM_REG("$3");
    register s32 copy1 ASM_REG("$4");
    register s32 copy2 ASM_REG("$5");
    register s32 copy3 ASM_REG("$6");
    register s32 call_zero ASM_REG("$7");
    register s32 call_arg0 ASM_REG("$4");
    register s32 mode ASM_REG("$4");
    register u16 old_count ASM_REG("$2");
    register u16 count ASM_REG("$3");
    register s32 signed_count ASM_REG("$2");
    u16 flags;

    if (FIELD(FIELD(arg0, void *, 8), void *, 0x2C) != &D_80175F38) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto out;
    }

    source = FIELD(arg0, Copy24 *, 4);
    copy0 = source->words[0];
    copy1 = source->words[1];
    copy2 = source->words[2];
    copy3 = source->words[3];
    ASM_KEEP(copy0);
    ASM_KEEP(copy1);
    ASM_KEEP(copy2);
    ASM_KEEP(copy3);
    FIELD(arg1, s32, 0) = copy0;
    FIELD(arg1, s32, 4) = copy1;
    FIELD(arg1, s32, 8) = copy2;
    FIELD(arg1, s32, 0xC) = copy3;
    copy0 = source->words[4];
    copy1 = source->words[5];
    ASM_KEEP(copy0);
    ASM_KEEP(copy1);
    FIELD(arg1, s32, 0x10) = copy0;
    FIELD(arg1, s32, 0x14) = copy1;

    object = FIELD(arg0, void *, 8);
    ASM_KEEP(object);
    call_zero = 0;
    ASM_KEEP(call_zero);
    call_arg0 = FIELD(object, s32, 8);
    ASM_KEEP(call_arg0);
    if (func_8003DE58(call_arg0, object,
                      (s16 *)local, call_zero) != 0) {
        FIELD(arg1, u16, 2) += local[0];
        FIELD(arg1, u16, 6) += local[1];
        FIELD(arg1, u16, 0xA) += local[2];
    }

    old_count = FIELD(arg0, u16, 2);
    mode = FIELD(arg0, s16, 0);
    count = old_count + 1;
    ASM_KEEP(old_count);
    ASM_KEEP(mode);
    ASM_KEEP(count);
    FIELD(arg0, u16, 2) = count;

    if (mode == 0) {
        goto mode_zero;
    }
    if (mode == 1) {
        goto mode_one;
    }
    goto out;

mode_zero:
    func_800478B8(arg2);
    flags = FIELD(arg2, u16, 0x14);
    if ((flags & 0x6000) == 0) {
        goto out;
    }
    FIELD(arg2, u16, 0x14) = flags | 0x80;
    FIELD(arg0, u16, 2) = 0;
    FIELD(arg0, u16, 0)++;
    goto out;

mode_one:
    signed_count = (s16)count;
    ASM_KEEP(signed_count);
    if (signed_count < 0x40) {
        goto out;
    }
    FIELD(arg2, u16, 0x14) &= 0xFF7F;
    func_80047784(arg2, 0x38, 0);
    FIELD(arg0, u16, 2) = 0;
    FIELD(arg0, s16, 0) = 0;

out:
    return;
}

/* MECHANISM: True-space epilogue joins and a u16[3] output object produce the 0x28 frame.
   Four guarded short-lived copy pins reproduce retail's v1/a0/a1/a2 copy roles.
   Ordering mode_zero before mode_one removes the word-61 displacement cascade. */
