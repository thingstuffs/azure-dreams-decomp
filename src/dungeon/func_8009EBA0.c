#include "common.h"


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


typedef struct S_800A4300_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A4300_0;   /* arg0 in func_800A4300 */

typedef struct S_800A4300_1 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800A4300_1;   /* arg1 in func_800A4300 */

typedef struct S_800A4300_2 {
    u8 pad_00[0xF0];
    union { void * p; s32 i; } unk_F0;   /* accessed as both */
} S_800A4300_2;   /* D_800814A8[0] in func_800A4300 */

void func_800A4300(S_800A4300_0 *arg0, S_800A4300_1 *arg1) {
    s32 first;
    u32 map_raw, floor_raw ASM_REG("$2");
    u8 *map_base, *floor_base ASM_REG("$2");
    s16 floor_index, map_index;
    u8 *floor_entry, *map_entry;

    first = func_800A4474(arg0->unk_24, arg0->unk_25);
    if ((first << 16) != 0) {
#ifndef NON_MATCHING
        u32 page = 0x80080000;
        register void *owner ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 out ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */

        owner = *(void *volatile *)D_800814A8;
        ASM_USE(owner);   /* MATCH pin: load-bearing for the whole function shape */
        out = first | 0x1400;
        *(s16 *)(page + 0x1470) = (s16)out;
#else
        *(s16 *)D_80081470 = (s16)(first | 0x1400);
        *(void *volatile *)D_800814A8;
#endif
        func_800A4410();
    }

    map_raw = (u32)func_800B500C(arg0->unk_24,
                                  arg0->unk_25,
                                  arg1->unk_88) << 16;
    map_index = (s16)((s32)map_raw >> 16);
    if (map_index >= 0) {
        map_base = D_800E3648;
        map_entry = map_base + map_index * 4;
        if (!(map_entry[3] & 0x40)) {
            *(void **)D_80081470 = *(void **)map_entry;
            ((S_800A4300_2 *)(D_800814A8[0]))->unk_F0.p = map_entry;
            func_800A4414();
        }
        ((S_800A4300_2 *)(D_800814A8[0]))->unk_F0.i = 0;
        func_800A4414();
    }

    floor_raw = (u32)func_800A70E4(arg0->unk_24,
                                    arg0->unk_25,
                                    arg1->unk_88) << 16;
    floor_index = (s16)((s32)floor_raw >> 16);
    if (floor_index >= 0) {
        floor_base = D_800E3548;
        floor_entry = floor_base + floor_index * 4;
        *(void **)D_80081470 = *(void **)floor_entry;
        ((S_800A4300_2 *)(D_800814A8[0]))->unk_F0.p = floor_entry;
        func_800A4414();
    }

    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    *(void **)D_80081470 = 0;
    ((S_800A4300_2 *)(D_800814A8[0]))->unk_F0.i = 0;
}
