#include "common.h"

typedef struct S_800AAF00_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    s16 unk_46;
    u8 pad_48[0x18];
    s32 unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_800AAF00_0;   /* obj in func_800AAF00 */

typedef struct S_800AAF00_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_800AAF00_1;   /* state in func_800AAF00 */

typedef struct S_800AAF00_2 {
    u8 pad_00[0x98];
    union { s32 s32; u16 u16; } unk_98;   /* accessed as both */
    u8 pad_9C[0xA];
    u16 unk_A6;
    u8 pad_A8[0x74];
    void * unk_11C;
} S_800AAF00_2;   /* D_800E3D7C in func_800AAF00 */

typedef struct S_800AAF00_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
} S_800AAF00_3;   /* owner in func_800AAF00 */

typedef struct S_800AAF00_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800AAF00_4;   /* other in func_800AAF00 */

typedef struct S_800AAF00_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AAF00_5;   /* state2 in func_800AAF00 */



extern s32 func_80047784();
extern s32 func_800A05A4();
extern s32 func_800A2B5C();
extern void func_800A4ACC();
extern s32 func_800A6D30();
extern void func_800C77D0();

extern u8 D_8006DE24[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 *D_800E3D7C;

void func_800AAF00(void *arg0, s32 arg1, void *arg2, u8 *arg3, s32 arg4) {
    void *owner = arg0;
    s32 call_arg = arg1;
    void *other = arg2;
    void *obj;
    register u8 *table ASM_REG("$21") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 special ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *state;
    u8 *state2;
    u8 *slot;
    u8 *entry;
    u8 *entry_base;
    volatile u16 *field_46;
    u16 input;
    s32 index;
    s32 table_index;

    obj = owner;
    ((S_800AAF00_0 *)obj)->unk_71 &= 0x7F;
    state = (u8 *)&D_80083460;
    input = ((S_800AAF00_1 *)state)->unk_02;
    special = 0;

    if (!(input & 0x2008)) {
        if ((((S_800AAF00_0 *)obj)->unk_1C & 0x2000) &&
            ((((S_800AAF00_0 *)obj)->unk_46 & 0x3FFF) >= 5)) {
            special = 1;
            if (((((S_800AAF00_2 *)D_800E3D7C)->unk_98.s32 & 0x3000) == 0x2000) &&
                (((S_800AAF00_2 *)D_800E3D7C)->unk_A6 == 0)) {
                ((S_800AAF00_2 *)D_800E3D7C)->unk_98.u16 |= 0x1000;
                ((S_800AAF00_2 *)D_800E3D7C)->unk_A6++;
                ((S_800AAF00_1 *)state)->unk_0A++;
                /* Jump to the shared body. */
                goto shared_body;
            }
            func_800A4ACC(obj);
            ((S_800AAF00_0 *)obj)->unk_6D--;
            ((S_800AAF00_3 *)owner)->unk_8C = arg4;
            /* Jump to the epilogue. */
            return;
        }

        if (!(input & 8) && ((func_800A2B5C(obj) << 16) == 0)) {
            func_800C77D0((u8 *)obj - 0x20, call_arg, 8, 0x300);
            if ((func_800A2B5C(obj) << 16) == 0) {
shared_body:
                if (!special) {
                    if (((S_800AAF00_0 *)obj)->unk_1C & 0x400) {
                        register s32 field14 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        s32 high_bit;

                        field14 = ((S_800AAF00_0 *)obj)->unk_14;
                        if (field14 >= 0) {
                            high_bit = 0x80000000;
                            ((S_800AAF00_0 *)obj)->unk_14 = field14 | high_bit;
                            ((S_800AAF00_0 *)obj)->unk_2A.u += (func_800A6D30() & 7) << 9;
                        }
                    }

                    field_46 = (volatile u16 *)((u8 *)obj + 0x46);
                    if (!(*field_46 & 0x4000)) {
                        index = *field_46 & 0x3FFF;
                        table_index = index;
                        table_index--;
                        entry_base = D_8006DE24;
                        index = table_index * 3;
                        slot = obj;
                        slot += index;
                        table_index = slot[8];
                        entry = entry_base + table_index * 20;
                        if ((entry[0x12] == 2) && (((S_800AAF00_0 *)obj)->unk_60 == 0)) {
                            ((S_800AAF00_0 *)obj)->unk_60 = func_800A05A4(
                                obj,
                                ((S_800AAF00_4 *)other)->unk_24,
                                ((S_800AAF00_4 *)other)->unk_25,
                                ((S_800AAF00_0 *)obj)->unk_2A.s,
                                entry[0x13]);
                            /* Jump to the shared tail. */
                            goto shared_tail;
                        }
                    }
                } else {
                    ((S_800AAF00_2 *)D_800E3D7C)->unk_11C = obj;
                }

shared_tail:
                ((S_800AAF00_3 *)owner)->unk_9A = 0x12;
                ((S_800AAF00_3 *)owner)->unk_9B = 0;
                ((S_800AAF00_3 *)owner)->unk_8C = 0;
                if (table != 0) {
                    (*(u8 * *)((u8 *)other + 0x2C)) = table;
                    func_80047784(
                        other,
                        table[((D_80083228 + ((S_800AAF00_0 *)obj)->unk_2A.s + 0x100) >> 9) & 7],
                        0);
                }
                state2 = (u8 *)&D_80083460;
                ((S_800AAF00_4 *)other)->unk_14 |= 0x800;
                ((S_800AAF00_5 *)state2)->unk_0A++;
            }
        }
    }

    ASM_KEEP(owner);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(call_arg);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(other);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(obj);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(table);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
}
