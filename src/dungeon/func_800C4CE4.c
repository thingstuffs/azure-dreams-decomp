#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CA444_0 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
} S_800CA444_0;   /* arg2 in func_800CA444 */

typedef struct S_800CA444_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
} S_800CA444_1;   /* arg3 in func_800CA444 */

typedef struct S_800CA444_2 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    s8 unk_9C;
} S_800CA444_2;   /* arg0 in func_800CA444 */

typedef struct S_800CA444_3 {
    s16 unk_00;
} S_800CA444_3;   /* ((s32) (var_s1 << 0x10) >> 0xF) + (u32) temp_s4 in func_800CA444 */

typedef struct S_800CA444_4 {
    u8 pad_00[0x58];
    s32 unk_58;
} S_800CA444_4;   /* *D_800814A8 in func_800CA444 */

typedef struct S_800CA444_5 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_800CA444_5;   /* (arg3 + (((S_800CA444_1 *)arg3)->unk_71 & 0x7F)) in func_800CA444 */


extern u16 D_80083462[5];
typedef struct {
    u8 pad_00[0xC];
    u16 flags;
    u8 pad_0E[6];
} DungeonTableEntry;

extern DungeonTableEntry D_800E2970[];
extern s16 D_8006CD00[];
extern u16 D_80082E80[];
extern u16 D_80083460[];
extern int D_800814A8[4];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
M2C_UNK func_800A0E6C();
M2C_UNK func_800A19E4();
M2C_UNK func_800A9A0C();
s32 func_8009A180();
s16 func_800BCB04();
s32 func_800CA1E0();

/* Find a movement direction, record the tile, and update the actor's position and height. */
void func_800CA444(void *motion_input, s32 unused, void *tile_input, void *actor_input) {
    register void *motion ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_800CA444_0 *tile;
    void *actor;
    register s16 next_heading ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 height;
    register s32 heading ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 heading_offset;
    register s32 scan_index ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 next_index ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 scan_result ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    M2C_UNK direction_index;
    s8 tile_type;
    s16 *heading_offsets;
    u16 *map_state;
    void *scan_tile;
    unsigned long x_step_addr;
    u32 trail_count;
    s32 steps_left;

    motion = motion_input;
    tile = tile_input;
    actor = actor_input;

    if (*D_80083462 & 0x4000) {
        func_800A9A0C(actor);
        goto done;
    }
    if (!(*D_80083462 & 0x2000)) {
        goto done;
    }
    func_800A19E4(tile, actor, 3, 6, motion + 0x9C);
    tile_type = tile->unk_26;
    if (tile_type < 0) {
        goto scan_start;
    }
    scan_tile = tile;
    if (!(D_800E2970[tile_type].flags & 2)) {
        goto scan_start;
    }
    goto scan_call;

write_hit:
    ((S_800CA444_1 *)actor)->unk_2A = next_heading;
    ((S_800CA444_5 *)((actor + (((S_800CA444_1 *)actor)->unk_71 & 0x7F))))->unk_74 = (u8) tile->unk_24.at00.v;
    ((S_800CA444_5 *)((actor + (((S_800CA444_1 *)actor)->unk_71 & 0x7F))))->unk_7C = (u8) tile->unk_24.at01.v;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    x_step_addr = (unsigned long) D_8006CCD8;
    trail_count = ((S_800CA444_1 *)actor)->unk_71;
    direction_index = ((u16) ((S_800CA444_1 *)actor)->unk_2A >> 8) & 0xE;
    trail_count++;
    x_step_addr = direction_index + x_step_addr;
    ((S_800CA444_1 *)actor)->unk_71 = (u8) trail_count;
    tile->unk_24.at00.v = (u8) (tile->unk_24.at00.v + *(u8 *) x_step_addr);
    tile->unk_24.at01.v = (u8) (tile->unk_24.at01.v + D_8006CCE8[direction_index]);
    goto state_done;

scan_start:
    if (((S_800CA444_1 *)actor)->unk_46 & 0x8000) {
        scan_result = 0;
    } else {
        scan_tile = tile;
scan_call:
        func_800A0E6C(scan_tile, ((S_800CA444_2 *)motion)->unk_9C, actor, motion + 0x98);
        scan_result = 0;
    }
    heading_offsets = D_8006CD00;
    map_state = D_80082E80;
scan_loop:
    heading = ((S_800CA444_1 *)actor)->unk_2A;
    if (((S_800CA444_2 *)motion)->unk_98 & 2) {
        heading_offset = ((S_800CA444_3 *)(((s32) (scan_result << 0x10) >> 0xF) + (u32) heading_offsets))->unk_00;
        next_heading = heading - heading_offset;
        goto calc_call;
    }
    heading_offset = ((S_800CA444_3 *)(((s32) (scan_result << 0x10) >> 0xF) + (u32) heading_offsets))->unk_00;
    next_heading = heading + heading_offset;
    goto calc_call;
calc_call:
    if ((func_800CA1E0(next_heading, tile, actor, 0x20) << 0x10) > 0) {
        goto write_hit;
    }
    if (scan_result != 0) {
        next_index = scan_result + 1;
        goto scan_increment;
    }
    if (map_state[0x12] == tile->unk_24.at00u.v) {
        next_index = scan_result + 1;
        goto scan_increment;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if ((func_8009A180(actor, ((S_800CA444_4 *)(*D_800814A8))->unk_58 + 0x20) << 0x10) != 0) {
        goto done;
    }
    next_index = scan_result + 1;
scan_increment:
    scan_result = next_index;
    if (next_index < 8) {
        goto scan_loop;
    }
    goto state_done;

state_done:
    scan_index = ((s32) (scan_result << 0x10)) >> 0x10;
    if (scan_index < 8) {
        goto state_long;
    }
    ((S_800CA444_1 *)actor)->unk_71 = (u8) (((S_800CA444_1 *)actor)->unk_71 & 0x7F);
    ((S_800CA444_1 *)actor)->unk_46 = (u16) (((S_800CA444_1 *)actor)->unk_46 & 0x7FFF);
    func_800A9A0C(actor);
    goto done;

state_long:
    ((S_800CA444_1 *)actor)->unk_46 = (u16) (((S_800CA444_1 *)actor)->unk_46 & 0x7FFF);
    ((S_800CA444_2 *)motion)->unk_9C = (s8) (u8) tile->unk_26;
    ((S_800CA444_1 *)actor)->unk_6D.u = (u8) (((S_800CA444_1 *)actor)->unk_6D.u - 1);
    D_80083460[4] = (u16) (D_80083460[4] + 1);
    steps_left = ((S_800CA444_1 *)actor)->unk_6D.s;
    if (steps_left == 0) {
        ((S_800CA444_1 *)actor)->unk_71 = (u8) (((S_800CA444_1 *)actor)->unk_71 & 0x7F);
        goto done;
    }
    scan_result = func_800BCB04((tile->unk_24.at00.v << 6) | 0x20, (tile->unk_24.at01.v << 6) | 0x20, (s16) (((S_800CA444_1 *)actor)->unk_88 - 0x20));
    height = (s16) (((s32) scan_result << 0x10) >> 0x10);
    if (height < 0x200) {
        ((S_800CA444_1 *)actor)->unk_88 = (u16) scan_result;
    }

done:
    return;
}
