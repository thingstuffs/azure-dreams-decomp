#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

/* This data symbol has no shared-catalog address. */
__asm__(".set D_80081470, 0x80081470");

extern u8 D_80081470[];
extern void *D_800814A8[];
extern u8 D_800E3548[];
extern u8 D_800E3648[];

extern s32 func_800A4474(u8, u8);
extern s16 func_800B500C(u8, u8, s16);
extern s16 func_800A70E4(u8, u8, s16);
extern void func_800A4410(void) __attribute__((noreturn));
extern void func_800A4414(void) __attribute__((noreturn));

void func_800A4300(void *arg0, void *arg1) {
    register s32 first ASM_REG("$5");
    register u32 map_raw ASM_REG("$2"), floor_raw ASM_REG("$2");
    register u8 *map_base ASM_REG("$2"), *floor_base ASM_REG("$2");
    s16 floor_index, map_index;
    u8 *floor_entry, *map_entry;

    first = func_800A4474(FIELD(arg0, u8, 0x24), FIELD(arg0, u8, 0x25));
    if ((first << 16) != 0) {
#ifndef NON_MATCHING
        register u32 page ASM_REG("$4") = 0x80080000;
        register void *owner ASM_REG("$3");
        register s32 out ASM_REG("$2");

        ASM_KEEP(page);
        owner = *(void *volatile *)D_800814A8;
        ASM_USE(owner);
        out = first | 0x1400;
        *(s16 *)(page + 0x1470) = (s16)out;
#else
        *(s16 *)D_80081470 = (s16)(first | 0x1400);
        *(void *volatile *)D_800814A8;
#endif
        func_800A4410();
    }

    map_raw = (u32)func_800B500C(FIELD(arg0, u8, 0x24),
                                  FIELD(arg0, u8, 0x25),
                                  FIELD(arg1, s16, 0x88)) << 16;
    ASM_USE(map_raw);
    map_index = (s16)((s32)map_raw >> 16);
    if (map_index >= 0) {
        map_base = D_800E3648;
        ASM_USE(map_base);
        map_entry = map_base + map_index * 4;
        if (!(map_entry[3] & 0x40)) {
            *(void **)D_80081470 = *(void **)map_entry;
            FIELD(D_800814A8[0], void *, 0xF0) = map_entry;
            func_800A4414();
        }
        FIELD(D_800814A8[0], s32, 0xF0) = 0;
        func_800A4414();
    }

    floor_raw = (u32)func_800A70E4(FIELD(arg0, u8, 0x24),
                                    FIELD(arg0, u8, 0x25),
                                    FIELD(arg1, s16, 0x88)) << 16;
    ASM_USE(floor_raw);
    floor_index = (s16)((s32)floor_raw >> 16);
    if (floor_index >= 0) {
        floor_base = D_800E3548;
        ASM_USE(floor_base);
        floor_entry = floor_base + floor_index * 4;
        *(void **)D_80081470 = *(void **)floor_entry;
        FIELD(D_800814A8[0], void *, 0xF0) = floor_entry;
        func_800A4414();
    }

    ASM_SCHED_BARRIER();
    *(void **)D_80081470 = 0;
    FIELD(D_800814A8[0], s32, 0xF0) = 0;
}
