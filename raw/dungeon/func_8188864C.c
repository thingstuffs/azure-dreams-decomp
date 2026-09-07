#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066708(void *);
extern void func_80067F20(void *, s32, s32, u16, s32);

typedef struct GlobalState {
    u8 pad[0x8D0];
    void *next;
} GlobalState;

extern GlobalState *D_80083160[];

s32 func_80025E4C(void *arg0) {
    GlobalState **global = D_80083160;
    u8 *scratch = (u8 *)0x1F800000;
    void *obj;
    u32 count;
    s32 value0;
    s32 value1;
    s32 next;
    void *value2;
    GlobalState *global_base;

    global_base = global[0];
    FIELD(scratch, void *, 0x20) = (u8 *)global_base + 0xB0;
    FIELD(scratch, void *, 0x18) = global_base->next;
    do {
        obj = FIELD(scratch, void *, 0x18);
        FIELD(scratch, void *, 0x18) = (u8 *)obj + 0x24;
        FIELD(scratch, void *, 0x70) = FIELD(arg0, void *, 0x30);
        FIELD(scratch, void *, 0x78) = FIELD(arg0, void *, 0x38);
        FIELD(scratch, void *, 0x80) = FIELD(arg0, void *, 0x40);
        value2 = FIELD(arg0, void *, 0x48);
        FIELD(scratch, u16, 0x74) = FIELD(arg0, u16, 0x34);
        FIELD(scratch, u16, 0x7C) = FIELD(arg0, u16, 0x3C);
        FIELD(scratch, u16, 0x84) = FIELD(arg0, u16, 0x44);
        FIELD(scratch, void *, 0x88) = value2;
        FIELD(scratch, u16, 0x8C) = FIELD(arg0, u16, 0x4C);
        count = func_800654B0(scratch + 0x70, scratch + 0x78,
                              scratch + 0x80, scratch + 0x88,
                              (u8 *)obj + 8, (u8 *)obj + 0x10,
                              (u8 *)obj + 0x18, (u8 *)obj + 0x20,
                              scratch + 0x90, scratch + 0x94) - 8;
        FIELD(scratch, u32, 0xC0) = count;
        if (count < 0x1E0U) {
            value0 = FIELD(arg0, s32, 0x50);
            FIELD(obj, s32, 0xC) = value0;
            FIELD(obj, s32, 4) = value0;
            value1 = FIELD(arg0, s32, 0x54);
            FIELD(obj, s32, 0x1C) = value1;
            FIELD(obj, s32, 0x14) = value1;
            func_80066708(obj);
            FIELD(obj, u8, 7) = (u8)(FIELD(obj, u8, 7) | 2);
            func_8006658C((u8 *)FIELD(scratch, void *, 0x20) +
                              (FIELD(scratch, u32, 0xC0) * 4), obj);
            obj = FIELD(scratch, void *, 0x18);
            FIELD(scratch, void *, 0x18) = (u8 *)obj + 0xC;
            func_80067F20(obj, 0, 0,
                          (u16)func_80066460(0, 1, 0, 0), 0);
            func_8006658C((u8 *)FIELD(scratch, void *, 0x20) +
                              (FIELD(scratch, u32, 0xC0) * 4), obj);
        }
        next = FIELD(arg0, s32, -8);
        if (next == 0) {
            break;
        }
        arg0 = (void *)(next + 0x20);
    } while (1);
    global[0]->next =
        FIELD(scratch, void *, 0x18);
    return 0;
}

