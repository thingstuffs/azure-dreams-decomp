#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct LocalResult {
    s32 unk0;
    s16 value;
} LocalResult;

extern s32 func_8003DE58(void *, void *, LocalResult *, s32);
extern void func_800A2B04(void *, u8, u8);
extern s16 func_800BCB04(s32, s32, s16);
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;



typedef struct S_800AACA4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x40];
    void * unk_60;
    u8 pad_64[0x6];
    u16 unk_6A;
    u8 pad_6C[0x1E];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_800AACA4_1;   /* arg3 in func_800AACA4 */

typedef struct S_800AACA4_2_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_800AACA4_2_pre;   /* the 0x18 bytes before root in func_800AACA4, addressed as root[-1] */

typedef struct S_800AACA4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    void * unk_28;
    void * unk_2C;
} S_800AACA4_3;   /* object in func_800AACA4 */

typedef struct S_800AACA4_4 {
    void * unk_00;
} S_800AACA4_4;   /* table in func_800AACA4 */

typedef struct S_800AACA4_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AACA4_5;   /* entry in func_800AACA4 */



typedef struct S_800AACA4_8 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_800AACA4_8;   /* ((S_800AACA4_1 *)arg3)->unk_60 in func_800AACA4 */

typedef struct S_800AACA4_9 {
    void * unk_00;
} S_800AACA4_9;   /* ((S_800AACA4_3 *)object)->unk_28 in func_800AACA4 */

typedef struct S_800AACA4_10 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_800AACA4_10;   /* ((S_800AACA4_3 *)object)->unk_2C in func_800AACA4 */

typedef struct S_800AACA4_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AACA4_11;   /* ((S_800AACA4_2_pre *)root)[-1].unk_00 in func_800AACA4 */

/* Initialize movement from the source object, set vertical speed, and advance the tile. */
void func_800AACA4(Rec_func_800A9E70_arg0 *state, Rec_D_800E3D7C *motion, Rec_D_80082E80 *tile, S_800AACA4_1 *entity) {
    LocalResult height_adjustment;
    S_800AACA4_3 *source_object;
    void *entity_data;
    S_800AACA4_4 *resource_table;
    S_800AACA4_5 *resource_entry;
    register u32 step_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u32 target_offset;
    s16 travel_steps;
    s32 target_height;
    s16 travel_duration;
    u16 initial_direction;

    state->unk_9A.as_s8 = 12;
    state->unk_9B.as_s8 = 0;
    state->unk_8C = 0;
    initial_direction = ((S_800AACA4_8 *)(entity->unk_60))->unk_2A;
    entity->unk_1C &= 0xFFF7FFFF;
    entity->unk_6A = initial_direction;
    state->unk_96.as_s16 = 2;

    entity_data = entity->unk_60;
    source_object = ((S_800AACA4_2_pre *)entity_data)[-1].unk_04;
    resource_table = ((S_800AACA4_9 *)(source_object->unk_28))->unk_00;
    resource_entry = (*(void * *)((u8 *)(resource_table->unk_00) + ((S_800AACA4_10 *)(source_object->unk_2C))->unk_02 * 4));
    if (func_8003DE58(resource_entry->unk_04, source_object, &height_adjustment, 0) == 0) {
        height_adjustment.value = -0x60;
    }

    entity_data = entity->unk_60;
    motion->unk_08.at02_s16.v = ((S_800AACA4_11 *)(((S_800AACA4_2_pre *)entity_data)[-1].unk_00))->unk_0A + height_adjustment.value;
    tile->unk_24 = source_object->unk_24;
    tile->unk_25 = source_object->unk_25;
    func_800A2B04(motion, tile->unk_24, tile->unk_25);

    travel_steps = entity->unk_8A.s;
    if (travel_steps != 0) {
        target_offset = entity->unk_6A;
        target_offset >>= 8;
        target_offset &= 0xE;
        target_height = func_800BCB04(
            ((tile->unk_24 + (*(s16 *)((u8 *)(&D_8006CCD8) + target_offset)) * travel_steps) << 6) + 0x20 & 0xFFE0,
            ((tile->unk_25 + (*(s16 *)((u8 *)(&D_8006CCE8) + target_offset)) * travel_steps) << 6) + 0x20 & 0xFFE0,
            motion->unk_08.at02_s16.v);
        travel_duration = entity->unk_8A.u + 2;
        entity->unk_8A.s = travel_duration;
        if (target_height < 0x200) {
            motion->unk_14.as_s32 = -((motion->unk_08.at02_s16.v - target_height) << 15) / travel_duration;
        } else {
            motion->unk_14.as_s32 = -((motion->unk_08.at02_s16.v - ((S_800AACA4_8 *)(entity->unk_60))->unk_88) << 15) / travel_duration;
        }
        entity->unk_8A.s = entity->unk_8A.u - 2;
    }

    step_offset = entity->unk_6A;
    step_offset >>= 8;
    step_offset &= 0xE;
    tile->unk_24 += (*(u8 *)((u8 *)(&D_8006CCD8) + step_offset));
    step_offset = entity->unk_6A;
    step_offset >>= 8;
    step_offset &= 0xE;
    tile->unk_25 += (*(u8 *)((u8 *)(&D_8006CCE8) + step_offset));
}
