#include "common.h"
#include "shared/record_ptrs.h"
#include "town/player.h"

typedef void (*Callback)(s32);


/* Invoke the callback at offset 0x280 with command 0xC1. */
void invoke_callback_280_c_1(void) {
    ((Callback) *(void **)
        ((u8 *) *(void **)((u8 *) *(void **)((s8 *)(&town_scene_root)) + 0x20) + 0x280))(0xC1);
}
