/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() 0
#define M2C_SYNC() 0

void func_80047784();
M2C_UNK func_8009C93C();
s32 func_800A2B5C();
M2C_UNK func_800C7930();
extern s16 D_80083228[];
extern u16 D_80083462[];

typedef struct S_80172434_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80172434_0;   /* arg3 in func_80172434 */

typedef struct S_80172434_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_80172434_1;   /* arg0 in func_80172434 */

typedef struct S_80172434_2 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_80172434_2;   /* arg2 in func_80172434 */

/* Initialize action state and directional animation when the entity status permits. */
void func_80172434(S_80172434_1 *action_state, M2C_UNK context, S_80172434_2 *animation, void *entity) {
    ((S_80172434_0 *)entity)->unk_71 = (s8) (((S_80172434_0 *)entity)->unk_71 & 0x7F);
    if (!(D_80083462[0] & 0x2000) && ((func_800A2B5C(entity) << 0x10) == 0)) {
        func_800C7930(entity - 0x20, context, 8, 0x300);
        if ((func_800A2B5C(entity) << 0x10) == 0) {
            action_state->unk_9A = 0x11;
            action_state->unk_8C = 0;
            action_state->unk_9B = 0;
            func_80047784(animation, *(animation->unk_2C + (((s32) (D_80083228[0] + ((S_80172434_0 *)entity)->unk_2A + 0x100) >> 9) & 7)), 0);
            ((S_80172434_0 *)entity)->unk_6D = (u8) (((S_80172434_0 *)entity)->unk_6D - 1);
            func_8009C93C(entity, animation, ((S_80172434_0 *)entity)->unk_2A, 1, 0);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
            ((S_80172434_0 *)entity)->unk_84 = 0x7C;
            ((S_80172434_0 *)entity)->unk_85 = 0;
        }
    }
}
