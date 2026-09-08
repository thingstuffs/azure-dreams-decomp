#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_800D92C0_0 {
    u8 pad_00[0x14];
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
    s8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
} S_800D92C0_0;   /* arg3 in func_800D92C0 */

typedef struct S_800D92C0_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x2C];
    s32 unk_58;
} S_800D92C0_1;   /* *D_800814A8 in func_800D92C0 */

typedef struct S_800D92C0_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
} S_800D92C0_2;   /* arg2 in func_800D92C0 */


typedef struct S_800D92C0_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_800D92C0_4;   /* (arg3 + ((u8) ((S_800D92C0_0 *)arg3)->unk_71 & 0x7F)) in func_800D92C0 */


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonEntry;

extern s32 D_80083460[3];
extern int D_800814A8[4];
extern u8 D_80082E80_initial[] __asm__("D_80082E80");
extern u8 D_80082E80_later[] __asm__("D_80082E80");
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u8 D_8006CCD8_bytes[] __asm__("D_8006CCD8");
extern u8 D_8006CCE8_bytes[] __asm__("D_8006CCE8");
extern DungeonEntry D_800E2970[];
extern s16 D_8006CD00[];
extern u16 D_80082EA4[8];
M2C_UNK func_8009A3D0();
s32 func_8009A180();
s32 func_8009A21C();
s32 func_8009A66C();
s32 func_8009FD7C();
M2C_UNK func_800A0E6C();
M2C_UNK func_800A0818();
M2C_UNK func_800A19E4();
M2C_UNK func_800A6D30();
M2C_UNK func_800A9A0C();
s16 func_800BCB04();

