#include "dungeon/effect/particle/render_textured_effect_parts.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

extern u8 D_800DE870[9];

/* Creates and initializes an object at an offset from the supplied origin. */
void func_800240C0(void *unused_context, void *origin, s32 unused_id, s16 offset_x, s16 offset_y, s16 offset_z) {
    SpriteFrameState *asset;
    D8181A8C0Object *object;
    s32 asset_param;
    s32 setup_mode;
    D8181A8C0Header *header;
    D8181A8C0Vector *position;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        header = (D8181A8C0Header *)((u8 *)object + 0x20);
        header->f2 = 1;
        header->f4 = 1;
        object->field10 = &render_textured_effect_parts;
        register_node(object, (s32)project_sprite_chain);
        asset_param = 0x60;
        setup_mode = 2;
        asset = object->fieldc;
        asset->tpage_abr = asset_param;
        asset->unk_06 = 0;
        asset->flags = (s16) (asset->flags | 0xC);
        position = object->field8;
        position->f2 = offset_x;
        position->f6 = (s16) offset_y;
        position->fa = (s16) offset_z;
        position->f2 += *(u16 *)((u8 *)origin + 2);
        position->f6 += *(u16 *)((u8 *)origin + 6);
        position->fa += *(u16 *)((u8 *)origin + 0xA);
        asset = object->fieldc;
        asset->scale_y = 0x400;
        asset->scale_x = 0x400;
        asset->color.c.b = 0x80;
        asset->color.c.g = 0x80;
        asset->color.c.r = 0x80;
        asset->clut = 0x7DCF;
        asset->flags = (u16) (asset->flags | 0x100);
        func_8003DB94(asset, D_800DE870, setup_mode);
    }
}
