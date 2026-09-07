#include "common.h"

extern void func_8004DDBC(void *arg0, void *arg1, void *arg2);
extern void func_80407160(void *arg0);
extern u8 D_80408A30[];

void func_804072CC(void *arg0, s32 *arg1, s32 *arg2) {
    s32 i;
    s32 dispatched;
    s32 offset;
    u8 *record;
    void **table;
    void *output;

    dispatched = 0;
    i = 0;
    record = arg0;
    offset = 4;
    do {
        if (arg2[i] != 0) {
            table = *(void ***)((u8 *)arg0 + 0x60);
            output = *(void **)((u8 *)table + (i * 4) + 8);
            dispatched = 1;
            if (arg1[i] != 0) {
                func_8004DDBC((u8 *)arg0 + offset, D_80408A30, output);
            } else {
                *(s32 *)output = 0;
                *(s32 *)(record + 8) = 0;
            }
        }
        record += 0xC;
        offset += 0xC;
        i++;
    } while (i < 2);

    if (dispatched != 0) {
        func_80407160(arg0);
    }
}
