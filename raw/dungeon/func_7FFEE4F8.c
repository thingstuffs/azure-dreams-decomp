#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void func_80035208();
extern void func_800478B8();
extern void func_8008B620();

extern u8 D_80072210[];
extern u8 D_80072214[];
extern s32 D_80082ABC;
extern u8 D_80083160[];
extern u8 D_80083780[];
extern u8 D_8008BED8[];
extern u8 D_800D2EA4[];
extern u8 D_800FC418;

void func_8008BC58(u8 *object, void *arg1, void *arg2)
{
    u8 *input = D_80083160;
    u8 *list = FIELD(object, u8 *, 0x7c);
    register u8 *record ASM_REG("$3");
    s16 state;

    if (D_800FC418 != 0) {
        FIELD(object, void *, 0x68) = D_8008BED8;
        goto done;
    }

    state = FIELD(object, s16, 0x66);
    if (state == 0) {
        u16 timer;
        s32 buttons;

        timer = FIELD(object, u16, 0x64) - 1;
        FIELD(object, u16, 0x64) = timer;
        if ((timer << 16) <= 0) {
            FIELD(object, u16, 0x64) = 0;
            if (FIELD(input, s32, 0x10) & 0x10000000) {
                FIELD(arg1, u16, 0x0a) += 0x10;
            }
            if (FIELD(input, s32, 0x10) & 0x40000000) {
                FIELD(arg1, u16, 0x0a) -= 0x10;
            }
            buttons = FIELD(input, s32, 0x10);
            if (buttons & 0x40) {
                D_800FC418 = 1;
                func_80035208(D_80072214);
                goto done;
            }
            if (buttons & 0x20) {
                D_800FC418 = 1;
                func_80035208(D_80072210);
                goto done;
            }
        } else {
            goto done;
        }
    } else if (state == 9) {
        s16 *position;
        s32 x;
        s32 y;

        func_800478B8(arg2);
        position = (s16 *)D_80083780;
        record = *(u8 **)object;
        x = position[1] / 64 - 0x18;
        FIELD(record, s32, 0x30) = x;
        record = *(u8 **)object;
        y = position[3] / 64 - 0x40;
        FIELD(record, s32, 0x34) = y;
        goto done;
    } else if (state == 10) {
        register s32 index ASM_REG("$2");
        u8 selection;
        register u8 *table ASM_REG("$4");
        s32 buttons;

        func_800478B8(arg2);
        buttons = FIELD(input, s32, 0x10);
        if (buttons & 0x6000) {
            index = FIELD(object, s32, 0x74) + 1;
            FIELD(object, s32, 0x74) = index;
            if (index >= FIELD(object, s32, 0x78)) {
                FIELD(object, s32, 0x74) = 0;
            }
        } else if (buttons & 0x9000) {
            index = FIELD(object, s32, 0x74) - 1;
            FIELD(object, s32, 0x74) = index;
            if (index < 0) {
                index = FIELD(object, s32, 0x78) - 1;
                FIELD(object, s32, 0x74) = index;
            }
        } else {
            goto update;
        }

        func_8008B620(list[FIELD(object, volatile s32, 0x74)]);

update:
        index = FIELD(object, s32, 0x74);
        table = D_800D2EA4;
        selection = list[index];
        record = *(u8 **)object;
        FIELD(record, s32, 0x30) = table[selection * 8] - 0x18;

        index = FIELD(object, s32, 0x74);
        selection = list[index];
        record = *(u8 **)object;
        FIELD(record, s32, 0x34) = table[selection * 8 + 1] - 0x40;

        index = FIELD(object, s32, 0x74);
        selection = list[index];
        D_80082ABC = selection;
    }

done:
    return;
}
