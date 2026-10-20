#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s16 state;
    u16 timer;
    u16 x;
    u16 y;
    u16 z;
    s32 unkC;
} DungeonState __attribute__((packed));

typedef struct {
    u8 bytes[8];
} PositionCopy __attribute__((packed));

typedef struct {
    u8 pad0[4];
    PositionCopy position;
} StatePositionView __attribute__((packed));

typedef struct {
    u8 pad0[0x2C];
    PositionCopy position;
} ObjectPositionView __attribute__((packed));

typedef struct {
    u8 pad0[4];
    s32 unk4;
} DungeonTemplate;

typedef struct {
    DungeonTemplate *unk0;
    u8 unk4;
    u8 unk5;
    u8 pad6[2];
    s32 unk8;
    s32 unkC;
    s16 unk10;
    u8 pad12[2];
    u16 unk14;
    u8 pad16[6];
    s16 unk1C;
    s16 unk1E;
} DungeonInner;

typedef struct {
    u8 pad0[8];
    DungeonInner *unk8;
    DungeonInner *unkC;
    DungeonInner *unk10;
    u8 pad14[0x18];
    PositionCopy position;
} DungeonObject;

typedef struct {
    u8 pad0[0x18];
    s16 position;
    s32 unk1C;
    u8 pad20[0xA];
    s16 unk2A;
    u8 pad2C[8];
    s32 unk34;
} DungeonObjectTail;

typedef struct {
    u8 pad0[0xA];
    u16 count;
} DungeonCounter;

extern u8 D_800DEA68[];
extern u8 D_800D7D30[];

extern s32 resolve_record_orientation_or_fallback(s32, void *, u16 *, s32);
extern DungeonObject *allocate_list_node(s32, void *);
extern void register_node(DungeonObject *, void *);
extern void play_sound_if_enabled(s32);

/* Updates the effect position, spawns eight objects per tick, and expires after a delay. */
void update_radial_effect(DungeonState *effect) {
    u16 position_offset[3];

    {
        TileObject *position_table = &D_80082E80;
        if (resolve_record_orientation_or_fallback(position_table->sprite_source, position_table, position_offset, 0) != 0) {
            effect->x = ((u16)D_80083780.x.w.i) + position_offset[0];
            effect->y = ((u16)D_80083780.y.w.i) + position_offset[1];
            effect->z = ((u16)D_80083780.z.w.i) + position_offset[2] + 0x20;
        }
    }

    switch (effect->state) {
    case 0:
        play_sound_if_enabled(0x600);
        effect->timer = 0x3C;
        effect->state += 1;

    case 1:
    {
        s32 spawn_index = 7;
        u8 *object_data = D_800D7D30;
        DungeonGlobalStatus *object_counter = &g_dungeon_status;
        DungeonTemplate *object_template = (DungeonTemplate *)D_800DEA68;

        do {
            DungeonObject *object = allocate_list_node(0x312, ((u8 *)(&D_80083498)));
            if (object != NULL) {
                object->unk10 = (DungeonInner *)object_data;
                object_counter->activity_counts.parts.pending_action_count += 1;
                register_node(object, project_sprite_chain);
                {
                    DungeonInner *object_inner = object->unkC;
                    DungeonObjectTail *object_tail = (DungeonObjectTail *)((u8 *)object + 0x20);
                    u16 saved_flags;

                    *(s32 *)((u8 *)object->unk8 + 0x14) = 0xFFFC0000;
                    saved_flags = ((SpriteFrameState *)object_inner)->flags;
                    ((SpriteFrameState *)object_inner)->scale_y = 0x600;
                    ((SpriteFrameState *)object_inner)->scale_x = 0x600;
                    ((SpriteFrameState *)object_inner)->tpage_abr = 0x20;
                    ((SpriteFrameState *)object_inner)->unk_00 = object_template;
                    ((SpriteFrameState *)object_inner)->flags = saved_flags | 0xC;
                    ((SpriteFrameState *)object_inner)->source = object_template->unk4;
                    ((SpriteFrameState *)object_inner)->unk_04 = 0;
                    ((SpriteFrameState *)object_inner)->unk_05 = 0;
                    ((SpriteFrameState *)object_inner)->color.word = effect->unkC;
                    ((ObjectPositionView *)object)->position = ((StatePositionView *)effect)->position;
                    *(u16 *)((u8 *)object->unk8 + 0xA) = effect->z;
                    object_tail->position = (s16)((spawn_index << 9) + ((s16)effect->timer * 0x28));
                    object_tail->unk1C = 0x180000 - ((0x3C - (s16)effect->timer) << 0xD);
                    object_tail->unk2A = 6;
                    object_tail->unk34 = ((s16)effect->timer - 0x3C) << 0xC;
                }
            }
            spawn_index -= 1;
        } while (spawn_index >= 0);
    }

        {
            u16 ticks_left = effect->timer - 1;
            effect->timer = ticks_left;
            if ((s16)ticks_left <= 0) {
                effect->timer = 8;
                effect->state = 0xFF;
            }
        }
        return;
    case 0xFF:
    {
        u16 ticks_left = effect->timer - 1;
        effect->timer = ticks_left;
        if ((s16)ticks_left <= 0) {
            ((DungeonCounter *)((u8 *)(&g_dungeon_status)))->count -= 1;
            *(u16 *)((u8 *)effect - 2) |= 0x8000;
            *(u32 *)((u8 *)(&object_flag_block)) |= 0x8000;
        }
    }
        return;
    }
}
