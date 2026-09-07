#include "common.h"

extern void func_80035208();
extern void func_800478B8();
extern void func_8008B620();
extern void func_8008BE34();
extern void func_8008BEBC();

extern u8 D_80072210[];
extern u8 D_80072214[];
extern s32 D_80082ABC;
extern u8 D_80083160[];
extern u8 D_80083780[];
extern u8 D_8008BED8[];
extern u8 D_800FC418;

void func_8008BC58(u8 *object, void *arg1, void *arg2) {
    u8 *input = D_80083160;
    u8 *list = *(u8 **)(object + 0x7C);
    s16 state;

    if (D_800FC418 != 0) {
        *(void **)(object + 0x68) = D_8008BED8;
        func_8008BEBC(arg2);
        return;
    }

    state = *(s16 *)(object + 0x66);
    if (state == 0) {
        u16 timer = *(u16 *)(object + 0x64) - 1;

        *(u16 *)(object + 0x64) = timer;
        if ((timer << 16) <= 0) {
            s32 buttons;

            *(u16 *)(object + 0x64) = 0;
            if (*(s32 *)(input + 0x10) & 0x10000000) {
                *(u16 *)((u8 *)arg1 + 0xA) += 0x10;
            }
            if (*(s32 *)(input + 0x10) & 0x40000000) {
                *(u16 *)((u8 *)arg1 + 0xA) -= 0x10;
            }

            buttons = *(s32 *)(input + 0x10);
            if (buttons & 0x40) {
                D_800FC418 = 1;
                func_80035208(D_80072214);
        return;
            return;
            }
            if (buttons & 0x20) {
                D_800FC418 = 1;
                func_80035208(D_80072210, arg1);
                return;
            }
        }
    } else if (state == 9) {
        s16 *position;

        func_800478B8();
        position = (s16 *)D_80083780;
        *(s32 *)(*(u8 **)object + 0x30) = position[1] / 64 - 0x18;
        *(s32 *)(*(u8 **)object + 0x34) = position[3] / 64 - 0x40;
        return;
    } else if (state == 10) {
        s32 buttons;
        s32 index;
        u8 selection;
        u8 *table;
        register u8 *page ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

        func_800478B8();
        buttons = *(s32 *)(input + 0x10);
        if (buttons & 0x6000) {
            if (++*(s32 *)(object + 0x74) >= *(s32 *)(object + 0x78)) {
                *(s32 *)(object + 0x74) = 0;
                func_8008BE34();
                return;
            }
        } else if (buttons & 0x9000) {
            if (--*(s32 *)(object + 0x74) < 0) {
                *(s32 *)(object + 0x74) = *(s32 *)(object + 0x78) - 1;
            }
        } else {
            goto skip;
        }
        func_8008B620(list[*(s32 *)(object + 0x74)]);
    skip:
        index = *(s32 *)(object + 0x74);
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a constant in a register as retail does */
        page = (u8 *)0x800D0000;
        ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
        table = page + 0x2EA4;
        selection = list[index];
        *(s32 *)(*(u8 **)object + 0x30) = table[selection * 8] - 0x18;

        index = *(s32 *)(object + 0x74);
        selection = list[index];
        *(s32 *)(*(u8 **)object + 0x34) = table[selection * 8 + 1] - 0x40;

        index = *(s32 *)(object + 0x74);
        D_80082ABC = list[index];
    }
}
