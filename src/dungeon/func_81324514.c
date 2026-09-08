#include "common.h"
#include "records/Rec_D_80082E80.h"


extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s32 func_8009A66C();
extern s16 func_800A0818();
extern void func_8016BEF0(void) __attribute__((noreturn));
extern void func_8016BEF4(void) __attribute__((noreturn));
extern s32 func_8016C698();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174674[];


typedef struct S_8016BD14_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_8016BD14_0;   /* ctx in func_8016BD14 */

typedef struct S_8016BD14_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 pad_9B[0x2];
    u8 unk_9D;
} S_8016BD14_1;   /* arg0 in func_8016BD14 */

typedef struct S_8016BD14_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8016BD14_2;   /* arg1 in func_8016BD14 */


typedef struct S_8016BD14_4 {
    u8 pad_00[0x7C];
    u8 unk_7C;
} S_8016BD14_4;   /* row in func_8016BD14 */

typedef struct S_8016BD14_5 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016BD14_5;   /* (u8 *)ctx + ((S_8016BD14_0 *)ctx)->unk_8A.s in func_8016BD14 */

void func_8016BD14(void *arg0, void *arg1, void *arg2, void *arg3) {
    register void *ctx ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 index;
    s32 mode;
    s16 next;
    s32 result;
    s32 raw;
    register u8 *row ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 mode2;
    s32 x;
    s32 y;
    s32 fifteen;
    s32 tmp;

    ctx = arg3;

    if (((S_8016BD14_0 *)ctx)->unk_71.s <= 0) {
        return;
    }

    fifteen = 15;
    if (((S_8016BD14_1 *)arg0)->unk_9A != fifteen) {
        ((S_8016BD14_1 *)arg0)->unk_90 = 0;
        ((S_8016BD14_2 *)arg1)->unk_14 = 0;
        ((S_8016BD14_1 *)arg0)->unk_9D = 0;
    }

    if (((S_8016BD14_0 *)ctx)->unk_71.u <= ((S_8016BD14_0 *)ctx)->unk_8A.s) {
        return;
    }

    if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 != D_80174674) {
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80174674;
        func_80047784(
            arg2,
            D_80174674[((D_80083228 + ((S_8016BD14_0 *)ctx)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    mode = ((S_8016BD14_0 *)ctx)->unk_1C;
    x = ((Rec_D_80082E80 *)arg2)->unk_24;
    y = ((Rec_D_80082E80 *)arg2)->unk_25;
    mode = mode & 0x2000;
    func_8009A3D0(x, y, mode ? 0x300 : 0x3000);

    next = func_800A0818(x, y,
                         ((S_8016BD14_5 *)((u8 *)ctx + ((S_8016BD14_0 *)ctx)->unk_8A.s))->unk_74,
                         ((S_8016BD14_5 *)((u8 *)ctx + ((S_8016BD14_0 *)ctx)->unk_8A.s))->unk_7C,
                         (u8 *)arg0 + 0x98);
    raw = func_8009A66C(next, arg2, ctx, 0x20);

    tmp = ((S_8016BD14_5 *)((u8 *)ctx + ((S_8016BD14_0 *)ctx)->unk_8A.s))->unk_74;
    raw = raw << 16;
    ((Rec_D_80082E80 *)arg2)->unk_24 = tmp;
    row = (u8 *)ctx + ((S_8016BD14_0 *)ctx)->unk_8A.s;
    result = raw >> 16;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ((Rec_D_80082E80 *)arg2)->unk_25 = ((S_8016BD14_4 *)row)->unk_7C;
    index = ((S_8016BD14_0 *)ctx)->unk_8A.u;
    mode2 = ((S_8016BD14_0 *)ctx)->unk_1C;
    index = index + 1;
    mode2 = mode2 & 0x2000;
    ((S_8016BD14_0 *)ctx)->unk_8A.u = index;
    func_8009A21C(((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25,
                  mode2 ? 0x300 : 0x3000);
    ((S_8016BD14_0 *)ctx)->unk_2A = next;

    if (result == 3) {
        if (!(D_80083462 & 0x80) && !(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
            func_8016C698(arg0, arg1, arg2, ctx);
            ((S_8016BD14_1 *)arg0)->unk_8C = 0;
            func_8016BEF4();
            return;
        }
        ((S_8016BD14_1 *)arg0)->unk_9A = 15;
        func_8016BEF0();
        return;
    }

    ((S_8016BD14_1 *)arg0)->unk_9A = fifteen;
    ((S_8016BD14_1 *)arg0)->unk_8C = 0;
    (*(s32 *)((u8 *)ctx + (0x1C))) |= 0x40000000;
    if (D_80083462 & 0x80) {
        ((S_8016BD14_1 *)arg0)->unk_96 = 0;
        return;
    }

    ((S_8016BD14_1 *)arg0)->unk_96 = 8;
    x = ((S_8016BD14_0 *)ctx)->unk_71.u;
    if (x > 0) {
        ((S_8016BD14_1 *)arg0)->unk_96 = 8 / x;
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
