#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

typedef struct S_8016ED98_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8016ED98_0;   /* state in finish_multi_form_actor_sequence */

typedef struct S_8016ED98_1 {
    u8 pad_00[0x46];
    u16 unk_46;
} S_8016ED98_1;   /* object in finish_multi_form_actor_sequence */

typedef struct S_8016ED98_2 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8016ED98_2;   /* D_800E3D7C + i * 4 in finish_multi_form_actor_sequence */


extern void set_monster_data_pointer(void);
extern void func_8016ECFC(void);
extern void clear_entry_flag_and_link_owner(void *);

extern u16 D_80013714[];
extern s32 D_80175D50;

/* End the floor: clear the visible flags, run the two teardown passes and release both resident objects. */
void finish_multi_form_actor_sequence(void)
{
    s32 i;
    s32 value;
    S_8016ED98_1 *object;

    object = (void *)(D_80175D50 + 0x20);
    g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    object->unk_46 &= 0x7FFF;
    D_80013714[0] &= 0xFFF6;
    set_monster_data_pointer();
    func_8016ECFC();
    i = 0;
    do {
        value = ((S_8016ED98_2 *)(((s32)D_800E3D7C) + i * 4))->unk_AC;
        if (value != 0) {
            clear_entry_flag_and_link_owner((void *)(value - 0x20));
        }
        i++;
    } while (i < 2);
}
