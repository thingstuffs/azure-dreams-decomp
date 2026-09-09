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
    u8 *input_page;
    register void *transform_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 direction;
    s32 current_angle;
    s32 target_angle;
    s32 turn_step;

    transform_arg = transform;
    input_page = (u8 *)0x80080000;
    ASM_KEEP_NV(input_page);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    input_state = input_page + 0x3160;
    func_80095544(transform_arg);
    ASM_KEEP_NV(input_state);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    {
        u8 *player_type;
        void *entity_type;

        player_type = (u8 *)0x800A0000;
        ASM_KEEP_NV(player_type);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        entity_type = *(void **)entity;
        player_type += 0x5A98;
        if (entity_type == player_type && (*(s32 *)(input_state + 8) & 0x2000)) {
            target_angle = *(s16 *)((u8 *)entity + 0x10);
            current_angle = *(s16 *)((u8 *)entity + 0x18);
            target_angle -= 0x200;
            turn_step = 0x200;
        } else if (entity_type == player_type && (*(s32 *)(input_state + 8) & 0x8000)) {
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

        ASM_USE(flip_table);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        if (flip_table[direction] != 0) {
            sprite_flags = *(u16 *)((u8 *)sprite + 0x14) | 1;
        } else {
            sprite_flags = *(u16 *)((u8 *)sprite + 0x14) & 0xFFFE;
        }
        *(u16 *)((u8 *)sprite + 0x14) = sprite_flags;
    }
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    func_80048AC8(sprite, 0);
    {
        u8 *render_state = D_80100D98;

        ASM_KEEP(render_state);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        func_800A48B0(render_state, transform);
        *(s32 *)(render_state + 8) = 0;
    }
}
