#include "common.h"

typedef struct S_8001EDE0_0 {
    u8 pad_00[0x2C];
    s32 unk_2C;
    u8 pad_30[0x10];
    s32 unk_40;
} S_8001EDE0_0;   /* ptr in func_8001EDE0 */

typedef struct S_8001EDE0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8001EDE0_1;   /* entry_ptr in func_8001EDE0 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_80400908(void);
extern s32 func_80402084(s32, s32);
extern s32 func_80402154(s32, s32);
extern void func_80402214(void);
extern void func_8040334C(void *);
extern void func_80404688(s32);
extern void func_80405AB4(void *);
extern void func_80405C44(s32);
extern void func_80406368(void);
extern void func_80405A3C(void);

void func_80405DE0(void *ptr) {
    s32 value;
    s32 index;
    void *offset_ptr;
    void *entry_ptr;

    if (func_80402154(((S_8001EDE0_0 *)ptr)->unk_2C, 0x80010000) != 0) {
        *(s32 *)0x80010208 = 0;
        if (func_80402084((*(s32 *)((u8 *)ptr + 0x28)), 0x80010000) != 0) {
            func_80405C44(0x80010000);
            index = 0;
            func_80402214();
            entry_ptr = ptr;
            do {
                value = ((S_8001EDE0_1 *)entry_ptr)->unk_04;
                entry_ptr = (u8 *)entry_ptr + 4;
                index += 1;
                func_80404688(value);
            } while (index < 5);
            func_80405AB4(ptr);
            func_80400908();
            ((S_8001EDE0_0 *)ptr)->unk_40 = 0;
            return;
        }
    }
    offset_ptr = (u8 *)ptr - 0x20;
    *(void (**)(void))((u8 *)ptr + 0x34) = func_80406368;
    func_8040334C(offset_ptr);
    *(void **)((u8 *)ptr - 0x10) = (void *)func_80405A3C;
    func_80400908();
    ((S_8001EDE0_0 *)ptr)->unk_40 = 0;
}
