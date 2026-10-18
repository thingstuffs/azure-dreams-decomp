#include "common.h"
typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    s16 z;
} Position;
typedef struct {
    u8 pad[0x6C];
    s16 timer;
} Object;
void move_reaction_toward_target(Object *object, Position *position, void *context);

typedef struct S_800CA75C_0 {
    u8 pad_00[0x54];
    s32 * unk_54;
    u8 pad_58[0x14];
    s16 unk_6C;
} S_800CA75C_0;   /* arg0 in initialize_reaction_data_and_timer_13 */

/* Set the object's data pointer and state to 13. */
void initialize_reaction_data_and_timer_13(S_800CA75C_0 *object) {
    object->unk_54 = &move_reaction_toward_target;
    object->unk_6C = 0xD;
}
