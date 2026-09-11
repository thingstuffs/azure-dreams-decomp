#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_8016BF74_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_8016BF74_0;   /* state in func_8016BF74 */

typedef struct S_8016BF74_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
} S_8016BF74_1;   /* arg3 in func_8016BF74 */

typedef struct S_8016BF74_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
} S_8016BF74_2;   /* arg2 in func_8016BF74 */

typedef struct S_8016BF74_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8016BF74_3_pre;   /* the 0x14 bytes before temp_v0 in func_8016BF74, addressed as temp_v0[-1] */

typedef struct S_8016BF74_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016BF74_4;   /* temp_v0_2 in func_8016BF74 */

typedef struct S_8016BF74_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    s8 unk_9C;
    u8 pad_9D[0x15];
    u8 unk_B2;
} S_8016BF74_5;   /* arg0 in func_8016BF74 */


typedef struct S_8016BF74_7 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8016BF74_7;   /* temp_v0_5 in func_8016BF74 */

typedef struct S_8016BF74_8 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8016BF74_8;   /* state2 in func_8016BF74 */

typedef struct S_8016BF74_9 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016BF74_9;   /* (arg3 + ((u8) ((S_8016BF74_1 *)arg3)->unk_71.s & 0x7F)) in func_8016BF74 */


s32 func_8009A180();                     /* extern */
M2C_UNK func_8009A21C();             /* extern */
M2C_UNK func_8009A3D0();             /* extern */
s32 func_8009A540();                /* extern */
s32 func_8009A66C();    /* extern */
s32 func_8009FD7C();                  /* extern */
s16 func_800A0134();                  /* extern */
void *func_800A02AC();                /* extern */
void *func_800A04F0();           /* extern */
u16 func_800A0818();          /* extern */
M2C_UNK func_800A0E6C();  /* extern */
M2C_UNK func_800A19E4(); /* extern */
M2C_UNK func_800A6D30();                            /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
s16 func_800BCB04();                   /* extern */
s32 func_8016C720();          /* extern */
typedef struct {
    u8 pad[0xC];
    u16 flags;
    u8 tail[6];
} D_800E2970Entry;
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern s16 D_8006CD00;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern u16 D_80082EA4;
extern M2C_UNK D_80083460;
extern D_800E2970Entry D_800E2970[];

