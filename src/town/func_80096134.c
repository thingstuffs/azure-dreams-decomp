#include "common.h"


typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} Unk96134Bytes;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk96134Pos;

typedef struct {
    Unk96134Pos pos;
    u8 padC[0xC];
    Unk96134Bytes bytes;
} Unk96134Work;

typedef struct {
    u8 pad0[0x10];
    void *unk10;
    u8 pad14[4];
    s32 unk18;
} Unk96134State;

extern void func_8008B5D8(void *arg0, s32 arg1);
extern s32 func_800937F8(void);
extern void func_80093974(void *arg0);
extern void func_80093A00(void *arg0);
extern void func_80093A28(void);
extern void func_80093ADC(void);
extern void func_80093D48(void *arg0, void *arg1, void *arg2);
extern void func_8009451C(void *arg0, void *arg1, void *arg2);
extern void func_800947BC(void *arg0, void *arg1, void *arg2);
extern void *func_8009DFD8(void *arg0, Unk96134Pos *arg1, s32 arg2);
extern s32 func_8009F71C(void *arg0, s32 arg1);
extern s32 func_8009FF50(s32 arg0);
extern s32 func_800A0608(void);
extern s32 func_800B28A0(void);

extern u8 D_80010980[];
extern u8 D_80083498[];
extern u8 D_80088C0C[];
extern u8 D_80088C48[];
extern u8 D_80088C8C[];
extern u8 D_80088CCC[];
extern u8 D_80088D04[];
extern s32 D_80093D48;
extern u8 D_800CFCB4[];
extern s32 D_800D0428;
extern s32 D_800D0728[];
extern s32 D_800FE518;
extern void (*D_800FE5D8)(void *arg0, void *arg1, void *arg2);
extern u8 D_80110EB8[];


typedef struct S_80093894_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80093894_0;   /* data in func_80093894 */

typedef struct S_80093894_1 {
    Unk96134Bytes * unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
} S_80093894_1;   /* context in func_80093894 */

typedef struct S_80093894_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80093894_2;   /* arg1 in func_80093894 */

typedef struct S_80093894_3 {
    void * unk_00;
} S_80093894_3;   /* &D_80110EB8 in func_80093894 */

typedef struct S_80093894_4 {
    u8 pad_00[0x2C];
    void * unk_2C;
} S_80093894_4;   /* object in func_80093894 */

void func_80093894(void) {
    Unk96134Work work;
    u8 *data;
    u8 *context;
    u8 *object;
    S_80093894_2 *arg1;
    void *arg2;
    void *result;
    u32 byte1;
    s32 delta;
    s32 state_is_12_or_13;
    s32 check;
    s32 mode;

    data = D_80083498;
    object = data + 0x20;
    context = D_80110EB8;
    arg1 = ((S_80093894_0 *)data)->unk_08;
    arg2 = ((S_80093894_0 *)data)->unk_0C;

    if (((S_80093894_1 *)context)->unk_08 == 3) {
        Unk96134Bytes *source = ((S_80093894_1 *)context)->unk_00;

        work.bytes.unk0 = source->unk0;
        byte1 = source->unk1;
        work.bytes.unk1 = byte1;
        work.bytes.unk2 = source->unk2;
        work.bytes.unk3 = source->unk3;
        delta = byte1 - 0x12;
        state_is_12_or_13 = (u32)delta < 2;
        check = func_8009FF50(delta) == 1;

        if (!check) {
            if (func_800937F8() != 0) {
                func_80093974(D_80088C0C);
                return;
            }
            if (func_800A0608() >= 0x12) {
                func_80093974(D_80088C48);
                return;
            }
            if (work.bytes.unk1 == 0x13) {
                void *callback_slot;
                register void (*callback)(void *, void *, void *) ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

                func_8008B5D8(D_80088C8C, 0x11);
                func_800947BC(object, arg1, arg2);
                callback_slot = &D_800FE5D8;
                callback = (void (*)(void *, void *, void *))&D_80093D48;
                *(void (**)(void *, void *, void *))callback_slot = callback;
                func_80093A28();
                return;
            }
        } else {
            if (work.bytes.unk1 == 0x13) {
                goto process;
            }
            if (work.bytes.unk1 == 0x12) {
                mode = func_800B28A0();
                if (func_8009F71C((void *)0x80010980, D_800D0728[mode]) == -1) {
                    func_80093A00(D_80088CCC);
                    return;
                }
            } else {
                func_8008B5D8(D_80088D04, 0x11);
                func_800947BC(object, arg1, arg2);
                D_800FE5D8 = (void (*)(void *, void *, void *))&D_80093D48;
                D_800FE518 = 0;
                func_80093ADC();
                return;
            }
        }

process:
        work.pos.unk0 = arg1->unk_00;
        work.pos.unk4 = arg1->unk_04;
        work.pos.unk8 = arg1->unk_08 + D_800D0428;
        mode = 0;
        if (state_is_12_or_13) {
            register s32 zero ASM_REG("$0");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

#ifdef NON_MATCHING
            zero = 0;
#else
#endif
            mode = (u32)zero < (u32)check;
        }
        result = func_8009DFD8(((S_80093894_3 *)(&D_80110EB8))->unk_00, &work.pos, mode);
        if (result != 0) {
            Unk96134State *state = (Unk96134State *)D_800CFCB4;
            void *next;

            next = (u8 *)result + 0x20;
            ((S_80093894_4 *)object)->unk_2C = next;
            state->unk10 = next;
            state->unk18 = 0;
            func_8009451C(object, arg1, arg2);
            func_80093ADC();
            return;
        }
        func_80093D48(object, arg1, arg2);
        func_80093ADC();
        return;
    }

    D_800FE5D8(object, arg1, arg2);
}
