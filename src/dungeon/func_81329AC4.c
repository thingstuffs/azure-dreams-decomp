#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"

typedef struct {
    u8 pad[0x3714];
    u16 flags;
    s16 field_3716, field_3718, field_371A;
    void *field_371C;
} StatePage;

typedef struct {
    u8 pad[0xB0];
    s16 field_B0;
    s16 field_B2;
} StateData;

typedef struct {
    u32 value;
} __attribute__((packed)) Unaligned32;

extern void clear_actor_pending_update_markers(void *state);
extern void unlink_entity_node(void *node);

extern void *D_80174AB4[3];
extern s16 D_80174AB8[5];
extern u8 D_80174B38[];
extern void *D_80174CD8[3];
extern Unaligned32 D_80174C58;

/* Initialize shared state and update the two active entries and their header flags. */
void initialize_shared_state_active_entries(void)
{
    s32 entry_index;
    StateData *state_data;
    u8 *entry_header;

    D_80174AB4[0] = D_80174B38;
    state_data = (StateData *)((u8 *)D_80174CD8[0] + 0x20);
    D_80174AB8[0] = 0;
    {
        Unaligned32 *source;
        Unaligned32 *destination;

        state_data->field_B2 = 1;
        state_data->field_B0 = 1;

        destination = (Unaligned32 *)0x80013720;
        source = &D_80174C58;
        *destination = *source;

        {
            StatePage *state_page;
            u32 state_flags;

            /* integer page pointer (decision 44, docs/evidence/r97_decisions.md): retail keeps lui 0x8001 in a register
               across the accesses below; flags at +0x3714 is D_80013714, +0x371C is D_8001371C */
            state_page = (StatePage *)0x80010000;
            D_800E296C |= 0x08000000;
            state_flags = state_page->flags;
            state_page->field_371A = 0;
            state_page->field_3718 = 0;
            state_page->field_3716 = 0;
            state_page->field_371C = (void *)&D_80174C58;
            state_page->flags = (state_flags | 9) & 0xFFEF;
        }
    }

    for (entry_index = 0; entry_index < 2; entry_index++) {
        void *entry = *(void **)((u8 *)D_800E3D7C + entry_index * 4 + 0xAC);

        if (entry != 0) {
            clear_actor_pending_update_markers(entry);
            unlink_entity_node(*(void **)((u8 *)D_800E3D7C + entry_index * 4 + 0xAC));
            entry_header = *(u8 **)((u8 *)D_800E3D7C + entry_index * 4 + 0xAC);
            entry_header -= 0x20;
            *(u32 *)(entry_header + 0x10) |= 0x80000000;
        }
    }
}
