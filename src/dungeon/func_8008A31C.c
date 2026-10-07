#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[6];
    s16 fieldA;
} D_80083460_t;

extern void func_80099F70(s32);
extern void func_80099F04(s32);
extern void func_80048A44(void *, u8, s16, s32);
extern s16 func_8009AF18(s16, void *, void *, s32);

extern s32 D_80081484[3];
extern u8 D_8008EAC8[];
extern u8 D_800DCFB0[8];
extern u8 D_800DCFD0[8];
extern u8 D_800DD060[8];
extern u8 D_800DD0B8[8];
extern u8 D_800DD0C8[8];
extern s32 D_800E3540[];


typedef struct S_8008FA7C_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8008FA7C_0;   /* arg1 in func_8008FA7C */

typedef struct S_8008FA7C_1 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8008FA7C_1;   /* state0_call_arg in func_8008FA7C */

typedef struct S_8008FA7C_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
} S_8008FA7C_2;   /* arg3 in func_8008FA7C */

typedef struct S_8008FA7C_3 {
    u8 pad_00[0x8C];
    union { u8 * p; s32 * p2; } unk_8C;   /* accessed as both */
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0xA];
    u16 unk_A2;
    u8 pad_A4[0x80];
    union { u8 * p; u32 i; } unk_124;   /* accessed as both */
} S_8008FA7C_3;   /* arg0 in func_8008FA7C */

typedef struct S_8008FA7C_4 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_8008FA7C_4;   /* object in func_8008FA7C */

typedef struct S_8008FA7C_5 {
    u8 pad_00[0x8A];
    s16 unk_8A;
} S_8008FA7C_5;   /* object2 in func_8008FA7C */

typedef struct S_8008FA7C_6 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x78];
    u8 unk_84;
    u8 unk_85;
    u8 pad_86[0x34BA];
    s32 unk_3540;
} S_8008FA7C_6;   /* (u8 *)state1_v1 in func_8008FA7C */

typedef struct S_8008FA7C_7 {
    u8 pad_00[0x1484];
    s32 unk_1484;
} S_8008FA7C_7;   /* (u8 *)state1_a1 in func_8008FA7C */

typedef struct S_8008FA7C_8 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8008FA7C_8;   /* call_arg in func_8008FA7C */

typedef struct S_8008FA7C_9 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8008FA7C_9;   /* state2_call_arg in func_8008FA7C */


