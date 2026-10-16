#include "modules/dungeon_resource06_slot0.h"

void func_80170BB8(u8 *actor, u8 *motion, u8 *entity)
{
    u8 *subject = actor;
    s16 state_index;
    s32 sprite_index;
    u32 global_flags;
    u16 *global_flags_ptr = (u16 *)((u8 *)D_80080000);
    u8 *part_base;
    R06_80170BB8_Callback callback;
    u16 entity_flags;
    s32 subject_flags;
    s16 ground_height;
    s32 bob_offset;
    s16 floor_offset;
    s32 height_limit;
    u16 height_raw;
    u16 height_raw2;
    s32 height_offset;
    s32 ground_offset;
    u32 loaded_height;
    s32 direction;
    s32 view_dir;
    u32 new_height;

    part_base = (*(u8 * *)((u8 *)actor + 0xA4));
    global_flags = global_flags_ptr[0x1A31];
    loaded_height = (u32)(part_base + 0x20);


    direction = (s32)(part_base + 0x28);
    if (global_flags & 0x2000) {
        callback = (*(R06_80170BB8_Callback *)((u8 *)actor + 0x8C));
        if (callback == (R06_80170BB8_Callback)((u8 *)func_8017140C)) {
            callback(actor, motion, entity, actor);
        } else {
            (*(u8 *)((u8 *)actor + 0x71)) &= 0x7F;
        }
    } else {
        u32 raw_state;

        raw_state = (*(u8 *)((u8 *)actor + 0x6D));
        state_index = (s8)raw_state;
        if (func_800A9E70(actor, motion, entity, actor) == 0) {
            {
                R06_80170BB8_Callback actor_callback;

                actor_callback = (*(R06_80170BB8_Callback *)((u8 *)actor + 0x8C));
                if (actor_callback != 0) {
                    actor_callback(actor, motion, entity, actor);
                }
            }
            ((R06_80170BB8_Callback *)D_8017589C)[(*(u8 *)((u8 *)actor + 0x9A))](actor, motion, entity, actor);

            if ((s16)state_index != (*(s8 *)((u8 *)actor + 0x6D))) {
                func_800AA36C(actor, motion, entity, actor);
            }

            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_00.at00.v += ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_0C;
            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_04.at00.v += ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_10;

            if (!((*(u32 *)((u8 *)actor + 0x1C)) & 0x00040000) &&
                !((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
                ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_14 += (*(s8 *)((u8 *)actor + 0x9D)) * 0x14000;
                (*(u8 *)((u8 *)actor + 0x9D))++;
            } else {
                (*(u8 *)((u8 *)actor + 0x9D)) = 0;
            }
            (*(s32 *)((u8 *)actor + 0x90)) += ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_14;

            if (((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u & 0x200) {
                if ((*(u16 *)((u8 *)actor + 0x98)) & 0x4000) {
                    ((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_3C = 0x00808080;
                    ((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_0C.u32 = 0x00808080;
                } else if (((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_0C.u8 >= 8) {
                    ((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_3C += 0xFFF7F7F8;
                    ((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_0C.u32 = ((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_3C;
                }

                if (((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_14 & 0x6000) {
                    if (((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_0C.u8 < 8 ||
                        ((*(u16 *)((u8 *)actor + 0x98)) & 0x4000)) {
                        u16 actor_flags = (*(u16 *)((u8 *)actor + 0x98));

                        if (!(actor_flags & 0x8000)) {
                            (*(u16 *)((u8 *)actor + 0x98)) = actor_flags | 0xC000;
                            ((R06_80170BB8_S_80170BB8_3 *)((u8 *)loaded_height))->unk_04 |= 0x8000;
                            (*(u16 *)((u8 *)actor + 0xA0)) =
                                (func_80069EF8() & 7) + 0x10;
                        }
                    }
                }

                sprite_index = 0;
                if (--(*(s16 *)((u8 *)actor + 0xA0)) == 0) {
                    (*(u16 *)((u8 *)actor + 0x98)) &= 0x7FFF;
                    ((R06_80170BB8_S_80170BB8_3 *)((u8 *)loaded_height))->unk_04 &= 0x7FFF;
                    if (((R06_80170BB8_S_80170BB8_3 *)((u8 *)loaded_height))->unk_02 > 0) {
                        do {
                            func_80047784((u8 *)direction + sprite_index * 0x30, 0x1C, 0);
                            sprite_index++;
                        } while (sprite_index < ((R06_80170BB8_S_80170BB8_3 *)((u8 *)loaded_height))->unk_02);
                    }
                }
            } else {
                if (((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_0C.u8 >= 0x80) {
                    ((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_3C = 0x00808080;
                    ((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_0C.u32 = 0x00808080;
                } else {
                    ((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_3C += 0x00080808;
                    ((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_0C.u32 = ((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_3C;
                }

                if ((*(u16 *)((u8 *)actor + 0x98)) & 0x4000) {
                    (*(u16 *)((u8 *)actor + 0x98)) &= 0x3FFF;
                    ((R06_80170BB8_S_80170BB8_3 *)((u8 *)loaded_height))->unk_04 &= 0x7FFF;
                }

                if ((*(u16 *)((u8 *)actor + 0x98)) & 0x1000) {
                    func_80047784((u8 *)direction, 0x1D, 0);
                    func_80047784((u8 *)direction + 0x30, 0x1D, 0);
                    (*(u16 *)((u8 *)actor + 0x98)) &= 0xEFFF;
                } else if (((*(u16 *)((u8 *)actor + 0x98)) & 0x2000) &&
                           (((R06_80170BB8_S_80170BB8_2 *)(u8 *)direction)->unk_14 & 0x6000)) {

                    if ((*(u8 *)((u8 *)actor + 0x9A)) == 7) {
                        func_80047784((u8 *)direction, 0x19, 0);
                        func_80047784((u8 *)direction + 0x30, 0x24, 0);
                    } else {
                        s32 random_value;

                        func_80047784((u8 *)direction, 0x19, 0);
                        random_value = func_80069EF8();
                        ground_offset = 0x24;
                        if (random_value & 3) {
                            ground_offset = 0x19;
                        }
                        func_80047784((u8 *)direction + 0x30, ground_offset, 0);
                    }
                }
            }

            entity_flags = ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14;
            if (!(entity_flags & 0x8000)) {
                {
                    s32 view_angle;

                    view_angle =
                        gameWork.view.viewAngle + ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_2A + 0x100;
                    state_index = (view_angle >> 9) & 7;
                }
                {

                    if ((*(s16 *)((u8 *)actor + 0x94)) != (view_dir = (s16)state_index)) {
                        func_80047738(entity,
                                      (*(u8 *)((u8 *)(((R06_80170BB8_S_80170BB8_4 *)entity)->unk_2C) + view_dir)),
                                      ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_04);
                        (*(s16 *)((u8 *)actor + 0x94)) = state_index;
                    }

                    if (((u8 *)D_8006CCF8)[view_dir] != 0) {
                        ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 |= 1;
                    } else {
                        ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 &= 0xFFFE;
                    }
                }

                if ((*(u8 *)((u8 *)actor + 0x9A)) != 8) {
                    func_800A020C(((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.s, entity + 0xC);
                }

                if (!(((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.s & 0x20)) {
                    if (!(((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 & 0x40)) {
                        func_800478B8(entity);
                    }
                } else {
                    ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 |= 0x7000;
                    ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u &= 0xFFFBFFFF;
                }

                ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u &= 0xF7FFFFFF;
                subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;

                if (subject_flags & 0x00040000) {
                    if (!(((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 & 0x40) &&
                        ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_2C == ((u8 *)D_8017586C)) {
                        u16 bob_frame = (*(u16 *)((u8 *)actor + 0xB8));

                        (*(u16 *)((u8 *)actor + 0xB8)) = bob_frame + 1;
                        (*(s32 *)((u8 *)actor + 0xB4)) +=
                            func_800644B8((s16)bob_frame * 0xAA) << 5;
                    }

                    if (!((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
                        ground_offset = (s16)(func_800BCB04(
                            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v, ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                            (s16)(((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 - 0x20)) -
                                              ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88);
                        height_offset = (*(s16 *)((u8 *)actor + 0x92));
                        height_raw = (*(u16 *)((u8 *)actor + 0x92));
                        height_limit = ground_offset - 0x18;
                        if (height_limit < height_offset) {

                            new_height = height_raw - 8;
                            (*(u16 *)((u8 *)actor + 0x92)) = new_height;
                            subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;
                        } else {
                            height_limit = ground_offset;
                            height_limit -= 0x20;
                            height_limit = height_offset < height_limit;
                            if (height_limit) {
                                new_height = height_raw + 8;
                                (*(u16 *)((u8 *)actor + 0x92)) = new_height;
                            }
                            subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;
                        }
                    } else {
                        subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;
                    }
                } else {
                    goto ground_reset;
                }
            } else {
                if (entity_flags & 0x800) {
                    ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 = entity_flags & 0x8FFF;
                } else {
                    ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 = entity_flags | 0x7000;
                }

                ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u &= 0xF7FFFFFF;
                subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;

                if (!(subject_flags & 0x00040000)) {
ground_reset:
                    bob_offset = (*(s32 *)((u8 *)actor + 0xB4));
                    (*(u16 *)((u8 *)actor + 0xB8)) = 0;
                    (*(s32 *)((u8 *)actor + 0xB4)) = 0;
                    (*(s32 *)((u8 *)actor + 0x90)) -= bob_offset;
                    if (!((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
                        ground_height = func_800BCB04(
                            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v, ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                            (s16)(((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 - 0x20));
                        floor_offset = (s16)(ground_height - ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88);
                        if (floor_offset < (*(s16 *)((u8 *)actor + 0x92))) {
                            (*(s16 *)((u8 *)actor + 0x92)) = floor_offset;
                            (*(u8 *)((u8 *)actor + 0x9D)) = 0;
                            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_14 = 0;
                            ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u |= 0x08000000;
                        }
                    }
                    subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;
                } else {
                    if (!(((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 & 0x40) &&
                        ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_2C == ((u8 *)D_8017586C)) {
                        u16 bob_frame = (*(u16 *)((u8 *)actor + 0xB8));

                        (*(u16 *)((u8 *)actor + 0xB8)) = bob_frame + 1;
                        (*(s32 *)((u8 *)actor + 0xB4)) +=
                            func_800644B8((s16)bob_frame * 0xAA) << 5;
                    }

                    if (!((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
                        ground_offset = (s16)(func_800BCB04(
                            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v, ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                            (s16)(((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 - 0x20)) -
                                              ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88);
                        height_offset = (*(s16 *)((u8 *)actor + 0x92));
                        height_raw2 = (*(u16 *)((u8 *)actor + 0x92));
                        height_limit = ground_offset - 0x18;
                        if (height_limit < height_offset) {
                            new_height = height_raw2 - 8;
                            (*(u16 *)((u8 *)actor + 0x92)) = new_height;
                        } else {
                            height_limit = ground_offset;
                            height_limit -= 0x20;
                            height_limit = height_offset < height_limit;
                            if (height_limit) {
                                new_height = height_raw2 + 8;
                                (*(u16 *)((u8 *)actor + 0x92)) = new_height;
                            }
                        }
                    }
                    subject_flags = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u;
                }
            }
            if (subject_flags & 0x40000000) {
                ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_1C.u = subject_flags & 0xBFFFFFFF;
                ground_height = func_800BCB04((((R06_80170BB8_S_80170BB8_4 *)entity)->unk_24 << 6) | 0x20,
                                       (((R06_80170BB8_S_80170BB8_4 *)entity)->unk_25 << 6) | 0x20,
                                       (s16)(((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 - 0x20));
                if ((s16)ground_height < 0x200) {
                    (*(u16 *)((u8 *)actor + 0x92)) +=
                        ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 - ground_height;
                    ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 = ground_height;
                }
            }

            ((R06_80170BB8_S_80170BB8_0 *)motion)->unk_0A = ((R06_80170BB8_S_80170BB8_1 *)subject)->unk_88 +
                                      (*(u16 *)((u8 *)actor + 0x92)) -
                                      (*(u16 *)((u8 *)actor + 0xB6));
            ((R06_80170BB8_S_80170BB8_4 *)entity)->unk_14 |= 0x40;
        }
    }

}
