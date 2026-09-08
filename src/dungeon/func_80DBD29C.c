#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;


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

    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 = (u8)(((Rec_D_800E3D7C *)actor)->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930(actor - 0x20, action_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((S_80174A9C_1 *)action_state)->unk_9A = 0x17;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((S_80174A9C_1 *)action_state)->unk_9B = 0;
            (*(u8 **)((u8 *)sprite + 0x2C)) = &D_80175414;
            func_80047784(sprite,
                          *(&D_80175414 + (((s32)(D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7)),
                          0);
            func_800A4ACC(actor);
            ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 = (u8)(((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 - 1);
            direction = ((u16)((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 9) & 7;
            ((Rec_D_800E3D7C *)actor)->unk_60.as_s32 =
                func_8009B25C(actor,
                              (((S_80174A9C_2 *)sprite)->unk_24 + D_8006CCD8[direction]) & 0xFFFF,
                              (((S_80174A9C_2 *)sprite)->unk_25 + D_8006CCE8[direction]) & 0xFFFF,
                              ((Rec_D_800E3D7C *)actor)->unk_88.as_s16);
        }
    }
}
