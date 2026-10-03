#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct S_800B70EC_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800B70EC_0;   /* work in func_800B70EC */


extern void func_80046E38();
extern void func_80067014();
extern void func_8006733C();
extern void func_800B73F0();


extern u8 D_800D2FB4[];
extern u8 D_800D381A[];
extern u8 D_80110EC8[];
extern u8 D_801116C8[];
extern u8 D_80111EC8[];
extern u8 D_80111F48[];
extern u16 D_80111FA8[];
extern u8 D_8012F004[];
extern u8 D_8014F004[];

static __inline__ s16 scene_below(s32 scene, s32 bound)
{
    return scene < bound;
}

/* Initialize town asset state and load graphics for the current scene. */
void func_800B70EC(void) {
    s32 special_scene;
    s32 scene_offset;
    s32 single_row;
    s32 size;
    s32 kind;
    s32 limit;
    s32 seven;
    u8 *asset_data;
    u8 *scene_table;
    u8 *kind_table;
    u8 *state_base;
    u8 *asset_state;
    RuntimeDispatchState *shared_state;
    u16 *upload_rect;
    u8 *image_data;

    upload_rect = D_80111FA8;
    image_data = D_80110EC8;
    state_base = ((u8 *)(&gameWork));
    asset_state = state_base + 0x1DC;
    limit = 0x7F;
    size = 0x2000;
    ((S_800B70EC_0 *)asset_state)->unk_14 = 7;
    ((S_800B70EC_0 *)asset_state)->unk_18 = limit;
    ((S_800B70EC_0 *)asset_state)->unk_1C = size;
    seven = 7;
    ((S_800B70EC_0 *)asset_state)->unk_16 = seven;
    ((S_800B70EC_0 *)asset_state)->unk_1A = limit;
    ((S_800B70EC_0 *)asset_state)->unk_1E = size;
    shared_state = &D_80082E60;
    D_80111FA8[0] = 0x328;
    upload_rect[1] = 0x80;
    upload_rect[2] = 8;
    upload_rect[3] = 0x80;
    (shared_state->flags16) |= 1;
    asset_data = D_8014F004;
    func_8006733C(upload_rect, image_data);

    single_row = 1;
    kind_table = D_800D2FB4;
    kind = kind_table[D_800D381A[0] << 5];
    special_scene = 0x21;
    if (kind != special_scene) {
        if (scene_below(kind, 0x21)) {
            goto common;
        }
        if ((s32)kind >= 0x29) {
            goto common;
        }
        scene_offset = (s32)kind < 0x26;
        if (scene_offset) {
            goto common;
        }
        D_80111FA8[0] = 0x330;
        upload_rect[1] = 0x80;
        upload_rect[2] = 8;
        upload_rect[3] = 0x80;
        func_8006733C(upload_rect, D_801116C8);
        D_80111FA8[0] = 0;
        upload_rect[1] = 0x1FB;
        upload_rect[2] = 0x40;
        upload_rect[3] = single_row;
        func_8006733C(upload_rect, D_80111EC8);
    } else {
        D_80111FA8[0] = 0x10;
        upload_rect[1] = 0x1C1;
        upload_rect[2] = 0x30;
        upload_rect[3] = single_row;
        func_8006733C(upload_rect, D_80111F48);
    }

common:
    func_80067014(0);
    *(void **)asset_state = asset_data;
    func_800B73F0(asset_data);
    scene_table = D_800D2FB4;
    {
        u8 *entry = &scene_table[D_800D381A[0] << 5];
        if (*entry != 0x29) {
            func_80046E38(*entry, D_8012F004);
        }
    }
}