/* Selects a movement direction and advances the actor path through available tiles. */
void func_8016BF74(void *raw_motion, void *context, void *raw_position, void *raw_actor) {
    void *motion;
    S_8016BF74_2 *position;
    void *actor;
    register s32 turn_index ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 near_target;
    register u8 *x_offsets ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    M2C_UNK old_tile_mask;
    M2C_UNK new_tile_mask;
    register s8 *angle_offsets ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s8 *offset_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 target_y;
    s32 target_x;
    s32 y_offset;
    s32 x_offset;
    s32 world_y;
    s32 world_x;
    s16 target_angle;
    s16 actor_distance;
    register s32 tile_x_or_offset ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 *x_offset_ptr;
    s32 move_value;
    register s32 initialized_bit ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 actor_flags;
    s32 direction_offset;
    s32 result;
    s8 tile_index;
    s8 *state;
    s32 state_flags;
    register void *target_entry ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_8016BF74_4 *target_position;
    void *ahead_target;
    register void *nearby_target ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 active_actor;
    s32 path_status;
    s32 tile_y;
    s32 current_angle;
    s16 candidate_angle;
    void *motion_flags;
    s32 source_x;
    s32 source_y;
    s32 dest_x;
    s32 dest_y;
    register s32 old_tile_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 new_tile_flags;
    s32 step_y;
    s32 next_x;
    s32 current_x;
    s16 next_path_index;
    register s32 current_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register u8 *y_offsets ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 *y_offset_ptr;
    u8 *world_position;

    motion = raw_motion;
    position = raw_position;
    actor = raw_actor;
    state = (s8 *)&D_80083460;
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    state_flags = ((S_8016BF74_0 *)state)->unk_02;
    near_target = 0;
    if ((state_flags & 0x4000) || (((S_8016BF74_1 *)actor)->unk_71.s >= 0)) {
        if (((u8) ((S_8016BF74_1 *)actor)->unk_12 >= 2U) || ((func_8016C720(motion, context, position, actor) << 0x10) == 0)) {
            func_800A9A0C(actor);
            return;
        }
        active_actor = ((S_8016BF74_0 *)state)->unk_0C;
        if ((void *)active_actor == actor) {
            path_status = 0xC008;
            ((S_8016BF74_1 *)actor)->unk_46 = (u16) path_status;
            return;
        }
        return;
    }
    if (state_flags & 0x2000) {
        func_800A19E4(position, actor, 3, 6, motion + 0x9C);
        actor_flags = ((S_8016BF74_1 *)actor)->unk_1C;
        if (actor_flags & 0x410) {
            if (actor_flags & 0x400) {
                target_entry = func_800A02AC(actor, position->unk_24.at00.v, position->unk_24.at01.v);
                if (target_entry != NULL) {
                    source_x = position->unk_24.at00.v;
                    target_position = ((S_8016BF74_3_pre *)target_entry)[-1].unk_00;
                    source_y = position->unk_24.at01.v;
                    dest_x = target_position->unk_24;
                    dest_y = target_position->unk_25;
                    motion_flags = motion + 0x98;
                    ((S_8016BF74_1 *)actor)->unk_2A.u = func_800A0818(source_x, source_y, dest_x, dest_y, motion_flags);
                    ((S_8016BF74_1 *)actor)->unk_71.u &= 0x7F;
                    return;
                }
                move_value = ((S_8016BF74_1 *)actor)->unk_14;
                if (move_value >= 0) {
                    initialized_bit = 0x80000000;
                    move_value |= initialized_bit;
                    ((S_8016BF74_1 *)actor)->unk_14 = move_value;
                    result = func_800A6D30();
                    ((S_8016BF74_1 *)actor)->unk_2A.u += (result & 7) << 9;
                    goto start_search;
                }
                goto start_search;
            }
            ahead_target = func_800A04F0(actor, position->unk_24.at00.v, position->unk_24.at01.v, (s16) ((S_8016BF74_1 *)actor)->unk_2A.u);
            turn_index = 0;
            if (ahead_target == NULL) {
                goto init_offsets;
            }
            goto finish_path;
        }
        if (((S_8016BF74_5 *)motion)->unk_B2 != 0) {
            turn_index = 0;
            if (!(((S_8016BF74_1 *)actor)->unk_46 & 0x8000)) {
                if (actor_flags & 0x20000) {
                    direction_offset = ((((S_8016BF74_1 *)actor)->unk_45 + ((s32) (((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_u16 << 0x10) >> 0x19)) & 7) * 2;
                    world_x = D_80082E80[0x24];
                    world_y = D_80082E80[0x25];
                    x_offset = (*(u16 *)((u8 *)(&D_8006CCD8) + direction_offset));
                    y_offset = (*(u16 *)((u8 *)(&D_8006CCE8) + direction_offset));
                    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    current_x = position->unk_24.at00.v;
                    target_x = world_x + x_offset;
                    target_y = world_y + y_offset;
                    ASM_KEEP(current_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    ASM_USE_NV(x_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    if ((current_x != (target_x & 0xFFFF)) || (position->unk_24.at01.v != (target_y & 0xFFFF))) {
                        target_angle = func_800A0818(position->unk_24.at00.v, position->unk_24.at01.v, (s16) target_x, (s16) target_y, motion + 0x98);
                        ((S_8016BF74_1 *)actor)->unk_2A.u = (u16) target_angle;
                        if ((func_8009A66C(target_angle, position, actor, 0x20) << 0x10) <= 0) {
                            u8 *fallback_position;

                            fallback_position = (u8 *)&D_80082EA4 - 0x24;
                            ((S_8016BF74_1 *)actor)->unk_2A.u = func_800A0818(position->unk_24.at00.v, position->unk_24.at01.v, fallback_position[0x24], fallback_position[0x25], motion + 0x98);
                        }
                        world_position = (u8 *)&D_80082EA4 - 0x24;
                        result = func_8009FD7C(position->unk_24.at00.v, position->unk_24.at01.v, world_position[0x24], world_position[0x25]);
                        ASM_CLOBBER("$19");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                        turn_index = 0;
                        if ((result << 0x10) == 0) {
                            goto init_offsets;
                        }
                        near_target = 1;
                        goto init_offsets;
                    }
                    goto finish_path;
                }
                goto choose_direction;
            }
            goto init_offsets;
        }
        tile_index = position->unk_26;
        if ((tile_index < 0) || !(D_800E2970[tile_index].flags & 2)) {
            turn_index = 0;
            if (!(((S_8016BF74_1 *)actor)->unk_46 & 0x8000)) {
                nearby_target = func_800A04F0(actor, position->unk_24.at00.v, position->unk_24.at01.v, (s16) ((S_8016BF74_1 *)actor)->unk_2A.u);
                if ((nearby_target == NULL) || !(((S_8016BF74_7 *)nearby_target)->unk_1C & 0x2000) || (func_800A0134(nearby_target, actor) >= 0x81) || ((func_8009A540(((s32) (((S_8016BF74_1 *)actor)->unk_2A.u << 0x10) >> 0x19) & 0xFFFF, position->unk_24.at00.v, position->unk_24.at01.v, (s16) (((S_8016BF74_1 *)actor)->unk_88 - 0x20)) << 0x10) == 0)) {
                    if (((S_8016BF74_1 *)actor)->unk_1C & 0x20000) {
                        u8 *world_origin;

                        world_origin = (u8 *)&D_80082E80;
                        ((S_8016BF74_1 *)actor)->unk_2A.u = func_800A0818(position->unk_24.at00.v, position->unk_24.at01.v, world_origin[0x24], world_origin[0x25], motion + 0x98);
                        if ((func_8009FD7C(position->unk_24.at00.v, position->unk_24.at01.v, world_origin[0x24], world_origin[0x25]) << 0x10) != 0) {
                            actor_distance = func_800A0134(D_800814A8, actor);
                            turn_index = 0;
                            if (actor_distance < 0x81) {
                                result = func_8009A540(((s32) (((S_8016BF74_1 *)actor)->unk_2A.u << 0x10) >> 0x19) & 0xFFFF, position->unk_24.at00.v, position->unk_24.at01.v, (s16) (((S_8016BF74_1 *)actor)->unk_88 - 0x20));
                                ASM_CLOBBER("$19");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                                turn_index = 0;
                                if ((result << 0x10) == 0) {
                                    goto init_offsets;
                                }
                                goto finish_path;
                            }
                            goto init_offsets;
                        }
                        goto start_search;
                    }
choose_direction:
                    goto update_direction;
                }
                goto finish_path;
            }
            goto init_offsets;
        }
update_direction:
        func_800A0E6C(position, ((S_8016BF74_5 *)motion)->unk_9C, actor, motion + 0x98);
start_search:
        turn_index = 0;
init_offsets:
#ifdef __mips__
        offset_page = (s8 *)0x80070000;
#else
        offset_page = (s8 *)&D_8006CCD8 + 0x3328;
#endif
        ASM_KEEP(offset_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        x_offsets = (u8 *)(offset_page - 0x3328);
#ifdef __mips__
        offset_page = (s8 *)0x80070000;
#else
        offset_page = (s8 *)&D_8006CD00 + 0x3300;
#endif
        ASM_KEEP(offset_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        angle_offsets = offset_page - 0x3300;
try_direction:
        current_angle = ((S_8016BF74_1 *)actor)->unk_2A.s;
        if (((S_8016BF74_5 *)motion)->unk_98 & 2) {
            move_value = *(s16 *)angle_offsets;
            candidate_angle = current_angle - move_value;
            goto check_direction;
        }
        move_value = *(s16 *)angle_offsets;
        candidate_angle = current_angle + move_value;
check_direction:
        if ((func_8009A66C(candidate_angle, position, actor, 0x20) << 0x10) > 0) {
            if (turn_index < 3) {
                goto take_step;
            }
            move_value = near_target;
            if (move_value != 0) {
                goto finish_search;
            }
take_step:
            ((S_8016BF74_1 *)actor)->unk_2A.u = (u16) candidate_angle;
            ((S_8016BF74_9 *)((actor + ((u8) ((S_8016BF74_1 *)actor)->unk_71.s & 0x7F))))->unk_74 = (u8) position->unk_24.at00.v;
            ((S_8016BF74_9 *)((actor + ((u8) ((S_8016BF74_1 *)actor)->unk_71.s & 0x7F))))->unk_7C = (u8) position->unk_24.at01.v;
            next_path_index = (u8) ((S_8016BF74_1 *)actor)->unk_71.s + 1;
            old_tile_flags = ((S_8016BF74_1 *)actor)->unk_1C & 0x2000;
            ((S_8016BF74_1 *)actor)->unk_71.s = (s8) next_path_index;
            tile_x_or_offset = position->unk_24.at00.v;
            tile_y = position->unk_24.at01.v;
            old_tile_mask = 0x3000;
            if (old_tile_flags) {
                old_tile_mask = 0x300;
            }
            func_8009A3D0(tile_x_or_offset, tile_y, old_tile_mask);
            tile_x_or_offset = ((u16) ((S_8016BF74_1 *)actor)->unk_2A.u >> 8) & 0xE;
            x_offset_ptr = (u8 *)((u32) tile_x_or_offset + (u32) x_offsets);
            position->unk_24.at00.v = (u8) (position->unk_24.at00.v + *x_offset_ptr);
            ASM_KEEP(x_offsets);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            y_offsets = (u8 *)&D_8006CCE8;
            y_offset_ptr = (u8 *)((u32) tile_x_or_offset + (u32) y_offsets);
            current_y = position->unk_24.at01.v;
            step_y = *y_offset_ptr;
            next_x = position->unk_24.at00.v;
            position->unk_24.at01.v = (u8) (current_y + step_y);
            new_tile_mask = 0x3000;
            new_tile_flags = ((S_8016BF74_1 *)actor)->unk_1C & 0x2000;
            tile_y = position->unk_24.at01.v;
            if (new_tile_flags) {
                new_tile_mask = 0x300;
            }
            func_8009A21C(next_x, tile_y, new_tile_mask);
            goto complete_step;
finish_search:
            goto finish_path;
        }
        if ((turn_index != 0) || (D_80082EA4 == position->unk_24.at00u.v) || (result = func_8009A180(actor, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 0x10, (result == 0))) {
            turn_index += 1;
            angle_offsets += 2;
            if (turn_index >= 8) {
                s8 *step_state;

complete_step:
                result = turn_index < 8;
                if (result == 0) {
                    ((S_8016BF74_1 *)actor)->unk_71.s = (s8) ((u8) ((S_8016BF74_1 *)actor)->unk_71.s & 0x7F);
                    ((S_8016BF74_1 *)actor)->unk_46 = (u16) (((S_8016BF74_1 *)actor)->unk_46 & 0x7FFF);
                    func_800A9A0C(actor);
                    return;
                }
                ((S_8016BF74_1 *)actor)->unk_46 = (u16) (((S_8016BF74_1 *)actor)->unk_46 & 0x7FFF);
                ((S_8016BF74_5 *)motion)->unk_9C = (s8) (u8) position->unk_26;
                ((S_8016BF74_1 *)actor)->unk_6D.u = (u8) (((S_8016BF74_1 *)actor)->unk_6D.u - 1);
                step_state = (s8 *)&D_80083460;
                ((S_8016BF74_8 *)step_state)->unk_08 = (u16) (((S_8016BF74_8 *)step_state)->unk_08 + 1);
                if (((S_8016BF74_1 *)actor)->unk_6D.s == 0) {
finish_path:
                    ((S_8016BF74_1 *)actor)->unk_71.u &= 0x7F;
                    return;
                }
                turn_index = func_800BCB04((position->unk_24.at00.v << 6) | 0x20, (position->unk_24.at01.v << 6) | 0x20, (s16) (((S_8016BF74_1 *)actor)->unk_88 - 0x20));
                result = turn_index < 0x200;
                if (result != 0) {
                    ((S_8016BF74_1 *)actor)->unk_88 = (u16) turn_index;
                }
                return;
            }
            goto try_direction;
        }
        return;
    }
    return;
}
