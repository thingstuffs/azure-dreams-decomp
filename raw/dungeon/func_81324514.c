#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s32 func_8009A66C();
extern s16 func_800A0818();
extern void func_8016BEF0(void) __attribute__((noreturn));
extern void func_8016BEF4(void) __attribute__((noreturn));
extern void func_8016BF48(void) __attribute__((noreturn));
extern s32 func_8016C698();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174674[];

void func_8016BD14(void *arg0, void *arg1, void *arg2, void *arg3) {
    register void *ctx ASM_REG("$17");
    s32 index;
    s32 mode;
    s16 next;
    register s32 result ASM_REG("$16");
    s32 raw;
    register u8 *row ASM_REG("$3");
    s32 mode2;
    s32 x;
    s32 y;
    s32 fifteen;
    s32 tmp;

    ctx = arg3;

    if (FIELD(ctx, s8, 0x71) <= 0) {
        return;
    }

    fifteen = 15;
    if (FIELD(arg0, u8, 0x9A) != fifteen) {
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg0, u8, 0x9D) = 0;
    }

    if (FIELD(ctx, u8, 0x71) <= FIELD(ctx, s16, 0x8A)) {
        return;
    }

    if (FIELD(arg2, u8 *, 0x2C) != D_80174674) {
        FIELD(arg2, u8 *, 0x2C) = D_80174674;
        func_80047784(
            arg2,
            D_80174674[((D_80083228 + FIELD(ctx, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }

    mode = FIELD(ctx, s32, 0x1C);
    x = FIELD(arg2, u8, 0x24);
    y = FIELD(arg2, u8, 0x25);
    mode = mode & 0x2000;
    func_8009A3D0(x, y, mode ? 0x300 : 0x3000);

    next = func_800A0818(x, y,
                         FIELD((u8 *)ctx + FIELD(ctx, s16, 0x8A), u8, 0x74),
                         FIELD((u8 *)ctx + FIELD(ctx, s16, 0x8A), u8, 0x7C),
                         (u8 *)arg0 + 0x98);
    raw = func_8009A66C(next, arg2, ctx, 0x20);

    tmp = FIELD((u8 *)ctx + FIELD(ctx, s16, 0x8A), u8, 0x74);
    ASM_KEEP(tmp);
    raw = raw << 16;
    ASM_KEEP(raw);
    FIELD(arg2, u8, 0x24) = tmp;
    row = (u8 *)ctx + FIELD(ctx, s16, 0x8A);
    result = raw >> 16;
    ASM_KEEP(result);
    FIELD(arg2, u8, 0x25) = FIELD(row, u8, 0x7C);
    index = FIELD(ctx, u16, 0x8A);
    mode2 = FIELD(ctx, s32, 0x1C);
    index = index + 1;
    mode2 = mode2 & 0x2000;
    FIELD(ctx, u16, 0x8A) = index;
    func_8009A21C(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                  mode2 ? 0x300 : 0x3000);
    FIELD(ctx, s16, 0x2A) = next;

    if (result == 3) {
        if (!(D_80083462 & 0x80) && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            func_8016C698(arg0, arg1, arg2, ctx);
            FIELD(arg0, s32, 0x8C) = 0;
            func_8016BEF4();
            return;
        }
        FIELD(arg0, u8, 0x9A) = 15;
        func_8016BEF0();
        return;
    }

    FIELD(arg0, u8, 0x9A) = fifteen;
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(ctx, s32, 0x1C) |= 0x40000000;
    if (D_80083462 & 0x80) {
        FIELD(arg0, s16, 0x96) = 0;
        func_8016BF48();
        return;
    }

    FIELD(arg0, s16, 0x96) = 8;
    x = FIELD(ctx, u8, 0x71);
    if (x > 0) {
        FIELD(arg0, s16, 0x96) = 8 / x;
    }
}

/* MECHANISM: gcc's pre-reload scheduler (sched1) sinks a low-priority sll/sra
   pair to the end of the block, so the (s16) narrowing of func_8009A66C's
   return must be nailed down: split it into raw<<16 and raw>>16 and BRACKET it
   with ASM_KEEP barriers (after the 0x74 byte load, after the sll, after the
   sra).  sched1 then fills the two load-delay slots exactly as retail does --
   sll after lbu 0x74, sra after the reloaded lh 0x8A -- which also frees $v0 in
   time for lbu 0x7C.  Frame objects: arg3 held in a pinned $s1 (unpinning it
   rebuilds the frame at -0x40/16 saved regs); the 0x7C row base pinned to $v1
   because the $s1 hard-reg pin makes gcc allocate a fresh $v0 for that addu;
   the two (x & 0x2000) mode flags are SEPARATE locals (one shared local forces
   one register and loses retail's $v0/$v1 split). */
