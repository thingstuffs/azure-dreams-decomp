#include "common.h"


typedef void (*Callback)(void *);

extern s32 func_80047FD8(void *arg0);
extern s32 func_8003C714(s32 arg0, void *arg1, s32 arg2);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern void func_8007BEF0(s32 arg0);
extern void func_80040560(s32 arg0, void *arg1);
extern s32 func_80403C78(void *arg0);
extern void func_80403D24(void *arg0);
extern void func_8007BFE0(void *arg0, s32 arg1);
extern void func_80403AC8(void *arg0, s32 arg1);
extern s32 func_80403AA0(void *arg0);
extern void func_80403B84(void *arg0, s32 arg1);
extern void func_804034D8(void *arg0);

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
s32 func_8001CBC4(s32 option_param) {
    s32 resource_id;
    s32 object_status;
    u8 *object = D_80409C90;
    u8 *subobject;
    register u8 *object_arg ASM_REG("$4");

    ASM_KEEP_NV(object);
    object_arg = object;
    subobject = object + 0x20;
    object_status = func_80047FD8(object_arg);
    if (object_status == 0) {
        resource_id = func_8003C714(0, object, 0x118);
        if (resource_id == 0) {
            func_8007C040(D_804005A0, D_804005C8, 0x151);
            func_8007BEF0(1);
        }
        func_80040560(resource_id, D_8040861C);
        return func_80403C78(subobject);
    }
    func_80403D24(object);
    D_80409CAE &= 0x7FFF;
    func_8007BFE0(subobject, 0x440);
    func_80403AC8(subobject, 0x12);
    ASM_KEEP_NV(subobject);
    (*(void * *)((u8 *)object + (0xC))) = subobject + 0x1A8;
    ((S_8001CBC4_0 *)subobject)->unk_1B4 = func_80403AA0(subobject + 0x1B8);
    func_80403B84(subobject, option_param);
    (*(Callback *)((u8 *)object + (0x10))) = func_804034D8;
    func_804034D8(subobject);
    return (s32)object;
}
