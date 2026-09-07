#include "common.h"

#if !defined(NON_MATCHING) && __GNUC__ < 3
#define LEGACY_ASM_KEEP(value) \
    ASM_KEEP(value)
#else
#define LEGACY_ASM_KEEP(value) ASM_KEEP(value)
#endif

extern void func_80047784(void *, s32, s32);
extern void func_80099EA4(void *);
extern void func_800A4ACC(void *);

extern s16 D_80083228[];
extern u8 D_80083460[];
extern u8 D_801755B4[];
extern u8 D_80175660[];

/* Starts a direction-based action when the object's state and global flags allow it. */
void func_80174FE4(void *action_state, void *unused, void *animation, void *object)
{
    register u8 *state_data ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *data_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *direction_table;
    s32 direction_index;

    state_data = D_80175660;
    *(u16 *)(state_data + 0x6C) = *(u16 *)((u8 *)object + 0x6C);
    *(u16 *)(state_data + 0x6E) = *(u16 *)((u8 *)object + 0x6E);
    func_80099EA4(state_data);

    if (*(s8 *)(state_data + 0x6D) != 0) {
        *(u8 *)((u8 *)object + 0x71) &= 0x7F;
        ASM_USE(state_data);   /* MATCH pin: retail basic-block layout depends on it */
        data_page = (u8 *)0x80080000;
        LEGACY_ASM_KEEP(data_page);
        state_data = data_page + 0x3460;
        if (!(*(u16 *)(state_data + 2) & 0x2000)) {
            direction_table = D_801755B4;
            *(s8 *)((u8 *)action_state + 0x9A) = 0x17;
            *(s32 *)((u8 *)action_state + 0x8C) = 0;
            *(s8 *)((u8 *)action_state + 0x9B) = 0;
            *(s16 *)((u8 *)action_state + 0x96) = 0;

            *(u8 **)((u8 *)animation + 0x2C) = direction_table;
            direction_index = (D_80083228[0] + *(s16 *)((u8 *)object + 0x2A) + 0x100) >> 9;
            func_80047784(animation, direction_table[direction_index & 7], 0);
            func_800A4ACC(object);
            *(u8 *)((u8 *)object + 0x6D) -= 1;
            *(u16 *)(state_data + 0xA) += 1;
        }
    }
}
