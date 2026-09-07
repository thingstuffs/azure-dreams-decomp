#include "common.h"

extern u8 D_800CF828[];
extern u8 D_800CF838[];

s32 func_8008B2E4(void *);
s32 func_8008B3AC(s32);
void func_8008B49C(s32);

void func_8008B408(s32 arg0) {
    register s32 i ASM_REG("$4");
    register void **slot ASM_REG("$2");
    register u8 *table ASM_REG("$3");
    register u8 *entry ASM_REG("$2");

    i = 0;
    table = D_800CF838;
    slot = (void **)(table + (arg0 * 4));
    if (func_8008B2E4(*slot) == 0) {
        i = 0;
    } else {
        i = func_8008B3AC(i);
        if (i >= 0) {
            entry = D_800CF828;
            entry = (u8 *)(i + (s32)entry);
            *entry = arg0;
            func_8008B49C(i);
            return;
        }
        i = 0;
    }

    {
        u8 *scan;
        u8 *scan_base;

        scan_base = D_800CF828;
        scan = (u8 *)(i + (s32)scan_base);
        do {
            if (*scan == 0) {
                *scan = arg0;
                ((u8 *)((s32)scan_base + i))[1] = 0;
                func_8008B49C(i);
                return;
            }
            i++;
            scan = (u8 *)(i + (s32)scan_base);
        } while (i < 15);
    }
}
