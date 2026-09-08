#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A5DFC_arg1.h"

M2C_UNK func_800B4C7C(); /* extern */
M2C_UNK func_800C5BBC(); 
typedef struct S_800A5DFC_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A5DFC_0_pre;   /* the 0x14 bytes before arg0 in func_800A5DFC, addressed as arg0[-1] */



typedef struct S_800A5DFC_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800A5DFC_2;   /* ((S_800A5DFC_0_pre *)arg0)[-1].unk_00 in func_800A5DFC */

/* extern */

/* Applies damage capped to leave one HP and displays the hit effect when applicable. */
void func_800A5DFC(void *entity, Rec_func_800A5DFC_arg1 *effect_pos) {
    s32 current_hp;
    s32 rounded_hp;
    s32 damage;
    u8 max_hp;

    if ((((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x40) && ((((Rec_D_800E3D7C *)entity)->unk_28 + ((Rec_D_800E3D7C *)entity)->unk_64.as_s16) >= 2)) {
        max_hp = ((Rec_D_800E3D7C *)entity)->unk_29;
        rounded_hp = max_hp + 0xF;
        ((Rec_D_800E3D7C *)entity)->unk_6A.as_s16 = (s16) (((Rec_D_800E3D7C *)entity)->unk_2A.as_u16 + 0x800);
        if (rounded_hp < 0) {
            rounded_hp = max_hp + 0x1E;
        }
        damage = rounded_hp >> 4;
        current_hp = ((Rec_D_800E3D7C *)entity)->unk_28 + ((Rec_D_800E3D7C *)entity)->unk_64.as_s16;
        if ((current_hp - damage) <= 0) {
            damage = current_hp - 1;
        }
        if (damage != 0) {
            ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0xDFFFFFFF);
            if (!(((S_800A5DFC_2 *)(((S_800A5DFC_0_pre *)entity)[-1].unk_00))->unk_14 & 0x8000)) {
                func_800B4C7C(3, entity, (s16) damage, 0);
                ((Rec_D_800E3D7C *)entity)->unk_64.as_s16 = (s16) ((u16) ((Rec_D_800E3D7C *)entity)->unk_64.as_s16 - damage);
                func_800C5BBC(effect_pos->unk_02, effect_pos->unk_06, (s16) (effect_pos->unk_0A - 8), 0x802080, 0x20, 1);
                return;
            }
            ((Rec_D_800E3D7C *)entity)->unk_28 = (u8) (((Rec_D_800E3D7C *)entity)->unk_28 - damage);
        }
    }
}
