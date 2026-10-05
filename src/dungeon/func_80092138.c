#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();        /* extern */
s32 func_800A6D30(void);   /* extern */
extern u8 D_800DD294[];


typedef struct S_80097898_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80097898_0;   /* arg0 in func_80097898 */

typedef struct S_80097898_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_80097898_1;   /* saved in func_80097898 */

void func_80097898(void *object, M2C_UNK unused, void *animation, void *actor) {
        /* MATCH: retain retail's a0 table base after the explicit argument call. */
    u8 *table;
        /* MATCH: save a2 then a3 before loading the state-byte constant. */
    void *saved2 = animation;
    void *saved = actor;
    ((S_80097898_0 *)object)->unk_9A = 0x39;
    ((S_80097898_0 *)object)->unk_9B = 0;
    ((S_80097898_0 *)object)->unk_8C = 0;
    if (!(func_800A6D30() & 3)) {
        ((S_80097898_1 *)saved)->unk_1C = (s32) (((S_80097898_1 *)saved)->unk_1C & ~0x620);
    }
    table = D_800DD294;
    (*(u8 **)((u8 *)saved2 + (0x2C))) = table;
    func_8003DB94(saved2, (*(s32 *)((u8 *)table + (((s32) (gameWork.view.viewAngle + ((S_80097898_1 *)saved)->unk_2A
        + 0x100) >> 7) & 0x1C))), 0);
}
