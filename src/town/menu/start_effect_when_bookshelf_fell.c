#include "script_symbols.h"
#include "common.h"
#include "town/menu.h"

#include "engine/object/test_resident_bitmap_bit_api.h"                         /* extern */

typedef struct S_800A6EA4_0 {
    u8 pad_00[0x50];
    void (*unk_50)(void *, s32,  s32,  void *);
    u8 pad_54[0x3C];
    s16 unk_90;
} S_800A6EA4_0;   /* arg0 in start_effect_when_bookshelf_fell */

/* Reset the object counter and select its next state when check 0x99 succeeds. */
void start_effect_when_bookshelf_fell(S_800A6EA4_0 *object) {
    if (test_resident_bitmap_bit(F_bookshelf_fall) != 0) {
        object->unk_90 = 0;
        object->unk_50 = &advance_effect_ramp_and_spawn_pair;
    }
}
