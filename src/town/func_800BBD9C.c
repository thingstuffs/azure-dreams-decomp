#include "common.h"

extern u8 D_800136B8;
extern void *D_800718E4[];
extern u8 D_80082E78;
extern u8 D_800D1A0C[];
extern u8 D_800D1D1C[];
extern u8 D_800D1D24[];
extern u8 D_800D1D2C[];
extern u8 D_800D1D54[];
extern u8 D_800D1D5C[];
extern u8 D_800D1D64[];
extern u8 D_800D1D6C[];
extern u8 D_800D1DB4[];
extern u8 D_800D1DBC[];
extern u8 D_800D1DC4[];
extern u8 D_800D1DCC[];
extern u8 D_800D1DD4[];
extern u8 D_800D1DDC[];
extern u8 D_800D1DE4[];
extern u8 D_800D1DEC[];
extern u8 D_800D1E7C[];
extern u8 D_800D2FB4[];
extern u8 D_800D3814[];

/* Builds a null-terminated entry list for the current map kind and variant. */
void func_800B94FC(void) {
    s32 count;
    s32 i;
    u32 records;
    u8 *state;
    u32 table;
    u8 *map_records;

    count = 1;
    D_800718E4[0] = D_800D1D1C;
    if ((u32)(D_80082E78 - 0x16) >= 2U) {
        count = 3;
        D_800718E4[1] = D_800D1D24;
        D_800718E4[2] = D_800D1D2C;
    }
    map_records = D_800D2FB4;
    switch (map_records[D_800D3814[6] << 5]) {
    default:
        i = 0;
        goto fallback;
    case 5:
        switch ((*(u8 *)0x800136B8)) {
        default: D_800718E4[count++] = D_800D1D54; break;
        case 0xB: D_800718E4[count++] = D_800D1D5C; break;
        case 0xC: D_800718E4[count++] = D_800D1D64; break;
        case 0xD: D_800718E4[count++] = D_800D1D6C; break;
        }
        D_800718E4[count++] = D_800D1E7C;
        break;
    case 0xF:
        switch ((*(u8 *)0x800136B8)) {
        default: D_800718E4[count++] = D_800D1DB4; break;
        case 0xB: D_800718E4[count++] = D_800D1DBC; break;
        case 0xC: D_800718E4[count++] = D_800D1DC4; break;
        case 0xD: D_800718E4[count++] = D_800D1DCC; break;
        }
        D_800718E4[count++] = D_800D1E7C;
        break;
    case 0x10:
        switch ((*(u8 *)0x800136B8)) {
        default: D_800718E4[count++] = D_800D1DD4; break;
        case 0xB: D_800718E4[count++] = D_800D1DDC; break;
        case 0xC: D_800718E4[count++] = D_800D1DE4; break;
        case 0xD: D_800718E4[count++] = D_800D1DEC; break;
        }
        D_800718E4[count++] = D_800D1E7C;
        break;
    }
    D_800718E4[count] = 0;
    return;

fallback:
    records = (u32)D_800D2FB4;
    state = D_800D3814;
    table = (u32)D_800D1A0C;
    do {
        D_800718E4[count++] = ((void **)((*(u8 *)((state[6] << 5) + records) << 3) + table))[i];
        i++;
    } while (i < 2);
    D_800718E4[count] = 0;
}
