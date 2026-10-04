#include "common.h"


typedef void (*Callback)(void *);

extern s32 func_80047FD8(void *object);
extern s32 func_8003C714(s32 value, void *object, s32 size);
extern void func_8007C040(void *ptr0, void *ptr1, s32 value);
extern void func_8007BEF0(s32 value);
extern void func_80040560(s32 object, void *ptr);
extern void func_80403D24(void *object);
extern void func_8007BFE0(void *object, s32 size);
extern void func_80403AC8(void *object, s32 value);
extern s32 func_80403AA0(void *ptr);
extern void func_80403B84(void *object, s32 option_param);
extern void func_804034D8(void *object);

extern u8 D_804005A0[];
extern u8 D_804005C8[];
extern u8 D_8040861C[];
extern u8 D_80409C90[];
extern u16 D_80409CAE;


typedef struct S_8001CBC4_0 {
    u8 pad_00[0x1B4];
    s32 unk_1B4;
} S_8001CBC4_0;   /* subobject in func_8001CBC4 */

/* Initializes or retrieves the memory card options object. */
s32 func_80403BC4(s32 option_param) {
    s32 object_status;
    u8 *object = D_80409C90;
    u8 *subobject;
    u8 *object_arg;

    object_arg = object;
    subobject = object + 0x20;
    object_status = func_80047FD8(object_arg);
    if (object_status == 0) {
        object = (u8 *)func_8003C714(0, object, 0x118);
        if (object == 0) {
            func_8007C040(D_804005A0, D_804005C8, 0x151);
            func_8007BEF0(1);
        }
        func_80040560((s32)object, D_8040861C);
    } else {
        func_80403D24(object);
        D_80409CAE &= 0x7FFF;
        func_8007BFE0(subobject, 0x440);
    }
    func_80403AC8(subobject, 0x12);
    (*(void * *)((u8 *)object + (0xC))) = subobject + 0x1A8;
    ((S_8001CBC4_0 *)subobject)->unk_1B4 = func_80403AA0(subobject + 0x1B8);
    func_80403B84(subobject, option_param);
    (*(Callback *)((u8 *)object + (0x10))) = func_804034D8;
    func_804034D8(subobject);
    return (s32)object;
}
