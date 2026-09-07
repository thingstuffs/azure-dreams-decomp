#include "common.h"

extern void func_8009A028(void *);
extern u16 func_800A0818(u8, u8, u8, u8, s32 *);
extern void func_8016A908(void *);

extern u8 D_80082E80[];
extern u8 D_80083460[];
extern u16 D_800834E2;
extern s8 D_800DCF4D;
extern u8 *D_800E3D7C;
extern u8 * volatile D_80174704;
extern s32 D_801748C8[];
extern s32 D_801749E0[];
extern s32 *D_80174CCC;
extern s16 D_80174CD0;

void func_8016DF94(void) {
    s32 local;
    s16 i;
    s32 offset;
    s32 table_value;
    u16 result;
    u16 count;
    u16 flags;
    u16 table_index;
    u8 *object;
    u8 *map_base;
    u8 *map;
    u8 *entry;
    u8 *entry_page;
    u8 *adjusted;
    u8 *status;
    u8 *state;

    i = 0;
    state = (u8 *)0x80010000;
#ifdef NON_MATCHING
    entry_page = (u8 *)&D_800E3D7C - 0x3D7C;
#else
    entry_page = (u8 *)0x800E0000;
#endif
    D_80174704[0xD2] = 1;
    *(s16 *)(state + 0x371A) = 0;
    *(s16 *)(state + 0x3718) = 0;
    *(s16 *)(state + 0x3716) = 0;
    status = D_80083460;
    count = *(u16 *)(status + 0xA);
    flags = *(u16 *)(state + 0x3714);
    ASM_MEM_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    map_base = D_80174704;
    ASM_KEEP(map_base);   /* MATCH pin: retail schedule: same instructions, different order without it */
    count--;
    flags |= 9;
    *(u16 *)(status + 0xA) = count;
    table_index = D_800834E2;
    flags &= 0xFFEF;
    table_value = D_801748C8[(table_index >> 9) & 7];
    *(u16 *)(state + 0x3714) = flags;
    ASM_CLOBBER("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    *(s32 *)(state + 0x371C) = table_value;
    object = *(u8 **)(map_base + 0xC);
    D_800DCF4D = -1;
    map = map_base + 0x20;
    result = func_800A0818(object[0x24], object[0x25],
                           D_80082E80[0x24], D_80082E80[0x25], &local);
    *(u16 *)(map + 0x2A) = result;
    D_80174CD0 = 0;
    D_80174CCC = (s32 *)D_801749E0[(result >> 9) & 7];

    do {
        offset = ((s32)i << 16) >> 14;
        entry = *(u8 **)&(*(u8 **)(entry_page + 0x3D7C))[offset + 0xAC];
        if (entry != 0) {
            register u32 high_bit ASM_REG("$3");   /* MATCH pin: retail immediate-load split depends on it */

            func_8016A908(entry);
            func_8009A028(*(u8 **)&(*(u8 **)(entry_page + 0x3D7C))[offset + 0xAC]);
            adjusted = *(u8 **)&(*(u8 **)(entry_page + 0x3D7C))[offset + 0xAC] - 0x20;
            high_bit = 0x80000000;
            *(u32 *)(adjusted + 0x10) |= high_bit;
        }
        i++;
    } while (i < 2);
}
