#include "common.h"

typedef struct S_80171F30_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80171F30_0;   /* object in func_80171F30 */

typedef struct S_80171F30_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80171F30_1;   /* arg0 in func_80171F30 */

typedef struct S_80171F30_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_80171F30_2;   /* data in func_80171F30 */

typedef struct S_80171F30_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80171F30_3;   /* header in func_80171F30 */

typedef struct S_80171F30_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    s16 unk_34;
} S_80171F30_4;   /* tail in func_80171F30 */

typedef struct S_80171F30_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80171F30_5;   /* ((S_80171F30_0 *)object)->unk_08 in func_80171F30 */

typedef struct S_80171F30_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80171F30_6;   /* ((S_80171F30_1 *)arg0)->unk_08 in func_80171F30 */



extern u8 D_80171704[];
extern u8 D_80171CC0[];
extern u8 D_80171D90[];
extern u8 D_80171E60[];

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 rand(void);

/* Creates an object at a randomized offset from its parent and initializes its mode and state. */
void func_80171F30(S_80171F30_1 *parent, s32 state_value, s16 tail_value_in, s16 mode_in)
{
    void *object;
    S_80171F30_3 *header;
    void *call_object;
    void *init_data;
    void *tail;
    register s32 resource_addr;
    register s16 mode ASM_REG("$19");
    s32 mode_index;
    register s16 tail_value;
    s16 mode_value;
    s32 alloc_kind;
    void *source;
    void *position;
    s32 jitter;
    s32 coord;

    alloc_kind = 0x211;
    source = parent;
    mode_value = mode_in;
    tail_value = tail_value_in;
    object = func_8003FD64(alloc_kind, source);
    if (object == 0) {
        return;
    }

    mode = mode_value;
    resource_addr = ((s32)mode_value) << 16;
    mode_index = resource_addr >> 16;
    resource_addr = (s32)0x80170000;
    if (mode_index == 0) {
        ASM_KEEP(resource_addr);
        resource_addr += 0x1CC0;
    } else {
        resource_addr = 1;
        if (mode_index == resource_addr) {
            resource_addr = (s32)0x80170000;
            ASM_KEEP(resource_addr);
            resource_addr += 0x1D90;
        } else {
            resource_addr = (s32)D_80171E60;
        }
    }
    ((S_80171F30_0 *)object)->unk_10 = (void *)resource_addr;
    ((S_80171F30_5 *)(((S_80171F30_0 *)object)->unk_08))->unk_02 =
        ((S_80171F30_6 *)(parent->unk_08))->unk_02;
    ((S_80171F30_5 *)(((S_80171F30_0 *)object)->unk_08))->unk_06 =
        ((S_80171F30_6 *)(parent->unk_08))->unk_06;
    ((S_80171F30_5 *)(((S_80171F30_0 *)object)->unk_08))->unk_0A =
        ((S_80171F30_6 *)(parent->unk_08))->unk_0A;

    if ((mode << 16) == 0) {
        jitter = rand();
        position = ((S_80171F30_0 *)object)->unk_08;
        coord = ((S_80171F30_2 *)position)->unk_02;
        jitter &= 7;
        coord -= 4;
        coord += jitter;
        ((S_80171F30_2 *)position)->unk_02 = coord;
        jitter = rand();
        position = ((S_80171F30_0 *)object)->unk_08;
        coord = ((S_80171F30_2 *)position)->unk_06;
        jitter &= 7;
        coord -= 4;
    } else {
        ASM_KEEP(mode);
        jitter = rand();
        position = ((S_80171F30_0 *)object)->unk_08;
        coord = ((S_80171F30_2 *)position)->unk_02;
        jitter &= 0xF;
        coord -= 0xC;
        coord += jitter;
        ((S_80171F30_2 *)position)->unk_02 = coord;
        jitter = rand();
        position = ((S_80171F30_0 *)object)->unk_08;
        coord = ((S_80171F30_2 *)position)->unk_06;
        jitter &= 0xF;
        coord -= 0xC;
    }
    coord += jitter;
    ((S_80171F30_2 *)position)->unk_06 = coord;
    ASM_KEEP(coord);

    call_object = object;
    init_data = D_80171704;
    header = ((S_80171F30_0 *)object)->unk_0C;
    tail = (u8 *)object + 0x20;
    header->unk_06 = 0;
    ((S_80171F30_4 *)tail)->unk_32 = tail_value;
    ((S_80171F30_4 *)tail)->unk_34 = tail_value;
    func_8004491C(call_object, init_data);
    ((S_80171F30_0 *)object)->unk_20 = state_value;
    ((S_80171F30_4 *)tail)->unk_08 = state_value;
}
