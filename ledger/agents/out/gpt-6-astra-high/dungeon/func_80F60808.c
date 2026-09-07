#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80083460[3];
extern s16 D_80083228[5];
s32 func_800A2BDC();                          /* extern */
M2C_UNK func_800A48F0();    /* extern */
s32 func_800A4ACC();                      /* extern */
extern u8 D_801741D4[8];

typedef struct S_80F60808_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_80F60808_0;   /* arg3 in func_80F60808 */

typedef struct S_80F60808_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80F60808_1;   /* arg0 in func_80F60808 */

typedef struct S_80F60808_2 {
    u8 pad_00[0x2C];
    M2C_UNK * unk_2C;
} S_80F60808_2;   /* arg2 in func_80F60808 */

/* Start the actor's directional animation and update its action state when allowed. */
void func_80F60808(S_80F60808_1 *action_state, void *unused, S_80F60808_2 *sprite, S_80F60808_0 *actor) {
    u16 *dungeon_state = (u16 *)D_80083460;
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(dungeon_state[1] & 0x2000) && ((func_800A2BDC(actor) << 0x10) == 0)) {
        action_state->unk_9A = 0xD;
        action_state->unk_8C = 0;
        action_state->unk_9B = 0;
        sprite->unk_2C = &D_801741D4;
        func_80047784(sprite, D_801741D4[(((s32) (*D_80083228 + actor->unk_2A + 0x100) >> 9) & 7)], 0);
        actor->unk_1C = (s32) (actor->unk_1C | 0x200);
        func_800A48F0(actor, 1, 4);
        actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
        func_800A4ACC(actor);
        actor->unk_6D = (u8) (actor->unk_6D - 1);
        dungeon_state[5] = (u16) (dungeon_state[5] + 1);
    }
}
