#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct EarlyCallData {
    u8 pad0[8];
    s32 value;
} EarlyCallData;

extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern s16 D_800E3DA8[2];
s32 func_8003DE58();
s32 func_8004CAE8(s32, s32);
M2C_UNK func_80094E34();
s32 func_8009B88C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AACA4();
M2C_UNK func_8009A21C();
M2C_UNK func_800AA36C();
s16 func_800BCB04();




typedef struct S_800AC82C_2_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_800AC82C_2_pre;   /* the 0x18 bytes before temp_v0 in func_800AC82C, addressed as temp_v0[-1] */

typedef struct S_800AC82C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x18];
    u8 unk_24;
    u8 unk_25;
} S_800AC82C_3;   /* temp_a1 in func_800AC82C */


typedef struct S_800AC82C_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800AC82C_5;   /* temp_s2 in func_800AC82C */

typedef struct S_800AC82C_6 {
    u8 pad_00[0x2A];
    union { volatile u16 v; s16 n; } unk_2A;   /* accessed as both */
} S_800AC82C_6;   /* temp_v0_5 in func_800AC82C */

typedef struct S_800AC82C_7_pre {
    EarlyCallData * unk_00;
    u8 pad_04[0x10];
} S_800AC82C_7_pre;   /* the 0x14 bytes before (*(void **)((u8 *)arg3 + 0x60)) in func_800AC82C, addressed as (*(void **)((u8 *)arg3 + 0x60))[-1] */

typedef struct S_800AC82C_7 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_800AC82C_7;   /* (*(void **)((u8 *)arg3 + 0x60)) in func_800AC82C */

/* Updates the actor's position and facing relative to its parent. */
s32 func_800AC82C(Rec_func_800A9E70_arg0 *state, Rec_D_800E3D7C *position, Rec_D_80082E80 *tile, void *actor) {
    u16 offset[3];
    u16 dest_x;
    u16 dest_y;
    M2C_UNK tile_mask;
    s16 ground_height;
    s32 flags;
    u16 parent_height;
    u16 parent_angle_raw;
    s32 parent_angle;
    s32 prev_parent_angle;
    u16 facing;
    s32 angle;
    u8 phase;
    u8 tile_x;
    u8 tile_y;
    S_800AC82C_3 *parent_data;
    S_800AC82C_5 *parent_position;
    void *parent;
    S_800AC82C_6 *parent_rotation;

    tile->unk_06.as_s16 = 0;
    phase = state->unk_9B.as_u8;
    if (phase != 0) {
        if (phase != 1) {
            return 0;
        }
        goto update_position;
    }
    parent_data = ((S_800AC82C_7_pre *)((*(void **)((u8 *)actor + 0x60))))[-1].unk_00;
    if (func_8004CAE8(((EarlyCallData *) parent_data)->value, 0) != 0) {
        state->unk_9B.as_u8 = (u8) (state->unk_9B.as_u8 + 1);
update_position:
        if ((*(s16 *)((u8 *)actor + 0x64)) < 0) {
            func_80094E34();
        }
        if ((*(s8 *)((u8 *)actor + 0x6D)) != 0) {
            func_800A9A0C(actor);
        }
        if ((*(s32 *)((u8 *)actor + 0x1C)) & 0x200000) {
            func_800AACA4(state, position, tile, actor);
            return 0;
        }
        parent = (*(void **)((u8 *)actor + 0x60));
        parent_data = ((S_800AC82C_2_pre *)parent)[-1].unk_04;
        parent_position = ((S_800AC82C_2_pre *)parent)[-1].unk_00;
        tile->unk_24 = (u8) parent_data->unk_24;
        tile->unk_25 = (u8) parent_data->unk_25;
        if (!((*(s32 *)((u8 *)actor + 0x1C)) & 0x80000)) {
            position->unk_10.at00_s32.v = 0;
            position->unk_0C.as_s32 = 0;
            state->unk_98 = (u16) (state->unk_98 & 0xFFF7);
            facing = ((S_800AC82C_7 *)((*(void **)((u8 *)actor + 0x60))))->unk_2A;
            (*(u16 *)((u8 *)actor + 0x6A)) = facing;
            tile->unk_24 = (u8) (parent_data->unk_24 + *(u8 *) &D_8006CCD8[(facing >> 9) & 7]);
            tile->unk_25 = (u8) (parent_data->unk_25 + *(u8 *) &D_8006CCE8[((u16) (*(u16 *)((u8 *)actor + 0x6A)) >> 9) & 7]);
            func_800A2B04(position, tile->unk_24, tile->unk_25);
            ground_height = func_800BCB04(position->unk_00.at02_u16.v, position->unk_04.at02_u16.v, (s16) ((*(u16 *)((u8 *)actor + 0x88)) - 0x20));
            if (ground_height < 0x200) {
                state->unk_90.at02_s16.v = 0;
                (*(u16 *)((u8 *)actor + 0x88)) = (u16) ground_height;
            }
            if ((func_8009B88C(actor, tile->unk_24, tile->unk_25, &dest_x, &dest_y) << 0x10) != 0) {
                tile->unk_24 = dest_x;
                tile->unk_25 = dest_y;
                func_800A2B04(position, tile->unk_24, tile->unk_25);
                flags = (*(s32 *)((u8 *)actor + 0x1C)) | 0x40000000;
                (*(s32 *)((u8 *)actor + 0x1C)) = flags;
                tile_x = tile->unk_24;
                tile_y = tile->unk_25;
                tile_mask = 0x3000;
                if (flags & 0x2000) {
                    tile_mask = 0x300;
                }
                func_8009A21C(tile_x, tile_y, tile_mask);
                (*(s8 *)((u8 *)actor + 0x71)) = 0;
                return 1;
            }
            func_800A2B04(position, tile->unk_24, tile->unk_25);
            func_800AA36C(state, position, tile, actor);
            return 0;
        }
        if (func_8003DE58(parent_data->unk_08, parent_data, offset, 0) != 0) {
            position->unk_00.at02_u16.v = (u16) ((u16) *D_800E3DA8 + (parent_position->unk_02 + offset[0]));
            position->unk_04.at02_u16.v = (u16) ((u16) D_800E3DA8[1] + (parent_position->unk_06 + offset[1]));
            parent_height = ((S_800AC82C_7 *)((*(void **)((u8 *)actor + 0x60))))->unk_88;
            (*(u16 *)((u8 *)actor + 0x88)) = parent_height;
            state->unk_90.at02_s16.v = (s16) (((parent_position->unk_0A + offset[2]) - parent_height) + 8);
            tile->unk_06.as_s16 = 0x10;
            (*(volatile s32 *)((u8 *)actor + 0x1C)) = (s32) ((*(s32 *)((u8 *)actor + 0x1C)) | 0x40000000);
            parent_rotation = (*(void * volatile *)((u8 *)actor + 0x60));
            prev_parent_angle = (*(s16 *)((u8 *)actor + 0x6A));
            parent_angle_raw = parent_rotation->unk_2A.v;
            parent_angle = parent_rotation->unk_2A.n;
            angle = (*(u16 *)((u8 *)actor + 0x2A)) - (prev_parent_angle - parent_angle);
            (*(u16 *)((u8 *)actor + 0x6A)) = parent_angle_raw;
            (*(s16 *)((u8 *)actor + 0x2A)) = angle;
        }
        return 0;
    }
    return 0;
}
