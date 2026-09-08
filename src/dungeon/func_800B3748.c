#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
} FuncInput;

typedef struct {
    u8 pad0[2];
    u16 unk2;
    u8 pad4[2];
    u16 unk6;
    u8 pad8[2];
    u16 unkA;
    u8 padC[2];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} FuncChild;

typedef struct {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
    s16 unk10;
    u8 pad12[2];
    u16 unk14;
    u8 pad16[6];
    s16 unk1C;
    s16 unk1E;
    u8 pad20[2];
    s16 unk22;
} FuncMeta;

typedef struct {
    u8 pad0[8];
    FuncChild *child;
    FuncMeta *meta;
    void *unk10;
    u8 pad14[14];
    s16 unk22;
} FuncObject;

extern s32 D_800CEEFC[3];
extern s32 D_800B8E18;
extern void *func_8003FD64(s16, s32);
extern s32 func_8004491C(void *, s32 *);

/* Allocate and initialize a type-0x12 object with child and metadata values. */
void func_800B8EA8(s32 alloc_arg, s32 child_x, s32 child_y, s32 child_z,
                   FuncInput *input, s32 meta_value, s16 step_count, s32 range_value, s16 object_tag) {
    FuncMeta *meta;
    FuncObject *object;
    FuncChild volatile *child;
    u16 input_z;
    s32 signed_count;

    object = func_8003FD64(0x12, alloc_arg);
    if (object != NULL) {
        object->unk10 = &D_800B8E18;
        func_8004491C(object, D_800CEEFC);
        child = object->child;
        child->unk2 = input->unk0;
        child->unk6 = input->unk2;
        input_z = input->unk4;
        child->unkE = child_x;
        child->unk12 = child_y;
        child->unk16 = child_z;
        child->unkA = input_z;
        meta = object->meta;
        meta->unk8 = meta_value;
        meta->unk1E = range_value;
        meta->unk1C = range_value;
        meta->unkC = 0x808080;
        signed_count = ((s32) step_count << 16) >> 16;
        if (signed_count != 0) {
            meta->unk10 = (s16) ((signed_count - 1) << 5);
            meta->unk14 = (u16) (meta->unk14 | 0xC);
        }
        object->unk22 = object_tag;
    }
}