/* Advances an actor along a traversable heading and updates its movement state. */
void func_800D92C0(void *move_state, void *context, S_800D92C0_2 *position, void *actor) {
    M2C_UNK tile_mask;
    s32 target_y;
    s32 target_x;
    s32 candidate_heading;
    s16 target_heading;
    register M2C_UNK direction_or_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 next_y;
    s32 room_cache;
    s32 turn_flags;
    register s32 move_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 flags_or_heading ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 actor_flags;
    s32 target_direction;
    s32 limit_turn;
    s8 room_id;
    s16 turn_index;
    u8 *turn_offsets;
    u16 *state = (u16 *)D_80083460;

    limit_turn = 0;
    if ((state[1] & 0x4000) || (((S_800D92C0_0 *)actor)->unk_71 >= 0)) {
        func_800A9A0C(actor);
        return;
    }
    if (state[1] & 0x2000) {
        room_cache = move_state + 0x9C;
        func_800A19E4(position, actor, 3, 6, room_cache);
        flags_or_heading = ((S_800D92C0_0 *)actor)->unk_1C;
        move_result = flags_or_heading & 0x410;
        if (move_result) {
            move_result = flags_or_heading & 0x400;
            if (move_result) {
                move_result = ((S_800D92C0_0 *)actor)->unk_14;
                if (move_result >= 0) {
                    ((S_800D92C0_0 *)actor)->unk_14 = (s32) (move_result | 0x80000000);
                    move_result = func_800A6D30();
                    move_result &= 7;
                    ((S_800D92C0_0 *)actor)->unk_2A.u = (u16)(((S_800D92C0_0 *)actor)->unk_2A.u + (move_result << 9));
                }
            }
            goto init_loop;
        }
        if ((((S_800D92C0_0 *)actor)->unk_71 < 0) && (state[1] & 0x2000)) {
            func_800A19E4(position, actor, 3, 6, room_cache);
            actor_flags = ((S_800D92C0_0 *)actor)->unk_1C;
            if (actor_flags & 0x2000) {
                if (actor_flags & 0x20000) {
                    {
                        u8 *coord_base = D_80082E80_initial;
                        target_direction = (((S_800D92C0_0 *)actor)->unk_45 + ((s32) (((S_800D92C0_1 *)(*D_800814A8))->unk_2A << 0x10) >> 0x19)) & 7;
                        target_x = coord_base[0x24] + D_8006CCD8[target_direction];
                        target_y = coord_base[0x25] + D_8006CCE8[target_direction];
                    }
                    if ((position->unk_24.at00.v != (target_x & 0xFFFF)) || (position->unk_24.at01.v != (target_y & 0xFFFF))) {
                        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        turn_flags = move_state + 0x98;
                        target_heading = func_800A0818(position->unk_24.at00.v, position->unk_24.at01.v, (s16)target_x, (s16)target_y, turn_flags);
                        ((S_800D92C0_0 *)actor)->unk_2A.u = (u16) target_heading;
                        if ((func_8009A66C(target_heading, position, actor, 0x20) << 0x10) <= 0) {
                            u8 *coord_later = D_80082E80_later;
                            ((S_800D92C0_0 *)actor)->unk_2A.u = func_800A0818(position->unk_24.at00.v, position->unk_24.at01.v, coord_later[0x24], coord_later[0x25], turn_flags);
                        }
                        {
                            u8 *coord_later = D_80082E80_later;
                            move_result = func_8009FD7C(position->unk_24.at00.v, position->unk_24.at01.v, coord_later[0x24], coord_later[0x25]);
                            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                            turn_index = 0;
                            if ((move_result << 0x10) != 0) {
                                limit_turn = 1;
                                goto loop_entry;
                            }
                        }
                        goto loop_entry;
                    }
                    goto mask_and_return;
                }
                goto prepare_heading;
            }
            room_id = position->unk_26;
            if ((room_id < 0) || !(D_800E2970[room_id].flags & 2)) {
                if (!(((S_800D92C0_0 *)actor)->unk_46 & 0x8000)) {
prepare_heading:
                    goto choose_heading;
                }
            } else {
choose_heading:
                func_800A0E6C(position, ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_s8, actor, move_state + 0x98);
            }
init_loop:
            turn_index = 0;
loop_entry:
            turn_offsets = (u8 *)D_8006CD00;
try_heading:
            move_result = ((Rec_func_800A9E70_arg0 *)move_state)->unk_98;
            flags_or_heading = ((S_800D92C0_0 *)actor)->unk_2A.s;
            if (move_result & 2) {
                move_result = (s32) (turn_index << 0x10) >> 0xF;
                move_result += (s32) turn_offsets;
                candidate_heading = flags_or_heading - *(s16 *)move_result;
            } else {
                move_result = (s32) (turn_index << 0x10) >> 0xF;
                move_result += (s32) turn_offsets;
                candidate_heading = flags_or_heading + *(s16 *)move_result;
            }
            if ((func_8009A66C((s16)candidate_heading, position, actor, 0x20) << 0x10) > 0) {
                if (turn_index >= 3) {
                    move_result = limit_turn;
                    if (move_result != 0) {
                        goto mask_and_return;
                    }
                }
                {
                    ((S_800D92C0_0 *)actor)->unk_2A.u = (u16) candidate_heading;
                    ((S_800D92C0_4 *)((actor + ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F))))->unk_74 = (u8) position->unk_24.at00.v;
                    ((S_800D92C0_4 *)((actor + ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F))))->unk_7C = (u8) position->unk_24.at01.v;
                    ((S_800D92C0_0 *)actor)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)actor)->unk_71 + 1);
                    func_8009A3D0(position->unk_24.at00.v, position->unk_24.at01.v,
                                  (((S_800D92C0_0 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000);
                    direction_or_x = ((u16) ((S_800D92C0_0 *)actor)->unk_2A.u >> 8) & 0xE;
                    {
                        u8 *x_table_base = D_8006CCD8_bytes;
                        register s32 next_x ASM_REG("$2") = position->unk_24.at00.v;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        next_x += x_table_base[direction_or_x];
                        position->unk_24.at00.v = (u8) next_x;
                    }
                    position->unk_24.at01.v = (u8) (position->unk_24.at01.v + D_8006CCE8_bytes[direction_or_x]);
                    direction_or_x = position->unk_24.at00.v;
                    next_y = position->unk_24.at01.v;
                    tile_mask = 0x3000;
                    if (((S_800D92C0_0 *)actor)->unk_1C & 0x2000) {
                        tile_mask = 0x300;
                    }
                    func_8009A21C(direction_or_x, next_y, tile_mask);
                    goto post_loop;
                }
            }
            {
                register s16 next_index ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                if (turn_index != 0) {
                    next_index = turn_index + 1;
                    goto increment_index;
                }
                if (*D_80082EA4 == position->unk_24.at00u.v) {
                    next_index = turn_index + 1;
                    goto increment_index;
                }
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                if ((func_8009A180(actor, ((S_800D92C0_1 *)(*D_800814A8))->unk_58 + 0x20) << 0x10) != 0) {
                    return;
                }
                next_index = turn_index + 1;
increment_index:
                turn_index = next_index;
                if (next_index < 8) {
                    goto try_heading;
                }
            }

post_loop:
            {
                s32 post_index = turn_index;
                if (post_index >= 8) {
                    ((S_800D92C0_0 *)actor)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F);
                    ((S_800D92C0_0 *)actor)->unk_46 = (u16) (((S_800D92C0_0 *)actor)->unk_46 & 0x7FFF);
                    func_800A9A0C(actor);
                    return;
                }
            }
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_s8 = (s8) (u8) position->unk_26;
            ((S_800D92C0_0 *)actor)->unk_6D.u = (u8) (((S_800D92C0_0 *)actor)->unk_6D.u - 1);
            {
                u16 *end_state = (u16 *)D_80083460;
                end_state[4] = (u16)(end_state[4] + 1);
            }
            if (((S_800D92C0_0 *)actor)->unk_6D.s != 0) {
                goto final_update;
            }

mask_and_return:
            ((S_800D92C0_0 *)actor)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)actor)->unk_71 & 0x7F);
            return;

final_update:
            turn_index = func_800BCB04((position->unk_24.at00.v << 6) | 0x20, (position->unk_24.at01.v << 6) | 0x20, (s16) (((S_800D92C0_0 *)actor)->unk_88 - 0x20));
            if (turn_index < 0x200) {
                ((S_800D92C0_0 *)actor)->unk_88 = (u16) turn_index;
            }
        }
    }
}
