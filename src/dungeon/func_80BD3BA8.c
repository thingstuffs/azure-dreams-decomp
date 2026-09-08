#include "common.h"
#include "records/Rec_D_80082E80.h"


typedef void (*Callback)(void *, void *, void *, void *);

#define func_8017153C func_8015F53C
#define func_801715E4 func_8015F5E4
#define func_80171650 func_8015F650
#define func_8017174C func_8015F74C
#define func_801717E4 func_8015F7E4
#define func_801718D4 func_8015F8D4
#define func_801718D8 func_8015F8D8
#define func_80171910 func_8015F910

extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s16 func_800BCB04();
extern void func_8017153C() __attribute__((noreturn));
extern void func_801715E4() __attribute__((noreturn));
extern void func_80171650() __attribute__((noreturn));
extern void func_8017174C() __attribute__((noreturn));
extern void func_801717E4() __attribute__((noreturn));
extern void func_801718D4() __attribute__((noreturn));
extern void func_801718D8() __attribute__((noreturn));
extern void func_80171910() __attribute__((noreturn));
extern void func_8015F53C() __attribute__((noreturn));
extern void func_8015F5E4() __attribute__((noreturn));
extern void func_8015F650() __attribute__((noreturn));
extern void func_8015F74C() __attribute__((noreturn));
extern void func_8015F7E4() __attribute__((noreturn));
extern void func_8015F8D4() __attribute__((noreturn));
extern void func_8015F8D8() __attribute__((noreturn));
extern void func_8015F910() __attribute__((noreturn));

extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_8015F9DC;
extern u8 D_80162634[8];
extern u8 D_80162644[8];
extern u8 D_80162654[8];
extern u8 D_8016265C[8];
extern u8 D_80162664[8];
extern u8 D_8016266C[8];
extern Callback D_801626A0[];


typedef struct S_8015F3A8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8015F3A8_0;   /* arg1 in func_8015F3A8 */


typedef struct S_8015F3A8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_8015F3A8_2;   /* base in func_8015F3A8 */

