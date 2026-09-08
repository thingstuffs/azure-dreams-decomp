#include "common.h"

typedef struct {
    u8 unk0;
    u8 active;
    u8 unk2;
    u8 unk3;
} Slot;

typedef struct {
    u8 unk0[6];
    u8 x;
    u8 y;
    u8 unk8[0xA];
    s16 z;
    u8 unk14[4];
} Status;

extern Slot D_800E3648[];
extern Status D_800E39C8[];
extern s32 func_8009A350(s16, s16, s32, u16 *);
extern void func_800B510C(void);

s32 func_800B500C(s16 arg0, s16 arg1, s16 arg2) {
    register s32 rv ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u16 flags;
    s32 i;
    s32 delta;

    if ((func_8009A350(arg0 - 1, arg1, 0, &flags) << 16) == 0) {
        rv = -1;
        ASM_KEEP(rv);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800B510C();
        return rv;
    }
    if (flags & 0x20) {
        i = 0;
        do {
            if (D_800E3648[i].active != 0 && D_800E39C8[i].x == arg0 &&
                D_800E39C8[i].y == arg1) {
                delta = arg2 - D_800E39C8[i].z;
                if (delta < 0) {
                    delta = -delta;
                }
                if (delta < 0x40) {
                    rv = (s16)i;
                    ASM_TAILSLOT_PIN(rv);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    func_800B510C();
                    return rv;
                }
            }
            i++;
        } while (i < 0x20);
    }
    return -1;
}

/* MECHANISM: func_800B510C is a j-only noreturn dispatcher (config/sibcall_syms.dungeon.txt)
   that is SERVED ITS ARGUMENT IN $v0, so the return value must be materialised BEFORE the
   tail call, not after it: a guarded `s32 rv` carrier assigned then
   `func_800B510C(); return rv;`. Site 1 (rv=-1 + ASM_KEEP) leaves the jal delay a nop, gcc's
   dbr steals `li v0,-1` into the preceding bnez delay slot, and LEAD-22 SHAPE B drops the dead
   j-to-epilogue. Site 2 (rv=(s16)i + ASM_TAILSLOT_PIN) keeps `sll v0,a0,16` as the block's
   first insn (dbr steals it into the loop bnez delay) and LEAD-28 ARM B sinks the standalone
   `sra v0,v0,16` into the converted j's empty delay slot (-1 word). The one-sided pin
   asymmetry also defeats -O2 cross-jumping, so BOTH tail sites survive; the extra reference to
   `i` from `rv=(s16)i` is what flips local-alloc to retail's i=$a0 / D_800E3648=$a2 coloring. */
