#include "common.h"
#include "records/Rec_D_800814A8.h"


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern s32 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171FC8(void *, void *, void *, void *);
extern void func_801721D8(void *, void *, void *, void *);
extern s32 func_80172920(void *, void *, void *, void *);
extern void func_80172AAC(void *, void *, void *, void *);
extern s32 func_80172B8C(void *, void *, void *, void *);
extern void func_801743F0(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern s32 D_801719DC;
extern u8 D_80174634[];
extern u8 D_80174644[];
extern u8 D_80174674[];
extern u8 D_8017467C[];
extern u8 D_80174684[];


typedef struct S_801719DC_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_A4;   /* overlapping accesses */
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
    u8 pad_B4[0x4];
    s16 unk_B8;
} S_801719DC_0;   /* arg0 in func_801719DC */

typedef struct S_801719DC_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_801719DC_1;   /* arg3 in func_801719DC */

typedef struct S_801719DC_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_801719DC_2;   /* arg2 in func_801719DC */


typedef struct S_801719DC_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801719DC_4;   /* origin in func_801719DC */

typedef struct S_801719DC_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_801719DC_5;   /* player in func_801719DC */

/* Update actor animation, facing, and action dispatch from dungeon state. */
void func_801719DC(void *motion_in, void *context_in, void *entity_in, void *actor_in)
{
    static void *const action_labels[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    s32 direction_aux;
    s8 room_id;
    u16 action_state;
    void *motion = motion_in;
    register void *context ASM_REG("$16") = context_in;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *entity = entity_in;
    void *actor = actor_in;

    if (D_80083462 & 0x1000) {
        ((S_801719DC_0 *)motion)->unk_9A = 0xE;
        func_80171FC8(motion_in, context_in, entity_in, actor_in);
        return;
    }
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(context);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    if (((S_801719DC_1 *)actor)->unk_25 == 0) {
        void *anim_table;

        func_800AA79C(motion, context, entity, actor);
        if (((S_801719DC_2 *)entity)->unk_2C == D_80174684) {
            return;
        }
        anim_table = D_8017467C;
        (*(void * *)((u8 *)entity + (0x2C))) = anim_table;
        func_80047784(entity,
            ((u8 *)anim_table)[((D_80083228 + ((S_801719DC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_801719DC_1 *)actor)->unk_1C & 0x200) {
        if (((S_801719DC_2 *)entity)->unk_2C == D_80174684) {
            ((S_801719DC_0 *)motion)->unk_9A = 0xD;
            ((S_801719DC_0 *)motion)->unk_9B = 1;
            ((S_801719DC_0 *)motion)->unk_8C = 0;
            ((S_801719DC_1 *)actor)->unk_1C &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(motion, context, entity, D_8017467C) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_801719DC_1 *)actor)->unk_1C & 0x100) {
            func_800AA258(motion, context, entity, actor);
            return;
        }

        {
            s32 current_state;
            u32 next_state;
            void *current_anim;
            void *anim_table;
            s32 motion_value;

            current_state = ((S_801719DC_0 *)motion)->unk_9A;

            next_state = 0xE;
            if (current_state != next_state) {
                current_anim = ((S_801719DC_2 *)entity)->unk_2C;
                anim_table = D_80174634;
                if (current_anim != anim_table) {
                    (*(void * *)((u8 *)entity + (0x2C))) = anim_table;
                    func_80047784(entity,
                        ((u8 *)anim_table)[((D_80083228 + ((S_801719DC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                        1);
                    ((S_801719DC_2 *)entity)->unk_05 = 1;
                    motion_value = ((S_801719DC_0 *)motion)->unk_A4.at00.v;
                    ((S_801719DC_0 *)motion)->unk_A4.at02.v = 0;
                    ((S_801719DC_0 *)motion)->unk_B8 = 0;
                    ((S_801719DC_0 *)motion)->unk_AC = 0;
                    ((S_801719DC_0 *)motion)->unk_B0 = 0;
                    ((S_801719DC_0 *)motion)->unk_A8 = motion_value;
                }
                ((S_801719DC_0 *)motion)->unk_9A = next_state;
            }
        }

        ((S_801719DC_0 *)motion)->unk_98 &= 0xFFF3;
        ((S_801719DC_1 *)actor)->unk_1C |= 0x40000;

        if (((S_801719DC_1 *)actor)->unk_64 != 0) {
            if (func_800AA6B4(motion, context, entity, D_80174644) != 0) {
                return;
            }
        }

        if (((S_801719DC_1 *)actor)->unk_1C & 0x80000) {
            u16 base_offset;
            u16 offset_delta;
            s32 motion_value;

            func_800AA888(motion, context, entity, actor);
            base_offset = ((S_801719DC_0 *)motion)->unk_92;
            offset_delta = ((S_801719DC_0 *)motion)->unk_A4.at02u.v;
            motion_value = ((S_801719DC_0 *)motion)->unk_A4.at00.v;
            ((S_801719DC_0 *)motion)->unk_A4.at02.v = 0;
            ((S_801719DC_0 *)motion)->unk_B8 = 0;
            ((S_801719DC_0 *)motion)->unk_AC = 0;
            ((S_801719DC_0 *)motion)->unk_B0 = 0;
            ((S_801719DC_0 *)motion)->unk_92 = base_offset - offset_delta;
            ((S_801719DC_0 *)motion)->unk_A8 = motion_value;
            func_801743F0(motion, context, entity, actor);
            return;
        }

        if ((func_800A1C58(actor) << 16) != 0) {
            func_800AAB10(motion, context, entity, actor);
        }
    }

    room_id = func_8009FB34(((S_801719DC_2 *)entity)->unk_24.at00.v, ((S_801719DC_2 *)entity)->unk_24.at01.v);
    ((S_801719DC_2 *)entity)->unk_26 = room_id;

    if (((S_801719DC_1 *)actor)->unk_6D > 0) {
        if (((S_801719DC_1 *)actor)->unk_1C & 0x20) {
            goto case_12;
        }
        if (((S_801719DC_2 *)entity)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((S_801719DC_1 *)actor)->unk_46 & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(actor,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172B8C(motion, context, entity, 0) << 16) == 0) {
                return;
            }
            action_state = ((S_801719DC_1 *)actor)->unk_46 | 0x4000;
            ((S_801719DC_1 *)actor)->unk_46 = action_state;
            if (!(action_state & 0x8000)) {
                goto generic;
            }
        }

        action_state = ((S_801719DC_1 *)actor)->unk_46 & 0x3FFF;
        if ((u32)(action_state - 1) >= 12) {
            goto generic;
        }
        (void)action_labels;
        goto *D_80170808[(u32)(action_state - 1)];

jt_c8:
jt_c9:
        if ((func_80172920(motion, context, entity, actor) << 16) != 0) {
            return;
        }
        func_80172AAC(motion, context, entity, actor);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 heading;

            heading = func_800A0818(
                ((S_801719DC_2 *)entity)->unk_24.at00.v, ((S_801719DC_2 *)entity)->unk_24.at01.v,
                ((S_801719DC_4 *)origin)->unk_24, ((S_801719DC_4 *)origin)->unk_25,
                &direction_aux);
            player = D_800814A8;
            ((S_801719DC_1 *)actor)->unk_2A = heading;
            if (((S_801719DC_5 *)player)->unk_9A == 0x11) {
                goto case_123;
            }
        }

jt_c12:
case_12:
        func_800A9A0C(actor);
        return;

jt_c1:
jt_c2:
jt_c3:
case_123:
        func_800AAF00(motion, context, entity, D_80174674, &D_801719DC);
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_801721D8(motion, context, entity, actor);
        return;
    }

    if (!(((S_801719DC_1 *)actor)->unk_1C & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(((DungeonRecord *)D_800E2970)[room_index].flags & 2)) {
            if (!(((S_801719DC_1 *)actor)->unk_1C & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_801719DC_2 *)entity)->unk_24.at00.v, ((S_801719DC_2 *)entity)->unk_24.at01.v,
                        ((S_801719DC_4 *)origin)->unk_24, ((S_801719DC_4 *)origin)->unk_25) << 16) != 0) {
                    ((S_801719DC_1 *)actor)->unk_2A = func_800A0818(
                        ((S_801719DC_2 *)entity)->unk_24.at00.v, ((S_801719DC_2 *)entity)->unk_24.at01.v,
                        ((S_801719DC_4 *)origin)->unk_24, ((S_801719DC_4 *)origin)->unk_25,
                        &direction_aux);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_801719DC_2 *)entity)->unk_14 & 0x40) {
        return;
    }
    {
        void *anim_table = D_80174634;
        s32 motion_value;

        if (((S_801719DC_2 *)entity)->unk_2C != anim_table) {
            (*(void * *)((u8 *)entity + (0x2C))) = anim_table;
            func_80047784(entity,
                ((u8 *)anim_table)[((D_80083228 + ((S_801719DC_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                1);
            ((S_801719DC_2 *)entity)->unk_05 = 1;
            motion_value = ((S_801719DC_0 *)motion)->unk_A4.at00.v;
            ((S_801719DC_0 *)motion)->unk_A4.at02.v = 0;
            ((S_801719DC_0 *)motion)->unk_B8 = 0;
            ((S_801719DC_0 *)motion)->unk_AC = 0;
            ((S_801719DC_0 *)motion)->unk_B0 = 0;
            ((S_801719DC_0 *)motion)->unk_A8 = motion_value;
        }
    }
}
