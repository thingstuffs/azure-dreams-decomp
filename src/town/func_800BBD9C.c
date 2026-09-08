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

void func_800B94FC(void) {
    s32 count;
    register s32 i ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 kind;
    s32 sub;
    register s32 test ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void **table;
    register void **slot ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *value;
    u8 *map_head;
    u8 *map_base;
    u8 *town_base;
    u8 *choice_base;
    void **dst;
    void **rebase;

    count = 1;
    D_800718E4[0] = D_800D1D1C;
    if ((u32)(D_80082E78 - 0x16) >= 2U) {
        count = 3;
        D_800718E4[1] = D_800D1D24;
        D_800718E4[2] = D_800D1D2C;
    }
    table = D_800718E4;

    map_head = D_800D2FB4;
    kind = map_head[D_800D3814[6] << 5];
    test = 0xF;
    if (kind == test) {
        goto kind_15_prep;
    }
    test = ((s32)kind < 0x10);
    if (test) {
        test = 5;
        if (kind == test) {
            goto kind_5_prep;
        }
        i = 0;
        goto fallback;
    }
    test = 0x10;
    if (kind == test) {
        goto kind_16_prep;
    }
    i = 0;
    goto fallback;

kind_5_prep:
    test = 0xC;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
kind_5:
    sub = D_800136B8;
    if (sub == test) {
        goto kind_5_12;
    }
    if ((s32)sub < 0xD) {
        if (sub == 0xB) {
            goto kind_5_11;
        }
        goto kind_5_default;
    }
    if (sub == 0xD) {
        goto kind_5_13;
    }

kind_5_default:
    rebase = D_800718E4;
    ASM_KEEP(count);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    slot = &rebase[count];
    value = D_800D1D54;
    goto store_value;

kind_5_11:
    slot = &table[count];
    value = D_800D1D5C;
    goto store_value;

kind_5_12:
    slot = &table[count];
    value = D_800D1D64;
    goto store_value;

kind_5_13:
    slot = &table[count];
    value = D_800D1D6C;
    goto store_value;

kind_15_prep:
    ASM_UNDEF(test);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
kind_15:
    sub = D_800136B8;
    ASM_KEEP(test);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    if (sub == 0xC) {
        goto kind_15_12;
    }
    if ((s32)sub < 0xD) {
        if (sub == 0xB) {
            goto kind_15_11;
        }
        goto kind_15_default;
    }
    if (sub == 0xD) {
        goto kind_15_13;
    }

kind_15_default:
    rebase = D_800718E4;
    ASM_KEEP(count);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    slot = &rebase[count];
    value = D_800D1DB4;
    goto store_value;

kind_15_11:
    slot = &table[count];
    value = D_800D1DBC;
    goto store_value;

kind_15_12:
    slot = &table[count];
    value = D_800D1DC4;
    goto store_value;

kind_15_13:
    slot = &table[count];
    value = D_800D1DCC;
    goto store_value;

kind_16_prep:
    test = 0xC;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
kind_16:
    sub = D_800136B8;
    if (sub == test) {
        goto kind_16_12;
    }
    if ((s32)sub < 0xD) {
        if (sub == 0xB) {
            goto kind_16_11;
        }
        goto kind_16_default;
    }
    if (sub == 0xD) {
        goto kind_16_13;
    }

kind_16_default:
    rebase = D_800718E4;
    ASM_KEEP(count);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    slot = &rebase[count];
    value = D_800D1DD4;
    goto store_value;

kind_16_11:
    slot = &table[count];
    value = D_800D1DDC;
    goto store_value;

kind_16_12:
    slot = &table[count];
    value = D_800D1DE4;
    goto store_value;

kind_16_13:
    slot = &table[count];
    value = D_800D1DEC;

store_value:
    *slot = value;
    ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    count++;
    rebase = D_800718E4;
    slot = &rebase[count];
    value = D_800D1E7C;
    *slot = value;
    ASM_KEEP(slot);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    count++;
    goto finish;

fallback:
    map_base = D_800D2FB4;
    town_base = D_800D3814;
    choice_base = D_800D1A0C;
    rebase = D_800718E4;
    slot = (void **)(count << 2);
    dst = (void **)((unsigned long)slot + (unsigned long)rebase);
    do {
        test = town_base[6];
        count++;
        slot = (void **)(u32)*(u8 *)(((unsigned long)test << 5) + (unsigned long)map_base);
        test = i << 2;
        slot = (void **)(((unsigned long)(s32)slot << 3) + (unsigned long)choice_base);
        value = *(void **)((unsigned long)test + (unsigned long)slot);
        *dst = value;
        i++;
        dst++;
    } while (i < 2);

finish:
    ASM_KEEP(count);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    slot = D_800718E4;
    test = count << 2;
    *(void **)((unsigned long)test + (unsigned long)slot) = 0;
}
