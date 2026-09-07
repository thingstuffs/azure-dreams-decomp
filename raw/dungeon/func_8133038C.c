#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    s32 word[3];
} __attribute__((packed)) PackedCopy12;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);

extern u8 D_80045340;
extern u8 D_801671AC;
extern u8 D_80173B58[48];

void func_8016738C(void *arg0)
{
    void *obj;
    void *dst;
    void *ctrl;
    void *node;

    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        node = (u8 *)obj + 0x20;
        FIELD(node, s16, 0x18) = 0x1E;
        FIELD(node, s16, 0x1A) = 0x1E;
        FIELD(obj, void *, 0x10) = &D_801671AC;
        func_8004491C(obj, &D_80045340);

        ctrl = FIELD(obj, void *, 0xC);
        
        FIELD(ctrl, s16, 0x10) = 0x20;
        FIELD(ctrl, u16, 0x14) = FIELD(ctrl, u16, 0x14) | 0xC;

        dst = FIELD(obj, void *, 8);
        FIELD(dst, s32, 0) = FIELD(arg0, s32, 0);
        FIELD(dst, s32, 4) = FIELD(arg0, s32, 4);
        FIELD(dst, s32, 8) = FIELD(arg0, s32, 8) + 0x180000;

        ctrl = FIELD(obj, void *, 0xC);
        
        FIELD(ctrl, s16, 0x1C) = 0x1400;
        FIELD(ctrl, s16, 0x1E) = 0x1400;
        FIELD(ctrl, s8, 0xE) = 0;
        FIELD(ctrl, s8, 0xD) = 0;
        FIELD(ctrl, s8, 0xC) = 0;
        FIELD(ctrl, s16, 6) = 0;
        FIELD(ctrl, u16, 0x14) = FIELD(ctrl, u16, 0x14) | 0x80;

        FIELD(obj, PackedCopy12, 0x48) = FIELD(D_80173B58, PackedCopy12, 0);
        FIELD(obj, PackedCopy12, 0x54) = FIELD(D_80173B58, PackedCopy12, 0xC);
        FIELD(obj, PackedCopy12, 0x60) = FIELD(D_80173B58, PackedCopy12, 0x18);
        FIELD(obj, PackedCopy12, 0x6C) = FIELD(D_80173B58, PackedCopy12, 0x24);
        FIELD(ctrl, void *, 8) = (u8 *)obj + 0x48;
    }
}

/* MECHANISM: Four packed 12-byte assignments emit retail's twelve unaligned
   copy quartets without gcc's large-copy loop. A guarded a3 pin preserves the
   control-pointer role while arg0/object remain live in s1/s0 for the 0x20 frame. */
