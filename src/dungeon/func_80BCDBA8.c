#include "common.h"
#include "records/Rec_D_80082E80.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s16 func_800BCB04();

extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_801659DC;
extern u8 D_80168634[8];
extern u8 D_80168644[8];
extern u8 D_80168654[8];
extern u8 D_8016865C[8];
extern u8 D_80168664[8];
extern u8 D_8016866C[8];
extern Callback D_801686A0[];


typedef struct S_801653A8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801653A8_0;   /* arg1 in func_801653A8 */


typedef struct S_801653A8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_801653A8_2;   /* base in func_801653A8 */

/* Runs entity callbacks and updates motion, directional animation, and ground height. */
void func_801653A8(void *entity, S_801653A8_0 *motion, void *sprite)
{
    register void *entity_base ASM_REG("$19") = entity;
    register s16 old_state ASM_REG("$16");
    register u8 state_byte ASM_REG("$2");
    void *check_entity;
    void *check_motion;
    void *check_sprite;
    s32 height_offset;
    register u32 height_bits ASM_REG("$3");
    s16 direction;
    s16 ground_height;
    s32 entity_flags;
    register s32 height_adjust;
    u16 initial_sprite_flags;
    u16 sprite_flags;
    s32 height_sum;
    register u16 height_flags ASM_REG("$4");

    if (D_80083462 & 0x2000) {
        void *callback_entity = entity;
        Callback entry_callback;

        entry_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (entry_callback == (Callback)&D_801659DC) {
            ASM_KEEP(callback_entity);
            entry_callback(callback_entity, motion, sprite, callback_entity);
            return;
        }
        (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        return;
    }

    check_entity = entity;
    check_motion = motion;
    check_sprite = sprite;
    ASM_KEEP4(check_entity, check_motion, check_sprite, entity_base);
    state_byte = (*(u8 *)((u8 *)entity + 0x6D));
    old_state = (s8)state_byte;
    if (func_800A9E70(check_entity, check_motion, check_sprite, entity) != 0) {
        return;
    }

    {
        Callback update_callback = (*(Callback *)((u8 *)entity + 0x8C));

        if (update_callback != 0) {
            update_callback(entity, motion, sprite, entity);
        }
    }
    D_801686A0[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, sprite, entity);
    {
        register s32 previous_state ASM_REG("$2");

        previous_state = (u32)(u16)old_state << 16;
        ASM_KEEP_NV(previous_state);
        previous_state >>= 16;
        if (previous_state != (*(s8 *)((u8 *)entity + 0x6D))) {
            func_800AA36C(entity, motion, sprite, entity);
        }
    }

    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if (!((*(s32 *)((u8 *)entity + 0x1C)) & 0x40000) &&
        !((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
        motion->unk_14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity + 0x9D))++;
    } else {
        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
    }
    (*(s32 *)((u8 *)entity + 0x90)) += motion->unk_14;
    initial_sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;

    if (!(initial_sprite_flags & 0x8000)) {
        direction = ((D_80083228 + ((S_801653A8_2 *)entity_base)->unk_2A + 0x100) >> 9) & 7;
        if ((*(s16 *)((u8 *)entity + 0x94)) != direction) {
            func_80047738(sprite,
                *(u8 *)(((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 + direction),
                ((Rec_D_80082E80 *)sprite)->unk_04.as_s8);
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }
        if (D_8006CCF8[direction] != 0) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 1;
        } else {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xFFFE;
        }
        func_800A020C(((S_801653A8_2 *)entity_base)->unk_1C, (u8 *)sprite + 0xC);
        if (!(((S_801653A8_2 *)entity_base)->unk_1C & 0x20)) {
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
                func_800478B8(sprite);
            }
        } else {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x7000;
            ((S_801653A8_2 *)entity_base)->unk_1C &= 0xFFFBFFFF;
        }

        ((S_801653A8_2 *)entity_base)->unk_1C &= 0xF7FFFFFF;
        entity_flags = ((S_801653A8_2 *)entity_base)->unk_1C;
        if (entity_flags & 0x40000) {
            sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
            if (!(sprite_flags & 0x40)) {
                u8 *direction_frames = ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8;

                if (direction_frames == D_80168634) {
                    if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 3 && (sprite_flags & 0x1000)) {
                        (*(s32 *)((u8 *)entity + 0xAC)) = 0x60000;
                        (*(s32 *)((u8 *)entity + 0xB0)) = (s32)0xFFFF3000;
                    }
                    (*(s32 *)((u8 *)entity + 0xA4)) += (*(s32 *)((u8 *)entity + 0xAC));
                    (*(s32 *)((u8 *)entity + 0xAC)) += (*(s32 *)((u8 *)entity + 0xB0));
                    if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                        goto adjust_normal;
                    }
                } else if (direction_frames == D_80168644 || direction_frames == D_8016866C) {
                    (*(s32 *)((u8 *)entity + 0xA4)) -= 0x40000;
                    if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                        goto adjust_normal;
                    }
                } else if (direction_frames != D_80168654 && direction_frames != D_8016865C &&
                           direction_frames != D_80168664) {
                    (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                }
            }

adjust_normal:
            height_adjust = (*(u16 *)((u8 *)entity + 0x98)) & 8;
            if (height_adjust == 0) {
                height_offset = (*(s16 *)((u8 *)entity + 0x92));
                height_bits = (*(u16 *)((u8 *)entity + 0x92));
                if (height_adjust < height_offset) {
                    height_adjust = height_bits - 8;
                    ASM_SCHED_BARRIER();
                    (*(s16 *)((u8 *)entity + 0x92)) = height_adjust;
                    goto finish_motion;
                }
                goto adjust_positive;
            }
            goto finish_motion;
        }

        {
            height_adjust = (*(s32 *)((u8 *)entity + 0xA4));
            height_sum = (*(s32 *)((u8 *)entity + 0x90));
            height_flags = (*(u16 *)((u8 *)entity + 0x98));
            (*(s16 *)((u8 *)entity + 0xB8)) = 0;
            (*(s32 *)((u8 *)entity + 0xA4)) = 0;
            height_sum += height_adjust;
            goto apply_tail_sum;
        }
    }

    if (initial_sprite_flags & 0x800) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = initial_sprite_flags & 0x8FFF;
    } else {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = initial_sprite_flags | 0x7000;
    }
    ((S_801653A8_2 *)entity_base)->unk_1C &= 0xF7FFFFFF;
    entity_flags = ((S_801653A8_2 *)entity_base)->unk_1C;

    if (!(entity_flags & 0x40000)) {
        height_adjust = (*(s32 *)((u8 *)entity + 0xA4));
        height_sum = (*(s32 *)((u8 *)entity + 0x90));
        height_flags = (*(u16 *)((u8 *)entity + 0x98));
        (*(s16 *)((u8 *)entity + 0xB8)) = 0;
        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
        height_sum -= height_adjust;
apply_tail_sum:
        (*(s32 *)((u8 *)entity + 0x90)) = height_sum;
        if (!(height_flags & 8)) {
            ground_height = func_800BCB04(motion->unk_00.at02.v,
                                  motion->unk_04.at02.v,
                                  (s16)(((S_801653A8_2 *)entity_base)->unk_88 - 0x20)) -
                    ((S_801653A8_2 *)entity_base)->unk_88;
            if (ground_height < (*(s16 *)((u8 *)entity + 0x92))) {
                (*(s16 *)((u8 *)entity + 0x92)) = ground_height;
                (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                motion->unk_14 = 0;
                ((S_801653A8_2 *)entity_base)->unk_1C |= 0x08000000;
                goto finish_motion;
            }
        }
        goto finish_motion;
    }

    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
        u8 *direction_frames = ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8;

        if (direction_frames == D_80168634) {
            (*(s32 *)((u8 *)entity + 0xAC)) = 0;
            goto clear_offset;
        }
        if (direction_frames == D_80168644 || direction_frames == D_8016866C) {
            (*(s32 *)((u8 *)entity + 0xA4)) -= 0x40000;
            if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                goto adjust_special;
            }
        } else if (direction_frames != D_80168654 && direction_frames != D_8016865C &&
                   direction_frames != D_80168664) {
clear_offset:
            (*(s32 *)((u8 *)entity + 0xA4)) = 0;
        }
    }

