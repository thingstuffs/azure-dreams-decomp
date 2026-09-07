#include "common.h"
#include "m2c_compat.h"

typedef struct S_801721C0_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_801721C0_0;   /* arg3 in func_801721C0 */

typedef struct S_801721C0_1 {
    u8 pad_00[0x98];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_801721C0_1;   /* arg0 in func_801721C0 */


M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800C7930(); /* extern */
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80176480;

/* Update the actor action state and directional animation when both checks pass. */
void func_801721C0(void *action_state, M2C_UNK action_ctx, void *sprite, void *actor) {
    ((S_801721C0_0 *)actor)->unk_71 = (u8) (((S_801721C0_0 *)actor)->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930(actor - 0x20, action_ctx, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            ((S_801721C0_1 *)action_state)->unk_9A = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((S_801721C0_1 *)action_state)->unk_9B = 0;
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80176480;
            func_80047784(sprite, *((((s32) (D_80083228 + ((S_801721C0_0 *)actor)->unk_2A + 0x100) >> 9) & 7) + &D_80176480), 0);
            ((S_801721C0_0 *)actor)->unk_6D = (u8) (((S_801721C0_0 *)actor)->unk_6D - 1);
            ((S_801721C0_1 *)action_state)->unk_98 = (u16) (((S_801721C0_1 *)action_state)->unk_98 | 8);
            ((S_801721C0_0 *)actor)->unk_84 = 0x7C;
            ((S_801721C0_0 *)actor)->unk_85 = 0;
            func_8009C93C(actor, sprite, ((S_801721C0_0 *)actor)->unk_2A, 1, 0);
        }
    }
}
