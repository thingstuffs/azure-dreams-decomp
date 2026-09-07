#include "common.h"
#include "m2c_compat.h"

typedef struct S_80172688_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x6];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x1];
    s8 unk_9D;
} S_80172688_0;   /* arg0 in func_80172688 */

typedef struct S_80172688_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80172688_1;   /* arg3 in func_80172688 */

typedef struct S_80172688_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80172688_2;   /* arg1 in func_80172688 */


M2C_UNK func_80047784();         /* extern */
extern s16 D_80083228;
extern u8 D_80174E04;

/* Initialize actor state and select the sprite frame for its facing angle. */
void func_80172688(void *actor_state, void *action_state, void *sprite, void *orientation) {
    ((S_80172688_0 *)actor_state)->unk_9A = 0x10;
    ((S_80172688_0 *)actor_state)->unk_9B = 0;
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80174E04;
    func_80047784(sprite, *((((s32) (D_80083228 + ((S_80172688_1 *)orientation)->unk_2A + 0x100) >> 9) & 7) + &D_80174E04), 0);
    ((S_80172688_0 *)actor_state)->unk_90 = 0;
    ((S_80172688_2 *)action_state)->unk_14 = 0;
    ((S_80172688_0 *)actor_state)->unk_9D = 0;
}
