#include "common.h"

#include "common.h"

typedef void (*Callback)(void *);

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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
    u8 *node;
    u8 *node_data;
    u8 *render_data;
    u8 *actor;

    node = func_8003FF2C(0x11, node_addr, 0x49, D_80082BC0);
    FIELD(node, Callback, 0x10) = func_8003605C;
    func_8004491C(node, func_80033D54);

    node_data = node + 0x20;
    render_data = FIELD(node, u8 *, 0xC);
    FIELD(node_data, s32 *, 0x44) = state_ref;
    FIELD(node_data, u8, 0x48) = 1;
    FIELD(node_data, s16, 0x4A) = (s16)option;
    ClearImage(image + 4, 0, 0, 0);

    func_80033C1C(display, *state_ref);
    FIELD(node, void *, 0x20) = display;
    FIELD(node_data, void *, 0x4) = image;
    FIELD(node_data, Callback, 0x8) = func_80037714;
    func_800375C0(node_data, D_8006AA3C);
    func_800350B0(owner, node_data);

    FIELD(node_data, Callback, 0x68) = func_80036110;
    actor = owner + 0x8C;
    FIELD(render_data, u32, 0xC) = 0x808080;
    FIELD(render_data, void *, 0x8) = D_80073AAC;
    FIELD(render_data, s32, 0x0) = 0;
    FIELD(render_data, u8, 0x4) = 0;
    FIELD(render_data, u8, 0x5) = 0;
    FIELD(node_data, void *, 0x74) = actor;

    FIELD(node_data, u16, 0x12) = D_8006A91C[FIELD(FIELD(actor, u8 *, 0x80), u8, 2)];
    FIELD(node_data, u16, 0x2E) = D_8006A924[FIELD(FIELD(actor, u8 *, 0x80), u8, 2)];
    FIELD(node_data, u16, 0x36) = D_8006A92C[FIELD(FIELD(actor, u8 *, 0x80), u8, 2)];
    func_80036988(node + 0x2C, FIELD(node_data, void *, 0x74));
    FIELD(render_data, u32, 0x8) = D_8006A8FC[FIELD(FIELD(actor, u8 *, 0x80), u8, 2)];
    FIELD(FIELD(node, u8 *, 0x20), s32, 0x34) =
        D_8006A914[FIELD(FIELD(actor, u8 *, 0x80), u8, 2)];
}
