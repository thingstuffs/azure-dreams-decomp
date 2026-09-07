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

/* Reset map state, update coordinate lookup values, and process both active entries. */
void func_8016DF94(void) {
    s32 coord_aux;
    s16 entry_slot;
    s32 entry_offset;
    s32 state_value;
    u16 coord_result;
    u16 status_count;
    u16 state_flags;
    u16 lookup_key;
    u8 *map_object;
    u8 *map_base;
    u8 *map_data;
    u8 *entry;
    u8 *entry_page;
    u8 *entry_header;
    u8 *status;
    u8 *state_page;

    entry_slot = 0;
    state_page = (u8 *)0x80010000;
#ifdef NON_MATCHING
    entry_page = (u8 *)&D_800E3D7C - 0x3D7C;
#else
    entry_page = (u8 *)0x800E0000;
#endif
    D_80174704[0xD2] = 1;
    *(s16 *)(state_page + 0x371A) = 0;
    *(s16 *)(state_page + 0x3718) = 0;
    *(s16 *)(state_page + 0x3716) = 0;
    status = D_80083460;
    status_count = *(u16 *)(status + 0xA);
    state_flags = *(u16 *)(state_page + 0x3714);
    ASM_MEM_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    map_base = D_80174704;
    ASM_KEEP(map_base);   /* MATCH pin: retail schedule: same instructions, different order without it */
    status_count--;
    state_flags |= 9;
    *(u16 *)(status + 0xA) = status_count;
    lookup_key = D_800834E2;
    state_flags &= 0xFFEF;
    state_value = D_801748C8[(lookup_key >> 9) & 7];
    *(u16 *)(state_page + 0x3714) = state_flags;
    ASM_CLOBBER("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    *(s32 *)(state_page + 0x371C) = state_value;
    map_object = *(u8 **)(map_base + 0xC);
    D_800DCF4D = -1;
    map_data = map_base + 0x20;
    coord_result = func_800A0818(map_object[0x24], map_object[0x25],
                           D_80082E80[0x24], D_80082E80[0x25], &coord_aux);
    *(u16 *)(map_data + 0x2A) = coord_result;
    D_80174CD0 = 0;
    D_80174CCC = (s32 *)D_801749E0[(coord_result >> 9) & 7];

    do {
        entry_offset = ((s32)entry_slot << 16) >> 14;
        entry = *(u8 **)&(*(u8 **)(entry_page + 0x3D7C))[entry_offset + 0xAC];
        if (entry != 0) {
            register u32 high_bit ASM_REG("$3");   /* MATCH pin: retail immediate-load split depends on it */

            func_8016A908(entry);
            func_8009A028(*(u8 **)&(*(u8 **)(entry_page + 0x3D7C))[entry_offset + 0xAC]);
            entry_header = *(u8 **)&(*(u8 **)(entry_page + 0x3D7C))[entry_offset + 0xAC] - 0x20;
            high_bit = 0x80000000;
            *(u32 *)(entry_header + 0x10) |= high_bit;
        }
        entry_slot++;
    } while (entry_slot < 2);
}
