#include "common.h"

extern s32 func_800A2B5C(void *);
extern void func_800C7930(void *, s32, s32, s32);
extern void func_80047784(void *, u8, s32);
extern void func_800A4ACC(void *);

extern s16 D_80083228[];
extern u16 D_80083462[];
extern u8 D_80175F30[];

/* Initialize the entity's action state and directional animation when allowed. */
s32 func_801723D8(void *state_ptr, s32 action_arg, void *sprite_ptr, void *entity_ptr) {
    u8 *state = state_ptr;
    u8 *sprite = sprite_ptr;
    u8 *entity = entity_ptr;

    entity[0x71] &= 0x7F;
    if (!(D_80083462[0] & 0x2000)) {
        if ((*(u16 *)(entity + 0x46) & 0x8000) || !(D_80083462[0] & 8)) {
            if ((func_800A2B5C(entity) << 16) == 0) {
                func_800C7930(entity - 0x20, action_arg, 8, 0x300);
                if ((func_800A2B5C(entity) << 16) == 0) {
                    state[0x9A] = 0x18;
                    state[0x9B] = 0;
                    *(s32 *)(state + 0x8C) = 0;
                    *(u8 **)(sprite + 0x2C) = D_80175F30;
                    func_80047784(sprite, D_80175F30[((D_80083228[0] + *(s16 *)(entity + 0x2A) + 0x100) >> 9) & 7], 0);
                    func_800A4ACC(entity);
                    entity[0x6D]--;
                    return 0;
                }
            }
        }
    }
    return -1;
}
