#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80083460[3];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
s32 func_8009B164();             /* extern */
s32 func_8009B88C();      /* extern */
void *func_8009C93C(); /* extern */
M2C_UNK func_8009CE1C(); /* extern */
u8 func_8009FB34();                           /* extern */
M2C_UNK func_800A19E4(); /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800AA5E4(); /* extern */
s16 func_800BCB04();                   /* extern */





typedef struct S_800AC010_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AC010_4;   /* counter1 in func_800AC010 */

typedef struct S_800AC010_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AC010_5;   /* counter2 in func_800AC010 */

/* Advance tile movement, handle object contact, and finalize the stopping position. */
s32 func_800AC010(void *move_state, Rec_D_800E3D7C *motion, Rec_D_80082E80 *tile_pos, Rec_D_800E3D7C *actor) {
    u16 resolved_x;
    u16 resolved_y;
    M2C_UNK contact_tile_mask;
    M2C_UNK stop_tile_mask;
    M2C_UNK contact_flags;
    M2C_UNK stop_flags;
    u8 contact_x;
    u8 contact_y;
    u8 stop_x;
    u8 stop_y;
    s32 *contact_counters;
    s32 *stop_counters;
    s16 move_ticks;
    s32 target_x;
    s32 axis_pos;
    s16 ticks_left;
    s16 ground_height;
    u16 steps_left;
    void *hit_object;

    move_ticks = ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16;
    if (move_ticks != 0) {
        target_x = tile_pos->unk_24;
        axis_pos = motion->unk_00.at02_s16.v;
        target_x <<= 6;
        axis_pos -= 0x20;
        motion->unk_0C.as_s32 = (s32) ((s32) ((target_x - axis_pos) << 0x10) / move_ticks);
        axis_pos = motion->unk_04.at02_s16.v - 0x20;
        motion->unk_10.at00_s32.v = (s32) ((s32) (((tile_pos->unk_25 << 6) - axis_pos) << 0x10) / (s16) ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16);
    }
    ticks_left = (u16) ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 - 1;
    ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        hit_object = func_8009C93C(actor, tile_pos, actor->unk_6A.as_s16, 0, 0);
        if (hit_object != NULL) {
            func_8009CE1C(actor, 4, 1, 8, (s32) (s16) ((u16) actor->unk_6A.as_s16 + 0x800), 0, 1);
            func_8009CE1C(hit_object, 8, 1, 8, (s32) actor->unk_6A.as_s16, 0, 1);
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)move_state)->unk_98 & 0xFFF7);
            motion->unk_14.as_s32 = 0;
            motion->unk_10.at00_s32.v = 0;
            motion->unk_0C.as_s32 = 0;
            actor->unk_1C.as_s32 = (s32) (actor->unk_1C.as_s32 | 0x40000000);
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_u8 = (u8) tile_pos->unk_26.as_u8;
            tile_pos->unk_26.as_u8 = func_8009FB34(tile_pos->unk_24, tile_pos->unk_25);
            func_800A19E4(tile_pos, actor, 3, 6, move_state + 0x9C);
            if ((func_8009B88C(actor, tile_pos->unk_24, tile_pos->unk_25, &resolved_x, &resolved_y) << 0x10) != 0) {
                goto object_move_ok;
            }
common_fail:
            func_800A2B04(motion, tile_pos->unk_24, tile_pos->unk_25);
            func_800AA5E4(move_state, motion, tile_pos, actor);
            return 0;
object_move_ok:
            tile_pos->unk_24 = resolved_x;
            tile_pos->unk_25 = resolved_y;
            func_800A2B04(motion, tile_pos->unk_24, tile_pos->unk_25);
            contact_flags = actor->unk_1C.as_s32;
            contact_x = tile_pos->unk_24;
            contact_y = tile_pos->unk_25;
            contact_tile_mask = 0x3000;
            if (contact_flags & 0x2000) {
                contact_tile_mask = 0x300;
            }
            func_8009A21C(contact_x, contact_y, contact_tile_mask);
            contact_counters = D_80083460;
            actor->unk_1C.as_s32 = (s32) (actor->unk_1C.as_s32 & 0xFFDFFFFF);
            ((S_800AC010_4 *)contact_counters)->unk_0A = (u16) (((S_800AC010_4 *)contact_counters)->unk_0A - 1);
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 = 0;
            actor->unk_71.as_s8 = 0;
            return 1;
        }
        if ((func_8009B164(actor->unk_6A.as_s16, motion, tile_pos) << 0x10) != 0) {
            steps_left = actor->unk_8A.as_u16 - 1;
            actor->unk_8A.as_u16 = steps_left;
            if ((steps_left << 0x10) > 0) {
                tile_pos->unk_24 = (u8) (tile_pos->unk_24 + *(((u16) actor->unk_6A.as_s16 >> 9 & 7) + D_8006CCD8));
                tile_pos->unk_25 = (u8) (tile_pos->unk_25 + *(((u16) actor->unk_6A.as_s16 >> 9 & 7) + D_8006CCE8));
                ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 = 2;
                goto movement_return;
            }
        }
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        ((Rec_func_800A9E70_arg0 *)move_state)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)move_state)->unk_98 & 0xFFF7);
        ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_u8 = (u8) tile_pos->unk_26.as_u8;
        tile_pos->unk_26.as_u8 = func_8009FB34(tile_pos->unk_24, tile_pos->unk_25);
        func_800A19E4(tile_pos, actor, 3, 6, move_state + 0x9C);
        ground_height = func_800BCB04((tile_pos->unk_24 << 6) | 0x20, (tile_pos->unk_25 << 6) | 0x20, (s16) (motion->unk_08.at02_u16.v - 0x20));
        if (ground_height < 0x200) {
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_90.at02_s16.v = 0;
            actor->unk_88.as_s16 = ground_height;
        }
        stop_counters = D_80083460;
        ((S_800AC010_5 *)stop_counters)->unk_0A = (u16) (((S_800AC010_5 *)stop_counters)->unk_0A - 1);
        ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 = 0;
        actor->unk_1C.as_s32 = (s32) ((actor->unk_1C.as_s32 | 0x40000000) & 0xFFDFFFFF);
        if ((func_8009B88C(actor, tile_pos->unk_24, tile_pos->unk_25, &resolved_x, &resolved_y) << 0x10) != 0) {
            tile_pos->unk_24 = resolved_x;
            tile_pos->unk_25 = resolved_y;
            func_800A2B04(motion, tile_pos->unk_24, tile_pos->unk_25);
            stop_flags = actor->unk_1C.as_s32;
            stop_x = tile_pos->unk_24;
            stop_y = tile_pos->unk_25;
            stop_tile_mask = 0x3000;
            if (stop_flags & 0x2000) {
                stop_tile_mask = 0x300;
            }
            func_8009A21C(stop_x, stop_y, stop_tile_mask);
            actor->unk_71.as_s8 = 0;
            return 1;
        }
        goto common_fail;
    }
movement_return:
    return 0;
}
