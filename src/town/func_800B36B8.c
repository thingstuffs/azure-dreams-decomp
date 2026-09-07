#include "common.h"

typedef struct {
    u8 pad[0x10];
    u8 kind;
    u8 pad2[3];
} ItemCategory;

typedef struct {
    u8 pad0;
    u8 category;
    s8 value;
    u8 flags;
} Item;

extern ItemCategory D_80073414[];
extern s32 memset(void *, s32, s32);
extern void func_8004E5A0(s32, s32, u8 *);
extern u8 *func_8004E69C(u8 *);
extern s32 func_8004E298(void *, u8 *, s32);

s32 func_800B0E18(void *arg0, Item *arg1) {
    u8 buffer[0x20];
    u8 category;
    s32 kind;

    memset(buffer, 0x20, 0x20);
    buffer[0x1F] = 0;
    category = arg1->category;
    kind = D_80073414[category].kind;
    if (kind == 1) {
        s8 value = arg1->value;

        if (value != 0) {
            buffer[0xA] = (value > 0) ? 0x6B : 0x6C;
            func_8004E5A0((arg1->value >= 0) ? arg1->value : -arg1->value,
                          2, &buffer[0xB]);
            func_8004E69C(&buffer[0xB]);
        }
        if (arg1->flags & 0x40) {
            buffer[0xD] = 0xA;
            buffer[0xE] = 0x7A;
        }
    } else {
        if (category != 4) {
            return 0;
        }
        func_8004E5A0(arg1->value, 2, &buffer[0xB]);
        func_8004E69C(&buffer[0xB]);
    }
    return func_8004E298(arg0, buffer, 0);
}
