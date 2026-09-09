#include "common.h"

typedef struct S_800B1BEC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x34];
    void * unk_44;
} S_800B1BEC_0;   /* part in func_800B1BEC */

typedef struct S_800B1BEC_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_800B1BEC_1;   /* object in func_800B1BEC */



extern void *func_8003FC64(s32);
extern void *func_8004B404(s32);
extern void func_8004B1A4(void *);
extern void func_800B1B70(void *);
extern void *func_800B1938(void *);
extern void func_800B1B10(void *, s32, s32, s32);
extern void func_8004491C(void *, void *);
extern void func_800B1890(void);

extern u8 D_8004CAA0[];
extern u32 D_800814A0;

void *func_800B1BEC(s32 arg0, s32 arg1, s32 arg2)
{
    void *object;
    S_800B1BEC_0 *part;
    void *second;
    u16 flags;
    u32 global_flags;

    object = func_8003FC64(0);
    if (object != 0) {
        part = (u8 *)object + 0x20;
        part->unk_08 = func_8004B404(0xCC);
        second = func_8004B404(0xCC);
        part->unk_0C = second;

        if (part->unk_08 != 0 && second != 0) {
            ((S_800B1BEC_1 *)object)->unk_0C = (u8 *)object + 0x58;
            func_800B1B70(part);
            part->unk_44 = func_800B1938((u8 *)object + 0x68);
            func_800B1B10(part, arg0, arg1, arg2);
            func_8004491C(object, D_8004CAA0);
            ((S_800B1BEC_1 *)object)->unk_10 = func_800B1890;
        } else {
            func_8004B1A4(part->unk_08);
            func_8004B1A4(part->unk_0C);
            flags = ((S_800B1BEC_1 *)object)->unk_1E | 0x8000;
            global_flags = D_800814A0 | 0x8000;
            ((S_800B1BEC_1 *)object)->unk_1E = flags;
            D_800814A0 = global_flags;
        }
    }
    return object;
}
