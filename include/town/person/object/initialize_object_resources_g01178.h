#ifndef TOWN_PERSON_OBJECT_INITIALIZE_OBJECT_RESOURCES_G01178_H
#define TOWN_PERSON_OBJECT_INITIALIZE_OBJECT_RESOURCES_G01178_H
struct TownObjectRecord;
/* Initialize object resources. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800C7AB4. */

#include "common.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80100D98.h"
#include "shared/vector.h"
#include "shared/object_index_slots.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"

#ifndef NULL
#define NULL 0
#endif

/* ((S_800C4F6C_5 *)arg0)->unk_80 in initialize_object_resources_2 */
/* arg1 in initialize_object_resources_2 */

typedef struct S_800C51DC_0 {
    u8 pad_00[0x54];
    s32 * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} S_800C51DC_0;

typedef struct S_800C5214_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA8];
    s32 unk_BC;
} S_800C5214_0;

void create_resource_display_object(s16 resource_index);
/* extern */
/* extern */
extern M2C_UNK D_800D50DC;
extern M2C_UNK D_800D50F0;
extern M2C_UNK D_800D50F8;
extern M2C_UNK D_800D5120;
extern M2C_UNK D_800D5124;
extern Rec_D_80100D98 town_position_reference_state;
extern void tcame_chase_fix(s32 *chase_fix);
extern s32 D_80113208[];
extern u8 message_motion_type_b[];
extern s32 D_800C5100;
/* object in create_user_data_object_b */
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern u8 D_800345B8[];
extern u8 D_800C52D0[];
extern u8 D_800F148C[];

/* Shared import declarations; data casts preserve each measured view. */
#include "town/person/object_setup.h"
#include "town/person.h"
#include "shared/town_object.h"

/* Functions defined in this translation unit. */
void initialize_object_resources_2(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *display_state);
void set_camera_chase_data(TownObjectRecord *object, ObjectPosition *chase_data, SpriteFrameState *request_param, s32 check_param);
void clear_object_slot_table_run(struct TownObjectRecord *obj, void *param_a, void *param_b);
void accelerate_object_coordinates_to_lower_limits(TownObjectRecord *context, ObjectPosition *record, SpriteFrameState *callback_arg);
void init_actor_handler_state(S_800C51DC_0 *actor, ObjectPosition *state);
void *create_user_data_object_b(s32 user_data);

#endif
