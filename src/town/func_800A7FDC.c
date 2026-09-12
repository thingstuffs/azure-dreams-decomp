#include "common.h"

extern u8 D_80083160[];
extern s32 D_800A5A98;
extern s16 D_800D01F8[];
extern u8 D_80100D98[];

extern void func_800489F4(void *, u8, s8, s32);
extern void func_80048AC8(void *, s32);
extern s16 func_80094AA0(s32, s32, s32);
extern s32 func_80095360(s16);
extern void func_80095544(void *);
extern void func_800A48B0(void *, void *);

/* Turn the entity toward its target angle and update its directional sprite. */
void func_800A573C(void *entity, void *transform, void *sprite) {
    u8 *input_state;
    void *transform_arg;
    s32 direction;
    s32 current_angle;
    s32 target_angle;
    s32 turn_step;

    transform_arg = transform;
    input_state = D_80083160;
    func_80095544(transform_arg);
    {
        void *entity_type;

        entity_type = *(void **)entity;
        if (entity_type == (u8 *)&D_800A5A98 && (*(s32 *)(input_state + 8) & 0x2000)) {
            target_angle = *(s16 *)((u8 *)entity + 0x10);
            current_angle = *(s16 *)((u8 *)entity + 0x18);
            target_angle -= 0x200;
            turn_step = 0x200;
        } else if (entity_type == (u8 *)&D_800A5A98 && (*(s32 *)(input_state + 8) & 0x8000)) {
            target_angle = *(s16 *)((u8 *)entity + 0x10);
            current_angle = *(s16 *)((u8 *)entity + 0x18);
            target_angle += 0x200;
            turn_step = 0x200;
        } else {
            current_angle = *(s16 *)((u8 *)entity + 0x18);
            target_angle = *(s16 *)((u8 *)entity + 0x10);
            ASM_CLOBBER("$6");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            turn_step = 0x200;
        }
    }
    {
        s16 next_angle;

        next_angle = func_80094AA0(current_angle, target_angle, turn_step);
        *(s16 *)((u8 *)entity + 0x18) = next_angle;
    }
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    direction = func_80095360(*(s16 *)((u8 *)entity + 0x18));
    if (*(s16 *)((u8 *)entity + 0x12) != direction) {
        func_800489F4(sprite,
                      *(u8 *)(*(u8 **)((u8 *)entity + 0x1C) + direction),
                      *(s8 *)((u8 *)sprite + 4), 0);
        *(s16 *)((u8 *)entity + 0x12) = direction;
    }
    {
        s16 *flip_table = D_800D01F8;
        u16 sprite_flags;

        if (flip_table[direction] != 0) {
            *(u16 *)((u8 *)sprite + 0x14) |= 1;
        } else {
            *(u16 *)((u8 *)sprite + 0x14) &= 0xFFFE;
        }
    }
    func_80048AC8(sprite, 0);
    {
        u8 *render_state = D_80100D98;

        func_800A48B0(render_state, transform);
        *(s32 *)(render_state + 8) = 0;
    }
}
