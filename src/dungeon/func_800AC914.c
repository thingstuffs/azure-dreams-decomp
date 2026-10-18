#include "shared/object_node.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/game_work.h"
extern s32 func_8004491C();
void play_sound_if_enabled(s32);
extern int func_80046398();
struct S_800B1F34_0;
struct S_800B1F34_1;
extern void advance_timed_panel_motion(struct S_800B1F34_0 *animation, struct S_800B1F34_1 *motion);

typedef struct S_800B2074_0 {
    u8 pad_00[0x1DC];
    s32 unk_1DC;
    u8 pad_1E0[0x10];
    s16 unk_1F0;
} S_800B2074_0;

typedef struct S_800B2074_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    u16 * unk_20;
} S_800B2074_1;

typedef struct S_800B2074_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800B2074_2;

typedef struct S_800B2074_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_800B2074_3;

typedef struct S_800B2074_4 {
    s16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800B2074_4;

typedef struct S_800B2074_5 {
    u8 pad_00[0xE];
    u16 unk_0E;
    u8 pad_10[0x1A];
    u16 unk_2A;
} S_800B2074_5;

typedef union { void *pointer; u32 word; } InitSlot;
/* Creates an object at the given map position and updates its tile record. */
s32 create_map_position_object(s32 world_x, s32 world_z) {
    s32 tile_addr;
    void *object;
    s32 pos_x;
    s32 pos_z;
    void *init_object;
    void *init_data;

    S_800B2074_5 *state_fields;
    u16 inherited_value;
    S_800B2074_3 *transform;
    S_800B2074_2 *render_state;

    pos_x = world_x;
    pos_z = world_z;
    tile_addr = g_game_work.map.cells;
    object = func_8003FC64(0x12);
    if (object != 0) {
        init_object = object;
        {
            InitSlot slot = { advance_timed_panel_motion };
            init_data = func_80046398;
            ((S_800B2074_1 *)object)->unk_10 = slot.pointer;
            func_8004491C(init_object, init_data);
        }
        render_state = ((S_800B2074_1 *)object)->unk_0C;
        render_state->unk_20 = 0x1000;
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        render_state->unk_08 = 2;
        render_state->unk_0C = 0x808080;
        transform = ((S_800B2074_1 *)object)->unk_08;
        transform->unk_16 = 6;
        transform->unk_02 = pos_x;
        transform->unk_06 = pos_z;
        tile_addr += (((s32) (pos_x << 0xA) >> 0x10) + (((s32) (pos_z << 0xA) >> 0x10) << g_game_work.map.shiftX)) * 6;
        ((S_800B2074_1 *)object)->unk_20 = (u16 *) (tile_addr + 2);
        ((S_800B2074_4 *)tile_addr)->unk_00 = 3;
        transform->unk_0A = (s16) (0 - *((S_800B2074_1 *)object)->unk_20);
        ((S_800B2074_4 *)tile_addr)->unk_02 = (u16) (((S_800B2074_4 *)tile_addr)->unk_02 + 0x20);
        ((S_800B2074_4 *)tile_addr)->unk_04 = (u16) (((S_800B2074_4 *)tile_addr)->unk_04 | 1);
        state_fields = object + 0x20;
        play_sound_if_enabled(0x603);
        inherited_value = ((u16)D_800814A8->facing);
        state_fields->unk_0E = inherited_value;
    }
}
