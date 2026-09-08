#include "common.h"

typedef struct S_8080C324_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xB8];
    void * unk_CC;
} S_8080C324_0;   /* node in func_8080C324 */

typedef struct S_8080C324_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8080C324_1;   /* root in func_8080C324 */

typedef struct S_8080C324_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_8080C324_2;   /* inner in func_8080C324 */

typedef struct S_8080C324_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8080C324_3;   /* ((S_8080C324_0 *)node)->unk_08 in func_8080C324 */


typedef struct {
    s16 f0;
    s16 f2;
    void *f4;
    s32 f8;
    s16 fC;
    s16 fE;
    s16 f10;
    s16 f12;
    s16 f14;
    u16 f16;
    u8 pad18[0x10];
} Record28;

typedef struct {
    s16 f0;
    s16 f2;
    s32 f4;
    u8 pad8[4];
    void *fC;
    s32 f10;
    s16 f14;
    s16 f16;
    s16 f18;
    s16 f1A;
    s16 f1C;
    u8 pad1E[0x12];
} Record30;

extern void func_80034A1C(void *, void *, s32);
extern void func_800351A8(s32, s32);
extern void *func_800374FC(s32, void *);
extern void func_8003BC18(void *, void *);
extern void func_80058F88(s32);
extern void func_8023FAE8(void *, void *, void *);
extern void func_80526BFC(void *, void *);
extern void func_80526C90(void *, void *);

extern u8 D_8003C558[];
extern u8 D_801328C8[];
extern u8 D_80289454[];
extern u8 D_805267E0[];
extern u8 D_805268D4[];
extern u8 D_80526970[];
extern u8 D_80526A0C[];
extern u8 D_80527250[];
extern u8 D_80527D5C[];
extern u8 D_8052FF84[];
extern s32 D_80530000[];
extern s32 D_805300BC[];
extern s32 D_805300C0[];
extern s16 D_80530666[];
extern s16 D_805306D6[];
extern s32 D_805306D8[];


s32 func_8080C324(void) {
    Record30 rec2;
    Record28 rec1;
    s16 *lower;
    s16 *upper;
    s32 count;
    s32 loop_value;
    register s32 page1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 page2;
    s32 store_page;
    s32 store_value;
    s16 value1;
    s32 loaded;
    s32 field_value;
    void *node;
    S_8080C324_1 *root;
    S_8080C324_2 *inner;
    void *call_base;
    void *call_record;

    root = 0;
    func_80058F88(0x704);
    func_800351A8(0x3C, 0);
    func_800351A8(0x3D, 0);
    node = func_800374FC(1, D_801328C8);
    if (node != 0) {
        root = (u8 *)node + 0x20;
        ((S_8080C324_0 *)node)->unk_10 = (s32)D_80527D5C;
    }
    node = func_800374FC(0x136, D_801328C8);
    root->unk_04 = node;
    if (node != 0) {
        ((S_8080C324_0 *)node)->unk_10 = (s32)D_80527250;
        func_8003BC18(node, D_8003C558);
        inner = ((S_8080C324_0 *)node)->unk_0C;
        ((S_8080C324_3 *)(((S_8080C324_0 *)node)->unk_08))->unk_00 = 0x03A00000;
        ((S_8080C324_3 *)(((S_8080C324_0 *)node)->unk_08))->unk_04 = 0x01E00000;
        ((S_8080C324_3 *)(((S_8080C324_0 *)node)->unk_08))->unk_08 = 0x00200000;
        ((S_8080C324_0 *)node)->unk_CC = root;
        inner->unk_1E = 0x1000;
        inner->unk_1C = 0x1000;
        func_80034A1C(inner, D_80289454, 0);
        inner->unk_0C = 0x00808080;
        func_8023FAE8((u8 *)node + 0x20, ((S_8080C324_0 *)node)->unk_08, D_8052FF84);
    }

    count = 7;
    loop_value = 0x30;
    page1 = 0x80530000;
    ASM_KEEP_NV(page1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    page1 += 0x6D6;
    upper = (s16 *)page1;
    page2 = 0x80530000;
    ASM_KEEP_NV(page2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    page2 += 0x666;
    lower = (s16 *)page2;
    do {
        *lower = 0;
        *upper = loop_value;
        upper--;
        count--;
        lower--;
    } while (count >= 0);

    loaded = 0x00404040;
    call_base = D_805267E0;
    call_record = &rec1;
    ASM_USE2(call_base, call_record);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    count = 8;
    value1 = 0xE0;
    rec1.f8 = loaded;
    loaded = rec1.f16;
    store_value = 0x3020;
    store_page = 0x80530000;
    *(s32 *)(store_page + 0x6D8) = store_value;
    rec1.fC = 0x30;
    rec1.fE = 0xA0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    field_value = 0xE0;
    ASM_KEEP_NV(field_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    rec1.f10 = field_value;
    rec1.f12 = 0x22;
    rec1.f14 = 2;
    rec1.f0 = 0;
    rec1.f2 = 0x10;
    rec1.f4 = root;
    loaded |= 3;
    rec1.f16 = loaded;
    func_80526C90(call_base, call_record);

    rec1.fE = 0xA2;
    rec1.f10 = 1;
    rec1.f12 = 0x1E;
    rec1.f14 = 0;
    rec1.f8 = 0x00808080;
    rec1.f0 = 0;
    rec1.f4 = root;
    rec1.f16 |= 0xFFFD;
    do {
        rec1.fC = value1;
        func_80526C90(D_805268D4, &rec1);
        count--;
        value1 -= 0x10;
    } while (count >= 0);

    rec1.fC = 0x32;
    rec1.fE = 0xB0;
    rec1.f10 = 0xDC;
    rec1.f12 = 1;
    func_80526C90(D_805268D4, &rec1);

    {
        s32 *words2;
        s32 count2;
        s16 value2;
        s32 init_value;
        s32 loop_value;
        void *base2;
        void *record2;

        init_value = 0x00808080;
        base2 = D_80526970;
        record2 = &rec2;
        ASM_USE2(base2, record2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        count2 = 8;
        ASM_KEEP_NV(count2);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        value2 = 0xE4;
        words2 = D_805300BC;
        rec2.f10 = init_value;
        init_value = (s32)0x80530000;
        init_value = *(s32 *)(init_value + 0xC0);
        rec2.f14 = 0x34;
        rec2.f16 = 0xB6;
        rec2.f18 = 3;
        rec2.f1C = 2;
        rec2.f1A = 0x7C80;
        rec2.f0 = 0;
        rec2.f2 = 0x10;
        rec2.fC = root;
        rec2.f4 = init_value;
        func_80526BFC(base2, record2);

        rec2.f16 = 0xA4;
        do {
            register void *iter_base ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            register void *iter_record ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

            iter_base = D_80526970;
            loop_value = *words2;
            ASM_USE(loop_value);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            iter_record = &rec2;
            ASM_KEEP_NV(iter_record);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            rec2.f14 = value2;
            value2 -= 0x10;
            words2--;
            count2--;
            rec2.f4 = loop_value;
            func_80526BFC(iter_base, iter_record);
        } while (count2 >= 0);

        rec2.f14 = 0xF4;
        rec2.f16 = 0xB6;
        rec2.f4 = (s32)D_805306D8;
        func_80526BFC(D_80526A0C, &rec2);
    }
    return 0;
}
