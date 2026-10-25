#ifndef TOWN_PERSON_OBJECT_INITIALIZE_OBJECT_RESOURCES_G01178_H
#define TOWN_PERSON_OBJECT_INITIALIZE_OBJECT_RESOURCES_G01178_H
/* Initialize object resources. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01178 - CL:town/func_800C7AB4. */

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

typedef struct S_800C4F6C_5 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C4F6C_5;

/* arg0 in initialize_object_resources_2 */
typedef struct S_800C4F6C_6 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800C4F6C_6;

/* ((S_800C4F6C_5 *)arg0)->unk_80 in initialize_object_resources_2 */
/* arg1 in initialize_object_resources_2 */
typedef struct S_800C4F6C_1 {
    s32 * unk_00;
} S_800C4F6C_1;

/* arg0 in initialize_object_resources_2; pointer addresses record offset 0x10 */
typedef struct S_800C4F6C_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800C4F6C_2;

/* arg2 in initialize_object_resources_2 */
typedef struct S_800C4F6C_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800C4F6C_4;

typedef struct S_800C51DC_0 {
    u8 pad_00[0x54];
    s32 * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} S_800C51DC_0;

/* arg0 in init_actor_handler_state */
typedef struct S_800C51DC_1 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_800C51DC_1;

typedef struct S_800C5214_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA8];
    s32 unk_BC;
} S_800C5214_0;

void create_resource_display_object(s16 resource_index);
/* extern */
void copy_entity_record_fields();
/* extern */
extern M2C_UNK D_800D50DC;
extern M2C_UNK D_800D50F0;
extern M2C_UNK D_800D50F8;
extern M2C_UNK D_800D5120;
extern M2C_UNK D_800D5124;
extern Rec_D_80100D98 town_position_reference_state;
extern s32 service_script_controller(void);
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

/* Functions defined in this translation unit. */
void initialize_object_resources_2(void *object, IntVector3 *position, S_800C4F6C_2 *display_state);
void set_camera_chase_data(void *object, void *chase_data, s32 request_param, s32 check_param);
void clear_object_slot_table_run(void *obj, void *param_a, void *param_b);
void accelerate_object_coordinates_to_lower_limits(void *context, EntityRec *record, void *callback_arg);
void init_actor_handler_state(S_800C51DC_0 *actor, S_800C51DC_1 *state);
void *create_user_data_object_b(s32 user_data);

#endif
