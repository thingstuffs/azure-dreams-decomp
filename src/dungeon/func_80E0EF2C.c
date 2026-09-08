#include "common.h"

extern void func_80047784();
extern s32 func_800A2B5C();
extern void func_800A4ACC();
extern void func_800C7930();
extern s16 D_80083208[16];
extern u16 D_80083460[4];
extern u8 D_8014A000[200000];
#define D_801764A0_OFF 0x2C4A0

/* Update action state and select a direction-specific sprite when the actor is ready. */
void func_8017272C(void *action_state, s32 action_param, void *sprite, void *actor) {
    u8 *frame_table;
    s32 direction;

    *((u8 *)actor + 0x71) = (u8)(*((u8 *)actor + 0x71) & 0x7F);
    if (!(*(u16 *)((u8 *)D_80083460 + 2) & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        {
            void *actor_base = (u8 *)actor - 0x20;
            func_800C7930(actor_base, action_param, 8, 0x300);
        }
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            *((s8 *)action_state + 0x9A) = 0x17;
            *(s32 *)((u8 *)action_state + 0x8C) = 0;
            *((s8 *)action_state + 0x9B) = 0;
            frame_table = &D_8014A000[D_801764A0_OFF];
            *(void **)((u8 *)sprite + 0x2C) = frame_table;
            direction = ((*(s16 *)((u8 *)D_80083208 + 0x20) + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7;
            func_80047784(sprite, frame_table[direction], 0);
            func_800A4ACC(actor);
            *((u8 *)actor + 0x6D) = (u8)(*((u8 *)actor + 0x6D) - 1);
            *(u16 *)((u8 *)action_state + 0x98) = (u16)(*(u16 *)((u8 *)action_state + 0x98) | 8);
        }
    }
}
