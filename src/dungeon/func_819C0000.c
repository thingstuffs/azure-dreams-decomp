#include "common.h"

typedef struct {
    u16 x;
    u16 y;
} LocalPoint;

typedef struct {
    LocalPoint point[3][3];
} LocalPoints;

typedef struct {
    s32 value;
} __attribute__((packed)) PackedWord;

typedef struct {
    u8 bytes[16];
} __attribute__((packed)) Packed16;

typedef struct {
    s32 words[4];
} Aligned16;

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define VU16_AT(p, o) (*(volatile u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))
#define PACKED_AT(p, o) (((PackedWord *)((u8 *)(p) + (o)))->value)

extern void func_80025648(void *, s32, s32, s32, s32);
extern void func_80025710(void *, u32, u32, s32, s32);
extern void func_80025FB0(void *, s32);
extern void func_80026060(void *, void *, s32, s32);
extern void func_8002612C(void *, s32);

extern LocalPoints D_80024004;
extern s32 D_80028630;
extern s16 D_8002992C;
extern s16 D_8002992E[5];
extern s32 D_800814A0;
extern u8 *D_800814A8;

/* Updates an owner-following effect or its fade, wait, and rising phases. */
void func_80025800(void *effect_in, void *position_in, void *visual_in)
{
    LocalPoints offsets;
    register u8 *copy_src ASM_REG("$6");
    register u8 *source_page ASM_REG("$2");
    register u8 *copy_dst ASM_REG("$7");
    u8 *copy_end;
    u8 *owner;
    u8 *owner_pos;
    u8 *owner_visual;
    u8 *world;
    s32 word_0;
    s32 word_1;
    s32 word_2;
    s32 word_3;
    s32 fade;
    s32 half_tile;
    u16 flags;
    s32 state;
    s32 rise_speed;
    u32 misalignment;
    s16 column;
    s16 row;
    s16 next_tick;
    s32 move_ticks;
    s32 anim_ticks;
    LocalPoint *point;

    copy_dst = (u8 *)&offsets;
#ifdef NON_MATCHING
    copy_src = (u8 *)&D_80024004;
#else
    source_page = (u8 *)0x80020000;
    ASM_KEEP_NV(source_page);
    copy_src = source_page + 0x4004;
#endif
    ASM_KEEP_NV(copy_src);
    misalignment = (u32)copy_src & 3;
    if (misalignment) {
        copy_end = copy_src + 0x20;
        do {
            word_0 = PACKED_AT(copy_src, 0);
            word_1 = PACKED_AT(copy_src, 4);
            word_2 = PACKED_AT(copy_src, 8);
            word_3 = PACKED_AT(copy_src, 0xC);
            PACKED_AT(copy_dst, 0) = word_0;
            PACKED_AT(copy_dst, 4) = word_1;
            PACKED_AT(copy_dst, 8) = word_2;
            PACKED_AT(copy_dst, 0xC) = word_3;
            ASM_SCHED_BARRIER();
            copy_src += 0x10;
            copy_dst += 0x10;
        } while (copy_src != copy_end);
    } else {
        copy_end = copy_src + 0x20;
        do {
            word_0 = S32_AT(copy_src, 0);
            word_1 = S32_AT(copy_src, 4);
            word_2 = S32_AT(copy_src, 8);
            word_3 = S32_AT(copy_src, 0xC);
            S32_AT(copy_dst, 0) = word_0;
            S32_AT(copy_dst, 4) = word_1;
            S32_AT(copy_dst, 8) = word_2;
            S32_AT(copy_dst, 0xC) = word_3;
            ASM_SCHED_BARRIER();
            copy_src += 0x10;
            copy_dst += 0x10;
        } while (copy_src != copy_end);
    }
    PACKED_AT(copy_dst, 0) = PACKED_AT(copy_src, 0);
    ASM_SCHED_BARRIER();

    D_8002992E[0] = 1;
    half_tile = 0x20;
    S16_AT(visual_in, 0x10) = half_tile;
    U16_AT(visual_in, 0x14) |= 0xC;
    owner = PTR_AT(effect_in, 0x20);
    world = D_800814A8;

    if (owner == 0) {
        state = S16_AT(effect_in, 0x2C);
        if (state == 1) {
            goto state_one;
        }
        if (state < 2) {
            if (state == 0) {
                goto state_zero;
            }
            goto function_done;
        }

        if (state == 2) {
            goto state_two;
        }
        goto function_done;

state_zero:
        move_ticks = U16_AT(effect_in, 0x30);
        anim_ticks = U16_AT(effect_in, 0x32);
        move_ticks--;
        anim_ticks++;
        VU16_AT(effect_in, 0x32) = anim_ticks;
        anim_ticks = (anim_ticks << 16) >> 16;
        VU16_AT(effect_in, 0x30) = move_ticks;
        if (anim_ticks < 0x19) {
            fade = anim_ticks << 8;
            U16_AT(visual_in, 0x20) = fade;
            U16_AT(visual_in, 0x1E) = fade;
            U16_AT(visual_in, 0x1C) = fade;
            S16_AT(effect_in, 0x3A) = 0;
            S16_AT(effect_in, 0x38) = 1;
            S16_AT(effect_in, 0x34) = 1;
            func_80026060(visual_in, (u8 *)effect_in + 0x34,
                          S16_AT(effect_in, 0x3A), S16_AT(effect_in, 0x38));
            func_80025FB0(effect_in, S32_AT(visual_in, 0));
            goto function_done;
        }
        U16_AT(effect_in, 0x30) = 0;
        U16_AT(effect_in, 0x32) = 0;
        U16_AT(effect_in, 0x2C) = U16_AT(effect_in, 0x2C) + 1;
        goto function_done;

state_one:
        next_tick = U16_AT(effect_in, 0x32) + 1;
        U16_AT(effect_in, 0x32) = next_tick;
        if (next_tick & 1) {
            S16_AT(effect_in, 0x3A) = state;
            S16_AT(effect_in, 0x38) = 0xF;
            S16_AT(effect_in, 0x34) = state;
            func_80026060(visual_in, (u8 *)effect_in + 0x34,
                          S16_AT(effect_in, 0x3A), S16_AT(effect_in, 0x38));
            func_80025FB0(effect_in, S32_AT(visual_in, 0));
        }
        if (S16_AT(D_800814A8, 0x96) == 0) {
            U16_AT(effect_in, 0x30) = 0;
            S32_AT(effect_in, 0x50) = 0x200000;
            S32_AT(effect_in, 0x5C) = 0;
            U16_AT(effect_in, 0x2C) = U16_AT(effect_in, 0x2C) + 1;
            goto function_done;
        }
        goto state_done;

state_two:
        {
            s32 base_x;
            s16 base_y;
            s32 pos_x;
            s32 pos_y;
            register s32 biased_x ASM_REG("$4");
            s32 biased_y;

            S32_AT(position_in, 0x14) = S32_AT(position_in, 8);
            rise_speed = S32_AT(effect_in, 0x50) + S32_AT(effect_in, 0x5C);
            S32_AT(effect_in, 0x50) = rise_speed;
            S32_AT(position_in, 8) += rise_speed;
            pos_x = S16_AT(position_in, 2);
            biased_x = pos_x - 0x20;
            if (biased_x < 0) {
                biased_x = pos_x + 0x1F;
            }
            pos_y = S16_AT(position_in, 6);
            biased_y = pos_y - 0x20;
            if (biased_y < 0) {
                biased_y = pos_y + 0x1F;
            }
            base_x = (u32)biased_x >> 6;
            base_y = (u32)biased_y >> 6;

            column = 0;
            do {
                row = 0;
                do {
                    s32 point_offset;
                    s32 offset_x;
                    register u32 tile_x ASM_REG("$5");
                    register u16 tile_y ASM_REG("$6");
                    point_offset = column * sizeof(LocalPoint) +
                                   row * 3 * sizeof(LocalPoint);
                    point = (LocalPoint *)((u8 *)&offsets + point_offset);
                    ASM_KEEP_NV(point);
                    tile_x = point->x;
                    tile_y = point->y;
                    tile_x = (base_x + tile_x) & 0xFFFF;
                    tile_y = base_y + tile_y;
                    func_80025710(world,
                                  tile_x,
                                  tile_y,
                                  S16_AT(position_in, 0xA),
                                  (s16)(U16_AT(position_in, 0xA) - 0x40));
                    offset_x = S16_AT(point, 0);
                    func_80025648((u8 *)effect_in - 0x20,
                                  (s16)(U16_AT(position_in, 2) + (offset_x << 6)),
                                  (s16)(U16_AT(position_in, 6) + ((s32)(point->y << 16) >> 10)),
                                  S16_AT(position_in, 0xA), S16_AT(position_in, 0x16));
                    row++;
                } while (row < 3);
                column++;
            } while (column < 3);

            next_tick = U16_AT(effect_in, 0x30) + 1;
            U16_AT(effect_in, 0x30) = next_tick;
            if (next_tick >= 0x28) {
                D_8002992C = 0;
                D_80028630 = 0;
                goto object_dead;
            }
        }
state_done:
        ;
    } else {
        if (U16_AT(owner, 0x1E) & 0x8000) {
object_dead:
            U16_AT(effect_in, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
            goto function_done;
        }

        owner_pos = PTR_AT(owner, 8);
        S16_AT(position_in, 2) = U16_AT(owner_pos, 2);
        S16_AT(position_in, 6) = U16_AT(owner_pos, 6);
        S16_AT(position_in, 0xA) = U16_AT(owner_pos, 0xA);
        owner = PTR_AT(effect_in, 0x20);
        flags = U16_AT(visual_in, 0x14);
        owner_visual = PTR_AT(owner, 0xC);
        flags |= 0xC;
        U16_AT(visual_in, 0x14) = flags;
        S16_AT(visual_in, 0x10) = half_tile;
        func_8002612C(visual_in, S8_AT(owner_visual, 4));
        func_80025FB0(effect_in, S32_AT(visual_in, 0));
        U16_AT(visual_in, 0x1C) = U16_AT(owner_visual, 0x1C);
        U16_AT(visual_in, 0x1E) = U16_AT(owner_visual, 0x1E);
        U16_AT(visual_in, 0x20) = U16_AT(owner_visual, 0x20);
        S32_AT(visual_in, 0xC) = S32_AT(owner_visual, 0xC);
        U16_AT(visual_in, 0x16) = U16_AT(owner_visual, 0x16);
        U16_AT(visual_in, 0x18) = U16_AT(owner_visual, 0x18);
        U16_AT(visual_in, 0x1A) = U16_AT(owner_visual, 0x1A);
    }
function_done:
    ;
}
