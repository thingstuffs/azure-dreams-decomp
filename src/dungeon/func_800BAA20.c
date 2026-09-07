#include "common.h"

extern s32 D_80083498;
extern s16 D_800DCED4[];
extern u8 *D_800E3D7C;

extern s32 func_800429E4(void *);
extern void func_800C0210(void);
extern s32 func_800C07AC(s32 *);
extern void func_800C542C(void *, s16, s32, s32);

s32 func_800C0180(void)
{
    s32 counter;
    void *object;
    register u8 *page ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    s16 *height_table;
    u8 *table_page;

    if (func_800C07AC(&D_80083498) == 0) {
        return 0;
    }

    counter = 1;
    page = (u8 *)0x800E0000;
    ASM_KEEP(page);   /* MATCH pin: retail schedule: same instructions, different order without it */
    table_page = (u8 *)0x800E0000;
    ASM_KEEP(table_page);   /* MATCH pin: load-bearing for the whole function shape */
    height_table = (s16 *)(table_page - 0x312C);
    do {
        object = *(void **)(*(u8 **)(page + 0x3D7C) + 0xAC + counter * 4);
        if (object != 0) {
            func_800C542C(object, height_table[func_800429E4(object)],
                          (s16)counter, 0);
        }
        counter--;
    } while (counter >= 0);

    return 1;
}

/* MECHANISM: Success-only 32-bit counter init yields the s1 branch-delay load.
   An s3 page pin/fence orders before the short-lived v0 table-page pin, deriving
   the s2 s16-table base; the current object remains call-live in s0. */
