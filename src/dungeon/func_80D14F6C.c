#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"

typedef s32 M2C_UNK;





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
extern u8 D_80174EC8;

/* Start the actor's directional action and record the adjacent tile result. */
void func_8017476C(void *action_state, M2C_UNK action_context, void *sprite, void *actor) {
    s32 direction;

    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 = (u8)(((Rec_D_800E3D7C *)actor)->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930(actor - 0x20, action_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x17;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_96.as_s16 = 0xF;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            (*(u8 **)((u8 *)sprite + 0x2C)) = &D_80174EC8;
            func_80047784(
                sprite,
                *(&D_80174EC8 + (((s32)(D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7)),
                0);
            ((Rec_func_800AA258_arg2 *)sprite)->unk_14 = (u16)(((Rec_func_800AA258_arg2 *)sprite)->unk_14 | 0x800);
            func_800A4ACC(actor);
            ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 = (u8)(((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 - 1);
            direction = ((u16)((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 9) & 7;
            ((Rec_D_800E3D7C *)actor)->unk_60.as_s32 = func_8009B25C(
                actor,
                (((Rec_func_800AA258_arg2 *)sprite)->unk_24 + D_8006CCD8[direction]) & 0xFFFF,
                (((Rec_func_800AA258_arg2 *)sprite)->unk_25 + D_8006CCE8[direction]) & 0xFFFF,
                ((Rec_D_800E3D7C *)actor)->unk_88.as_s16);
        }
    }
}
