#include "common.h"
#include "dungeon/player/item.h"

typedef struct S_func_80091934_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_func_80091934_0;

/* Sets object state bytes from the mode and clears its state word. */
void begin_deferred_player_item_effect(void *object_in, unsigned long unused_1, void *unused_2, void *mode) {
    S_func_80091934_0 *object = object_in;
    object->unk_9A = 0x2B;
    if (mode == 0) {
        object->unk_9B = 0x10;
    } else {
        object->unk_9B = 0;
    }
    object->unk_8C = 0;
    return;
}
