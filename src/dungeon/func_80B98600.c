#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80171E00_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80171E00_1;   /* flags_base in func_80171E00 */


typedef struct S_80171E00_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80171E00_3;   /* arg0 in func_80171E00 */


M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009C93C(); /* extern */
s32 func_800A0134();                     /* extern */
s32 func_800A04F0();             /* extern */
s32 func_800A2B5C();                          /* extern */
s32 func_800A2CB8();                     /* extern */
M2C_UNK func_800C7930(); /* extern */
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80174F28;

/* Check movement conditions and initialize the actor action and directional animation. */
s32 func_80171E00(void *action_state, M2C_UNK action_ctx, void *sprite, void *actor) {
    volatile s64 frame_pad;
    u8 *flags_base;
    u8 *direction_table;
    s32 move_heading;
    u16 flags;

    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)actor)->unk_71.as_u8 & 0x7F);
    flags_base = (u8 *) &D_80083460;
    if (((S_80171E00_1 *)flags_base)->unk_02 & 0x2000) {
        goto return_minus_one;
    }
    move_heading = func_800A04F0(actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16);
    if ((func_800A2CB8(actor, move_heading) << 0x10) == 0) {
        return 0;
    }
    flags = ((S_80171E00_1 *)flags_base)->unk_02;
    if (flags & 0x2000) {
        return -1;
    }
    if (!(((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000)) {
        if (flags & 8) {
            return -1;
        }
    }
    if ((u32) (((0 - func_800A0134(move_heading, actor)) + 0x3F) & 0xFFFF) >= 0x7FU) {
        return 0;
    }
    if ((func_800A2B5C(actor) << 0x10) != 0) {
        return -1;
    }
    func_800C7930(actor - 0x20, action_ctx, 8, 0x300);
    if ((func_800A2B5C(actor) << 0x10) == 0) {
        goto success;
    }
return_minus_one:
    return -1;
success:
    ((S_80171E00_3 *)action_state)->unk_9A = 0x11;
    ((S_80171E00_3 *)action_state)->unk_9B = 0;
    ((S_80171E00_3 *)action_state)->unk_8C = 0;
    ((Rec_D_800E3D7C *)actor)->unk_84.as_s8 = 0x7C;
    ((Rec_D_800E3D7C *)actor)->unk_85.as_s8 = 0;
    direction_table = &D_80174F28;
    (*(u8 **)((u8 *)sprite + 0x2C)) = direction_table;
    func_80047784(sprite, direction_table[((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 - 1);
    func_8009C93C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1, 0);
    return 1;
}
