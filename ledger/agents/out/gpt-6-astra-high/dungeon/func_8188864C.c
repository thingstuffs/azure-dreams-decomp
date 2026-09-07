#include "common.h"

typedef struct S_80025E4C_0 {
    u8 pad_00[0x18];
    void * unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
    u8 pad_24[0x4C];
    void * unk_70;
    u16 unk_74;
    u8 pad_76[0x2];
    void * unk_78;
    u16 unk_7C;
    u8 pad_7E[0x2];
    void * unk_80;
    u16 unk_84;
    u8 pad_86[0x2];
    void * unk_88;
    u16 unk_8C;
    u8 pad_8E[0x32];
    u32 unk_C0;
} S_80025E4C_0;   /* scratch in func_80025E4C */

typedef struct S_80025E4C_1_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_80025E4C_1_pre;   /* the 0x8 bytes before arg0 in func_80025E4C, addressed as arg0[-1] */

typedef struct S_80025E4C_1 {
    u8 pad_00[0x30];
    void * unk_30;
    u16 unk_34;
    u8 pad_36[0x2];
    void * unk_38;
    u16 unk_3C;
    u8 pad_3E[0x2];
    void * unk_40;
    u16 unk_44;
    u8 pad_46[0x2];
    void * unk_48;
    u16 unk_4C;
    u8 pad_4E[0x2];
    s32 unk_50;
    s32 unk_54;
} S_80025E4C_1;   /* arg0 in func_80025E4C */

typedef struct S_80025E4C_2 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x4];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80025E4C_2;   /* obj in func_80025E4C */



extern s32 func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066708(void *);
extern void func_80067F20(void *, s32, s32, u16, s32);

typedef struct GlobalState {
    u8 pad[0x8D0];
    void *next;
} GlobalState;

extern GlobalState *D_80083160[];

/* Project linked quads and queue their shaded primitives and draw modes by depth. */
s32 func_80025E4C(void *quad) {
    GlobalState **render_states = D_80083160;
    u8 *scratch = (u8 *)0x1F800000;
    void *packet;
    u32 depth_bucket;
    s32 first_color;
    s32 second_color;
    s32 next_node;
    void *vertex3_xy;
    GlobalState *render_state;

    render_state = render_states[0];
    (*(void * *)((u8 *)scratch + 0x20)) = (u8 *)render_state + 0xB0;
    ((S_80025E4C_0 *)scratch)->unk_18 = render_state->next;
    do {
        packet = ((S_80025E4C_0 *)scratch)->unk_18;
        ((S_80025E4C_0 *)scratch)->unk_18 = (u8 *)packet + 0x24;
        ((S_80025E4C_0 *)scratch)->unk_70 = ((S_80025E4C_1 *)quad)->unk_30;
        ((S_80025E4C_0 *)scratch)->unk_78 = ((S_80025E4C_1 *)quad)->unk_38;
        ((S_80025E4C_0 *)scratch)->unk_80 = ((S_80025E4C_1 *)quad)->unk_40;
        vertex3_xy = ((S_80025E4C_1 *)quad)->unk_48;
        ((S_80025E4C_0 *)scratch)->unk_74 = ((S_80025E4C_1 *)quad)->unk_34;
        ((S_80025E4C_0 *)scratch)->unk_7C = ((S_80025E4C_1 *)quad)->unk_3C;
        ((S_80025E4C_0 *)scratch)->unk_84 = ((S_80025E4C_1 *)quad)->unk_44;
        ((S_80025E4C_0 *)scratch)->unk_88 = vertex3_xy;
        ((S_80025E4C_0 *)scratch)->unk_8C = ((S_80025E4C_1 *)quad)->unk_4C;
        depth_bucket = func_800654B0(scratch + 0x70, scratch + 0x78,
                              scratch + 0x80, scratch + 0x88,
                              (u8 *)packet + 8, (u8 *)packet + 0x10,
                              (u8 *)packet + 0x18, (u8 *)packet + 0x20,
                              scratch + 0x90, scratch + 0x94) - 8;
        ((S_80025E4C_0 *)scratch)->unk_C0 = depth_bucket;
        if (depth_bucket < 0x1E0U) {
            first_color = ((S_80025E4C_1 *)quad)->unk_50;
            ((S_80025E4C_2 *)packet)->unk_0C = first_color;
            ((S_80025E4C_2 *)packet)->unk_04.at00.v = first_color;
            second_color = ((S_80025E4C_1 *)quad)->unk_54;
            ((S_80025E4C_2 *)packet)->unk_1C = second_color;
            ((S_80025E4C_2 *)packet)->unk_14 = second_color;
            func_80066708(packet);
            ((S_80025E4C_2 *)packet)->unk_04.at03.v = (u8)(((S_80025E4C_2 *)packet)->unk_04.at03.v | 2);
            func_8006658C((u8 *)((S_80025E4C_0 *)scratch)->unk_20 +
                              (((S_80025E4C_0 *)scratch)->unk_C0 * 4), packet);
            packet = ((S_80025E4C_0 *)scratch)->unk_18;
            ((S_80025E4C_0 *)scratch)->unk_18 = (u8 *)packet + 0xC;
            func_80067F20(packet, 0, 0,
                          (u16)func_80066460(0, 1, 0, 0), 0);
            func_8006658C((u8 *)((S_80025E4C_0 *)scratch)->unk_20 +
                              (((S_80025E4C_0 *)scratch)->unk_C0 * 4), packet);
        }
        next_node = ((S_80025E4C_1_pre *)quad)[-1].unk_00;
        if (next_node == 0) {
            break;
        }
        quad = (void *)(next_node + 0x20);
    } while (1);
    render_states[0]->next =
        ((S_80025E4C_0 *)scratch)->unk_18;
    return 0;
}

