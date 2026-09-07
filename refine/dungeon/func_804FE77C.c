#include "common.h"

typedef struct S_804FE87C_0 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    s16 unk_42;
    s16 unk_44;
    s16 unk_46;
    s16 unk_48;
    u8 pad_4A[0xE];
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    s16 unk_62;
    s16 unk_64;
    s16 unk_66;
    s16 unk_68;
    u8 pad_6A[0xE];
    s32 unk_78;
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    s32 unk_88;
} S_804FE87C_0;   /* state in func_804FE87C */

typedef struct S_804FE87C_1 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_804FE87C_1;   /* base in func_804FE87C */


#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct DispatchInner {
    u8 pad_00[0x218];
    void (*callback)(void *);
} DispatchInner;

typedef struct DispatchOuter {
    u8 pad_00[0x20];
    DispatchInner *inner;
} DispatchOuter;

extern s32 func_80018964(s32);
extern void func_800188E4(s32);
extern void func_8001886C(s32);
extern void func_80064F20(s32);
extern void func_80064EE0(s32, s32, s32);
extern void func_80064D50(void *);
extern void func_80064D20(void *);
extern void func_80064624(s32, s32);
extern void func_80064EC0(s32, s32, s32);
extern void func_80064F00(s32, s32);

extern void func_8001D4FC(void);
extern void func_8001D508(void);
extern void func_8001D540(void);
extern void func_8001D5C0(void);
extern void func_8001D578(void);
extern void func_8001D5B0(void);
extern void func_8001E944(void);
extern void func_8001E87C(void);
extern void func_8001E8A4(void);
extern void func_8001E8E8(void);
extern void func_8001E8B8(void);
extern void func_8001E910(void);

extern DispatchOuter *D_80016000[];
extern u8 D_800190D4[];
extern u8 D_80083160[];
extern void *D_80083478;
extern u8 D_800DDC7C[];
extern u8 D_801C9E40[16];
extern u8 D_801DA714[16];

#ifdef __mips__
#define ROW_ATTR __attribute__((used, section(".text.func_8001677C")))
#else
#define ROW_ATTR
#endif

void func_8001677C(void) ROW_ATTR;
/* Updates two states and invokes the active object's callback. */
void func_8001677C(void)
{
#ifdef __mips__
    register u32 *stack ASM_REG("$29");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u32 return_address ASM_REG("$31");   /* MATCH pin: retail register colouring depends on it */
#endif

    if (func_80018964(0x601) != 0) {
        func_800188E4(0x601);
    } else {
        func_8001886C(0x601);
    }

    if (func_80018964(0x1202) != 0) {
        func_800188E4(0x1202);
    } else {
        func_8001886C(0x1202);
    }

    D_80016000[0]->inner->callback(D_800190D4);

#ifdef __mips__
    return_address = stack[4];
    stack = (u32 *)((u8 *)stack + 24);
    ASM_KEEP(return_address);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    __asm__(".end func_8001677C\n.if 0");
#endif
}

#ifdef __mips__
__asm__(".endif");
static void (*const dispatch_table[])(void)
    __attribute__((used, section(".text.func_8001677C"), aligned(4))) = {
        func_8001D4FC,
        func_8001D508,
        func_8001D540,
        func_8001D5C0,
        func_8001D578,
        func_8001D5B0,
        func_8001D5B0,
        func_8001D5B0,
        func_8001D5B0,
        func_8001D5B0,
        func_8001D5B0,
        func_8001D5B0,
        func_8001D5B0,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E87C,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E944,
        func_8001E8A4,
        func_8001E8E8,
        func_8001E8B8,
        func_8001E910,
    };
#endif

static void func_804FE87C(void) ROW_ATTR;
/* Initializes lighting, projection, and viewport state. */
static void func_804FE87C(void)
{
    u8 *render_data = D_80083160;
    u8 *render_state = render_data + 0x18;
    s32 light_xz;
    s32 light_y;
    void *light_matrix;

    ((S_804FE87C_0 *)render_state)->unk_88 = 0x200;
    func_80064F20(0x200);

    ((S_804FE87C_0 *)render_state)->unk_78 = 0;
    ((S_804FE87C_0 *)render_state)->unk_7C = 0;
    ((S_804FE87C_0 *)render_state)->unk_80 = 0;
    func_80064EE0(0, 0, 0);

    ((S_804FE87C_0 *)render_state)->unk_58 = 0x200;
    ((S_804FE87C_0 *)render_state)->unk_5E = 0x200;
    ((S_804FE87C_0 *)render_state)->unk_64 = 0x200;
    ((S_804FE87C_0 *)render_state)->unk_5A = -0x100;
    ((S_804FE87C_0 *)render_state)->unk_60 = -0x100;
    ((S_804FE87C_0 *)render_state)->unk_66 = -0x100;
    ((S_804FE87C_0 *)render_state)->unk_5C = 0;
    ((S_804FE87C_0 *)render_state)->unk_62 = 0;
    ((S_804FE87C_0 *)render_state)->unk_68 = 0;
    func_80064D50(render_data + 0x70);

    light_matrix = render_data + 0x50;
    ASM_KEEP(light_matrix);   /* MATCH pin: retail schedule: same instructions, different order without it */
    light_xz = -0x800;
    light_y = 0x800;
    ASM_KEEP(light_y);   /* MATCH pin: retail address form (%hi/%lo vs render_data+offset) depends on it */
    ((S_804FE87C_0 *)render_state)->unk_38 = light_xz;
    ((S_804FE87C_0 *)render_state)->unk_3C = light_xz;
    light_xz = 0x800;
    ((S_804FE87C_0 *)render_state)->unk_3A = light_y;
    light_y = -0x800;
    ((S_804FE87C_0 *)render_state)->unk_3E = light_xz;
    ((S_804FE87C_0 *)render_state)->unk_40 = light_y;
    ((S_804FE87C_0 *)render_state)->unk_42 = light_xz;
    ((S_804FE87C_0 *)render_state)->unk_44 = 0;
    ((S_804FE87C_0 *)render_state)->unk_46 = 0;
    ((S_804FE87C_0 *)render_state)->unk_48 = 0;
    func_80064D20(light_matrix);

    ((S_804FE87C_0 *)render_state)->unk_84 = 0x1000;
    func_80064624(0x1000, ((S_804FE87C_0 *)render_state)->unk_88);
    func_80064EC0(0xA0, 0xA0, 0xA0);

    D_801C9E40[0x19] = 0;
    D_801C9E40[0x1A] = 0;
    D_801C9E40[0x1B] = 0;
    D_801DA714[0x19] = 0;
    D_801DA714[0x1A] = 0;
    D_801DA714[0x1B] = 0;
    func_80064F00(0xA0, 0x78);

    ((S_804FE87C_1 *)render_data)->unk_18 = -0xBC;
    ((S_804FE87C_1 *)render_data)->unk_1A = -0x88;
    ((S_804FE87C_1 *)render_data)->unk_1C = 0x172;
    ((S_804FE87C_1 *)render_data)->unk_1E = 0x19A;
    D_80083478 = D_800DDC7C;
}

#ifdef __mips__
__asm__(".size func_8001677C, 604");
#endif
