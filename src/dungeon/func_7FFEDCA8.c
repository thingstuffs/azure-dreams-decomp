#include "common.h"

extern s32 func_8008B2E4(void *);
extern s32 func_8008B3AC(s32);
extern u8 D_800CF828[];
extern u8 D_800CF838[];

void func_8008B408(s32 arg0) {
    register s32 i ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void **slot;
    u8 *table;
    u8 *entry;

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
            return;
        }
        i = 0;
    }

    {
        u8 *scan;
        u8 *scan_base;

        s32 t;

        scan_base = D_800CF828;
        scan = (u8 *)(i + (s32)scan_base);
        do {
            t = *scan;
            if (t == 0) {
                t = (s32)scan_base + i;
                *scan = arg0;
                ((u8 *)t)[1] = 0;
                return;
            }
            i++;
            scan = (u8 *)(i + (s32)scan_base);
        } while (i < 15);
    }
}
