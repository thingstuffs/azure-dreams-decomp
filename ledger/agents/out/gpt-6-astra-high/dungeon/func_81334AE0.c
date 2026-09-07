#include "common.h"

extern u16 D_80083462[5];
s32 func_8009C93C(void *arg0, s32 arg1, s16 arg2, s32 arg3, s32 arg4);
s16 func_800A2B5C(void *arg0);
s32 func_800C7930(void *arg0, s32 arg1, s32 arg2, s32 arg3);

/* Clear the entity flag and advance its action when both checks pass. */
void func_8016BAE0(void *action_state, s32 check_arg, s32 action_arg, void *entity) {
    *(u8 *)((s8 *)entity + 0x71) &= 0x7F;
    if (!(*D_80083462 & 0x2000) && ((func_800A2B5C(entity) << 0x10) == 0)) {
        func_800C7930((s8 *)entity - 0x20, check_arg, 8, 0x300);
        if ((func_800A2B5C(entity) << 0x10) == 0) {
            *(s32 *)((s8 *)action_state + 0x8C) = 0;
            *(s8 *)((s8 *)action_state + 0x9A) = 0x11;
            *(s8 *)((s8 *)action_state + 0x9B) = 0;
            *(u8 *)((s8 *)entity + 0x6D) = *(u8 *)((s8 *)entity + 0x6D) - 1;
            func_8009C93C(entity, action_arg, *(s16 *)((s8 *)entity + 0x2A), 1, 0);
            *(u8 *)((s8 *)entity + 0x84) = 0x80;
            *(u8 *)((s8 *)entity + 0x85) = 0x20;
        }
    }
}

