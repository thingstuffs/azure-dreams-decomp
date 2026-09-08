#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;


typedef struct S_80172514_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80172514_1;   /* arg0 in func_80172514 */



extern M2C_UNK func_80047784();
extern M2C_UNK func_8009C93C();
extern s32 func_800A2B5C();
extern M2C_UNK func_800C7930();
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80175258[];

/* Reset actor action state and select a facing-dependent animation when status checks pass. */
void func_80172514(void *action_state, M2C_UNK action_context, void *sprite, void *actor) {
    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 &= 0x7F;

    if (!(D_80083462 & 0x2000) &&
        ((func_800A2B5C(actor) << 16) == 0) &&
        (func_800C7930((u8 *)actor - 0x20, action_context, 8, 0x300),
         ((func_800A2B5C(actor) << 16) == 0))) {
        ((S_80172514_1 *)action_state)->unk_8C = 0;
        ((S_80172514_1 *)action_state)->unk_9B = 0;

        if (((S_80172514_1 *)action_state)->unk_98 & 0x8000) {
            ((S_80172514_1 *)action_state)->unk_9A = 0x17;
            ((Rec_D_800E3D7C *)actor)->unk_84.as_u8 = 0x28;
            ((Rec_D_800E3D7C *)actor)->unk_85.as_u8 = 0x10;
        } else {
            ((S_80172514_1 *)action_state)->unk_9A = 0x11;
            ((Rec_D_800E3D7C *)actor)->unk_84.as_u8 = 0x7C;
            ((Rec_D_800E3D7C *)actor)->unk_85.as_u8 = 0;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = D_80175258;
        func_80047784(
            sprite,
            D_80175258[((s32)(D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8--;
        func_8009C93C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1, 0);
    }
}
