#include "common.h"

typedef struct S_8017380C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017380C_0;   /* arg0 in func_8017380C */

typedef struct S_8017380C_1 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x1];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
} S_8017380C_1;   /* arg3 in func_8017380C */

typedef struct S_8017380C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8017380C_2;   /* arg2 in func_8017380C */

typedef struct S_8017380C_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017380C_3;   /* arg1 in func_8017380C */



extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_801717F4;
extern u8 D_80175988[];
extern u8 D_80175998[];
extern u8 D_801759C8[];

extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

/* Updates a staged movement sequence and returns the entity to its tile. */
void func_8017380C(void *action, void *motion, void *entity, void *actor)
{
    s32 state;

    state = ((S_8017380C_0 *)action)->unk_9B;
    if (state == 1) {
        goto move_outward;
    }
    if (state < 2) {
        if (state == 0) {
            goto init_movement;
        }
        goto end;
    }
    if (state == 2) {
        goto return_to_tile;
    }
    if (state == 3) {
        goto finish_movement;
    }
    goto end;

init_movement:
    func_800AD4D0(actor);
    ((S_8017380C_0 *)action)->unk_96.s = 4;
    ((S_8017380C_0 *)action)->unk_9B++;
    if (((S_8017380C_1 *)actor)->unk_28 == 0) {
        goto stop_movement;
    }
    if (!(((S_8017380C_2 *)entity)->unk_14 & 0x8000)) {
        goto end;
    }
    ((S_8017380C_0 *)action)->unk_96.s = 0;
    ((S_8017380C_0 *)action)->unk_9B = 3;
    goto end;

move_outward:
    {
        s16 frames_left;

        frames_left = ((S_8017380C_0 *)action)->unk_96.u - 1;
        ((S_8017380C_0 *)action)->unk_96.s = frames_left;
        if (frames_left > 0) {
            ((S_8017380C_3 *)motion)->unk_0C =
                *(s16 *)((u8 *)&D_8006CCD8 +
                    ((((S_8017380C_1 *)actor)->unk_6A >> 8) & 0xE)) << 19;
            ((S_8017380C_3 *)motion)->unk_10 =
                *(s16 *)((u8 *)&D_8006CCE8 +
                    ((((S_8017380C_1 *)actor)->unk_6A >> 8) & 0xE)) << 19;
            goto end;
        }
        if (frames_left != 0) {
            goto end;
        }
        ((S_8017380C_3 *)motion)->unk_0C =
            *(s16 *)((u8 *)&D_8006CCD8 +
                ((((S_8017380C_1 *)actor)->unk_6A >> 8) & 0xE)) << 18;
        ((S_8017380C_3 *)motion)->unk_10 =
            *(s16 *)((u8 *)&D_8006CCE8 +
                ((((S_8017380C_1 *)actor)->unk_6A >> 8) & 0xE)) << 18;
        ((S_8017380C_0 *)action)->unk_96.s = 6;
        ((S_8017380C_0 *)action)->unk_9B++;
        goto end;
    }

return_to_tile:
    if (((S_8017380C_1 *)actor)->unk_28 != 0) {
        goto interpolate_return;
    }
stop_movement:
    ((S_8017380C_3 *)motion)->unk_14 = 0;
    ((S_8017380C_3 *)motion)->unk_10 = 0;
    ((S_8017380C_3 *)motion)->unk_0C = 0;
    func_800AAA54(action, motion, entity, D_801759C8);
    goto end;

interpolate_return:
    {
        s16 return_frames;
        s32 origin_y;
        u16 previous_frames;

        return_frames = ((S_8017380C_0 *)action)->unk_96.s;
        if (return_frames != 0) {
            ((S_8017380C_3 *)motion)->unk_0C =
                (((((S_8017380C_2 *)entity)->unk_24 << 6) - ({ ((S_8017380C_3 *)motion)->unk_02 - 0x20; })) << 16) / return_frames;
            origin_y = ((S_8017380C_3 *)motion)->unk_06 - 0x20;
            ((S_8017380C_3 *)motion)->unk_10 =
                (((((S_8017380C_2 *)entity)->unk_25 << 6) - origin_y) << 16) /
                ((S_8017380C_0 *)action)->unk_96.s;
        }
        previous_frames = ((S_8017380C_0 *)action)->unk_96.u;
        ((S_8017380C_0 *)action)->unk_96.s = previous_frames - 1;
        if ((s32)(previous_frames << 16) > 0) {
            goto end;
        }
        ((S_8017380C_3 *)motion)->unk_14 = 0;
        ((S_8017380C_3 *)motion)->unk_10 = 0;
        ((S_8017380C_3 *)motion)->unk_0C = 0;
        ((S_8017380C_0 *)action)->unk_9B++;
        goto end;
    }

finish_movement:
    ((S_8017380C_3 *)motion)->unk_14 = 0;
    ((S_8017380C_3 *)motion)->unk_10 = 0;
    ((S_8017380C_3 *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((S_8017380C_2 *)entity)->unk_24, ((S_8017380C_2 *)entity)->unk_25);
    if (((S_8017380C_2 *)entity)->unk_2C == D_80175998) {
        u8 *direction_table;

        direction_table = D_80175988;
        (*(void * *)((u8 *)entity + 0x2C)) = direction_table;
        func_80047784(entity,
            direction_table[((D_80083228 + ((S_8017380C_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
    {
        s32 *entity_refs;
        s32 entity_ref;

        entity_refs = &D_80083460;
        entity_ref = entity_refs[4];
        if (entity_ref == (s32)((u8 *)actor - 0x20)) {
            entity_refs[4] = entity_ref & 0x7FFFFFFF;
        }
    }
    ((S_8017380C_0 *)action)->unk_8C = &D_801717F4;

end:
    return;
}
