#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u16 D_80083462[5];
extern u8 D_8017423C[];
extern s16 D_80083228[5];
M2C_UNK func_8009C93C(); /* extern */
s16 func_800A2B5C();                          /* extern */
s32 func_800C7930(); /* extern */

typedef struct S_80172090_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80172090_0;   /* arg3 in func_80172090 */

typedef struct S_80172090_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_80172090_1;   /* arg0 in func_80172090 */

typedef struct S_80172090_2 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_80172090_2;   /* arg2 in func_80172090 */

/* Start the actor action and animation when input and actor checks allow it. */
void func_80172090(S_80172090_1 *action_state, M2C_UNK context, S_80172090_2 *animation, void *actor) {
    ((S_80172090_0 *)actor)->unk_71 = (u8) (((S_80172090_0 *)actor)->unk_71 & 0x7F);
    if (!(*D_80083462 & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930(actor - 0x20, context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            action_state->unk_9A = 0x11;
            action_state->unk_8C = 0;
            action_state->unk_9B = 0;
            animation->unk_2C = D_8017423C;
            func_80047784(animation, D_8017423C[((s32) (*D_80083228 + ((S_80172090_0 *)actor)->unk_2A + 0x100) >> 9) & 7], 0);
            ((S_80172090_0 *)actor)->unk_6D = (u8) (((S_80172090_0 *)actor)->unk_6D - 1);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
            func_8009C93C(actor, animation, ((S_80172090_0 *)actor)->unk_2A, 1, 0);
            ((S_80172090_0 *)actor)->unk_84 = 0x7C;
            ((S_80172090_0 *)actor)->unk_85 = 0;
        }
    }
}
