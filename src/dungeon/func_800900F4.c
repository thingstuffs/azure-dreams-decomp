#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80095854_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x46];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x18];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x88];
    void * unk_124;
} S_80095854_0;   /* arg0 in begin_familiar_summoning */

typedef struct S_80095854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_80095854_1;

   /* arg2 in begin_familiar_summoning */


void func_80048A44(); /* extern */
void clear_player_linked_action_flags(void);                            /* extern */
void cycle_map_cell_flags();           /* extern */
void update_map_cell_flags_with_item_limit();           /* extern */
s32 find_valid_nearby_position();   /* extern */
extern u8 D_800DD130;

s32 begin_familiar_summoning(void *record, s32 input1, void *pointer_input, s32 value_input) {
    s16 candidate_x;
    s16 candidate_y;
    s16 checked_x;
    s16 checked_y;
    void *pointer_data = pointer_input;
    s32 input_value = value_input;
    u16 status;
    s32 value;
    s32 direction_index;
    s32 condition;
    s8 next_y;
    void *child;

    status = 0;
    child = ((S_80095854_0 *)record)->unk_124;
    ((S_80095854_0 *)record)->unk_9A = 0x31;
    ((S_80095854_0 *)record)->unk_9B = 0;
    ((S_80095854_0 *)record)->unk_8C = 0;
    if (child != 0) {
        value = ((S_80095854_1 *)child)->unk_13;
        value = value > 0;
        status = value;
    }
    clear_player_linked_action_flags();
    (*(s32 **)((u8 *)pointer_data + 0x2C)) = &D_800DD130;
    func_80048A44(pointer_data, *((((s32) (g_game_work.view.viewAngle + ((S_80095854_0 *)record)->unk_2A + 0x100) >> 9) & 7)
        + &D_800DD130), 0, 1);
    D_80082E80.unk_030 = input_value;
    direction_index = ((u16) (((S_80095854_0 *)record)->unk_2A) >> 8) & 0xE;
    ((S_80095854_0 *)record)->unk_72 = (s8) (((MovingTile *)pointer_data)->unk_24 + *(direction_index + ((s8 *)dir_step_x)));
    next_y = ((MovingTile *)pointer_data)->unk_25 + *(direction_index + ((s8 *)dir_step_y));
    ((S_80095854_0 *)record)->unk_73 = next_y;
    if ((find_valid_nearby_position(0, ((S_80095854_0 *)record)->unk_72, next_y, &candidate_x, &candidate_y) << 0x10) != 0) {
        value = status << 0x10;
        if (value != 0) {
            cycle_map_cell_flags(candidate_x, candidate_y, 0x8000);
            status = find_valid_nearby_position(0, ((S_80095854_0 *)record)->unk_72, ((S_80095854_0 *)record)->unk_73, &checked_x, &checked_y);
            update_map_cell_flags_with_item_limit(candidate_x, candidate_y, 0x8000);
            condition = status << 0x10;
            if (condition != 0) {
                ((S_80095854_0 *)record)->unk_72 = (s8) (u8) checked_x;
                ((S_80095854_0 *)record)->unk_73 = (s8) (u8) checked_y;
                return 1;
            }
            return 0;
        }
        ((S_80095854_0 *)record)->unk_72 = (s8) (u8) candidate_x;
        ((S_80095854_0 *)record)->unk_73 = (s8) (u8) candidate_y;
        return 1;
    }
    return 0;
}
