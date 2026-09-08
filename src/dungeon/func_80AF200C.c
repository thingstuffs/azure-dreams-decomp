#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8017380C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017380C_0;   /* arg0 in func_8017380C */






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
    if (((Rec_D_800E3D7C *)actor)->unk_28 == 0) {
        goto stop_movement;
    }
    if (!(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
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
            ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 =
                *(s16 *)((u8 *)&D_8006CCD8 +
                    ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 19;
            ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
                *(s16 *)((u8 *)&D_8006CCE8 +
                    ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 19;
            goto end;
        }
        if (frames_left != 0) {
            goto end;
        }
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 =
            *(s16 *)((u8 *)&D_8006CCD8 +
                ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 18;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            *(s16 *)((u8 *)&D_8006CCE8 +
                ((((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 8) & 0xE)) << 18;
        ((S_8017380C_0 *)action)->unk_96.s = 6;
        ((S_8017380C_0 *)action)->unk_9B++;
        goto end;
    }

return_to_tile:
    if (((Rec_D_800E3D7C *)actor)->unk_28 != 0) {
        goto interpolate_return;
    }
stop_movement:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800AAA54(action, motion, entity, D_801759C8);
    goto end;

interpolate_return:
    {
        s16 return_frames;
        s32 origin_y;
        u16 previous_frames;

        return_frames = ((S_8017380C_0 *)action)->unk_96.s;
        if (return_frames != 0) {
            ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 =
                (((((Rec_D_80082E80 *)entity)->unk_24 << 6) - ({ ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20; })) << 16) / return_frames;
            origin_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;
            ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
                (((((Rec_D_80082E80 *)entity)->unk_25 << 6) - origin_y) << 16) /
                ((S_8017380C_0 *)action)->unk_96.s;
        }
        previous_frames = ((S_8017380C_0 *)action)->unk_96.u;
        ((S_8017380C_0 *)action)->unk_96.s = previous_frames - 1;
        if ((s32)(previous_frames << 16) > 0) {
            goto end;
        }
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        ((S_8017380C_0 *)action)->unk_9B++;
        goto end;
    }

finish_movement:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)entity)->unk_24, ((Rec_D_80082E80 *)entity)->unk_25);
    if (((Rec_D_80082E80 *)entity)->unk_2C.as_pv == D_80175998) {
        u8 *direction_table;

        direction_table = D_80175988;
        (*(void * *)((u8 *)entity + 0x2C)) = direction_table;
        func_80047784(entity,
            direction_table[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
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
