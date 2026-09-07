#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u32 word[3];
} __attribute__((packed)) Copy12;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 rand(void);

extern u8 D_80045340;
extern u8 D_80173C0C;
extern u8 D_80175324[12];

void func_80173CFC(void *arg0, void *arg1, s32 arg2, s16 arg3)
{
    void *node;
    void *part;
    void *data;
    void *pos;

    node = func_8003FC64(0x212);
    if (node != 0) {
        part = (u8 *)node + 0x20;
        FIELD(part, s16, 0x24) = 5;
        FIELD(node, void *, 0x10) = &D_80173C0C;
        func_8004491C(node, &D_80045340);
        data = FIELD(node, void *, 0xC);
        FIELD(data, s16, 0x10) = 0x60;
        FIELD(data, u16, 0x14) |= 0xC;
        pos = FIELD(node, void *, 8);
        FIELD(pos, u16, 2) = FIELD(arg1, u16, 2);
        FIELD(pos, u16, 6) = FIELD(arg1, u16, 6);
        FIELD(pos, s16, 0xA) = FIELD(arg1, u16, 0xA) - 0x28;
        data = FIELD(node, void *, 0xC);
        FIELD(data, s16, 6) = 6;
        FIELD(data, s16, 0x1E) = arg3;
        FIELD(data, s16, 0x1C) = arg3;
        FIELD(part, s8, 1) = 0x30;
        FIELD(part, s8, 2) = 0x30;
        FIELD(node, s8, 0x20) = 0x30;
        FIELD(data, s8, 0xE) = 0x30;
        FIELD(data, s8, 0xD) = 0x30;
        FIELD(data, s8, 0xC) = 0x30;
        FIELD(data, s16, 0x1A) = rand() & 0xFFF;
        FIELD(node, Copy12, 0x9A) = FIELD(D_80175324, Copy12, 0);
        FIELD(data, void *, 8) = (u8 *)node + 0x9A;
    }
}

/* MECHANISM: The four-argument ABI keeps arg1/arg3 in s3/s4 while node, data, and
   node+0x20 occupy s2/s1/s0, producing retail's 0x28 frame and full save set.
   One packed 12-byte assignment emits the retail lwl/lwr and swl/swr copy. */
