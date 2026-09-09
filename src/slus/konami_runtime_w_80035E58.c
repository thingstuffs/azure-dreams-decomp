#include "common.h"

#include "common.h"

typedef void (*Callback)(void *);

typedef struct S_func_80035E58_0 {
    u8 pad_00[0xC];
    u8 *unk_0C;
    Callback unk_10;
    u8 pad_14[0xC];
    void *unk_20;
} S_func_80035E58_0;

typedef struct S_func_80035E58_1 {
    u8 pad_00[0x4];
    void *unk_04;
    Callback unk_08;
    u8 pad_0C[0x6];
    u16 unk_12;
    u8 pad_14[0x1A];
    u16 unk_2E;
    u8 pad_30[0x6];
    u16 unk_36;
    u8 pad_38[0xC];
    s32 *unk_44;
    u8 unk_48;
    u8 pad_49[0x1];
    s16 unk_4A;
    u8 pad_4C[0x1C];
    Callback unk_68;
    u8 pad_6C[0x8];
    void *unk_74;
} S_func_80035E58_1;

typedef struct S_func_80035E58_2 {
    s32 unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    union {
        void *unk_08_ptr;
        u32 unk_08_u32;
    } unk_08;
    u32 unk_0C;
} S_func_80035E58_2;

typedef struct S_func_80035E58_3 {
    u8 pad_00[0x80];
    u8 *unk_80;
} S_func_80035E58_3;

typedef struct S_func_80035E58_4 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_func_80035E58_4;

typedef struct S_func_80035E58_5 {
    u8 pad_00[0x34];
    s32 unk_34;
} S_func_80035E58_5;

extern void *func_8003FF2C(s32, s32, s32, void *);
extern void func_8004491C(void *, Callback);
extern void ClearImage(void *, s32, s32, s32);
extern void func_80033C1C(void *, s32);
extern void func_800350B0(void *, void *);
extern void func_80036988(void *, void *);
extern void func_800375C0(void *, void *);

extern void func_80033D54(void *);
extern void func_8003605C(void *);
extern void func_80036110(void *);
extern void func_80037714(void *);

extern u8 D_80082BC0[];
extern u8 D_8006AA3C[];
extern u8 D_80073AAC[];
extern u16 D_8006A91C[];
extern u16 D_8006A924[];
extern u16 D_8006A92C[];
extern u32 D_8006A8FC[];
extern s16 D_8006A914[];

/* Initializes an actor-linked display node, clears its image region, and sets callbacks and rendering data. */
void func_80035E58(s32 node_addr, void *display, u8 *image, s32 *state_ref,
                   s32 option, u8 *owner) {
    S_func_80035E58_0 *node;
    S_func_80035E58_1 *node_data;
    S_func_80035E58_2 *render_data;
    S_func_80035E58_3 *actor;

    node = func_8003FF2C(0x11, node_addr, 0x49, D_80082BC0);
    node->unk_10 = func_8003605C;
    func_8004491C(node, func_80033D54);

    node_data = (S_func_80035E58_1 *)((u8 *)node + 0x20);
    render_data = (S_func_80035E58_2 *)node->unk_0C;
    node_data->unk_44 = state_ref;
    node_data->unk_48 = 1;
    node_data->unk_4A = (s16)option;
    ClearImage(image + 4, 0, 0, 0);

    func_80033C1C(display, *state_ref);
    node->unk_20 = display;
    node_data->unk_04 = image;
    node_data->unk_08 = func_80037714;
    func_800375C0(node_data, D_8006AA3C);
    func_800350B0(owner, node_data);

    node_data->unk_68 = func_80036110;
    actor = (S_func_80035E58_3 *)(owner + 0x8C);
    render_data->unk_0C = 0x808080;
    render_data->unk_08.unk_08_ptr = D_80073AAC;
    render_data->unk_00 = 0;
    render_data->unk_04 = 0;
    render_data->unk_05 = 0;
    node_data->unk_74 = actor;

    node_data->unk_12 = D_8006A91C[((S_func_80035E58_4 *)actor->unk_80)->unk_02];
    node_data->unk_2E = D_8006A924[((S_func_80035E58_4 *)actor->unk_80)->unk_02];
    node_data->unk_36 = D_8006A92C[((S_func_80035E58_4 *)actor->unk_80)->unk_02];
    func_80036988((u8 *)node + 0x2C, node_data->unk_74);
    render_data->unk_08.unk_08_u32 = D_8006A8FC[((S_func_80035E58_4 *)actor->unk_80)->unk_02];
    ((S_func_80035E58_5 *)node->unk_20)->unk_34 =
        D_8006A914[((S_func_80035E58_4 *)actor->unk_80)->unk_02];
}
