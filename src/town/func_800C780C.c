#include "common.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct S_800C4F6C_5 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C4F6C_5;   /* arg0 in initialize_object_resources_2 */

typedef struct S_800C4F6C_6 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800C4F6C_6;   /* ((S_800C4F6C_5 *)arg0)->unk_80 in initialize_object_resources_2 */


typedef struct S_800C4F6C_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800C4F6C_0;   /* arg1 in initialize_object_resources_2 */

typedef struct S_800C4F6C_1 {
    s32 * unk_00;
} S_800C4F6C_1;   /* arg0 in initialize_object_resources_2; pointer addresses record offset 0x10 */

typedef struct S_800C4F6C_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800C4F6C_2;   /* arg2 in initialize_object_resources_2 */


typedef struct S_800C4F6C_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800C4F6C_4;


void create_resource_display_object();                     /* extern */
void copy_entity_record_fields();            /* extern */
void initialize_object_and_register_slot(); /* extern */
void *func_800C5214();                      /* extern */
void set_camera_chase_data(void *object, void *chase_data, s32 request_param, s32 check_param);
extern M2C_UNK D_800D50DC;
extern M2C_UNK D_800D50F0;
extern M2C_UNK D_800D50F8;
extern M2C_UNK D_800D5120;
extern M2C_UNK D_800D5124;
#include "records/Rec_D_80100D98.h"
extern Rec_D_80100D98 D_80100D98;

/* Initialize object resources and display state, then copy its position to shared state. */
void initialize_object_resources_2(void *object, S_800C4F6C_0 *position, S_800C4F6C_2 *display_state) {
    EntityRec *shared_position;

    initialize_object_and_register_slot(object, 0x1D, &D_800D5120, &D_800D5124,
                  &D_800D50F0, &D_800D50F8);
    position->unk_08 = 0xFF800000;
    ((S_800C4F6C_6 *)(((S_800C4F6C_5 *)object)->unk_80))->unk_04 = &D_800D50DC;
    ((S_800C4F6C_1 *)((u8 *)object - 0x10))->unk_00 = &set_camera_chase_data;
    display_state->unk_10 = 0;
    display_state->unk_14 = (u16) (display_state->unk_14 | 0xC);
    func_800C5214(object - 0x20);
    create_resource_display_object(0);
    create_resource_display_object(1);
    display_state->unk_1E = 0x800;
    display_state->unk_1C = 0x800;
    position->unk_04 = 0x04300000;
    ((EntityRec *)((u8 *)(&D_80083780)))->x.v = position->unk_00;
    shared_position = &D_80083780;
    shared_position->y.v = (s32) position->unk_04;
    shared_position->z.v = (s32) position->unk_08;
    copy_entity_record_fields(&D_80100D98, shared_position);
}
