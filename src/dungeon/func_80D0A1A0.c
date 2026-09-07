#include "common.h"

typedef struct {
    u8 pad00[0x8c];
    void *field8c;
} Obj0;

typedef struct {
    u8 pad00[0x2c];
    u8 *table2c;
} Obj2;

typedef struct {
    u8 pad00[0x1c];
    u32 flags1c;
    u8 pad20[5];
    u8 flag25;
    u8 pad26[4];
    s16 value2a;
    u8 pad2c[0x1c];
    u8 kind48;
} Obj3;

extern s16 D_80083228;
extern u8 D_801544BC[];
extern s32 D_80157DC4;
extern s32 D_80157DCC;
extern s32 D_80157DD4;
extern u8 D_80157E24[];
extern u8 D_80157E2C[];
extern u8 D_80157E34[];
extern u8 D_80157E54[];
extern u8 D_80157E5C[];
extern u8 D_80157E64[];

extern void func_80047784(Obj2 *, u8, s32);
extern s32 func_800AC82C(Obj0 *, void *, Obj2 *, Obj3 *);
extern s32 func_800AD9B4(Obj2 *, Obj3 *);

void func_801579A0(Obj0 *arg0, void *arg1, Obj2 *arg2, Obj3 *arg3)
{
    Obj2 *obj2 = arg2;
    Obj3 *obj3 = arg3;
    u32 table;
    register u32 new_table ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    u32 current;
    u8 kind;
    s32 index;


    kind = obj3->kind48;
    switch (kind) {
    case 13:
        if ((obj3->flags1c & 0x200) != 0) {
            goto kind13_default;
        }
        if (obj3->flag25 != 0) {
            goto kind13_alternate;
        }
kind13_default:
        current = (u32)obj2->table2c;
        table = (u32)D_80157E54;
        goto first_join;
kind13_alternate:
        current = (u32)obj2->table2c;
        table = (u32)D_80157E24;
        goto first_join;

    case 14:
        if ((obj3->flags1c & 0x200) != 0) {
            goto kind14_default;
        }
        if (obj3->flag25 != 0) {
            goto kind14_alternate;
        }
kind14_default:
        current = (u32)obj2->table2c;
        table = (u32)D_80157E5C;
        goto first_join;
kind14_alternate:
        current = (u32)obj2->table2c;
        table = (u32)D_80157E2C;
        goto first_join;

    case 15:
        if ((obj3->flags1c & 0x200) != 0) {
            goto kind15_default;
        }
        if (obj3->flag25 != 0) {
            goto kind15_alternate;
        }
kind15_default:
        current = (u32)obj2->table2c;
        table = (u32)D_80157E64;
        goto first_join;
kind15_alternate:
        current = (u32)obj2->table2c;
        table = (u32)D_80157E34;
        goto first_join;

    default:
        goto after_first_update;
    }

first_join:
    if (current != table) {
        *(u32 * volatile)((u8 *)obj2 + 0x2c) = table;
        index = (D_80083228 + obj3->value2a + 0x100) >> 9;
        func_80047784(obj2, *(u8 *)((index & 7) + table), 0);
    }

after_first_update:
    if (func_800AC82C(arg0, arg1, obj2, obj3) != 0) {
        if ((func_800AD9B4(obj2, obj3) << 16) > 0) {
            arg0->field8c = D_801544BC;
        }
        return;
    }

    switch (obj3->kind48) {
    case 13:
        if (obj2->table2c != D_80157E54 ||
            (obj3->flags1c & 0x208) != 0) {
            return;
        }
        new_table = (u32)&D_80157DC4;
        *(u32 * volatile)((u8 *)obj2 + 0x2c) = new_table;
        index = (D_80083228 + obj3->value2a + 0x100) >> 9;
        func_80047784(obj2, *(u8 *)((index & 7) + new_table), 0);
        return;
    case 14:
        if (obj2->table2c != D_80157E5C ||
            (obj3->flags1c & 0x208) != 0) {
            return;
        }
        new_table = (u32)&D_80157DCC;
        *(u32 * volatile)((u8 *)obj2 + 0x2c) = new_table;
        index = (D_80083228 + obj3->value2a + 0x100) >> 9;
        func_80047784(obj2, *(u8 *)((index & 7) + new_table), 0);
        return;
    case 15:
        if (obj2->table2c != D_80157E64 ||
            (obj3->flags1c & 0x208) != 0) {
            return;
        }
        new_table = (u32)&D_80157DD4;
        *(u32 * volatile)((u8 *)obj2 + 0x2c) = new_table;
        index = (D_80083228 + obj3->value2a + 0x100) >> 9;
        func_80047784(obj2, *(u8 *)((index & 7) + new_table), 0);
        return;
    default:
        return;
    }

}
