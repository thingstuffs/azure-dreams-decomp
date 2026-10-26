#include "common.h"
#include "shared/object_node.h"
#include "engine/node.h"

typedef struct S807AF9A4 S807AF9A4;

typedef struct S_80175814_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    void (*unk_10)(S807AF9A4 *);
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x6];
    u16 unk_2A;
} S_80175814_0;

typedef struct S_80175814_1 {
    s32 unk_00;
    u8 pad_04[0x3E];
    u16 unk_42;
} S_80175814_1;   /* arg0 in create_linked_source_object; pointer addresses record offset 0x18 */

/* cfail-repair: tf7-phase1-cache-v3 */
s32 play_sound_if_enabled();                     /* extern */
extern void func_801756D4(S807AF9A4 *data);

/* Creates an object linked to the source record and copies its initialization fields. */
void create_linked_source_object(void *sourceRecordData) {
    S_80175814_0 *createdObject;

    createdObject = allocate_list_node(0x202, sourceRecordData - 0x20);
    if (createdObject != 0) {
        createdObject->unk_10 = &func_801756D4;
        createdObject->unk_20 = sourceRecordData;
        createdObject->unk_08 = (s32) ((S_80175814_1 *)((u8 *)sourceRecordData - 0x18))->unk_00;
        createdObject->unk_2A = (u16) ((S_80175814_1 *)((u8 *)sourceRecordData - 0x18))->unk_42;
        play_sound_if_enabled(0x703);
    }
}