/* Advances an actor's action state, updating linked-object flags and directional animation. */
void func_8008FA7C(u8 *actor, u8 *motion, u8 *animation, u8 *entity) {
    s16 countdown;
    s32 direction;
    s16 state;
    s32 saved_value;
    s16 action_result;
    u32 mask_or_base;
    u32 object_or_base;
    u8 *init_anim;

    state = actor[0x9B];
    switch (state) {
    case 0:
        init_anim = animation;
        ((S_8008FA7C_0 *)motion)->unk_14 = 0xFFEA0000;
        ((S_8008FA7C_1 *)init_anim)->unk_2C = D_800DD0C8;
        {
            s32 init_entry;
            u8 init_frame;

            init_entry = ((gameWork.view.viewAngle + ((S_8008FA7C_2 *)entity)->unk_2A + 0x100) >> 9) & 7;
            init_entry += (u32)D_800DD0C8;
            {
                init_frame = *(u8 *)init_entry;
            }
            /* MATCH: Keep the zero argument in the shared-call jump delay slot. */
            func_80048A44(init_anim, init_frame, 0, 1);
            actor[0x9B]++;
        }
        return;

    case 1:
        countdown = ((S_8008FA7C_3 *)actor)->unk_96 - 1;
        ((S_8008FA7C_3 *)actor)->unk_96 = countdown;
        if (countdown > 0) {
            return;
        }

        action_result = func_8009AF18(((S_8008FA7C_2 *)entity)->unk_2A, motion, animation, 8);
        if (action_result == 0) {
            actor[0x9B]++;
            return;
        }
        {
            u32 set_mask;
            u32 linked_flags;
            u8 *linked_object;
            u8 *linked_result;
            u8 *active_anim;
            u8 *active_table;
            s32 entity_angle;
            s32 active_entry;
            s32 effect_duration;
            u32 entity_flags;

            mask_or_base = 0xFFEF0000;
            linked_object = ((S_8008FA7C_3 *)actor)->unk_124.p;
            set_mask = 0x200000;
            linked_flags = ((S_8008FA7C_4 *)linked_object)->unk_1C;
            mask_or_base |= 0xFFFF;
            linked_flags |= set_mask;
            ((S_8008FA7C_4 *)linked_object)->unk_1C = linked_flags;
            linked_result = ((S_8008FA7C_3 *)actor)->unk_124.p;
            active_anim = animation;
            ((S_8008FA7C_5 *)linked_result)->unk_8A = action_result;
            effect_duration = 0x78;
            object_or_base = ((S_8008FA7C_3 *)actor)->unk_124.i;
            ((S_8008FA7C_6 *)((u8 *)object_or_base))->unk_84 = effect_duration;
            object_or_base = ((S_8008FA7C_3 *)actor)->unk_124.i;
            ((S_8008FA7C_6 *)((u8 *)object_or_base))->unk_85 = 2;
            entity_flags = ((S_8008FA7C_2 *)entity)->unk_1C;
            entity_flags &= mask_or_base;
            mask_or_base = 0x80080000;
            saved_value = ((S_8008FA7C_7 *)((u8 *)mask_or_base))->unk_1484;
            object_or_base = (u32)((D_80083460_t *)&dungeonStatus);
            ((S_8008FA7C_7 *)((u8 *)mask_or_base))->unk_1484 = 0;
            active_table = D_800DCFD0;
            ((S_8008FA7C_2 *)entity)->unk_1C = entity_flags;
            countdown = ((S_8008FA7C_6 *)((u8 *)object_or_base))->unk_0A;
            countdown++;
            ((S_8008FA7C_6 *)((u8 *)object_or_base))->unk_0A = countdown;
            ((S_8008FA7C_8 *)active_anim)->unk_2C = active_table;
            active_entry = gameWork.view.viewAngle;
            entity_angle = ((S_8008FA7C_2 *)entity)->unk_2A;
            D_800E3540[0] = saved_value;
            active_entry += entity_angle;
            active_entry += 0x100;
            active_entry >>= 9;
            active_entry &= 7;
            active_entry += (s32)active_table;
            func_80048A44(active_anim, *(u8 *)active_entry, 5, 1);
            actor[0x9B]++;
        }
        return;

    case 2:
        {
            u8 *next_anim;

            if (!(((S_8008FA7C_3 *)actor)->unk_A2 & 0x10)) {
                return;
            }
            ((S_8008FA7C_0 *)motion)->unk_14 = 0;
            next_anim = animation;
            if (((S_8008FA7C_2 *)entity)->unk_1C & 0x100000) {
                actor[0x9B]++;
            return;
            }
            ((S_8008FA7C_9 *)next_anim)->unk_2C = D_800DD060;
            {
                s32 next_entry;

                next_entry = ((gameWork.view.viewAngle + ((S_8008FA7C_2 *)entity)->unk_2A + 0x100) >> 9) & 7;
                next_entry += (u32)D_800DD060;
                func_80048A44(next_anim, *(u8 *)next_entry, 0, 1);
                actor[0x9B]++;
            }
            return;
        }

    case 3:
        if (dungeonStatus.unk_0A != 0) {
            return;
        }
        dungeonStatus.flags |= 0x412;
        func_80099F70(((S_8008FA7C_2 *)entity)->unk_5C);
        func_80099F04(((S_8008FA7C_2 *)entity)->unk_5C);
        if (((S_8008FA7C_2 *)entity)->unk_1C & 0x100000) {
            ((S_8008FA7C_3 *)actor)->unk_8C.p = D_8008EAC8;
            (*(u8 * *)((u8 *)animation + (0x2C))) = D_800DD0B8;
        } else {
            ((S_8008FA7C_3 *)actor)->unk_8C.p2 = func_8008ACDC;
            (*(u8 * *)((u8 *)animation + (0x2C))) = D_800DCFB0;
        }
        direction = ((gameWork.view.viewAngle + ((S_8008FA7C_2 *)entity)->unk_2A + 0x100) >> 9) & 7;
        func_80048A44(animation, (*(u8 * *)((u8 *)animation + (0x2C)))[direction], 0, 1);
        actor[0x9B]++;
    }
}
