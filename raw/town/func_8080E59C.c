#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

typedef struct {
    u8 bytes[8];
} Copy8;

typedef union {
    Copy8 copy;
    s16 half[4];
} StackData;

typedef struct {
    s32 word[6];
} Copy24;

extern void *func_800373DC();
extern void func_8003BC18();
extern void func_8006E590();
extern void func_8006E8B8();
extern void func_8023FA58(void *, void *, void *, void *);

extern u8 D_8003D588[];
extern u8 D_8052643C[];
extern Copy8 D_80526440[];
extern u8 D_80529AC4[];
extern u8 D_8052A0A4[];
extern u8 D_8052AE20[];
extern u8 D_805300C4[];
extern u8 D_805300DC[];
extern u8 D_80530668[];

void func_8080E59C(void)
{
    StackData stack;
    void **root;
    void *obj;
    void *part;
    register void *data ASM_REG("$9");
    u8 *slot;
    u8 *persistent;
    s32 i;
    s32 scale;

    root = 0;
    ASM_SCHED_BARRIER();
    stack.copy = D_80526440[0];
    obj = func_800373DC(2, D_80526440);
    persistent = D_8052643C;
    if (obj != 0) {
        root = (void **)((u8 *)obj + 0x20);
        FIELD(obj, void *, 0x10) = D_8052A0A4;
    }

    obj = func_800373DC(0x136);
    *root = obj;
    if (obj != 0) {
        register void *call_a0 ASM_REG("$4");
        register void *call_a1 ASM_REG("$5");
        register void *call_a2 ASM_REG("$6");
        register s32 color ASM_REG("$3");

        func_8003BC18(obj, D_8003D588);
        color = 0x808080;
        ASM_KEEP(color);
        call_a0 = (u8 *)obj + 0x2C;
        call_a1 = (u8 *)obj + 0x78;
        call_a2 = D_805300DC;
        ASM_KEEP(call_a0);
        ASM_KEEP(call_a1);
        ASM_KEEP(call_a2);
        data = FIELD(obj, void *, 8);
        part = FIELD(obj, void *, 0xC);
        FIELD(obj, void *, 0x10) = D_80529AC4;
        FIELD(obj, void **, 0x20) = root;
        FIELD(part, s16, 0x1C) = 0x1000;
        FIELD(part, s16, 0x1E) = 0x1000;
        FIELD(part, s16, 0x20) = 0x1000;
        FIELD(part, s16, 6) = 3;
        FIELD(part, s32, 8) = 0x2D;
        FIELD(part, s16, 0x12) = 0;
        FIELD(part, s16, 0x14) = 0;
        FIELD(part, s16, 0x10) = 0;
        FIELD(part, s16, 0x16) = 0;
        FIELD(part, s16, 0x18) = 0;
        FIELD(part, s16, 0x1A) = 0;
        FIELD(part, s32, 0) = 0;
        FIELD(part, s8, 4) = 0;
        FIELD(part, s8, 5) = 0;
        FIELD(part, s32, 0xC) = color;
        FIELD(data, s32, 0) = 0x03600000;
        FIELD(data, s32, 4) = 0x03600000;
        FIELD(data, s32, 8) = 0;
        ASM_KEEP(data);
        {
            s32 copy0;
            s32 copy1;
            register s32 copy2 ASM_REG("$7");
            register s32 copy3 ASM_REG("$8");

            copy0 = FIELD(data, s32, 0);
            copy1 = FIELD(data, s32, 4);
            copy2 = FIELD(data, volatile s32, 8);
            copy3 = FIELD(data, s32, 0xC);
            ASM_KEEP(copy0);
            ASM_KEEP(copy1);
            ASM_KEEP(copy2);
            ASM_KEEP(copy3);
            FIELD(obj, s32, 0x78) = copy0;
            FIELD(obj, s32, 0x7C) = copy1;
            FIELD(obj, s32, 0x80) = copy2;
            FIELD(obj, s32, 0x84) = copy3;
            copy0 = FIELD(data, s32, 0x10);
            copy1 = FIELD(data, s32, 0x14);
            FIELD(obj, s32, 0x88) = copy0;
            FIELD(obj, s32, 0x8C) = copy1;
            ASM_KEEP(copy0);
            ASM_KEEP(copy1);
            FIELD(obj, void *, 0x74) = persistent;
            func_8023FA58(call_a0, call_a1, call_a2, (void *)copy2);
        }
    }

    i = 2;
    scale = 0x1000;
    slot = (u8 *)root + 8;
    do {
        obj = func_800373DC(0x136);
        FIELD(slot, void *, 4) = obj;
        if (obj != 0) {
            register s32 loop_color ASM_REG("$3");
            register void *loop_a0 ASM_REG("$4");
            register void *handler ASM_REG("$2");
            register void *loop_a2 ASM_REG("$6");

            func_8003BC18(obj, D_8003D588);
            loop_color = 0x808080;
            ASM_KEEP(loop_color);
            loop_a0 = (u8 *)obj + 0x28;
            ASM_KEEP(loop_a0);
            handler = D_8052AE20;
            ASM_KEEP(handler);
            data = FIELD(obj, void *, 8);
            part = FIELD(obj, void *, 0xC);
            ASM_KEEP(data);
            ASM_KEEP(part);
            loop_a2 = D_805300C4;
            ASM_KEEP(loop_a2);
            FIELD(obj, void *, 0x10) = handler;
            FIELD(obj, void **, 0x24) = root;
            FIELD(obj, s16, 0x74) = i;
            FIELD(part, s16, 0x12) = 0;
            FIELD(part, s16, 0x14) = 0;
            FIELD(part, s16, 0x10) = 0;
            FIELD(part, s16, 0x16) = 0;
            FIELD(part, s16, 0x18) = 0;
            FIELD(part, s16, 0x1A) = 0;
            FIELD(part, s32, 0) = 0;
            FIELD(part, s8, 4) = 0;
            FIELD(part, s8, 5) = 0;
            FIELD(part, s16, 0x1C) = scale;
            FIELD(part, s16, 0x1E) = scale;
            FIELD(part, s16, 0x20) = scale;
            FIELD(part, s32, 0xC) = loop_color;
            FIELD(part, s32, 8) = *(s32 *)((u8 *)D_805300C4 + 0x54 +
                (FIELD(obj, s16, 0x74) << 2));
            FIELD(data, s32, 0) = (i << 23) + 0x04600000;
            FIELD(data, s32, 4) = 0x03600000;
            FIELD(data, s32, 8) = 0;
            FIELD(obj, void *, 0x70) = persistent;
            func_8023FA58(loop_a0, data, loop_a2, part);
        }
        i--;
        slot -= 4;
    } while (i >= 0);

    stack.half[0] = 0x70;
    stack.half[1] = 0x1C1;
    stack.half[2] = 0x30;
    stack.half[3] = 1;
    func_8006E8B8(stack.half, D_80530668);
    func_8006E590(0);
}
