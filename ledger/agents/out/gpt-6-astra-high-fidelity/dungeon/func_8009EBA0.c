#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


/* This data symbol has no shared-catalog address. */
__asm__(".set D_80081470, 0x80081470");

extern u8 D_80081470[];
extern void *D_800814A8[];
extern u8 D_800E3548[];
extern u8 D_800E3648[];

extern s32 func_800A4474(u8, u8);
extern s16 func_800B500C(u8, u8, s16);
extern s16 func_800A70E4(u8, u8, s16);




typedef struct S_800A4300_2 {
    u8 pad_00[0xF0];
    union { void * p; s32 i; } unk_F0;   /* accessed as both */
} S_800A4300_2;   /* D_800814A8[0] in func_800A4300 */

void func_800A4300(Rec_D_80082E80 *arg0, Rec_D_800E3D7C *arg1) {
    s32 first;
    register void *owner ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 map_raw, floor_raw ASM_REG("$2");
    u8 *map_base, *floor_base ASM_REG("$2");
    s16 floor_index, map_index;
    u8 *floor_entry, *map_entry;

    first = func_800A4474(arg0->unk_24, arg0->unk_25);
    if ((first << 16) != 0) {
#ifndef NON_MATCHING
        u32 page = 0x80080000;
        register s32 out ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

        ASM_USE(page); /* MATCH: materialize the data page before loading the shared-tail owner. */
        owner = *(void *volatile *)D_800814A8;
        ASM_USE(owner);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        out = first | 0x1400;
        *(s16 *)(page + 0x1470) = (s16)out;
#else
        *(s16 *)D_80081470 = (s16)(first | 0x1400);
        owner = *(void *volatile *)D_800814A8;
#endif
    } else {

        map_raw = (u32)func_800B500C(arg0->unk_24,
                                      arg0->unk_25,
                                      arg1->unk_88.as_s16) << 16;
        map_index = (s16)((s32)map_raw >> 16);
        if (map_index >= 0) {
            map_base = D_800E3648;
            map_entry = map_base + map_index * 4;
            if (!(map_entry[3] & 0x40)) {
                *(void **)D_80081470 = *(void **)map_entry;
                ((S_800A4300_2 *)(D_800814A8[0]))->unk_F0.p = map_entry;
                return;
            }
            ((S_800A4300_2 *)(D_800814A8[0]))->unk_F0.i = 0;
            return;
        }

        floor_raw = (u32)func_800A70E4(arg0->unk_24,
                                        arg0->unk_25,
                                        arg1->unk_88.as_s16) << 16;
        floor_index = (s16)((s32)floor_raw >> 16);
        if (floor_index >= 0) {
            floor_base = D_800E3548;
            floor_entry = floor_base + floor_index * 4;
            *(void **)D_80081470 = *(void **)floor_entry;
            ((S_800A4300_2 *)(D_800814A8[0]))->unk_F0.p = floor_entry;
            return;
        }

           /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        owner = D_800814A8[0];
        *(void **)D_80081470 = 0;
    }
    ((S_800A4300_2 *)owner)->unk_F0.i = 0;
}
