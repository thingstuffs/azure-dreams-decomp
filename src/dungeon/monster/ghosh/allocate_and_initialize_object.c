#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_status.h"


typedef struct {
    u8 bytes[12];
} Packed12;

extern void register_node(void *, void *);
extern u8 D_80044BB0[];
extern Packed12 D_80077818;
extern u8 D_8016A9FC[];


typedef struct S_8016AC30_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8016AC30_0;   /* position in allocate_and_initialize_object */

typedef struct S_8016AC30_1 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_8016AC30_1;   /* primitive in allocate_and_initialize_object */

/* Allocate and initialize a dungeon object, then increment the object count. */
void allocate_and_initialize_object(void) {
    ObjectNodeHeader * object;
    S_8016AC30_0 *position;
    S_8016AC30_1 *primitive;

    object = allocate_flagged_object_node(0x12);
    if (object != 0) {
        (object->unk_10) = D_8016A9FC;
        register_node(object, D_80044BB0);

        position = (object->unk_08);
        position->unk_0A = 0;
        position->unk_06 = 0;
        position->unk_02 = 0;

        primitive = (object->unk_0C);
        primitive->unk_1E = 0;
        primitive->unk_1C = 0;
        primitive->unk_0E = 0;
        primitive->unk_0D = 0;
        primitive->unk_0C = 0;

        (*(Packed12 *)((u8 *)object + 0x4C)) = D_80077818;
        primitive->unk_08 = (u8 *)object + 0x4C;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }
}