adjust_special:
    height_adjust = (*(u16 *)((u8 *)entity + 0x98)) & 8;
    if (height_adjust == 0) {
        height_offset = (*(s16 *)((u8 *)entity + 0x92));
        height_bits = (*(u16 *)((u8 *)entity + 0x92));
        if (height_adjust < height_offset) {
            height_adjust = height_bits - 8;
            goto store_adjustment;
        }
adjust_positive:
        height_adjust = height_offset < -8;
        if (height_adjust != 0) {
            height_adjust = height_bits + 8;
        } else {
            goto finish_motion;
        }
store_adjustment:
        (*(s16 *)((u8 *)entity + 0x92)) = height_adjust;
    }
finish_motion:
    entity_flags = ((S_801653A8_2 *)entity_base)->unk_1C;
    if (entity_flags & 0x40000000) {
        ((S_801653A8_2 *)entity_base)->unk_1C = entity_flags & 0xBFFFFFFF;
        ground_height = func_800BCB04((((Rec_D_80082E80 *)sprite)->unk_24 << 6) | 0x20,
                              (((Rec_D_80082E80 *)sprite)->unk_25 << 6) | 0x20,
                              (s16)(((S_801653A8_2 *)entity_base)->unk_88 - 0x20));
        if (ground_height < 0x200) {
            (*(s16 *)((u8 *)entity + 0x92)) =
                (u16)(*(s16 *)((u8 *)entity + 0x92)) +
                (((S_801653A8_2 *)entity_base)->unk_88 - ground_height);
            ((S_801653A8_2 *)entity_base)->unk_88 = ground_height;
        }
    }
    motion->unk_0A = ((S_801653A8_2 *)entity_base)->unk_88 +
                             (u16)(*(s16 *)((u8 *)entity + 0x92)) -
                             (*(u16 *)((u8 *)entity + 0xA6));
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x40;
}
