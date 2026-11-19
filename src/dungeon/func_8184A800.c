#include "common.h"
#include "slus/imports.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

#include "sdk/rand.h"

#ifdef __mips__
/* Code bases of the two routines that dispatch through these tables. */
extern const u8 D_80025020[];
extern const u8 D_80025090[];

/* The entry word and case addresses precede this bank's first update. */
static const struct {
    const u8 *entry;
    u32 pad_04;
    const u8 *first_cases[7];
    u32 pad_24;
    const u8 *update_cases[8];
} func_8184A800_table __attribute__((section(".text.func_8184A800"))) = {
    D_80025090,
    0,
    {
        D_80025020 + 0x60, D_80025020 + 0x60, D_80025020 + 0x60,
        D_80025020 + 0x38, D_80025020 + 0x48, D_80025020 + 0x58,
        D_80025020 + 0x60
    },
    0,
    {
        D_80025090 + 0x7C, D_80025090 + 0xCC, D_80025090 + 0x5E4,
        D_80025090 + 0x6A0, D_80025090 + 0x6E0, D_80025090 + 0x794,
        D_80025090 + 0x7E8, D_80025090 + 0x820
    }
};
#endif

/* Apply a random number of updates to the target and propagate its status flags. */
void func_8184A800(void *owner, void *unused, SpriteFrameState *target)
{
    s32 random_value;
    s16 update_count;
    s16 update_index;
    s16 next_index;
    void *owner_data;

    owner_data = *(void **)((u8 *)owner + 0xC);
    *(u16 *)((u8 *)owner_data + 0x16) += 1;
    target->angle_z = 0;

    random_value = rand();
    update_count = (random_value % 4) + 1;

    update_index = 0;
    if (update_count > 0) {
        do {
            advance_sprite_animation_and_textures(target);
            next_index = update_index + 1;
            update_index = next_index;
        } while (next_index < update_count);
    }

    if (target->flags & 0x6000) {
        NODE_HEADER(owner)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

