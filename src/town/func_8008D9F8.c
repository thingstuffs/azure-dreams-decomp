#include "common.h"

typedef struct {
    u8 pad0[8];
    u32 flags0;
    u32 flags1;
} Item;

typedef struct {
    u8 pad0[0x48];
    s32 value48;
    u8 pad4C[0x14];
    s32 value60;
    u8 pad64[0x34];
    Item *item98;
} Object;

typedef struct {
    s32 value0;
    s32 value4;
    s32 value8;
    s32 valueC;
    s32 value10;
    s32 value14;
} TownState;

extern TownState D_801131B8;
extern void func_80035208(s32);
extern void func_8008B0E8(s32, u32, u32, u32);
extern void func_8008B220(void *);

void func_8008B158(Object *arg0) {
    Item *item;
    u32 mask;
    u32 arg3;
    s32 arg0_call;
    u32 arg1;
    u32 arg2;
    register u32 tail_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 tail_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    item = arg0->item98;
    if (item != 0) {
        mask = item->flags0 & 0xC0000000;
        if (mask == 0xC0000000) {
            D_801131B8.value0 = arg0->value60;
            arg0_call = (item->flags0 >> 23) & 1;
            D_801131B8.value4 = arg0_call;
            arg1 = (item->flags0 & 0x3F000000) >> 24;
            D_801131B8.value8 = arg1;
            arg2 = (item->flags0 & 0x007F0000) >> 16;
            D_801131B8.valueC = arg2;
            arg3 = item->flags1;
            if ((arg3 & mask) == mask) {
                D_801131B8.value10 = (arg3 & 0x3F000000) >> 24;
                D_801131B8.value14 = (item->flags1 & 0x007F0000) >> 16;
            }
            func_8008B0E8(arg0_call, arg1, arg2, arg3);
            tail_base = 0x80016000;
            tail_offset = *(u16 *)&item->flags0;
            return func_8008B220((void *)(tail_base + tail_offset));
        }
    }
    func_80035208(arg0->value48);
}
