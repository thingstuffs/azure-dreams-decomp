#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "records/Rec_D_80175D54.h"
#include "shared/dungeon_moving_views.h"

void *allocate_list_node();               /* extern */
s32 register_node();           /* extern */
extern M2C_UNK D_80077854;
extern void initialize_action_offset_and_notify(void *action, void *position);
extern s16 D_80173AFC[];
extern void *D_80175D54;
extern void *D_80175DB8;

typedef struct S_801715D0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_801715D0_1;

typedef struct S_801715D0_3 {
    u8 pad_00[0x24];
    void * unk_24;
    u8 pad_28[0x30];
    s8 unk_58;
    s8 unk_59;
} S_801715D0_3;

typedef struct S_801715D0_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801715D0_6;

typedef struct S_801715D0_7 {
    s16 unk_00;
    s16 unk_02;
} S_801715D0_7;   /* entry in create_action_offset_object */

/* Creates and initializes an object offset in its owner's facing direction. */
void create_action_offset_object(void) {
    s32 owner_x;
    s32 owner_y;
    s32 tile_x;
    s32 tile_y;
    MovingPosition *object_pos;
    S_801715D0_6 *owner_state;
    MovingPosition *owner_pos;
    u8 *direction;
    u8 *direction_table;
    S_801715D0_3 *object_state;
    void *object;
    SpriteFrameState *render_flags;
    SpriteFrameState *sprite;

    owner_pos = ((Rec_D_80175D54 *)D_80175D54)->unk_08;
    owner_state = D_80175D54 + 0x20;
    object = allocate_list_node(0x12, D_80175D54);
    if (object != NULL) {
        ((S_801715D0_1 *)object)->unk_10 = &initialize_action_offset_and_notify;
        object_state = object + 0x20;
        register_node(object, project_sprite_chain);
        render_flags = ((S_801715D0_1 *)object)->unk_0C;
        render_flags->flags = (u16) ((render_flags->flags & 0xFFF3) | 0x80);
        object_state->unk_24 = owner_state;
        object_pos = ((S_801715D0_1 *)object)->unk_08;
        object_pos->unk_02 = (u16) owner_pos->unk_02;
        object_pos->unk_06 = (u16) owner_pos->unk_06;
        object_pos->unk_0A = (u16) owner_pos->unk_0A;
        direction_table = (u8 *)&D_80173AFC;
        direction = (u8 *) ((u32) (((u16) owner_state->unk_2A >> 7) & 0x1C) + (u32) direction_table);
        object_pos->unk_02 = (u16) (object_pos->unk_02 + (((S_801715D0_7 *)direction)->unk_00 * 6));
        direction = (u8 *) ((u32) (((u16) owner_state->unk_2A >> 7) & 0x1C) + (u32) direction_table);
        object_pos->unk_06 = (u16) (object_pos->unk_06 + (((S_801715D0_7 *)direction)->unk_02 * 6));
        sprite = ((S_801715D0_1 *)object)->unk_0C;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        owner_x = (s16) owner_pos->unk_02;
        tile_x = owner_x - 0x20;
        if (tile_x < 0) {
            tile_x = (s32) (owner_x + 0x1F) >> 6;
        } else {
            tile_x >>= 6;
        }
        object_state->unk_58 = (s8) tile_x;
        owner_y = (s16) owner_pos->unk_06;
        tile_y = owner_y - 0x20;
        if (tile_y < 0) {
            tile_y = (s32) (owner_y + 0x1F) >> 6;
            object_state->unk_59 = (s8) tile_y;
            sprite->color.c.b = 0x80;
            sprite->color.c.g = 0x80;
            sprite->color.c.r = 0x80;
            sprite->source = &D_80077854;
            D_80175DB8 = object;
        } else {
            tile_y >>= 6;
            object_state->unk_59 = (s8) tile_y;
            sprite->color.c.b = 0x80;
            sprite->color.c.g = 0x80;
            sprite->color.c.r = 0x80;
            sprite->source = &D_80077854;
            D_80175DB8 = object;
        }
    }
}

/* MECHANISM: A held 0x80170000 page plus addiu 0x3AFC prevents the direction_table low half from
   folding into its signed halfword loads. Named integer-form index+base sums preserve addu v0,v0,a1;
   shared v0 normalization and u8 color stores close the tail. */
