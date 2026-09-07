#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern u8 D_8006DE24[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
extern u8 *D_800E3D7C;

extern void func_80047784(void *, u8, s32);
extern s32 func_800A05A4(void *, u8, u8, s16, u8);
extern s32 func_800A2B5C(void *);
extern void func_800A4ACC(void *);
extern s32 func_800A6D30(void);
extern void func_800C77D0(void *, s32, s32, s32);

void func_801717D0(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3, s32 arg4)
{
    register s32 call_arg1 ASM_REG("$19");
    register u8 *call_arg2 ASM_REG("$20");
    register u8 *call_arg3 ASM_REG("$21");
    u8 *self;
    u8 *player;
    u8 *slot;
    register u8 *counter_base ASM_REG("$3");
    register u8 *table_base ASM_REG("$3");
    u8 *entry;
    volatile u16 *field_46;
    u16 counter;
    s32 active;
    s32 index;
    register s32 table_index ASM_REG("$4");
    register s32 field_14 ASM_REG("$2");

    call_arg1 = arg1;
    call_arg2 = arg2;
    call_arg3 = arg3;
    active = 0;
    self = arg0;
    ASM_KEEP(call_arg1);
    ASM_KEEP(call_arg2);
    ASM_KEEP(call_arg3);
    FIELD(self, u8, 0x71) &= 0x7F;

    if (FIELD(self, s32, 0x1C) & 0x2000) {
        if ((FIELD(self, s16, 0x46) & 0x3FFF) >= 5) {
            active = 1;
            if (FIELD(D_800E3D7C, u16, 0xA6) == 2) {
                counter_base = (u8 *)&D_80083460;
                ASM_KEEP(counter_base);
                counter = FIELD(counter_base, u16, 0xA);
                counter--;
                FIELD(counter_base, u16, 0xA) = counter;
            }

            player = D_800E3D7C;
            if ((FIELD(player, s32, 0x98) & 0x3000) == 0x2000 &&
                FIELD(player, u16, 0xA6) != active) {
                FIELD(player, u16, 0xA6) = active;
                FIELD(player, u16, 0x98) |= 0x1000;
                counter_base = (u8 *)&D_80083460;
                ASM_KEEP(counter_base);
                FIELD(counter_base, u16, 0xA)++;
                goto process;
            }

            func_800A4ACC(self);
            FIELD(self, u8, 0x6D)--;
            FIELD(arg0, s32, 0x8C) = arg4;
            goto done;
        }
    }

    if (D_80083462 & 8) {
        goto done;
    }
    if ((func_800A2B5C(self) << 16) != 0) {
        goto done;
    }

    func_800C77D0(self - 0x20, call_arg1, 8, 0x300);
    if ((func_800A2B5C(self) << 16) != 0) {
        goto done;
    }

process:
    if (active == 0) {
        if (FIELD(self, s32, 0x1C) & 0x400) {
            field_14 = FIELD(self, s32, 0x14);
            ASM_KEEP(field_14);
            if (field_14 >= 0) {
                field_14 |= 0x80000000;
                FIELD(self, s32, 0x14) = field_14;
                FIELD(self, u16, 0x2A) += (func_800A6D30() & 7) << 9;
            }
        }

        field_46 = (volatile u16 *)(self + 0x46);
        if (!(*field_46 & 0x4000)) {
            index = *field_46 & 0x3FFF;
            table_index = index - 1;
            table_base = D_8006DE24;
            slot = self;
            slot += table_index * 3;
            table_index = slot[8];
            entry = table_base + table_index * 20;
            ASM_KEEP(table_index);
            ASM_KEEP(table_base);
            if (FIELD(entry, u8, 0x12) == 2) {
                FIELD(self, s32, 0x60) =
                    func_800A05A4(self,
                                  FIELD(call_arg2, u8, 0x24),
                                  FIELD(call_arg2, u8, 0x25),
                                  FIELD(self, s16, 0x2A),
                                  FIELD(entry, u8, 0x13));
            }
        }
    }

    FIELD(arg0, u8, 0x9A) = 0x12;
    FIELD(arg0, u8, 0x9B) = 0;
    FIELD(arg0, s32, 0x8C) = 0;

    if (call_arg3 != 0) {
        FIELD(call_arg2, u8 *, 0x2C) = call_arg3;
        index = (D_80083228 + FIELD(self, s16, 0x2A) + 0x100) >> 9;
        func_80047784(call_arg2, call_arg3[index & 7], 0);
        ASM_KEEP(call_arg3);
    }

    counter_base = (u8 *)&D_80083460;
    ASM_KEEP(counter_base);
    FIELD(counter_base, u16, 0xA)++;

done:
    return;
}
