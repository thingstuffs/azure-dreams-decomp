#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u32 word0;
    u32 word1;
} Copy8 __attribute__((packed));

typedef struct {
    u8 pad0[8];
    void *child;
    void *sub;
    u8 *d81d4;
} Entry;

typedef struct S_func_800D7FB8_0 {
    s16 unk_00;
    union {
        s16 s16_value;
        u16 u16_value;
    } unk_02;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
} S_func_800D7FB8_0;

typedef struct S_func_800D7FB8_1 {
    u8 pad_00[0x4A];
    s16 unk_4A;
} S_func_800D7FB8_1;

typedef struct S_func_800D7FB8_4 {
    u8 pad_00[4];
    s32 unk_04;
} S_func_800D7FB8_4;

typedef struct S_func_800D7FB8_6 {
    s32 unk_00;
} S_func_800D7FB8_6;

typedef struct S_func_800D7FB8_7 {
    u16 unk_00;
} S_func_800D7FB8_7;

extern u8 D_800DEC00[];
extern s32 D_800D81D4;

extern void *allocate_list_node(void *, void *);
extern void register_node(void *, void *);
extern s32 play_sound_if_enabled(s32);

/* Spawns effect entries and marks the controller finished after two delays. */
void update_effect_controller(S_func_800D7FB8_0 *controller) {
    S_func_800D7FB8_1 *entry_data;
    s16 state;
    s32 spawn_index;
    u16 finish_timer;
    u16 effect_timer;
    s32 resource_word;
    SpriteFrameState *sub_data;
    Entry *entry;

    state = controller->unk_00;
    switch (state) {
    case 0:
        controller->unk_02.s16_value = 0x3C;
        controller->unk_00 = (s16)((u16)controller->unk_00 + 1);
        play_sound_if_enabled(0x600);
        spawn_index = 0x96;
        do {
            entry = allocate_list_node((void *)0x312, ((u8 *)(&D_80083498)));
            if (entry != NULL) {
                entry_data = (S_func_800D7FB8_1 *)((u8 *)entry + 0x20);
                entry->d81d4 = (u8 *)&D_800D81D4;
                register_node(entry, project_sprite_chain);
                sub_data = entry->sub;
                ((MovingPosition *)entry->child)->unk_02 = controller->unk_04;
                ((MovingPosition *)entry->child)->unk_06 = controller->unk_06;
                ((MovingPosition *)entry->child)->unk_0A = controller->unk_08;
                sub_data->scale_y = 0x400;
                sub_data->scale_x = 0x400;
                sub_data->tpage_abr = 0x20;
                sub_data->unk_00 = D_800DEC00;
                sub_data->flags = (u16)(sub_data->flags | 0xC);
                resource_word = ((S_func_800D7FB8_4 *)D_800DEC00)->unk_04;
                sub_data->unk_04 = 0;
                sub_data->unk_05 = 0;
                sub_data->color.word = 0;
                sub_data->source = resource_word;
                __builtin_memcpy((u8 *)entry + 0x2C, (u8 *)controller + 4, 8);
                entry_data->unk_4A = (spawn_index & 1) ? 1 : -1;
                ((MovingPosition *)entry->child)->unk_0A = controller->unk_08;
            }
            spawn_index -= 1;
        } while (spawn_index >= 0);
    case 1:
        effect_timer = (u16)(controller->unk_02.u16_value - 1);
        controller->unk_02.u16_value = effect_timer;
        if ((effect_timer << 0x10) <= 0) {
            controller->unk_02.u16_value = 8U;
            controller->unk_00 = (s16)0xFF;
        }
        return;
    case 0xFF:
        finish_timer = (u16)(controller->unk_02.u16_value - 1);
        controller->unk_02.u16_value = finish_timer;
        if ((finish_timer << 0x10) <= 0) {
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
            ((S_func_800D7FB8_7 *)((u8 *)controller - 2))->unk_00 =
                (u16)(((S_func_800D7FB8_7 *)((u8 *)controller - 2))->unk_00 | 0x8000);
            ((S_func_800D7FB8_6 *)((s32 *)(&object_flag_block)))->unk_00 =
                ((S_func_800D7FB8_6 *)((s32 *)(&object_flag_block)))->unk_00 | 0x8000;
        }

        return;
    }
}
