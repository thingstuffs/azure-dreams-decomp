#include "common.h"

typedef struct S_80404364_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80404364_0;   /* record in func_80404364 */

typedef struct S_80404364_1 {
    u8 pad_00[0x1D4];
    s32 unk_1D4;
} S_80404364_1;   /* body in func_80404364 */



extern s32 func_80047FD8(void *arg0);
extern void *func_8003C714(s32 arg0, void *arg1, s32 arg2);
extern void func_80040560(void *arg0, void *arg1);
extern void func_8007BEF0(s32 arg0);
extern void func_8007BFE0(void *arg0, s32 arg1);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern s32 func_8040422C(void *arg0);
extern void func_80404224(void);
extern void func_80404254(void *arg0, s32 arg1);
extern void func_80404314(void *arg0, s32 arg1, s32 arg2);
extern void func_80404570(void *arg0);

extern u8 D_804005F8[];
extern u8 D_80400620[];
extern u8 D_8040861C[];
extern u8 D_8040A0F0[];

/* Create or reset a slot record, initialize its body, and install its callback. */
void func_80404364(s32 init_value, s32 slot_index)
{
    u8 *record;
    u8 *body;
    s32 record_offset;

    record_offset = slot_index * 0x360;
    record = D_8040A0F0 + record_offset;
    body = record + 0x20;

    if (slot_index >= 5) {
        func_8007C040(D_804005F8, D_80400620, 0x12B);
        func_8007BEF0(1);
    }
    if (slot_index < 0) {
        func_8007C040(D_804005F8, D_80400620, 0x12C);
        func_8007BEF0(1);
    }

    if (func_80047FD8(record) == 0) {
        record = func_8003C714(0, record, 0xD8);
        if (record == 0) {
            func_8007C040(D_804005F8, D_80400620, 0x12F);
            func_8007BEF0(1);
        }
        func_80040560(record, D_8040861C);
        goto initialize_body;
    }

    func_80404570(record);
    ((S_80404364_0 *)record)->unk_1E &= 0x7FFF;
    func_8007BFE0(body, 0x340);

initialize_body:
    func_80404254(body, 10);
    ((S_80404364_0 *)record)->unk_0C = body + 0x1C8;
    ((S_80404364_1 *)body)->unk_1D4 = func_8040422C(body + 0x1D8);
    func_80404314(body, init_value, slot_index);
    {
        typedef void (*Callback)(void);
        u8 *callback_record;
        Callback callback;
        Callback default_callback;

        default_callback = func_80404224;

        if (init_value != 0) {
            callback_record = record + (init_value - init_value);
        } else {
            callback_record = record + init_value;
        }
        if (init_value != 0) {
            callback = func_80404224;
        } else {
            callback = default_callback;
        }
        (*(Callback *)((u8 *)callback_record + 0x10)) = callback;
    }
}
