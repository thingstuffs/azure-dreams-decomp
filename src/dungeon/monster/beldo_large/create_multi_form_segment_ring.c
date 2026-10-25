#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/entity.h"
#include "dungeon/monster/beldo_large.h"

typedef struct S_8016E998_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x15];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x58];
    s16 unk_74;
    s16 unk_76;
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    s16 unk_7E;
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    s16 unk_86;
    s16 unk_88;
    s16 unk_8A;
} S_8016E998_0;

typedef struct S_8016E998_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    s8 unk_20;
} S_8016E998_1;

s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */           /* extern */
s32 rsin();                             /* extern */
s32 rcos();                        /* extern */
void emit_multi_form_ring_geometry(void *animation, s32 *origin, void *color);
extern void *D_80175D78;

/* Creates sixteen radial effect segments around the supplied position. */
void create_multi_form_segment_ring(EntityRec *origin) {
    s32 origin_z;
    s32 start_angle;
    s32 end_x;
    s32 start_x;
    s32 end_z;
    s16 unit_scale;
    s32 initial_count;
    s8 color_level = 0;
    s32 end_angle;
    s32 segment_index;
    s32 *effect_handler;
    void **effect_slot;
    SpriteFrameState *appearance;
    S_8016E998_0 *effect_data;
    ObjectNodeHeader *effect;
    ObjectPosition *position;

    segment_index = 0;
    effect_handler = &emit_multi_form_ring_geometry;
    effect_slot = &D_80175D78;
    end_angle = 0x100;
    do {
        effect = allocate_flagged_object_node(0x12);
        if (effect != 0) {
            effect_data = ((void *)effect) + 0x20;
            initial_count = 0x32;
            effect_data->unk_18 = (s16) initial_count;
            effect_data->unk_1A = (s16) initial_count;
            effect->update_callback = effect_handler;
            register_node(effect, project_sprite_chain);
            appearance = effect->sprite;
            appearance->flags |= 0xC;
            appearance->tpage_abr = 0x20;
            appearance->flags |= 0x80;
            position = effect->position;
            position->x.v = (s32) origin->x.v;
            position->y.v = (s32) origin->y.v;
            origin_z = origin->z.v;
            position->y.w.i = (u16) (*(u16 *)&position->y.w.i - 0x440);
            position->z.v = origin_z;
            effect_data->unk_7E = -0x40;
            effect_data->unk_78 = -0x40;
            effect_data->unk_8A = 0;
            effect_data->unk_84 = 0;
            start_angle = segment_index << 8;
            end_x = (s32) (rcos(end_angle) << 5) >> 0xC;
            effect_data->unk_80 = (s16) end_x;
            effect_data->unk_74 = (s16) end_x;
            start_x = (s32) (rcos(start_angle) << 5) >> 0xC;
            effect_data->unk_86 = (s16) start_x;
            effect_data->unk_7A = (s16) start_x;
            end_z = (s32) (rsin(end_angle) << 5) >> 0xC;
            effect_data->unk_82 = (s16) end_z;
            effect_data->unk_76 = (s16) end_z;
            unit_scale = (s32) (rsin(start_angle) << 5) >> 0xC;
            effect_data->unk_88 = (s16) unit_scale;
            effect_data->unk_7C = (s16) unit_scale;
            appearance = effect->sprite;
            color_level = 0x40;
            appearance->color.c.r = color_level;
            appearance->scale_y = 0x1000;
            appearance->scale_x = 0x1000;
            appearance->color.c.g = color_level;
            appearance->color.c.b = color_level;
            ((S_8016E998_1 *)effect)->unk_20 = *(s8 *)&appearance->color.c.r;
            effect_data->unk_01 = appearance->color.c.g;
            effect_data->unk_02 = appearance->color.c.b;
            *effect_slot = effect;
        }
        effect_slot = (void **)((s8 *)((void **)((s8 *)effect_slot + 4)));
        segment_index += 1;
        end_angle += 0x100;
    } while (segment_index < 0x10);
}

/* MECHANISM: the flag word is two compound ORs (cse keeps them apart and
   post-reload CSE turns the re-read into `move`); effect->unk_20 re-reads the
   just-stored colour byte; one pointer variable carries both effect->unk_0C
   loads (two sets -> global pseudo -> $a1); color_level is a user variable
   declared with an initialiser, so loop.c does not hoist the 0x40 set. */
