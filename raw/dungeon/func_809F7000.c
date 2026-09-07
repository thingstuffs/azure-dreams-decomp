#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u32 word[3];
} __attribute__((packed)) Copy12;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 rand(void);

extern u8 D_80045340;
extern u8 D_80174600;
extern u8 D_8017520C[12];

void func_80174800(void *arg0, void *arg1, s32 arg2, s16 arg3)
{
    void *node;
    void *part;
    void *data;
    void *pos;

    node = func_8003FC64(0x212);
    if (node != 0) {
        part = (u8 *)node + 0x20;
        FIELD(part, s16, 0x1A) = 65;
        FIELD(node, void *, 0x10) = &D_80174600;
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
        FIELD(node, s8, 0x20) = 0x70;
        FIELD(part, s8, 1) = 0x10;
        FIELD(part, s8, 2) = 0x10;
        FIELD(data, s8, 0xE) = 0;
        FIELD(data, s8, 0xD) = 0;
        FIELD(data, s8, 0xC) = 0;
        FIELD(data, s16, 0x1A) = rand() & 0xFFF;
        FIELD(node, Copy12, 0x48) = FIELD(D_8017520C, Copy12, 0);
        FIELD(data, void *, 8) = (u8 *)node + 0x48;
    }
}
