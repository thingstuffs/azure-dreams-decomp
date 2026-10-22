#ifndef MODULE_DUNGEON_OVL_51E800_H
#define MODULE_DUNGEON_OVL_51E800_H

#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_804FE87C_0 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    s16 unk_42;
    s16 unk_44;
    s16 unk_46;
    s16 unk_48;
    u8 pad_4A[0xE];
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    s16 unk_62;
    s16 unk_64;
    s16 unk_66;
    s16 unk_68;
    u8 pad_6A[0xE];
    s32 unk_78;
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    s32 unk_88;
} S_804FE87C_0;   /* state in func_8001607C */


extern void func_80064F20(s32);
extern void func_80064EE0(s32, s32, s32);
extern void func_80064D50(void *);
extern void func_80064D20(void *);
extern void func_80064624(s32, s32);
extern void func_80064EC0(s32, s32, s32);
extern void func_80064F00(s32, s32);

extern u8 monster_spawn_records[];
extern u8 upper_draw_context[0x1C];
extern u8 lower_draw_context[0x1C];

static __inline__ void set_light_vectors(S_804FE87C_0 *state, s16 x, s16 y) {
    state->unk_38 = x;
    state->unk_3A = y;
    state->unk_3C = x;
    state->unk_3E = -x;
    state->unk_40 = -y;
    state->unk_42 = -x;
    state->unk_44 = 0;
    state->unk_46 = 0;
    state->unk_48 = 0;
}

/* Initializes lighting, projection, and viewport state and selects the floor monster table. */
#endif
