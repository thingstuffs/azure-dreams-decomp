#include "common.h"

extern void func_80402A1C(void *arg0, void *arg1);
extern void func_80402BE0(void *arg0);
extern void func_8040274C(void *arg0);
extern void func_804027F8(void);
extern void func_8040293C(void);
extern u8 D_80408ADF[];

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
} Struct8001BF04;

/* Initialize the object from its table entry and select its callback. */
void func_8001BF04(Struct8001BF04 *object) {
    s32 callback;
    s32 table_offset;

    func_80402A1C((void *)((s32) object + 0x24), object);
    func_80402BE0(object);
    table_offset = object->unk08 * 4;
    object->unk00 = D_80408ADF[table_offset];
    func_8040274C(object);
    callback = (s32) func_804027F8;
    if (object->unk0C == 2) {
        callback = (s32) func_8040293C;
    }
    *(s32 *)((s32) object - 0x10) = callback;
}
