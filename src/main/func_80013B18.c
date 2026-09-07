#include "common.h"

extern void func_800269B4(void *arg0);
extern void func_8004CBFC(void *arg0, s32 arg1, s32 *arg2);

void func_80026B18(void *arg0, s32 *arg1, s32 *arg2)
{
    s32 *value;
    s32 *active;
    s32 *enabled;
    s32 offset;
    s32 i;
    s32 used;
    u8 *owner;
    u8 *record;
    u8 *destination;
    u8 *global_base;

    value = arg2;
    used = 0;
    if (arg0 != 0) {
        i = used;
    } else {
        i = used;
    }
    record = arg0;
    offset = 4;
    enabled = arg1;
    owner = arg0;
    active = value;
    do {
        if (*active != 0) {
            value = *(s32 **)(owner + 0x68);
            used = 1;
            if (*enabled != 0) {
                destination = (u8 *)arg0 + offset;
                ASM_KEEP_NV(destination);
                global_base = (u8 *)0x80020000;
                ASM_KEEP_DEP_NV(global_base, destination);
                global_base -= -0x7E68;
                func_8004CBFC(destination,
                              (s32)(unsigned long)global_base, value);
            } else {
                *value = 0;
                *(s32 *)(record + 8) = 0;
            }
        }
        record += 0xC;
        offset += 0xC;
        enabled++;
        owner += 4;
        i++;
        active++;
    } while (i < 2);
    used++;
    if (used != 1) {
        func_800269B4(arg0);
    }
}
