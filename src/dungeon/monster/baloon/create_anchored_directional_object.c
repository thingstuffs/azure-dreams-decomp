#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80D653B8_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x12];
    s16 unk_AA;
    u8 pad_AC[0x4];
    void * unk_B0;
} S_80D653B8_0;   /* work in create_anchored_directional_object */

typedef struct S_80D653B8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80D653B8_1;   /* linked in create_anchored_directional_object */

typedef struct S_80D653B8_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_80D653B8_2;   /* object_data in create_anchored_directional_object */

typedef struct S_80D653B8_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80D653B8_3;   /* arg3 in create_anchored_directional_object */

   /* position in create_anchored_directional_object */

typedef struct S_80D653B8_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0xA];
    u16 unk_16;
} S_80D653B8_5;   /* arg1 in create_anchored_directional_object */

extern void *allocate_list_node();
extern void register_node();
extern void project_sprite_chain(void);
extern void select_sprite_entry();

extern u8 D_800D6FEC[];
extern u8 D_800E23D0[];

/* Creates an object from a template, selects its direction, and positions it at the anchor. */
void create_anchored_directional_object(void *unused, S_80D653B8_5 *anchor, S_80D653B8_2 *object_template,
                   S_80D653B8_3 *facing_source, s32 initial_value)
{
    void *object;
    S_80D653B8_2 *object_data;
    MovingPosition *position;
    S_80D653B8_0 *object_work;

    (void)unused;
    object = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (object != NULL) {
        object_work = (u8 *)object + 0x20;
        object_work->unk_96 = initial_value;
        object_work->unk_AA = initial_value;
        ((S_80D653B8_1 *)object)->unk_10 = D_800D6FEC;
        object_work->unk_B0 = anchor;
        object_data = ((S_80D653B8_1 *)object)->unk_0C;
        *object_data = *object_template;

        ((SpriteFrameState *)object_data)->scale_y = 0x1000;
        ((SpriteFrameState *)object_data)->scale_x = 0x1000;
        ((SpriteFrameState *)object_data)->color.c.b = 0x80;
        ((SpriteFrameState *)object_data)->color.c.g = 0x80;
        ((SpriteFrameState *)object_data)->color.c.r = 0x80;
        ((SpriteFrameState *)object_data)->tpage_abr = 0x20;
        ((SpriteFrameState *)object_data)->clut = 0xFF80;
        ((SpriteFrameState *)object_data)->unk_06 = -6;
        ((SpriteFrameState *)object_data)->flags |= 0xC;
        register_node(object, project_sprite_chain);

        {
            u8 *direction_table = D_800E23D0;

            ((SpriteFrameState *)object_data)->frameTable = direction_table;
            select_sprite_entry(object_data,
                direction_table[((g_game_work.view.viewAngle + facing_source->unk_2A + 0x100) >> 9) & 7],
                0);
        }

        position = ((S_80D653B8_1 *)object)->unk_08;
        position->unk_02 = anchor->unk_02;
        position->unk_06 = anchor->unk_06;
        position->unk_0A =
            anchor->unk_0A + anchor->unk_16;
    }
}
