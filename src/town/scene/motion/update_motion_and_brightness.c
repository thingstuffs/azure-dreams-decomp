#include "common.h"
#include "shared/entity.h"
#include "shared/object_links.h"


typedef struct S_80814610_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_80814610_1;   /* arg2 in update_motion_and_brightness */

   /* the 0x2 bytes before arg0 in update_motion_and_brightness, addressed as arg0[-1] */
void func_8003EA54(void *);                 /* extern */
extern s32 scene_object_flags;

/* Updates motion and brightness, processes the visual, and marks flagged objects. */
void update_motion_and_brightness(void *object, void *motion, void *visual) {
    s32 velocity;
    u8 brightness;
    __typeof__(((ObjectPosition *)motion)->z.v) hoisted_1;

    velocity = ((ObjectPosition *)motion)->velocity_z;
    if (velocity != 0) {
        hoisted_1 = ((ObjectPosition *)motion)->z.v;
        ((ObjectPosition *)motion)->z.v = (s32) (hoisted_1 + velocity);
        ((ObjectPosition *)motion)->velocity_z = (s32) (((ObjectPosition *)motion)->velocity_z + 0x18000);
        brightness = ((S_80814610_1 *)visual)->unk_0E - 0x20;
        ((S_80814610_1 *)visual)->unk_0E = brightness;
        ((S_80814610_1 *)visual)->unk_0D = brightness;
        ((S_80814610_1 *)visual)->unk_0C = brightness;
    }
    func_8003EA54(visual);
    if (((S_80814610_1 *)visual)->unk_14 & 0x6000) {
        (*(u16 *)((u8 *)object + -2)) = (u16) (((ObjectStatusPrefix16 *)object)[-1].flags | 0x8000);
        scene_object_flags |= 0x8000;
    }
}
