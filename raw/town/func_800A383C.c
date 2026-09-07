#include "common.h"

typedef struct TownObject {
    s16 field_00;
    s16 field_02;
    s16 field_04;
    u8 pad_06[2];
    s16 field_08;
    s16 field_0A;
    s32 field_0C;
    s16 field_10;
    s16 field_12;
    u8 pad_14[0x40];
    void *items[6];
    s16 field_6C;
    s16 field_6E;
    s16 field_70;
    s16 field_72;
    u8 pad_74[4];
    s16 field_78;
    s16 field_7A;
} TownObject;

extern void *func_800A1C94(TownObject *, s32, void *);
extern void func_800A105C(void);

s32 func_800A0F9C(TownObject *arg0, void *arg1, s32 arg2) {
    void **item;
    void **items;
    register s32 count ASM_REG("$16");

    count = arg2;
    items = arg0->items;
    if (count > 0) {
        ASM_KEEP(count);
        item = (void **)((unsigned long)(count * sizeof(*items)) +
                        (unsigned long)items);
        item--;
        do {
            count--;
            *item = func_800A1C94(arg0, count, arg1);
            if (items == 0) {
                func_800A105C();
                return count + 1;
            }
            item--;
        } while (count > 0);
        item++;
        ASM_USE(item);
    }

    arg0->field_00 = 0;
    arg0->field_02 = 0x800;
    arg0->field_04 = 0;
    arg0->field_08 = 0x180;
    arg0->field_10 = 0;
    arg0->field_0C = 0;
    arg0->field_12 = 0xFF;
    arg0->field_6C = 0x340;
    arg0->field_6E = 0;
    arg0->field_70 = 0x80;
    arg0->field_72 = 0x80;
    arg0->field_78 = 0x80;
    arg0->field_7A = 0xA0;
    arg0->field_0A = 0;
    return 0;
}

/* MECHANISM: The 0x28 frame follows from held arg0/arg1/count/items-base/item roles;
   a block-local $s0 keep preserves loop coloring, and index-first integer address math fixes addu order.
   A void zero-arg tail plus return count+1 triggers SHAPE-C; explicit zero-store order closes the tail. */
