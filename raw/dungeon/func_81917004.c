#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct Copy24 {
    s32 word[6];
} Copy24;

extern void *func_8003FD64();
extern s32 func_80069EF8();
extern void func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();

extern s32 D_80024710;
extern s32 D_80025B10;
extern s32 D_80045340;

void *func_80024804(void *arg0, Copy24 *arg1, s16 arg2)
{
    register void *result ASM_REG("$2");
    register void *held_arg0 ASM_REG("$21") = arg0;
    register Copy24 *held_arg1 ASM_REG("$22") = arg1;
    register s16 held_arg2 ASM_REG("$16") = arg2;
    register void *obj ASM_REG("$20");
    void *part;
    register Copy24 *position ASM_REG("$17");
    register u8 *work ASM_REG("$19");
    register s32 angle ASM_REG("$18");
    s32 first;
    register s32 scaled_first ASM_REG("$16");
    s32 delta;
    s16 height;
    register s32 alloc_kind ASM_REG("$4");
    register void *alloc_source ASM_REG("$5");
    register s32 sign_word ASM_REG("$2");

    alloc_kind = 0x212;
    alloc_source = (u8 *)held_arg0 - 0x20;
    ASM_KEEP_NV(alloc_kind);
    ASM_KEEP_NV(alloc_source);
    ASM_KEEP_NV(held_arg0);
    ASM_KEEP_NV(held_arg1);
    ASM_KEEP_NV(held_arg2);
    obj = func_8003FD64(alloc_kind, alloc_source);
    if (obj == NULL) {
        goto null_result;
    }

    FIELD(obj, void *, 0x10) = &D_80024710;
    FIELD(obj, s32, 0x20) = FIELD(held_arg0, s32, 0);
    ASM_SCHED_BARRIER();

    sign_word = (s32)held_arg2 << 16;
    angle = sign_word >> 16;
    ASM_KEEP(sign_word);
    ASM_KEEP(angle);
    part = FIELD(obj, void *, 0x0C);
    FIELD(part, s8, 0x0D) = -0x60 - (angle << 6);
    FIELD(part, s8, 0x0C) = -0x60 - (angle << 6);
    FIELD(part, u8, 0x0E) = 0xC0;
    FIELD(part, s16, 0x12) = 0x7DCF;
    FIELD(part, void *, 0x08) = &D_80025B10;

    FIELD(part, u16, 0x14) |= 0x000C;
    FIELD(part, u16, 0x10) |= 0x0020;
    FIELD(part, u16, 0x14) |= 0x0100;

    delta = func_80069EF8();
    work = (u8 *)obj + 0x20;
    FIELD(part, s16, 0x1A) = delta % 0x1000;

    height = (angle << 8) + 0x500;
    FIELD(part, s16, 0x1E) = height;
    FIELD(part, s16, 0x1C) = height;
    func_8004491C(obj, &D_80045340);

    position = FIELD(obj, Copy24 *, 0x08);
    ASM_KEEP(position);
    ASM_KEEP(part);
    *position = *held_arg1;

    FIELD(work, u16, 0x0E) = FIELD(held_arg0, u16, 0x0E);
    FIELD(work, u16, 0x10) = FIELD(held_arg0, u16, 0x10);

    first = func_800644B8(FIELD(work, s16, 0x0E));
    angle += 2;
    position->word[0] -= (scaled_first = first >> 4) *
        (func_800644B8(FIELD(work, s16, 0x10)) >> 4) * angle * 8;

    first = func_800644B8(FIELD(work, s16, 0x0E));
    position->word[1] -= (scaled_first = first >> 4) *
        (func_80064584(FIELD(work, s16, 0x10)) >> 4) * angle * 8;

    position->word[2] -=
        ((func_80064584(FIELD(work, s16, 0x0E)) >> 4) * angle) << 11;
    result = obj;
    ASM_KEEP_NV(result);
    goto return_result;

null_result:
    ASM_CLOBBER("$20");
    result = NULL;
    ASM_KEEP(result);

return_result:
    return result;
}
