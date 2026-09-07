#include "common.h"

typedef struct S_800A6620_0 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800A6620_0;   /* arg0 in func_800A6620 */

typedef struct S_800A6620_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A6620_1_pre;   /* the 0x14 bytes before object in func_800A6620, addressed as object[-1] */

typedef struct S_800A6620_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x23];
    u8 unk_43;
    u8 unk_44;
} S_800A6620_1;   /* object in func_800A6620 */

typedef struct S_800A6620_2 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x20];
    s32 unk_D0;
} S_800A6620_2;   /* entry in func_800A6620 */

typedef struct S_800A6620_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A6620_3;   /* owner in func_800A6620 */



extern void func_800422DC(void *arg0, void *arg1);
extern s32 func_80042900(void *arg0, s32 arg1);
extern void func_80098B38(void *arg0);
extern void func_8009A028(void *arg0);
extern void func_8009A3D0(u8 arg0, u8 arg1, s32 arg2);
extern s16 func_800A1BD0(void *arg0);
extern void func_800A32A4(void *arg0);

extern s32 D_800E3D7C;
extern void *D_800E3DF0[];
extern s32 D_800814A0;

s16 func_800A6620(void *arg0, s32 arg1)
{
    s32 mode;
    s32 index;
    void **slot;
    void **table;
    void *object;
    void *entry;
    void *owner;
    u8 sound_x;
    u8 sound_y;

    table = D_800E3DF0;
    index = ((S_800A6620_0 *)arg0)->unk_03 & 0x1F;
    slot = &table[index];
    object = *slot;
    *slot = 0;
    index = ((S_800A6620_1 *)object)->unk_43;

    if (index < 0x40) {
        ((S_800A6620_1 *)object)->unk_44 = 0;
        func_800422DC((void *)(0x80010A80 + index * 0x54), object);
    }

    if (((S_800A6620_0 *)arg0)->unk_03 & 0x20) {
        index = func_800A1BD0(object);
        if (index >= 0) {
            entry = (void *)(index * 4 + D_800E3D7C);
            ((S_800A6620_2 *)entry)->unk_AC = 0;
            ((S_800A6620_2 *)entry)->unk_D0 = 0;
        }

        if ((func_80042900(object, 0x1B) << 16) == 0) {
            owner = ((S_800A6620_1_pre *)object)[-1].unk_00;
            sound_x = ((S_800A6620_3 *)owner)->unk_24;
            sound_y = ((S_800A6620_3 *)owner)->unk_25;
            mode = 0x3000;
            if (((S_800A6620_1 *)object)->unk_1C & 0x2000) {
                mode = 0x300;
            }
            func_8009A3D0(sound_x, sound_y, mode);
        }

        if (arg1 != 0) {
            func_800A32A4(object);
        }
        func_8009A028(object);
        (*(u16 *)((u8 *)object + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    func_80098B38(arg0);
    return index;
}