/* Run entity callbacks and update motion, facing, and ground height. */
void func_8015F3A8(void *entity, S_8015F3A8_0 *motion, void *sprite)
{
    register void *entity_base ASM_REG("$19") = entity;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s16 old_state ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 state_byte ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *call_entity;
    void *call_motion;
    void *call_sprite;
    s32 height_offset;
    register u32 height_bits ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 direction;
    s16 ground_height;
    s32 flags;
    register s32 height_step ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u16 initial_flags;
    u16 sprite_flags;

    if (D_80083462 & 0x2000) {
        void *entry_entity = entity;
        Callback entry_callback;

        entry_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (entry_callback == (Callback)&D_8015F9DC) {
            ASM_KEEP(entry_entity);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            entry_callback(entry_entity, motion, sprite, entry_entity);
            return;
        }
        (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        return;
    }

    call_entity = entity;
    call_motion = motion;
    call_sprite = sprite;
    ASM_KEEP4(call_entity, call_motion, call_sprite, entity_base);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    state_byte = (*(u8 *)((u8 *)entity + 0x6D));
    old_state = (s8)state_byte;
    if (func_800A9E70(call_entity, call_motion, call_sprite, entity) != 0) {
        return;
    }

    {
        Callback update_callback = (*(Callback *)((u8 *)entity + 0x8C));

        if (update_callback != 0) {
            update_callback(entity, motion, sprite, entity);
        }
    }
    D_801626A0[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, sprite, entity);
    {
        register s32 state_check ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

        state_check = (u32)(u16)old_state << 16;
        ASM_KEEP_NV(state_check);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        state_check >>= 16;
        if (state_check != (*(s8 *)((u8 *)entity + 0x6D))) {
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
    initial_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;

    if (!(initial_flags & 0x8000)) {
        direction = ((D_80083228 + ((S_8015F3A8_2 *)entity_base)->unk_2A + 0x100) >> 9) & 7;
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
        func_800A020C(((S_8015F3A8_2 *)entity_base)->unk_1C, (u8 *)sprite + 0xC);
        if (!(((S_8015F3A8_2 *)entity_base)->unk_1C & 0x20)) {
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
                func_800478B8(sprite);
                goto clear_8000000;
            }
        } else {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x7000;
            ((S_8015F3A8_2 *)entity_base)->unk_1C &= 0xFFFBFFFF;
        }

clear_8000000:
        ((S_8015F3A8_2 *)entity_base)->unk_1C &= 0xF7FFFFFF;
        flags = ((S_8015F3A8_2 *)entity_base)->unk_1C;
        if (flags & 0x40000) {
            sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
            if (!(sprite_flags & 0x40)) {
                u8 *direction_frames = ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8;

                if (direction_frames == D_80162634) {
                    if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 3 && (sprite_flags & 0x1000)) {
                        (*(s32 *)((u8 *)entity + 0xAC)) = 0x60000;
                        (*(s32 *)((u8 *)entity + 0xB0)) = (s32)0xFFFF3000;
                    }
                    (*(s32 *)((u8 *)entity + 0xA4)) += (*(s32 *)((u8 *)entity + 0xAC));
                    (*(s32 *)((u8 *)entity + 0xAC)) += (*(s32 *)((u8 *)entity + 0xB0));
                    if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                    }
                } else if (direction_frames == D_80162644 || direction_frames == D_8016266C) {
                    (*(s32 *)((u8 *)entity + 0xA4)) -= 0x40000;
                    if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                    }
                } else if (direction_frames != D_80162654 && direction_frames != D_8016265C &&
                           direction_frames != D_80162664) {
                    (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                }
            }

            height_step = (*(u16 *)((u8 *)entity + 0x98)) & 8;
            if (height_step == 0) {
                height_offset = (*(s16 *)((u8 *)entity + 0x92));
                height_bits = (*(u16 *)((u8 *)entity + 0x92));
                if (height_step < height_offset) {
                    height_step = height_bits - 8;
                    (*(s16 *)((u8 *)entity + 0x92)) = height_step;
                    func_80171910();
                    return;
                }
                goto adjust_positive;
            }
            goto finish_motion;
        }

        {
            s32 height_sum;
            register u16 motion_flags ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            height_step = (*(s32 *)((u8 *)entity + 0xA4));
            height_sum = (*(s32 *)((u8 *)entity + 0x90));
            motion_flags = (*(u16 *)((u8 *)entity + 0x98));
            (*(s16 *)((u8 *)entity + 0xB8)) = 0;
            (*(s32 *)((u8 *)entity + 0xA4)) = 0;
            height_sum += height_step;
            ASM_USE_NV(motion_flags);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            ASM_TAILSLOT_PIN(height_sum);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_801717E4();
            return;
        }
    }

    if (initial_flags & 0x800) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = initial_flags & 0x8FFF;
    } else {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = initial_flags | 0x7000;
    }
    ((S_8015F3A8_2 *)entity_base)->unk_1C &= 0xF7FFFFFF;
    flags = ((S_8015F3A8_2 *)entity_base)->unk_1C;

    if (!(flags & 0x40000)) {
        height_step = (*(s32 *)((u8 *)entity + 0xA4));
        (*(s16 *)((u8 *)entity + 0xB8)) = 0;
        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
        (*(s32 *)((u8 *)entity + 0x90)) -= height_step;
        if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
            ground_height = func_800BCB04(motion->unk_00.at02.v,
                                         motion->unk_04.at02.v,
                                         (s16)(((S_8015F3A8_2 *)entity_base)->unk_88 - 0x20)) -
                            ((S_8015F3A8_2 *)entity_base)->unk_88;
            if (ground_height < (*(s16 *)((u8 *)entity + 0x92))) {
                (*(s16 *)((u8 *)entity + 0x92)) = ground_height;
                (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                motion->unk_14 = 0;
                ((S_8015F3A8_2 *)entity_base)->unk_1C |= 0x08000000;
                goto finish_motion;
            }
        }
        goto finish_motion;
    }

    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
        u8 *direction_frames = ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8;

        if (direction_frames == D_80162634) {
            (*(s32 *)((u8 *)entity + 0xAC)) = 0;
            (*(s32 *)((u8 *)entity + 0xA4)) = 0;
        } else if (direction_frames == D_80162644 || direction_frames == D_8016266C) {
            (*(s32 *)((u8 *)entity + 0xA4)) -= 0x40000;
            if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                (*(s32 *)((u8 *)entity + 0xA4)) = 0;
            }
        } else if (direction_frames != D_80162654 && direction_frames != D_8016265C &&
                   direction_frames != D_80162664) {
            (*(s32 *)((u8 *)entity + 0xA4)) = 0;
        }
    }

    height_step = (*(u16 *)((u8 *)entity + 0x98)) & 8;
    if (height_step == 0) {
        height_offset = (*(s16 *)((u8 *)entity + 0x92));
        height_bits = (*(u16 *)((u8 *)entity + 0x92));
        if (height_step < height_offset) {
            height_step = height_bits - 8;
            goto store_adjustment;
        }
adjust_positive:
        height_step = height_offset < -8;
        if (height_step != 0) {
            height_step = height_bits + 8;
        } else {
            goto finish_motion;
        }
store_adjustment:
        (*(s16 *)((u8 *)entity + 0x92)) = height_step;
    }
finish_motion:
    flags = ((S_8015F3A8_2 *)entity_base)->unk_1C;
    if (flags & 0x40000000) {
        ((S_8015F3A8_2 *)entity_base)->unk_1C = flags & 0xBFFFFFFF;
        ground_height = func_800BCB04((((Rec_D_80082E80 *)sprite)->unk_24 << 6) | 0x20,
                                     (((Rec_D_80082E80 *)sprite)->unk_25 << 6) | 0x20,
                                     (s16)(((S_8015F3A8_2 *)entity_base)->unk_88 - 0x20));
        if (ground_height < 0x200) {
            (*(s16 *)((u8 *)entity + 0x92)) =
                (u16)(*(s16 *)((u8 *)entity + 0x92)) +
                (((S_8015F3A8_2 *)entity_base)->unk_88 - ground_height);
            ((S_8015F3A8_2 *)entity_base)->unk_88 = ground_height;
        }
    }
    motion->unk_0A = ((S_8015F3A8_2 *)entity_base)->unk_88 +
                     (u16)(*(s16 *)((u8 *)entity + 0x92)) -
                     (*(u16 *)((u8 *)entity + 0xA6));
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x40;
}
