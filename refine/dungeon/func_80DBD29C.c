#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_80174A9C_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x34];
    s32 unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    s16 unk_88;
} S_80174A9C_0;   /* arg3 in func_80174A9C */

typedef struct S_80174A9C_1 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
} S_80174A9C_1;   /* arg0 in func_80174A9C */

typedef struct S_80174A9C_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80174A9C_2;   /* arg2 in func_80174A9C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80047784();
s32 func_8009B25C();
s32 func_800A2B5C();
M2C_UNK func_800A4ACC();
M2C_UNK func_800C7930();
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80175414;

/* Starts an actor action and selects its directional sprite and adjacent target. */
void func_80174A9C(void *action_state, M2C_UNK action_context, void *sprite, void *actor) {
    s32 direction;

    ((S_80174A9C_0 *)actor)->unk_71 = (u8)(((S_80174A9C_0 *)actor)->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930(actor - 0x20, action_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((S_80174A9C_1 *)action_state)->unk_9A = 0x17;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((S_80174A9C_1 *)action_state)->unk_9B = 0;
            (*(u8 **)((u8 *)sprite + 0x2C)) = &D_80175414;
            func_80047784(sprite,
                          *(&D_80175414 + (((s32)(D_80083228 + ((S_80174A9C_0 *)actor)->unk_2A + 0x100) >> 9) & 7)),
                          0);
            func_800A4ACC(actor);
            ((S_80174A9C_0 *)actor)->unk_6D = (u8)(((S_80174A9C_0 *)actor)->unk_6D - 1);
            direction = ((u16)((S_80174A9C_0 *)actor)->unk_2A >> 9) & 7;
            ((S_80174A9C_0 *)actor)->unk_60 =
                func_8009B25C(actor,
                              (((S_80174A9C_2 *)sprite)->unk_24 + D_8006CCD8[direction]) & 0xFFFF,
                              (((S_80174A9C_2 *)sprite)->unk_25 + D_8006CCE8[direction]) & 0xFFFF,
                              ((S_80174A9C_0 *)actor)->unk_88);
        }
    }
}
