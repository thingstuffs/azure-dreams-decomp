#include "common.h"
#include "shared/game_work.h"

/* D_80083160: shared state table (own view here); this function only touches
 * a u32 field at offset 8 and a s16 field at offset 0xC8 (declared >8 bytes
 * to force %hi/%lo addressing). */


extern s32 input_angle_with_offset(s32 unused, s32 angle_offset);
extern void add_a_directional_step_vector_scale_down_exceeds_length_limit(s16 angle, s32 max_length, s32 vector);

/* Passes the valid shared angle, fixed value 0x120000, and context to add_a_directional_step_vector_scale_down_exceeds_length_limit. */
void call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58(s32 context)
{
    s16 angle = input_angle_with_offset(g_game_work.buttons, g_game_work.view.camera_rotation.parts.viewAngle);

    if (angle != -1) {
        add_a_directional_step_vector_scale_down_exceeds_length_limit(angle, 0x120000, context);
    }
}
