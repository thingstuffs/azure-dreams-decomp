#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_8017405C_0 {
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
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
} S_8017405C_0;   /* d in func_8017405C */

typedef struct S_8017405C_1 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_8017405C_1;   /* c in func_8017405C */

typedef struct S_8017405C_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017405C_2_pre;   /* the 0x14 bytes before e in func_8017405C, addressed as e[-1] */

typedef struct S_8017405C_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8017405C_2;   /* e in func_8017405C */

typedef struct S_8017405C_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017405C_3;   /* e2 in func_8017405C */

typedef struct S_8017405C_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8017405C_4;   /* root in func_8017405C */



typedef struct S_8017405C_7_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017405C_7_pre;   /* the 0x14 bytes before pa in func_8017405C, addressed as pa[-1] */

typedef struct S_8017405C_8_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017405C_8_pre;   /* the 0x14 bytes before pb in func_8017405C, addressed as pb[-1] */

typedef struct S_8017405C_9 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017405C_9;   /* p2 in func_8017405C */

typedef struct S_8017405C_10 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017405C_10;   /* p1 in func_8017405C */

typedef struct S_8017405C_11 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8017405C_11;   /* (u8 *)d + (((S_8017405C_0 *)d)->unk_71.u & 0x7F) in func_8017405C */



typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonModeRecord;

