#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800814A8.h"

M2C_UNK func_80047784();         /* extern */
s32 func_8009A180();                     /* extern */
s8 func_8009FB34();                           /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
M2C_UNK func_800AA258(); /* extern */
s32 func_800AA6B4(); /* extern */
M2C_UNK func_800AA888(); /* extern */
M2C_UNK func_8016FA84();                            /* extern */
M2C_UNK func_8016FCE4(); /* extern */
s32 func_80170224(); /* extern */
M2C_UNK func_8017092C(); /* extern */
M2C_UNK func_80174320();     /* extern */
extern u16 D_80013714;
extern void *D_800814A8;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174A2C[];
extern u8 D_80174A64[];


typedef struct S_8016F78C_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x4];
    u16 unk_98;
    union { u8 n; volatile u8 v; } unk_9A;   /* accessed as both */
} S_8016F78C_0;   /* arg0 in func_8016F78C */

/* Updates actor state, directional animation, and action handling. */
void func_8016F78C(void *actor, M2C_UNK context, void *sprite, void *entity) {
    u8 stack_pad[8];
    u8 current_state;
    s32 next_state;

    if (D_80083462 & 0x1000) {
        ((S_8016F78C_0 *)actor)->unk_9A.n = 0xEU;
        func_8016FA84(actor, context, sprite, entity);
        return;
    }
    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x100) {
            func_800AA258(actor, context, sprite, entity);
            return;
        }
        current_state = ((S_8016F78C_0 *)actor)->unk_9A.v;
        next_state = 0xE;
        if (current_state != next_state) {
            if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_80174A2C) {
                (*(u8 **)((u8 *)sprite + (0x2C))) = D_80174A2C;
                func_80047784(sprite, D_80174A2C[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
            }
            ((S_8016F78C_0 *)actor)->unk_9A.n = next_state;
        }
        ((S_8016F78C_0 *)actor)->unk_98 = (u16) (((S_8016F78C_0 *)actor)->unk_98 & 0xFFF3);
        if ((((Rec_D_800E3D7C *)entity)->unk_64.as_s16 == 0) || (func_800AA6B4(actor, context, sprite, D_80174A64) == 0)) {
            if (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x80000) {
                func_800AA888(actor, context, sprite, entity);
                func_8017092C(actor, context, sprite, entity);
                (*(u8 **)((u8 *)sprite + (0x2C))) = D_80174A2C;
                func_80047784(sprite, D_80174A2C[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
                ((S_8016F78C_0 *)actor)->unk_90 = 0;
                return;
            }
            goto check_action;
        }
    } else {
check_action:
        ((Rec_D_80082E80 *)sprite)->unk_26.as_s8 = func_8009FB34(((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if (((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 > 0) {
            if (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x20) {
                func_800A9A0C(entity);
                return;
            }
            if (!(((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x8000)) {
                if (!(D_80083462 & 0x2000) || ((func_8009A180(entity, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 0x10) == 0)) {
                    if (D_80013714 & 8) {
                        func_80174320(actor, context, sprite);
                        ((Rec_D_800E3D7C *)entity)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)entity)->unk_71.as_u8 & 0x7F);
                        func_800A9A0C(entity);
                        ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x7FFF);
                        return;
                    }
                    if ((func_80170224(actor, context, sprite, 0) << 0x10) != 0) {
                        ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v | 0x4000);
                        goto finish_action;
                    }
                }
            } else {
finish_action:
                ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x7FFF);
                ((Rec_D_800E3D7C *)entity)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)entity)->unk_71.as_u8 & 0x7F);
                func_800A9A0C(entity);
                func_8016FCE4(actor, context, sprite, entity);
            }
        }
    }
}
