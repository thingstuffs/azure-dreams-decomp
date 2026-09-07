#include "common.h"

typedef struct {
    u8 x;
    u8 y;
    s16 value;
} Record;

extern s16 D_80080B04[5];
extern Record *D_80081508[3];

extern s32 func_800448BC(s32 x, s32 y);
extern void func_800D1720(Record *record);

void func_800D169C(s32 x, s32 y, s32 value, s32 commit)
{
    register s32 held_x ASM_REG("$16") = x;
    register s32 held_y ASM_REG("$17") = y;
    Record *record;
    volatile u16 *counter_page;

    if (D_80080B04[0] < 64) {
        if ((s16)func_800448BC((u16)held_x, (u16)held_y) == 0) {
            record = &D_80081508[0][D_80080B04[0]];
            record->x = held_x;
            record->y = held_y;
            if ((s16)commit != 0) {
                record->value = value;
                func_800D1720(record);
                return;
            }
            record->value = (s16)0x8000;
            ASM_MEM_BARRIER();
            counter_page = (volatile u16 *)0x80080000;
            counter_page[0x582]++;
            record[1].x = 0;
        }
    }
}

/* MECHANISM: Multi-entry declarations hold D_80080B04's page in s2 and expose
   D_80081508's split page load in the branch delay slot. A memory barrier plus
   a fresh 0x80080000 page local yields the final one-lui v1 counter RMW. */
