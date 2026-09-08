#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_800B7C14_1_pre {
    u16 unk_00;
} S_800B7C14_1_pre;   /* the 0x2 bytes before arg0 in func_800B7C14, addressed as arg0[-1] */

typedef struct S_800B7C14_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u16 unk_16;
} S_800B7C14_1;   /* arg0 in func_800B7C14 */

typedef struct S_800B7C14_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800B7C14_2;   /* arg1 in func_800B7C14 */


M2C_UNK func_8003DB94();        /* extern */
M2C_UNK func_800478B8();                      /* extern */
extern M2C_UNK D_800814A0;

/* Advance effect motion, fade its primitive, and mark it for removal when its lifetime ends. */
void func_800B7C14(void *effect, void *motion, void *primitive) {
    s32 velocity_x;
    u16 life_left;
    u8 brightness;

    if (((Rec_D_80082E80 *)primitive)->unk_00 != 0) {
        func_800478B8(primitive);
        if (((Rec_D_80082E80 *)primitive)->unk_14.at00_u16.v & 0x4000) {
            func_8003DB94(primitive, ((S_800B7C14_1 *)effect)->unk_08, 0);
        }
    }
    ((S_800B7C14_2 *)motion)->unk_00 = (s32) (((S_800B7C14_2 *)motion)->unk_00 + ((S_800B7C14_2 *)motion)->unk_0C);
    ((S_800B7C14_2 *)motion)->unk_04 = (s32) (((S_800B7C14_2 *)motion)->unk_04 + ((S_800B7C14_2 *)motion)->unk_10);
    velocity_x = ((S_800B7C14_2 *)motion)->unk_0C;
    ((S_800B7C14_2 *)motion)->unk_08 = (s32) (((S_800B7C14_2 *)motion)->unk_08 + ((S_800B7C14_2 *)motion)->unk_14);
    ((S_800B7C14_2 *)motion)->unk_0C = (s32) (velocity_x - (velocity_x >> 4));
    ((S_800B7C14_2 *)motion)->unk_10 = (s32) (((S_800B7C14_2 *)motion)->unk_10 - (((S_800B7C14_2 *)motion)->unk_10 >> 4));
    ((S_800B7C14_2 *)motion)->unk_14 = (s32) (((S_800B7C14_2 *)motion)->unk_14 + 0x40000);
    if (((S_800B7C14_1 *)effect)->unk_12 != 0) {
        brightness = ((Rec_D_80082E80 *)primitive)->unk_0C.at00_u8.v;
        if (brightness != 0) {
            brightness -= 8;
            ((Rec_D_80082E80 *)primitive)->unk_0C.at00_u8.v = brightness;
            ((Rec_D_80082E80 *)primitive)->unk_0C.at02_u8.v = brightness;
            ((Rec_D_80082E80 *)primitive)->unk_0C.at01_u8.v = brightness;
        }
    }
    ((Rec_D_80082E80 *)primitive)->unk_14.at02_u16.v = (u16) (((Rec_D_80082E80 *)primitive)->unk_14.at02_u16.v + ((S_800B7C14_1 *)effect)->unk_14);
    ((Rec_D_80082E80 *)primitive)->unk_18 = (u16) (((Rec_D_80082E80 *)primitive)->unk_18 + ((S_800B7C14_1 *)effect)->unk_16);
    life_left = ((S_800B7C14_1 *)effect)->unk_10 - 1;
    ((S_800B7C14_1 *)effect)->unk_10 = life_left;
    if ((life_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_800B7C14_1_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }
}
