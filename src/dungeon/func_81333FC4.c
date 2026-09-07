#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8016AFC4_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_8016AFC4_0;   /* arg3 in func_8016AFC4 */



typedef struct S_8016AFC4_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016AFC4_3;   /* entry in func_8016AFC4 */

typedef struct S_8016AFC4_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016AFC4_4;   /* (u8 *)arg3 + ((S_8016AFC4_0 *)arg3)->unk_8A.s in func_8016AFC4 */



extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s32 func_8009A66C();
extern s16 func_800A0818();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801739C0[8];
extern u8 D_801739C8[8];
extern u8 D_801739D0[8];
extern u8 D_801739D8[8];

void func_8016AFC4(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 move_mode;
    s32 behavior;
    s32 count;
    s32 old_x;
    s32 old_y;
    s16 direction;
    u8 *entry;

    if (((S_8016AFC4_0 *)arg3)->unk_71.s <= 0) {
        return;
    }
    {
        s32 path_count = ((S_8016AFC4_0 *)arg3)->unk_71.u;
        if (((S_8016AFC4_0 *)arg3)->unk_8A.s >= path_count) {
            return;
        }
    }

    behavior = ((Rec_func_800A9E70_arg0 *)arg0)->unk_AC;
    switch (behavior) {
    case 0:
        if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 != D_801739C0) {
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801739C0;
            func_80047784(arg2,
                D_801739C0[((D_80083228 + ((S_8016AFC4_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 1:
        if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 != D_801739C8) {
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801739C8;
            func_80047784(arg2,
                D_801739C8[((D_80083228 + ((S_8016AFC4_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 2:
        if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 != D_801739D0) {
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801739D0;
            func_80047784(arg2,
                D_801739D0[((D_80083228 + ((S_8016AFC4_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 3:
        if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 != D_801739D8) {
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801739D8;
            func_80047784(arg2,
                D_801739D8[((D_80083228 + ((S_8016AFC4_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        break;
    }

    move_mode = 0x3000;
    old_x = ((Rec_D_80082E80 *)arg2)->unk_24;
    old_y = ((Rec_D_80082E80 *)arg2)->unk_25;
    if (((S_8016AFC4_0 *)arg3)->unk_1C & 0x2000) {
        move_mode = 0x300;
    }
    func_8009A3D0(old_x, old_y, move_mode);

    entry = (u8 *)arg3 + ((S_8016AFC4_0 *)arg3)->unk_8A.s;
    direction = func_800A0818(old_x, old_y, ((S_8016AFC4_3 *)entry)->unk_74,
                              ((S_8016AFC4_3 *)entry)->unk_7C, (u8 *)arg0 + 0x98);
    func_8009A66C(direction, arg2, arg3, 0x20);

    ((Rec_D_80082E80 *)arg2)->unk_24 =
        ((S_8016AFC4_4 *)((u8 *)arg3 + ((S_8016AFC4_0 *)arg3)->unk_8A.s))->unk_74;
    ((Rec_D_80082E80 *)arg2)->unk_25 =
        ((S_8016AFC4_4 *)((u8 *)arg3 + ((S_8016AFC4_0 *)arg3)->unk_8A.s))->unk_7C;
    ((S_8016AFC4_0 *)arg3)->unk_8A.u++;

    func_8009A21C(((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25,
                  (((S_8016AFC4_0 *)arg3)->unk_1C & 0x2000) ? 0x300 : 0x3000);

    ((S_8016AFC4_0 *)arg3)->unk_2A = direction;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_s8 = 0xF;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
    (*(s32 *)((u8 *)arg3 + 0x1C)) |= 0x40000000;

    if (D_80083462 & 0x80) {
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_96.as_s16 = 0;
        return;
    }

    if (((Rec_func_800A9E70_arg0 *)arg0)->unk_B0 != 0) {
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_96.as_s16 = 0x10;
    } else {
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_96.as_s16 = 8;
    }
    count = ((S_8016AFC4_0 *)arg3)->unk_71.u;
    if (count > 0) {
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_96.as_s16 = ((Rec_func_800A9E70_arg0 *)arg0)->unk_96.as_s16 / count;
    }
}
