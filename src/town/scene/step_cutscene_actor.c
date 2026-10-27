#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"


typedef struct Copy12 {
    s32 word[3];
} Copy12;

extern s32 func_80034A1C();
extern s32 func_8003EA54();
extern s32 func_80071494(void);
extern s32 func_80245C10();
extern s16 func_8025E01C(void *position);
extern s32 scene_object_flags;
extern s32 D_80526430[3];
extern u8 D_80288EE0[];
extern u8 D_80288FF0[];
extern u8 D_80289030[];
extern u8 D_80289058[];
extern u8 D_80288F60[];
extern u8 D_80288F88[];


typedef struct S_8080DF94_0 {
    void * unk_00;
    s16 unk_04;
    u16 unk_06;
    u16 unk_08;
} S_8080DF94_0;   /* obj in step_cutscene_actor */

typedef struct S_8080DF94_1 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x2E];
    s16 unk_36;
} S_8080DF94_1;   /* owner in step_cutscene_actor */



typedef struct S_8080DF94_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8080DF94_4;   /* target in step_cutscene_actor */

/* Per-frame step for the town cutscene actor: dispatch its state and drive its motion, colour fade and timers. */
void step_cutscene_actor(void *obj, ObjectPosition *motion, SpriteFrameState *part) {
    Copy12 scratch;
    s16 state;
    s32 result;
    s32 *scratch_words;
    s32 flag;
    u16 count;
    u16 ticks;
    void *owner;
    void *target;
    s32 vel_x;
    s32 step_x;
    s32 pos_x;

    owner = ((S_8080DF94_0 *)obj)->unk_00;
    scratch_words = scratch.word;
    flag = 0;
    target = (*(void **)((u8 *)(((S_8080DF94_1 *)owner)->unk_04) + (8)));
    scratch = *(Copy12 *)D_80526430;
    func_8003EA54(part);
    func_80245C10(motion);
    state = ((S_8080DF94_0 *)obj)->unk_04;

    switch (state) {
    case 0:
        part->color.word = (s32)(part->color.word + 0x101010);
        if ((u8)part->color.word >= 0xA0U) {
            part->color.word = 0x808080;
            part->flags = (u16)(part->flags & 0xFFF3);
            ((S_8080DF94_0 *)obj)->unk_04 = (s16)((u16)((S_8080DF94_0 *)obj)->unk_04 + 1);
        }
        break;
    case 1:
        if (((S_8080DF94_0 *)obj)->unk_08 & 1) {
            result = func_80071494();
            flag = scratch_words[result % 3];
            motion->velocity_x = (s32)(((func_80071494() & 0x7F) - 0x40) << 0xF);
            motion->velocity_z = (s32)((0 - ((func_80071494() & 0xF) + 8)) << 0x10);
            if (motion->velocity_x > 0) {
                part->flags = (u16)(part->flags | 1);
            }
            motion->velocity_y = (s32)((S_8080DF94_4 *)target)->unk_10;
            ((S_8080DF94_0 *)obj)->unk_04 = 0x20;
        }
        if (((S_8080DF94_1 *)owner)->unk_36 == 0xA) {
            if (func_80071494() & 1) {
                flag = (s32)D_80289030;
            } else {
                flag = (s32)D_80289058;
            }
            {
                s32 next_state = 0x100;
                ((S_8080DF94_0 *)obj)->unk_04 = (s16)next_state;
            }
        }
        break;
    case 0x20:
    {
        s16 floor_y;

        motion->velocity_z = (s32)(motion->velocity_z + 0x40000);
        floor_y = func_8025E01C(motion);
        if (floor_y < motion->z.v) {
            motion->z.v = (s32)floor_y;
            motion->velocity_z = (s32)((s32)(0 - motion->velocity_z) >> 3);
        }
        if (part->flags & 0x6000) {
            ((S_8080DF94_0 *)obj)->unk_06 = 0xA;
            if (part->unk_00 == D_80288FF0) {
                part->color.word = 0xA0A0A0;
                part->flags = (u16)(part->flags | 0xC);
                ((S_8080DF94_0 *)obj)->unk_04 = 0x22;
                break;
            }
            if (func_80071494() & 1) {
                flag = (s32)D_80288F60;
            } else {
                flag = (s32)D_80288F88;
            }
            ((S_8080DF94_0 *)obj)->unk_04 = (s16)((u16)((S_8080DF94_0 *)obj)->unk_04 + 1);
        }
        pos_x = motion->velocity_x;
        vel_x = motion->velocity_y;
        step_x = pos_x >> 3;
        pos_x -= step_x;
        motion->velocity_x = pos_x;
        pos_x = vel_x >> 3;
        vel_x -= pos_x;
        motion->velocity_y = vel_x;
        break;
    }
    case 0x21:
    {
        s16 floor_y;

        motion->velocity_z = (s32)(motion->velocity_z + 0x40000);
        floor_y = func_8025E01C(motion);
        if (floor_y < motion->z.v) {
            motion->z.v = (s32)floor_y;
            motion->velocity_z = (s32)((s32)(0 - motion->velocity_z) >> 3);
        }
        pos_x = motion->velocity_x;
        vel_x = motion->velocity_y;
        step_x = pos_x >> 3;
        pos_x -= step_x;
        motion->velocity_x = pos_x;
        pos_x = vel_x >> 3;
        vel_x -= pos_x;
        motion->velocity_y = vel_x;
        count = part->flags;
        if (count & 0x6000) {
            part->flags = (u16)(count | 0xC);
            part->color.word = 0xA0A0A0;
            ((S_8080DF94_0 *)obj)->unk_04 = (s16)((u16)((S_8080DF94_0 *)obj)->unk_04 + 1);
        }
        break;
    }
    case 0x22:
        part->color.word = (s32)(part->color.word + 0xFFDFDFE0);
        if (motion->z.v > 0) {
            motion->velocity_z = 0;
            motion->z.v = 0;
        }
        if ((u8)part->color.word < 0x20U) {
            part->color.word = 0;
        }
        if ((((S_8080DF94_1 *)owner)->unk_36 == 9) || (ticks = ((S_8080DF94_0 *)obj)->unk_06 - 1,
            ((S_8080DF94_0 *)obj)->unk_06 = ticks, ((ticks << 0x10) <= 0))) {
            ((S_8080DF94_0 *)obj)->unk_04 = 0xFFF;
        }
        break;
    case 0x100:
        part->color.word = 0xA0A0A0;
        part->flags = (u16)(part->flags | 0xC);
        ((S_8080DF94_0 *)obj)->unk_04 = (s16)((u16)((S_8080DF94_0 *)obj)->unk_04 + 1);
                        /* fall through */
    case 0x101:
        part->color.word = (s32)(part->color.word + 0xFFDFDFE0);
        if ((u8)part->color.word < 0x20U) {
            part->color.word = 0;
            ((S_8080DF94_0 *)obj)->unk_04 = 0xFFF;
        }
        break;
    case 0xFFF:
    {
        s32 global_flags;

        (*(u16 *)((u8 *)(obj) + (-2))) = (u16)((*(u16 *)((u8 *)(obj) + (-2))) | 0x8000);
        global_flags = scene_object_flags;
        global_flags |= 0x8000;
        scene_object_flags = global_flags;
        break;
    }
    }

    if (flag != 0) {
        func_80034A1C(part, flag, 0);
        part->flags = (u16)(part->flags & 0x9FFF);
    }
}
