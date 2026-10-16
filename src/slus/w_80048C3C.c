#include "common.h"
#include "m2c_compat.h"

typedef struct S_80048C3C_0 {
    s32 unk_00;
    void * unk_04;
} S_80048C3C_0;   /* temp_s1 in resourceLoadIndexedSpriteBundle */

typedef struct S_80048C3C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
} S_80048C3C_1;   /* temp_s2 in resourceLoadIndexedSpriteBundle */

M2C_UNK DrawSync();                          /* extern */
M2C_UNK Control_CD();       /* extern */
M2C_UNK drainCdCommandQueue();                            /* extern */
void uploadVramRowAndCache(); /* extern */
s32 relocateSpriteMetadataPointers();                      /* extern */
void markPaletteColorsWithHighBit();    /* extern */
void textureMarkUnprocessedTypeN2NodeSequencesSetLowSixBitsN14();                      /* extern */
extern u8 D_80071210[];
extern s8 D_80080A89;

/* Loads and initializes a resource, registers its payload in two VRAM cache slots, and returns its table slot. */
void *resourceLoadIndexedSpriteBundle(s32 resource_id) {
    void *payload;
    void *entry;
    void *entry2;
    void *entry3;
    void *resource;
    s32 load_mode;

    entry = (void *)(resource_id * 8);
    load_mode = 6;
    entry2 = (u8 *)entry + (u32)D_80071210;
    Control_CD(load_mode, ((S_80048C3C_0 *)entry2)->unk_00, 0);
    drainCdCommandQueue();
    resource = ((S_80048C3C_0 *)entry2)->unk_04;
    payload = resource + ((S_80048C3C_1 *)resource)->unk_1C;
    uploadVramRowAndCache(payload, 0x7A00, ((S_80048C3C_1 *)resource)->unk_20, 2);
    DrawSync(0);
    markPaletteColorsWithHighBit(payload, 1, 1);
    uploadVramRowAndCache(payload, 0x7980, ((S_80048C3C_1 *)resource)->unk_20, 2);
    relocateSpriteMetadataPointers(resource);
    entry3 = (u8 *)entry2 + 4;
    textureMarkUnprocessedTypeN2NodeSequencesSetLowSixBitsN14(resource);
    D_80080A89 = 0;
    return entry3;
}
