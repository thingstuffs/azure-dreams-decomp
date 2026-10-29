#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"
#include "town/scene/motion.h"
typedef struct Vec3s { s16 x; s16 y; s16 z; s16 pad; } Vec3s;
typedef void (*ReportValue)(const char *, const char *, s32);

extern char D_8001610C[8];
extern char D_80016118[8];
extern char D_80016120[8];
extern char D_80016128[8];
/* Blends s0 and s1 into s, reports their x values, and stores the result coordinates. */
void blend_position_and_trace(s32 first_input, s32 second_input, s32 blend_weight, s32 remaining_weight)
{
    Vec3s s0;
    Vec3s s1;
    Vec3s s;
    Rec_D_80016000 *root;
    const char *first_format;
    const char *second_format;
    const char *result_format;
    call_state_handler_and_copy_values(&s0, first_input);
    {
        ReportValue report;
        report = town_scene_root->services->callback_168;
        first_format = D_8001610C;
        report(first_format, D_80016118, s0.x);
    }
    first_format = 0;
    call_state_handler_and_copy_values(&s1, second_input);
    {
        ReportValue report;
        report = town_scene_root->services->callback_168;
        second_format = D_8001610C;
        report(second_format, D_80016120, s1.x);
    }
    second_format = 0;
    blend_point_2s_by_signed_weight(&s0, &s1, blend_weight, remaining_weight, &s);
    {
        ReportValue report;
        report = town_scene_root->services->callback_168;
        result_format = D_8001610C;
        report(result_format, D_80016128, s.x);
    }
    root = town_scene_root;
    ((TownPositionState *)root->position)->x = s.x;
    ((TownPositionState *)root->position)->y = s.y;
}
