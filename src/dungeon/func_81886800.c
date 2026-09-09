#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80024064(void);
extern void func_800240C8(void);
extern void func_80024160(void);
extern void func_800243C8(void);
extern void func_80024640(void);
extern void func_8002467C(void);
extern void func_800247C8(void) __attribute__((noreturn));
extern void func_800246F0(void);
extern void func_80024790(void);
extern void func_8002485C(void);
extern void func_80024884(void);
extern void func_80024924(void);
extern void func_800249F4(void);
extern void func_80024AA8(void);

extern void func_800B835C(void *, void *, s32, s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(s32);
extern void func_80024DE8(void *, void *);
extern s32 set_item_w0(s32, s32, s32, s32);
extern void func_800A56E0(s32);
extern s32 func_800A45D8(s32, s32, s32);
extern void func_80065F90(s32, s32);
extern void *func_80024C80(void *, void *, s32);
extern void func_800262B8(void *, s32, void *);
extern void func_800241E8(void) __attribute__((noreturn));
extern void func_80024380(void) __attribute__((noreturn));
extern void func_8002477C(void) __attribute__((noreturn));

extern void *D_80024008[];
extern u8 D_80026324[];
extern u8 D_80026326[];
extern u8 D_80026328[];
extern u8 D_8002632A[];
extern u8 D_8002632C[];
extern u8 D_80045340[];
extern u8 D_80026344[];
extern u8 D_80026470[];
extern u8 D_80026474[];
extern u8 D_80026878[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_800DDC40[];
extern u8 D_800814A0[];
extern u8 D_8008346C[];

#ifdef __mips__
static void (*const func_81886800_table[])(void) __asm__("func_81886800")
    __attribute__((section(".text.func_81886800"), aligned(4))) = {
    func_80024064,
    0,
    func_800240C8,
    func_80024160,
    func_800243C8,
    func_80024640,
    func_8002467C,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800247C8,
    func_800246F0,
    func_80024790,
    func_8002485C,
    func_80024884,
    func_80024924,
    func_800249F4,
    func_80024AA8,
};
#define BODY_NAME func_81886864
#else
#define BODY_NAME func_81886864
#endif

void BODY_NAME(void *effect_in, void *motion_in, void *sprite_in)
    __attribute__((section(".text.func_81886800")));

/* Initialize and update a moving effect through targeting, collision, and fading states. */
void BODY_NAME(void *effect_in, void *motion_in, void *sprite_in)
{
#ifdef __mips__
    void *effect = effect_in;
    register void *motion ASM_REG("$17") = motion_in;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *sprite = sprite_in;
    register void *owner ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *owner_base;
    void *owner_motion;
#else
    void *effect = effect_in;
    void *motion = motion_in;
    void *sprite = sprite_in;
    void *owner;
    void *owner_base;
    void *owner_motion;
#endif
    s32 state;
    u32 valid_state;
    u16 owner_flags;
    s16 surface_pos[3];
    s32 texture_rect[2];
    static void *const state_labels[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_5, &&case_6, &&case_7, &&case_8, &&case_9,
        &&case_10, &&case_11, &&case_12, &&case_13, &&case_14,
        &&case_15, &&case_16, &&case_17,
    };

    owner = FIELD(effect, void *, 0);
    state = FIELD(effect, s16, 0xA);
    owner_base = (u8 *)owner - 0x20;
    valid_state = (u32)state < 18u;
    owner_motion = FIELD(owner_base, void *, 8);
    if (!valid_state) {
        goto end;
    }
    (void)state_labels;
    goto *D_80024008[state];

case_0:
    texture_rect[0] = 0x01000340;
    texture_rect[1] = 0x00200020;
    func_800B835C(D_8002632C, texture_rect, 1, 0);

    FIELD(sprite, u32, 0xC) = 0x00808080;
    FIELD(sprite, u16, 0x1E) = 0x555;
    FIELD(sprite, u16, 0x1C) = 0x555;
    FIELD(sprite, void *, 8) = D_80026344;
    FIELD(D_80026324, u16, 0) = 0;
    FIELD(D_80026328, u16, 0) = 0;
    FIELD(D_8002632A, u16, 0) = 0;
    FIELD(D_80026470, s32, 0) = 0;
    owner_flags = FIELD(owner, u16, 0x2A);
    FIELD(D_80026474, s32, 0) = 0;
    FIELD(effect, u16, 0x16) = (owner_flags >> 9) & 7;
    FIELD(effect, u16, 0xA)++;

    if (func_8003DF74(
            FIELD(FIELD(owner_base, void *, 0xC), void *, 8),
            FIELD(owner_base, void *, 0xC), surface_pos, 0) == 0) {
        if ((FIELD(FIELD(owner_base, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
            goto end;
        }
    }

    FIELD(motion, u16, 2) = FIELD(owner_motion, u16, 2);
    FIELD(motion, u16, 6) = FIELD(owner_motion, u16, 6);
    if (FIELD(FIELD(owner_base, void *, 0xC), u16, 0x14) & 0x8000) {
        {
            s32 start_height;

            start_height = FIELD(owner_motion, u16, 0xA) - 64;
            ASM_TAILSLOT_PIN(start_height);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            func_800241E8();
        }
    }
    FIELD(motion, u16, 0xA) = FIELD(owner_motion, u16, 0xA) + surface_pos[2];
    FIELD(effect, u16, 0x2E) = FIELD(motion, u16, 0xA);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    {
        void *effect_flags = FIELD(effect, void *, 4);
        if ((FIELD(effect_flags, u16, 0) & 0x80) == 0) {
            goto end;
        }
        if ((FIELD(effect, u8, 0x12) & 4) == 0) {
            func_8004491C((u8 *)effect - 0x20, D_80045340);
            FIELD(sprite, u16, 0x10) = 0x20;
            FIELD(sprite, u8, 0xE) = 0x80;
            FIELD(sprite, u8, 0xD) = 0x80;
            FIELD(sprite, u8, 0xC) = 0x80;
            FIELD(sprite, u16, 0x14) |= 0xC;
            FIELD(effect, u8, 0x12) |= 4;
        }
    }

    {
        if (FIELD(owner, void *, 0x60) == 0) {
            goto case_0_no_object;
        }
        {
            void *target_data;

            target_data =
                FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
            FIELD(effect, u16, 0xC) = FIELD(target_data, u16, 2);
            FIELD(effect, u16, 0xE) = FIELD(target_data, u16, 6);
            {
                u8 target_kind;
                u8 *height_offsets;

                height_offsets = D_800DDC40;
                target_kind = FIELD(FIELD(owner, void *, 0x60), u8, 0x13);
                FIELD(effect, u16, 0x10) =
                    FIELD(target_data, u16, 0xA) - height_offsets[target_kind];
            }
            {
                s16 direction;
                u8 tile_coord;
                direction = FIELD(effect, s16, 0x16);
                target_data = FIELD(owner, void *, -0x14);
                tile_coord = FIELD(target_data, u8, 0x24) +
                        D_8006CCD8[(s32)direction * 2];
                FIELD(effect, u8, 0x1E) = tile_coord;
                FIELD(effect, u8, 0x20) = tile_coord;
            }
            {
                s16 direction;
                u8 tile_coord;
                direction = FIELD(effect, s16, 0x16);
                tile_coord = FIELD(target_data, u8, 0x25) +
                        D_8006CCE8[(s32)direction * 2];
                FIELD(effect, u8, 0x1F) = tile_coord;
                FIELD(effect, u8, 0x21) = tile_coord;
            }
            {
#ifdef __mips__
                s32 owner_tile;
                register s32 target_tile ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#else
                s32 owner_tile;
                s32 target_tile;
#endif
                s32 tile_distance;
                owner_tile = FIELD(owner, s8, 0x72);
                target_tile = FIELD(target_data, u8, 0x24);
                if (owner_tile == target_tile) {
                    owner_tile = FIELD(owner, s8, 0x73);
                    target_tile = FIELD(target_data, u8, 0x25);
                    tile_distance = owner_tile - target_tile;
                } else {
                    tile_distance = owner_tile - target_tile;
                }
                if (tile_distance < 0) {
                    tile_distance = -tile_distance;
                }
                FIELD(effect, u16, 0x14) = tile_distance + 1;
            }
        }
    }
    func_80024380();

case_0_no_object:
    FIELD(effect, u16, 0x14) = 8;
    FIELD(effect, u16, 0xC) = FIELD(motion, u16, 2);
    FIELD(effect, u16, 0xE) = FIELD(motion, u16, 6);
    FIELD(effect, u16, 0x10) = FIELD(owner, u16, 0x88) - 80;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    {
        u8 *x_offsets = D_8006CCD8;
        s16 direction = FIELD(effect, s16, 0x16);
        FIELD(motion, u16, 0xE) =
            FIELD(x_offsets + (s32)direction * 2, s16, 0) * 8;
        {
            u8 *y_offsets = D_8006CCE8;
            s16 y_direction = FIELD(effect, s16, 0x16);
            FIELD(motion, u16, 0x12) =
                FIELD(y_offsets + (s32)y_direction * 2, s16, 0) * 8;
        }
    }
    func_8002477C();

case_1:
    {
#ifdef __mips__
        s32 x_step;
        register s32 x_velocity ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
#else
        s32 x_step;
        s32 x_velocity;
#endif
        x_step = FIELD(motion, s32, 0xC);
        x_velocity = x_step;
        FIELD(motion, s32, 0) += x_step;
        ASM_KEEP(x_step);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        x_velocity += x_velocity >> 4;
        FIELD(motion, s32, 0xC) = x_velocity;
        if ((x_velocity < 0 ? -x_velocity : x_velocity) > 0x200000) {
            x_velocity = x_velocity > 0 ? 0x200000 : -0x200000;
            FIELD(motion, s32, 0xC) = x_velocity;
        }
    }
    {
#ifdef __mips__
        s32 y_step;
        register s32 y_velocity ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
#else
        s32 y_step;
        s32 y_velocity;
#endif
        y_step = FIELD(motion, s32, 0x10);
        y_velocity = y_step;
        FIELD(motion, s32, 4) += y_step;
        ASM_KEEP(y_step);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        y_velocity += y_velocity >> 4;
        FIELD(motion, s32, 0x10) = y_velocity;
        if ((y_velocity < 0 ? -y_velocity : y_velocity) > 0x200000) {
            y_velocity = y_velocity > 0 ? 0x200000 : -0x200000;
            FIELD(motion, s32, 0x10) = y_velocity;
        }
    }
    {
        s32 height = FIELD(effect, s32, 0x2C);
        height += (((s32)FIELD(effect, s16, 0x10) << 16) - height) >> 4;
        FIELD(effect, s32, 0x2C) = height;
        height = FIELD(motion, s32, 8);
        height += (((s32)FIELD(effect, s16, 0x10) << 16) - height) >> 4;
        FIELD(motion, s32, 8) = height;
    }
    {
        s32 bob_offset = func_800644B8((s32)FIELD(effect, s16, 0x18) << 7);
        FIELD(motion, s32, 8) += bob_offset << 6;
    }
    func_80024DE8(motion, sprite);
    {
        s32 tile_coord = FIELD(motion, s16, 2);
        if (tile_coord < 0) {
            tile_coord += 63;
        }
        FIELD(effect, u8, 0x1E) = tile_coord >> 6;
        tile_coord = FIELD(motion, s16, 6);
        if (tile_coord < 0) {
            tile_coord += 63;
        }
        FIELD(effect, u8, 0x1F) = tile_coord >> 6;
    }
    if (FIELD(effect, s16, 0x20) == FIELD(effect, s16, 0x1E)) {
        goto end;
    }
    if (FIELD(owner, void *, 0x60) != 0) {
        if (FIELD(effect, s16, 0x58) == 0) {
            s32 target_distance = set_item_w0(
                FIELD(effect, volatile u8, 0x1E),
                FIELD(effect, volatile u8, 0x1F),
                FIELD(owner, volatile u8, 0x72),
                FIELD(owner, volatile u8, 0x73));
            target_distance = (s16)target_distance;
            if (target_distance < 5) {
                FIELD(effect, s16, 0x58) = 1;
                func_800A56E0(0x300);
            }
        }
    }
    if (FIELD(owner, void *, 0x60) != 0) {
        if ((FIELD(owner, volatile u32, 0x70) & 0xFFFF0000) ==
            (FIELD(effect, volatile u32, 0x1C) & 0xFFFF0000)) {
            void *snapped_motion;

            snapped_motion = motion;
            {
                s32 coordinate = FIELD(owner, s8, 0x72);
                FIELD(motion, s16, 2) = (coordinate << 6) + 0x20;
            }
            {
                s32 coordinate = FIELD(owner, s8, 0x73);
                FIELD(motion, s16, 6) = (coordinate << 6) + 0x20;
            }
            FIELD(motion, u16, 0xA) = FIELD(effect, u16, 0x10);
            func_80024DE8(snapped_motion, sprite);
            {
                u16 next_state = FIELD(effect, u16, 0xA);
                u16 target_id =
                    FIELD(FIELD(owner, void *, 0x60), u16, 0x88);
                next_state++;
                FIELD(effect, u16, 0xA) = next_state;
                FIELD(D_80026878, u16, 0) = target_id;
            }
            func_800247C8();
        }
    }

case_1_continue:
    {
        u8 x = FIELD(effect, u8, 0x1E);
        u8 y = FIELD(effect, u8, 0x1F);
        s32 timer = FIELD(effect, u16, 0x14) - 1;
        s32 collision;
        FIELD(effect, u16, 0x14) = timer;
        FIELD(effect, u8, 0x20) = x;
        FIELD(effect, u8, 0x21) = y;
        if ((timer << 16) != 0) {
            s32 world_x = (((s32)FIELD(effect, s8, 0x1E) << 6) + 0x20) & 0xFFE0;
            s32 world_y = (((s32)FIELD(effect, s8, 0x1F) << 6) + 0x20) & 0xFFE0;
            collision = func_800A45D8(world_x, world_y, FIELD(effect, s16, 0x2E));
            if ((collision << 16) == 0) {
                goto end;
            }
        }
        FIELD(effect, u16, 0xA) = 16;
        func_800247C8();
    }

case_2:
    func_80065F90(FIELD(motion, s16, 0xE), FIELD(motion, s16, 0x12));
    {
#ifdef __mips__
        register void *target_object ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#else
        void *target_object;
#endif
        FIELD(effect, void *, 0x28) = func_80024C80(
            effect, motion, (target_object = FIELD(owner, void *, 0x60),
                            FIELD(target_object, s16, 0x88)));
        if (FIELD(effect, void *, 0x28) == 0) {
            goto end;
        }
        FIELD(effect, u16, 0xA)++;
        FIELD(sprite, u8, 0xC) -= FIELD(sprite, u8, 0xC) >> 2;
        FIELD(sprite, u8, 0xD) -= FIELD(sprite, u8, 0xD) >> 2;
        FIELD(sprite, u8, 0xE) -= FIELD(sprite, u8, 0xE) >> 2;
        if ((FIELD(FIELD(effect, void *, 0x28), u16, 0x1E) & 0x8000) == 0) {
            goto end;
        }
        if (FIELD(owner, void *, 0x60) != 0) {
            func_800262B8(FIELD(owner, void *, 0x60),
                          FIELD(effect, u8, 9), owner);
        }
        FIELD(effect, u16, 0xA) = 17;
        func_800247C8();
    }

case_3:
    {
#ifdef __mips__
        register void *moving_motion ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
#else
        void *moving_motion;
#endif
        moving_motion = motion;
        FIELD(moving_motion, s32, 0) += FIELD(moving_motion, s32, 0xC);
        FIELD(moving_motion, s32, 4) += FIELD(moving_motion, s32, 0x10);
        {
            s32 target_height = (s32)FIELD(effect, s16, 0x10) << 16;
            s32 height = FIELD(moving_motion, s32, 8);
            height += (target_height - height) >> 4;
            FIELD(moving_motion, s32, 8) = height;
        }
        FIELD(sprite, u8, 0xC) -= FIELD(sprite, u8, 0xC) >> 1;
        FIELD(sprite, u8, 0xD) -= FIELD(sprite, u8, 0xD) >> 1;
        FIELD(sprite, u8, 0xE) -= FIELD(sprite, u8, 0xE) >> 1;
        func_80024DE8(moving_motion, sprite);
        if (FIELD(sprite, u8, 0xC) < 2) {
            FIELD(effect, u16, 0xA)++;
            func_800247C8();
        } else {
            goto end;
        }
    }

case_4:
    if (FIELD(D_80026326, s16, 0) != 0) {
        goto end;
    }
    FIELD(D_8008346C, s32, 0) = 0;
    FIELD((u8 *)effect - 2, u16, 0) |= 0x8000;
    FIELD(D_800814A0, s32, 0) |= 0x8000;

case_5:
case_6:
case_7:
case_8:
case_9:
case_10:
case_11:
case_12:
case_13:
case_14:
case_15:
case_16:
case_17:
end:
    {
        u16 frame_count = FIELD(effect, u16, 0x18);
        FIELD(D_80026326, u16, 0) = 0;
        FIELD(effect, u16, 0x18) = frame_count + 1;
    }
}

#ifdef __mips__
__asm__(
    ".globl func_81886800\n"
    ".type func_81886800,@function\n"
    ".size func_81886800,2052\n");
#endif
