#include "common.h"
#include "shared/sys_flags.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"

typedef struct S_8009F868_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
    u16 unk_0A;
    u8 * unk_0C;
} S_8009F868_0;   /* state in advance_monster_timed_sequence */

extern u8 D_800DCE60[16];

extern void bind_view_triplet_source(void *);
extern void queue_view_slot(s32);
extern void set_camera_targets(s32, void *, s32);

/* Advances a timed sequence, following relative jumps and handling its end. */
void *advance_monster_timed_sequence(void)
{
    u8 *state;
    u8 *entry;
    u8 opcode;
    u16 elapsed_ticks;

    state = (u8 *)0x80013710;
    entry = ((S_8009F868_0 *)state)->unk_0C + ((S_8009F868_0 *)state)->unk_0A * 2;
    opcode = entry[1];

    if (opcode == 0) {
        if (D_80013714 & 8) {
            ((S_8009F868_0 *)state)->unk_04 |= 0x10;
            return 0;
        }
        ((S_8009F868_0 *)state)->unk_0A = 0;
        ((S_8009F868_0 *)state)->unk_04 &= 0xC;
        bind_view_triplet_source(((u8 *)(&D_80083780)));
        g_game_work.view.slot[2].callback = 0;
        queue_view_slot(1);
        set_camera_targets(0, D_800DCE60, 8);
        return 0;
    }

    if (opcode == 0xD0) {
        ((S_8009F868_0 *)state)->unk_08 = 0;
        ((S_8009F868_0 *)state)->unk_0A += (s8)entry[0];
        return advance_monster_timed_sequence();
    }

    if ((s8)entry[0] < 0 ||
        (elapsed_ticks = ((S_8009F868_0 *)state)->unk_08 + 1,
         ((S_8009F868_0 *)state)->unk_08 = elapsed_ticks,
         (u16)elapsed_ticks >= entry[0])) {
        ((S_8009F868_0 *)state)->unk_08 = 0;
        ((S_8009F868_0 *)state)->unk_0A++;
    }
    return entry;
}