extern void func_800A9A0C(void *);
extern void func_800A19E4(void *, void *, s32, s32, void *);
extern void *func_800A02AC(void *, s32, s32);
extern u16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A6D30(void);
extern void *func_800A04F0(void *, s32, s32, s32);
extern s16 func_8009A66C(s16, void *, void *, s32);
extern void func_800A0E6C(void *, s32, void *, void *);
extern s16 func_800A0134(void *, void *);
extern s16 func_8009A540(s32, s32, s32, s32);
extern s32 func_800A07D0(s32, s32, s32, s32);
extern s16 func_8009FD40(void *, void *);
extern s16 func_8009FD7C(s32, s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern void func_8009A21C(s32, s32, s32);
extern s16 func_8009A180(void *, void *);
extern s16 func_800BCB04(s32, s32, s16);
extern s16 func_80174BCC(void *, s32, void *, void *);

extern u16 D_80083462;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern u16 D_80082EA4;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern s16 D_8006CD00[];
extern DungeonModeRecord D_800E2970[];
extern u16 D_80083460[];

/* Chooses a movement heading, advances the actor, and updates its path state and height. */
void func_8017405C(void *context, s32 action, S_8017405C_1 *actor, void *movement)
{
    s16 move_index;
    s16 stop_fallback = 0;
    s32 heading;
    register s32 target_x ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 target_y ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 state_flags;
    s32 flags;
    void *root;

    state_flags = D_80083462;

    if ((state_flags & 0x4000) || ((S_8017405C_0 *)movement)->unk_71.s >= 0) {
        if (((S_8017405C_0 *)movement)->unk_71.s >= 0 || func_80174BCC(context, action, actor, movement) == 0) {
            func_800A9A0C(movement);
        } else {
            ((S_8017405C_0 *)movement)->unk_46 = 0xC008;
        }
        return;
    }
    if (!(state_flags & 0x2000)) {
        return;
    }

    func_800A19E4(actor, movement, 3, 6, (u8 *)context + 0x9C);
    ASM_KEEP(stop_fallback);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    flags = ((S_8017405C_0 *)movement)->unk_1C;
    if (flags & 0x410) {
        if (flags & 0x400) {
            register void *target ASM_REG("$3") = func_800A02AC(movement, actor->unk_24.at00.v, actor->unk_24.at01.v);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            if (target != 0) {
                S_8017405C_3 *target_pos = ((S_8017405C_2_pre *)target)[-1].unk_00;
                ((S_8017405C_0 *)movement)->unk_2A.u = func_800A0818(actor->unk_24.at00.v, actor->unk_24.at01.v,
                                                    target_pos->unk_24, target_pos->unk_25,
                                                    (u8 *)context + 0x98);
                ((S_8017405C_0 *)movement)->unk_71.u &= 0x7F;
                return;
            }
            {
                s32 turn_flags = ((S_8017405C_0 *)movement)->unk_14;
                if (!(turn_flags & 0x80000000)) {
                    turn_flags |= 0x80000000;
                    ((S_8017405C_0 *)movement)->unk_14 = turn_flags;
                    ((S_8017405C_0 *)movement)->unk_2A.u += (func_800A6D30() & 7) << 9;
                }
            }
            goto choose_step;
        }
        if (func_800A04F0(movement, actor->unk_24.at00.v, actor->unk_24.at01.v, ((S_8017405C_0 *)movement)->unk_2A.s) == 0) {
            goto choose_step;
        }
        goto stop_path;
    }
    if (flags & 0x2000) {
        if (((S_8017405C_0 *)movement)->unk_46 & 0x8000) {
            goto choose_step;
        }
        if (!(flags & 0x20000)) {
            goto update_heading;
        }
        {
            void **root_page = &D_800814A8;
            register u8 *leader_pos ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            register unsigned long x_lookup ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            unsigned long y_lookup;
            register s32 leader_x ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 leader_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            register s32 y_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            u8 actor_x;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            leader_pos = D_80082E80;
            x_lookup = (unsigned long)D_8006CCD8;
            root = *root_page;
            y_lookup = ((S_8017405C_0 *)movement)->unk_45;
            leader_x = leader_pos[0x24];
            y_lookup += (s16)((S_8017405C_4 *)root)->unk_2A >> 9;
            leader_y = leader_pos[0x25];
            y_lookup &= 7;
            y_lookup <<= 1;
            x_lookup += y_lookup;
            {
                u16 *y_steps = D_8006CCE8;
                y_lookup += (unsigned long)y_steps;
                x_lookup = *(u16 *)x_lookup;
                y_offset = *(u16 *)y_lookup;
            }
            actor_x = actor->unk_24.at00.v;
            target_x = leader_x + (s32)x_lookup;
            target_y = leader_y + y_offset;
            if (actor_x == (u16)target_x && actor->unk_24.at01.v == (u16)target_y) {
                goto stop_path;
            }
        }
        {
            void *path_state = (u8 *)context + 0x98;
            u16 target_heading = func_800A0818(actor->unk_24.at00.v, actor->unk_24.at01.v, (s16)target_x, (s16)target_y, path_state);
            ((S_8017405C_0 *)movement)->unk_2A.u = target_heading;
            if (func_8009A66C((s16)target_heading, actor, movement, 0x20) > 0) {
                goto choose_step;
            }
            {
                u8 *leader_pos = (u8 *)&D_80082EA4 - 0x24;
                ((S_8017405C_0 *)movement)->unk_2A.u = func_800A0818(actor->unk_24.at00.v, actor->unk_24.at01.v,
                                                    leader_pos[0x24], leader_pos[0x25], path_state);
            }
        }
        goto choose_step;
    }
    {
        s32 mode = actor->unk_26.s;
        if (mode >= 0 && (D_800E2970[mode].flags & 2)) {
update_heading:
            func_800A0E6C(actor, ((Rec_func_800A9E70_arg0 *)context)->unk_9C.as_s8, movement, (u8 *)context + 0x98);
            goto choose_step;
        }
    }
    if (!(((S_8017405C_0 *)movement)->unk_46 & 0x8000)) {
        register void *target ASM_REG("$3") = func_800A04F0(movement, actor->unk_24.at00.v, actor->unk_24.at01.v, ((S_8017405C_0 *)movement)->unk_2A.s);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        if (target != 0 && (((S_8017405C_2 *)target)->unk_1C & 0x2000) && func_800A0134(target, movement) < 0x81) {
            if (func_8009A540((((s16)((S_8017405C_0 *)movement)->unk_2A.u >> 9) & 0xFFFF),
                              actor->unk_24.at00.v, actor->unk_24.at01.v,
                              (s16)(((S_8017405C_0 *)movement)->unk_88 - 0x20)) != 0) {
                goto stop_path;
            }
        }
    }
    if (((S_8017405C_0 *)movement)->unk_1C & 0x20000) {
        void *first_master;
        void *second_master;
        ((Rec_func_800A9E70_arg0 *)context)->unk_A6 = 0;
        first_master = ((Rec_D_800814A8 *)D_800814A8)->unk_AC;
        if (first_master != 0) {
            second_master = ((Rec_D_800814A8 *)D_800814A8)->unk_B0;
            if (second_master != 0) {
                goto follow_master;
            }
        }
        {
            u8 *leader_pos = D_80082E80;
            s32 angle_delta;
            s32 relative_angle;
            angle_delta = func_800A07D0(leader_pos[0x24], leader_pos[0x25],
                                  actor->unk_24.at00.v, actor->unk_24.at01.v);
            relative_angle = (((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_u16 + angle_delta) & 0xFFF;
            if (relative_angle > 0x400 && relative_angle < 0xC00) {
                ((S_8017405C_0 *)movement)->unk_45 = 3;
            } else if (relative_angle == 0x400 || relative_angle == 0xC00) {
                ((S_8017405C_0 *)movement)->unk_45 = 1;
            } else {
                ((S_8017405C_0 *)movement)->unk_45 = 2;
            }
        }
        {
            void **root_page = &D_800814A8;
            register u8 *leader_pos = D_80082E80;
            register unsigned long x_lookup ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            unsigned long y_lookup;
            s32 target_x_sum;
            register u16 target_x ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            register u16 target_y ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 actor_x;
            s32 actor_y;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            x_lookup = (unsigned long)D_8006CCD8;
            root = *root_page;
            actor_x = actor->unk_24.at00.v;
            actor_y = actor->unk_24.at01.v;
            y_lookup = (((S_8017405C_0 *)movement)->unk_45 + ((s16)((S_8017405C_4 *)root)->unk_2A >> 9)) & 7;
            target_x_sum = *(volatile u8 *)(leader_pos + 0x24);
            y_lookup <<= 1;
            x_lookup += y_lookup;
            {
                u16 *y_steps = D_8006CCE8;
                y_lookup += (unsigned long)y_steps;
                x_lookup = *(u16 *)x_lookup;
                y_lookup = *(u16 *)y_lookup;
            }
            target_x_sum += (s32)x_lookup;
            target_x = target_x_sum;
            target_x_sum = (s16)target_x_sum;
            x_lookup = leader_pos[0x25];
            x_lookup += y_lookup;
            target_y = (s32)x_lookup;
            x_lookup = (s16)(s32)x_lookup;
            ((S_8017405C_0 *)movement)->unk_2A.u = func_800A0818(actor_x, actor_y,
                                                target_x_sum, (s32)x_lookup, (u8 *)context + 0x98);
            {
                s32 current_x = actor->unk_24.at00.v;
                register s32 expected_x ASM_REG("$2") = (u16)target_x;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                if (current_x != expected_x) {
                    goto choose_step;
                }
            }
            {
                s32 current_y = actor->unk_24.at01.v;
                register s32 expected_y ASM_REG("$2") = (u16)target_y;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                if (current_y != expected_y) {
                    goto choose_step;
                }
            }
        }
        goto stop_path;
follow_master:
        {
            void *first_pos = ((S_8017405C_7_pre *)first_master)[-1].unk_00;
            register void *second_pos ASM_REG("$17") = ((S_8017405C_8_pre *)second_master)[-1].unk_00;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s16 first_distance = func_8009FD40(first_pos, actor);
            if (first_distance < func_8009FD40(second_pos, actor)) {
                ((S_8017405C_0 *)movement)->unk_2A.u = func_800A0818(actor->unk_24.at00.v, actor->unk_24.at01.v,
                                                    ((S_8017405C_9 *)first_pos)->unk_24, ((S_8017405C_9 *)first_pos)->unk_25,
                                                    (u8 *)context + 0x98);
                if (func_8009FD7C(actor->unk_24.at00.v, actor->unk_24.at01.v,
                                  ((S_8017405C_9 *)first_pos)->unk_24, ((S_8017405C_9 *)first_pos)->unk_25) == 0) {
                    goto choose_step;
                }
                goto stop_path;
            }
            ((S_8017405C_0 *)movement)->unk_2A.u = func_800A0818(actor->unk_24.at00.v, actor->unk_24.at01.v,
                                                ((S_8017405C_10 *)second_pos)->unk_24, ((S_8017405C_10 *)second_pos)->unk_25,
                                                (u8 *)context + 0x98);
            if (func_8009FD7C(actor->unk_24.at00.v, actor->unk_24.at01.v,
                              ((S_8017405C_9 *)first_pos)->unk_24, ((S_8017405C_9 *)first_pos)->unk_25) == 0) {
                goto choose_step;
            }
            ASM_KEEP(first_pos);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            goto stop_path;
        }
    }
    if (((Rec_func_800A9E70_arg0 *)context)->unk_A6 != 0) {
        goto choose_step;
    }
    ((Rec_func_800A9E70_arg0 *)context)->unk_A6 = 1;
    ((Rec_func_800A9E70_arg0 *)context)->unk_A4 = ((func_800A6D30() & 3) << 10) + 0x200;

choose_step:
    move_index = 0;
    {
        s16 *heading_offsets = D_8006CD00;
try_heading:
        {
            if (((Rec_func_800A9E70_arg0 *)context)->unk_A6 != 0) {
                s32 base_heading = ((Rec_func_800A9E70_arg0 *)context)->unk_A4;
                if (((Rec_func_800A9E70_arg0 *)context)->unk_98 & 2) {
                    heading = base_heading - heading_offsets[move_index];
                } else {
                    heading = base_heading + heading_offsets[move_index];
                }
            } else {
                register s32 base_heading ASM_REG("$3") = ((S_8017405C_0 *)movement)->unk_2A.s;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                if (((Rec_func_800A9E70_arg0 *)context)->unk_98 & 2) {
                    heading = base_heading - heading_offsets[move_index];
                } else {
                    heading = base_heading + heading_offsets[move_index];
                }
            }
            if (func_8009A66C(heading, actor, movement, 0x20) > 0) {
                if (move_index >= 3) {
                    if (stop_fallback != 0) {
                        goto stop_path;
                    }
                    if (((Rec_func_800A9E70_arg0 *)context)->unk_A6 != 0) {
                        goto stop_path;
                    }
                }
                ((S_8017405C_0 *)movement)->unk_2A.u = heading;
                ((S_8017405C_11 *)((u8 *)movement + (((S_8017405C_0 *)movement)->unk_71.u & 0x7F)))->unk_74 = actor->unk_24.at00.v;
                ((S_8017405C_11 *)((u8 *)movement + (((S_8017405C_0 *)movement)->unk_71.u & 0x7F)))->unk_7C = actor->unk_24.at01.v;
                ((S_8017405C_0 *)movement)->unk_71.u = ((S_8017405C_0 *)movement)->unk_71.u + 1;
                func_8009A3D0(actor->unk_24.at00.v, actor->unk_24.at01.v,
                              (((S_8017405C_0 *)movement)->unk_1C & 0x2000) ? 0x300 : 0x3000);
                {
                    s32 step_offset;
                    register u8 *x_steps ASM_REG("$3") = (u8 *)D_8006CCD8;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    step_offset = (((S_8017405C_0 *)movement)->unk_2A.u >> 8) & 0xE;
                    actor->unk_24.at00.v = actor->unk_24.at00.v +
                                         *(u8 *)((unsigned long)step_offset + (unsigned long)x_steps);
                    {
                        u8 *y_steps = (u8 *)D_8006CCE8;
                        actor->unk_24.at01.v = actor->unk_24.at01.v +
                                             *(u8 *)((unsigned long)step_offset + (unsigned long)y_steps);
                    }
                }
                func_8009A21C(actor->unk_24.at00.v, actor->unk_24.at01.v,
                              (((S_8017405C_0 *)movement)->unk_1C & 0x2000) ? 0x300 : 0x3000);
                goto step_done;
            }
            if (move_index == 0 && D_80082EA4 != actor->unk_24.at00u.v) {
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                if (func_8009A180(movement, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pu8 + 0x20) != 0) {
                    return;
                }
            }
            move_index = move_index + 1;
            if (move_index < 8) {
                goto try_heading;
            }
        }
    }
step_done:

    if (move_index >= 8) {
        ((S_8017405C_0 *)movement)->unk_71.u &= 0x7F;
        ((S_8017405C_0 *)movement)->unk_46 &= 0x7FFF;
        func_800A9A0C(movement);
        return;
    }
    {
        u16 *counters = D_80083460;
        ((S_8017405C_0 *)movement)->unk_46 &= 0x7FFF;
        ((Rec_func_800A9E70_arg0 *)context)->unk_9C.as_s8 = actor->unk_26.u;
        ((S_8017405C_0 *)movement)->unk_6D.u = ((S_8017405C_0 *)movement)->unk_6D.u - 1;
        counters[4] = counters[4] + 1;
    }
    if (((S_8017405C_0 *)movement)->unk_6D.s != 0) {
        goto update_height;
    }
stop_path:
    ((S_8017405C_0 *)movement)->unk_71.u &= 0x7F;
    return;
update_height:
    move_index = func_800BCB04((actor->unk_24.at00.v << 6) | 0x20,
                        (actor->unk_24.at01.v << 6) | 0x20,
                        (s16)(((S_8017405C_0 *)movement)->unk_88 - 0x20));
    if (move_index < 0x200) {
        ((S_8017405C_0 *)movement)->unk_88 = move_index;
    }
    return;
}
