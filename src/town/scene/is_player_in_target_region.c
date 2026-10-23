#include "common.h"
#include "shared/record_ptrs.h"


typedef void (*Callback)(s32);


typedef struct S_8051EAF8_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_8051EAF8_0;   /* position in is_player_in_target_region */

/* Invokes the object's callback with 1, then checks its position against the target region. */
s32 is_player_in_target_region(void) {
    void *currentObject;
    S_8051EAF8_0 *position;
    Callback callback;
    s32 x;
    s32 y;

    currentObject = *(void **)((s8 *)(&town_scene_root));
    currentObject = (*(void * *)((u8 *)currentObject + 0x20));
    callback = (*(Callback *)((u8 *)currentObject + 0x248));
    callback(1);

    currentObject = *(void **)((s8 *)(&town_scene_root));
    position = (*(void * *)((u8 *)currentObject + 0x1C));
    x = position->unk_04;
    y = position->unk_08;
    if ((u32)(x - 0x341) < 0x5FU) {
        if (y < 0x3F0) {
            return 1;
        }
    }
    return 0;
}
