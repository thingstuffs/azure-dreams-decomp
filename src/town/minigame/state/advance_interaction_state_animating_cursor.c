#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity_objects.h"
#include "engine/script.h"
#include "sdk/libc.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "town/minigame/state.h"
#include "town/person.h"


typedef struct Entry {
    u8 bytes[8];
} Entry;

typedef struct EntryPair {
    Entry entries[2];
} EntryPair;

typedef struct Counter {
    u32 value;
    u32 pad[2];
} Counter;

extern EntryPair D_800898C4;
extern u8 D_80011F81[];
extern Counter town_money;

/* Advances the interaction state, animating the cursor and vertical position. */
void advance_interaction_state_animating_cursor(FixedInteractionEffectBody *self, ObjectPosition *position, SpriteFrameState *cursor_data) {
    EntryPair entries;
    s32 state;
    register s32 x_range_check;
    register s32 entry_index;
    register s32 target_x;
    register s32 counter_value;
    register s32 current_x;

    entries = D_800898C4;
    self->counter = self->counter - 1;
    state = self->state;
    switch (state) {
    case 0:
        /* BYTES: reorg mostly_true_jump: LOOP_BEG before the join label decides a delay-slot fill (ledger/onetrip_loadbearing.jsonl: town/func_800C1A68). */
        do {
            const Counter *global_counter = &town_money;
            entry_index = 0;
            if (D_80011F81[0] != 0) {
                entry_index = 1;
            } else {
                counter_value = global_counter->value;
                if ((u32)counter_value >= 0x1388U) {
                    entry_index = 1;
                }
            }
            MoveImage(&entries.entries[entry_index], 0x188, 0x180);
        } while (0);
    case 3:
    {
        x_range_check = 0x3FFFFF;
        current_x = view_reference_entity.x.v;
        target_x = position->x.v;
        {
            s32 x_distance = abs((s32)((u32)current_x - (u32)target_x));
            x_range_check = x_range_check < x_distance;
        }
        if (x_range_check != 0) {
            return;
        }
    }
        if (service_script_controller() == 0) {
            return;
        }
        if (check_town_target_and_callback(self) == 0) {
            return;
        }
        SD_Call(0x50B);
        self->counter = 0x20;
        self->state = (u16)self->state + 1;
        return;

    case 1:
        if (view_reference_entity.y.v < position->y.v + 0x800000) {
            view_reference_entity.y.v += 0x40000;
        }
        {
            register s32 cursor = cursor_data->angle_z;
            cursor -= 0x20;
            cursor_data->angle_z = cursor;
        }
        if ((s16)self->counter > 0) {
            return;
        }
        self->state = (u16)self->state + 1;
        break;

    case 2:
    case 5:
        if (service_script_controller() != 0 && check_town_target_and_callback(self) != 0) {
            return;
        }
        {
            s32 next_state = self->state;
            next_state += 1;
            next_state %= 6;
            self->state = (s16)next_state;
            return;
        }

    case 4:
        cursor_data->angle_z += 0x20;
        if ((s16)self->counter > 0) {
            return;
        }
        self->state = (u16)self->state + 1;
        break;
    }
}
