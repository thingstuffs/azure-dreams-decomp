#include "common.h"

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

extern u8 D_80082E60[];
extern u8 D_80083160[];
extern u8 D_800D2FB4[];
extern volatile u8 D_800D381A[];
extern u8 D_80110EC8[];
extern u8 D_801116C8[];
extern u8 D_80111EC8[];
extern u8 D_80111F48[];
extern u16 D_80111FA8[];
extern u8 D_8012F004[];
extern u8 D_8014F004[];

/* Initialize town asset state and load graphics for the current scene. */
void func_800B70EC(void) {
    register s32 scene_id ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 special_scene;
    register s32 below_extra_range ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 scene_index;
    s32 scene_offset;
    s32 single_row;
    s32 size;
    s32 limit;
    s32 seven;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *asset_data;
    u8 *state_base;
    u8 *asset_state;
    u8 *shared_state;
    u16 *upload_rect;
    register u16 *initial_rect ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u8 *image_data;
    register u8 *scene_entry ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    upload_rect = D_80111FA8;
    initial_rect = upload_rect;
    image_data = D_80110EC8;
    state_base = D_80083160;
    asset_state = state_base + 0x1DC;
    seven = 7;
    limit = 0x7F;
    size = 0x2000;
    ASM_KEEP(upload_rect);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(image_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP4(asset_state, seven, limit, size);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    ((S_800B70EC_0 *)asset_state)->unk_14 = seven;
    seven = 7;
    ((S_800B70EC_0 *)asset_state)->unk_16 = seven;
    ((S_800B70EC_0 *)asset_state)->unk_18 = limit;
    ((S_800B70EC_0 *)asset_state)->unk_1C = size;
    ((S_800B70EC_0 *)asset_state)->unk_1A = limit;
    ((S_800B70EC_0 *)asset_state)->unk_1E = size;
    shared_state = D_80082E60;
    D_80111FA8[0] = 0x328;
    upload_rect[1] = 0x80;
    upload_rect[2] = 8;
    upload_rect[3] = 0x80;
    (*(u16 *)((u8 *)shared_state + 0x16)) |= 1;
    asset_data = D_8014F004;
    func_8006733C(initial_rect, image_data, limit);

    scene_id = D_800D2FB4[D_800D381A[0] << 5];
    ASM_KEEP(scene_id);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    single_row = 1;
    special_scene = 0x21;
    if (scene_id != special_scene) {
        ASM_KEEP(special_scene);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if ((s32)scene_id < 0x21) {
            goto common;
        }
        if ((s32)scene_id >= 0x29) {
            goto common;
        }
        below_extra_range = (s32)scene_id < 0x26;
        if (below_extra_range) {
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
    size = D_800D2FB4;
    scene_index = D_800D381A[0];
    scene_offset = scene_index << 5;
    scene_entry = size + scene_offset;
    ASM_KEEP(scene_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(scene_entry);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    scene_id = *scene_entry;
    if (scene_id != 0x29) {
        func_80046E38(scene_id, D_8012F004);
    }
}
