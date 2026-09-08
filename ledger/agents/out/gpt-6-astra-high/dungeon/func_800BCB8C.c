#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

void func_80041E70(void *);             /* extern */
s32 func_80042900();            /* extern */
M2C_UNK func_8008D344(); /* extern */
M2C_UNK func_80098864();           /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_800997FC();                   /* extern */
M2C_UNK func_80099844();           /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083780;
extern u8 D_800DDE84[];
extern M2C_UNK D_800E1580;
extern M2C_UNK D_800E15A2;
extern s32 D_800E3D7C;
extern void *D_800E3DF0[];



typedef struct S_800C22EC_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C22EC_1;   /* counter in func_800C22EC */

typedef struct S_800C22EC_2 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x1];
    u8 unk_03;
} S_800C22EC_2;   /* temp_a0 in func_800C22EC */

typedef struct S_800C22EC_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    s8 unk_28;
    u8 unk_29;
} S_800C22EC_3;   /* temp_s0 in func_800C22EC */

/* Processes an entity action and updates the selected target or reports failure. */
s32 func_800C22EC(Rec_D_800E3D7C *entity, s32 action, s16 action_type, M2C_UNK context) {
    s32 target_index;
    s32 flags_mask;
    s32 target_updated;
    S_800C22EC_2 *selection;
    S_800C22EC_3 *target;

    target_updated = 0;
    if (action_type == 0xD) {
        return func_80098864(action, context);
    }
    if (entity == D_800E3D7C) {
        entity->unk_110 = action;
        func_8008D344(entity, &D_80083780, &D_80082E80, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, action, action_type);
        if (func_800AD6FC(entity, ((u16 *)D_800DDE84)[entity->unk_10.at03_u8.v] & 3, 0) == 0) {
            func_800A5F38(entity, action);
            return 1;
        }
        func_80098B38(action);
        {
            void *counter;

            counter = &D_80083460;
            ((S_800C22EC_1 *)counter)->unk_0A = (u16) (((S_800C22EC_1 *)counter)->unk_0A - 1);
        }
        return 1;
    }
    selection = *(void **)((u8 *)&D_80082E80 + 0x34);
    if (selection->unk_01 == 0x13) {
        target_index = selection->unk_03 & 0x1F;
        if (target_index < 0x14) {
            target = D_800E3DF0[target_index];
            if ((func_80042900(target, 0xE, action_type) << 0x10) != 0) {
                register void *update_target ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

                flags_mask = 0xFBFFFFFF;
                update_target = target;
                target->unk_28 = (s8) (((u8) target->unk_29 >> 1) + 1);
                target->unk_1C = (s32) (target->unk_1C & flags_mask);
                target_updated = 1;
                func_80041E70(update_target);
                func_80099844(target, &D_800E1580);
            }
        }
    }
    if (target_updated == 0) {
        func_800997FC(&D_800E15A2);
    }
    func_80098B38(action);
    {
        void *counter;

        counter = &D_80083460;
        ((S_800C22EC_1 *)counter)->unk_0A = (u16) (((S_800C22EC_1 *)counter)->unk_0A - 1);
    }
    return 1;
}
