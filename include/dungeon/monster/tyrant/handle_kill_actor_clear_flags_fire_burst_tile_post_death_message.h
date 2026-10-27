#include "shared/entity.h"
#ifndef DUNGEON_OVL_7F0F7800_P07_H
#define DUNGEON_OVL_7F0F7800_P07_H
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"

typedef struct T_80173AD4_S_80173AD4_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} T_80173AD4_S_80173AD4_0;   /* actor in func_80173AD4 */

   /* state in func_80173AD4 */

typedef struct T_80173AD4_S_80173AD4_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    u8 pad_A8[0x2];
    s16 unk_AA;
} T_80173AD4_S_80173AD4_2;   /* work in func_80173AD4 */




extern void select_sprite_entry(void *object, s16 table_index, s16 entry_index);
extern void func_80047784(SpriteFrameState *object, s16 table_index, s16 entry_index);
extern void * get_unused_text_buffer(void);
extern u8 * expand_text_control_codes();
extern u8 * clear_byte_and_advance(u8 *byte_ptr);
extern u8 *append_entity_display_text(void *record, u8 *out);
extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
#include "dungeon/player/object/action_state.h"
#include "shared/sprite_frame_state.h"
extern s32 display_text_with_fullwidth_adjustment(s8 *text);
extern u8 D_80170854[];
extern u8 tyrant_frame_set_1[];
void handle_kill_actor_clear_flags_fire_burst_tile_post_death_message(void *work_in, ObjectPosition *part_a, void *part_b_in, void *actor);
#endif
