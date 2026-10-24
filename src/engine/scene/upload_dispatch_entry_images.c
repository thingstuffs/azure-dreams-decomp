#include "common.h"
#include "engine/scene.h"

/* Struct pointed to by D_8006CE80[i].unk4; its field at offset 8 is a pointer
 * passed to decode_and_upload_image_array. */
typedef struct S_8006CE80_inner {
    s32 unk0;
    s32 unk4;
    void *unk8;
} S_8006CE80_inner;

/* Array element struct for D_8006CE80, 12 bytes wide (idx*12 indexing). */
typedef struct S_8006CE80 {
    s32 unk0;
    S_8006CE80_inner *unk4;
    s32 unk8;
} S_8006CE80;

extern S_8006CE80 dispatch_resource_records[35];
extern void decode_and_upload_image_array(void *arg);

/* Passes the indexed entry's nested pointer to decode_and_upload_image_array if both pointers exist. */
void upload_dispatch_entry_images(u16 index) {
    s32 byte_offset = (s32)index * 3 * 4;
    S_8006CE80 *entry = (S_8006CE80 *)((u8 *)dispatch_resource_records + byte_offset);
    S_8006CE80_inner *inner = entry->unk4;

    if (inner != (S_8006CE80_inner *)0) {
        void *target = inner->unk8;

        if (target != (void *)0) {
            decode_and_upload_image_array(target);
        }
    }
}
