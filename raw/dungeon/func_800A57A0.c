#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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
    register void *owner ASM_REG("$19") = arg0;
    register s32 call_arg ASM_REG("$20") = arg1;
    register void *other ASM_REG("$18") = arg2;
    register void *obj ASM_REG("$16");
    register u8 *table ASM_REG("$21") = arg3;
    register s32 special ASM_REG("$17");
    u8 *state;
    u8 *state2;
    u8 *slot;
    u8 *entry;
    register u8 *entry_base ASM_REG("$3");
    volatile u16 *field_46;
    u16 input;
    register s32 index ASM_REG("$2");
    register s32 table_index ASM_REG("$4");

    obj = owner;
    FIELD(obj, u8, 0x71) &= 0x7F;
    state = (u8 *)&D_80083460;
    input = FIELD(state, u16, 2);
    special = 0;

    if (!(input & 0x2008)) {
        if ((FIELD(obj, s32, 0x1C) & 0x2000) &&
            ((FIELD(obj, s16, 0x46) & 0x3FFF) >= 5)) {
            special = 1;
            if (((FIELD(D_800E3D7C, s32, 0x98) & 0x3000) == 0x2000) &&
                (FIELD(D_800E3D7C, u16, 0xA6) == 0)) {
                FIELD(D_800E3D7C, u16, 0x98) |= 0x1000;
                FIELD(D_800E3D7C, u16, 0xA6)++;
                FIELD(state, u16, 0xA)++;
                /* interior jump — was mis-decoded as extern func_800AB048() */
                goto shared_body;
            }
            func_800A4ACC(obj);
            FIELD(obj, u8, 0x6D)--;
            FIELD(owner, s32, 0x8C) = arg4;
            /* jump to own epilogue — was mis-decoded as extern func_800AB198() */
            return;
        }

        if (!(input & 8) && ((func_800A2B5C(obj) << 16) == 0)) {
            func_800C77D0((u8 *)obj - 0x20, call_arg, 8, 0x300);
            if ((func_800A2B5C(obj) << 16) == 0) {
shared_body:
                if (!special) {
                    if (FIELD(obj, s32, 0x1C) & 0x400) {
                        register s32 field14 ASM_REG("$2");
                        register s32 high_bit ASM_REG("$3");

                        field14 = FIELD(obj, s32, 0x14);
                        if (field14 >= 0) {
                            high_bit = 0x80000000;
                            FIELD(obj, s32, 0x14) = field14 | high_bit;
                            FIELD(obj, u16, 0x2A) += (func_800A6D30() & 7) << 9;
                        }
                    }

                    field_46 = (volatile u16 *)((u8 *)obj + 0x46);
                    if (!(*field_46 & 0x4000)) {
                        index = *field_46 & 0x3FFF;
                        ASM_KEEP_NV(index);
                        table_index = index;
                        table_index--;
                        entry_base = D_8006DE24;
                        index = table_index * 3;
                        slot = obj;
                        slot += index;
                        table_index = slot[8];
                        entry = entry_base + table_index * 20;
                        ASM_KEEP(table_index);
                        ASM_KEEP(entry_base);
                        if ((entry[0x12] == 2) && (FIELD(obj, s32, 0x60) == 0)) {
                            FIELD(obj, s32, 0x60) = func_800A05A4(
                                obj,
                                FIELD(other, u8, 0x24),
                                FIELD(other, u8, 0x25),
                                FIELD(obj, s16, 0x2A),
                                entry[0x13]);
                            /* interior jump — was mis-decoded as extern func_800AB12C() */
                            goto shared_tail;
                        }
                    }
                } else {
                    FIELD(D_800E3D7C, void *, 0x11C) = obj;
                }

shared_tail:
                FIELD(owner, u8, 0x9A) = 0x12;
                FIELD(owner, u8, 0x9B) = 0;
                FIELD(owner, s32, 0x8C) = 0;
                if (table != 0) {
                    FIELD(other, u8 *, 0x2C) = table;
                    func_80047784(
                        other,
                        table[((D_80083228 + FIELD(obj, s16, 0x2A) + 0x100) >> 9) & 7],
                        0);
                }
                state2 = (u8 *)&D_80083460;
                FIELD(other, u16, 0x14) |= 0x800;
                FIELD(state2, u16, 0xA)++;
            }
        }
    }

    ASM_KEEP(owner);
    ASM_KEEP(call_arg);
    ASM_KEEP(other);
    ASM_KEEP(obj);
    ASM_KEEP(table);
    ASM_KEEP(special);
}
