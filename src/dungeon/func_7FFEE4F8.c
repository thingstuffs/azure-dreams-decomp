#include "common.h"

typedef struct S_8008BC58_0 {
    u8 pad_00[0x64];
    u16 unk_64;
    s16 unk_66;
    void * unk_68;
    u8 pad_6C[0x8];
    union { s32 s; volatile s32 u; } unk_74;   /* accessed as both */
    s32 unk_78;
    u8 * unk_7C;
} S_8008BC58_0;   /* object in func_8008BC58 */

typedef struct S_8008BC58_1 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8008BC58_1;   /* input in func_8008BC58 */

typedef struct S_8008BC58_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8008BC58_2;   /* arg1 in func_8008BC58 */

typedef struct S_8008BC58_3 {
    u8 pad_00[0x30];
    s32 unk_30;
    s32 unk_34;
} S_8008BC58_3;   /* record in func_8008BC58 */



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

void func_8008BC58(u8 *object, S_8008BC58_2 *arg1, void *arg2)
{
    u8 *input = D_80083160;
    u8 *list = ((S_8008BC58_0 *)object)->unk_7C;
    u8 *record;
    s16 state;

    if (D_800FC418 != 0) {
        ((S_8008BC58_0 *)object)->unk_68 = D_8008BED8;
        goto done;
    }

    state = ((S_8008BC58_0 *)object)->unk_66;
    if (state == 0) {
        u16 timer;
        s32 buttons;

        timer = ((S_8008BC58_0 *)object)->unk_64 - 1;
        ((S_8008BC58_0 *)object)->unk_64 = timer;
        if ((timer << 16) <= 0) {
            ((S_8008BC58_0 *)object)->unk_64 = 0;
            if (((S_8008BC58_1 *)input)->unk_10 & 0x10000000) {
                arg1->unk_0A += 0x10;
            }
            if (((S_8008BC58_1 *)input)->unk_10 & 0x40000000) {
                arg1->unk_0A -= 0x10;
            }
            buttons = ((S_8008BC58_1 *)input)->unk_10;
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
        ((S_8008BC58_3 *)record)->unk_30 = x;
        record = *(u8 **)object;
        y = position[3] / 64 - 0x40;
        ((S_8008BC58_3 *)record)->unk_34 = y;
        goto done;
    } else if (state == 10) {
        register s32 index ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        u8 selection;
        register u8 *table ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
        s32 buttons;

        func_800478B8(arg2);
        buttons = ((S_8008BC58_1 *)input)->unk_10;
        if (buttons & 0x6000) {
            index = ((S_8008BC58_0 *)object)->unk_74.s + 1;
            ((S_8008BC58_0 *)object)->unk_74.s = index;
            if (index >= ((S_8008BC58_0 *)object)->unk_78) {
                ((S_8008BC58_0 *)object)->unk_74.s = 0;
            }
        } else if (buttons & 0x9000) {
            index = ((S_8008BC58_0 *)object)->unk_74.s - 1;
            ((S_8008BC58_0 *)object)->unk_74.s = index;
            if (index < 0) {
                index = ((S_8008BC58_0 *)object)->unk_78 - 1;
                ((S_8008BC58_0 *)object)->unk_74.s = index;
            }
        } else {
            goto update;
        }

        func_8008B620(list[((S_8008BC58_0 *)object)->unk_74.u]);

update:
        index = ((S_8008BC58_0 *)object)->unk_74.s;
        table = D_800D2EA4;
        selection = list[index];
        record = *(u8 **)object;
        ((S_8008BC58_3 *)record)->unk_30 = table[selection * 8] - 0x18;

        index = ((S_8008BC58_0 *)object)->unk_74.s;
        selection = list[index];
        record = *(u8 **)object;
        ((S_8008BC58_3 *)record)->unk_34 = table[selection * 8 + 1] - 0x40;

        index = ((S_8008BC58_0 *)object)->unk_74.s;
        selection = list[index];
        D_80082ABC = selection;
    }

done:
    return;
}
