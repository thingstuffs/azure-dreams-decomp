#include "common.h"

typedef struct DungeonState818D4800 {
    u8 pad0[0x8D0];
    u8 *next;
} DungeonState818D4800;

typedef struct Scratch818D4800 {
    u16 x;
    u16 y;
    u16 z;
    u8 pad06[0x12];
    u8 *volatile next;
    u8 pad1C[4];
    u32 *ot;
    u8 pad24[0x6C];
    u32 unk90;
    u32 unk94;
    u8 pad98[0x28];
    u32 index;
} Scratch818D4800;

extern u8 D_80083160[];
#ifdef __mips__
extern void func_8002409C(void) __attribute__((noreturn));
extern void func_8002409C_args(void *arg0, void *arg1)
    __asm__("func_8002409C") __attribute__((noreturn));
#else
extern void func_8002409C(void *arg0, void *arg1) __attribute__((noreturn));
#define func_8002409C_args func_8002409C
#endif
extern u32 func_80065420(void *arg0, void *arg1, void *arg2, void *arg3);
extern s32 func_80066460(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80067F20(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

#ifdef __mips__
static const u32 split_prefix[] __asm__("func_818D4800")
    __attribute__((section(".text.func_818D4800"), aligned(4))) = {
    0x80024668, 0x00000010, 0x00100010, 0x00100000,
    0x0010FFF0, 0x0000FFF0, 0xFFF0FFF0, 0xFFF00000,
    0xFFF00010, 0x00000000, 0x80024764, 0x800247E4,
    0x80024A48, 0x80024C8C, 0x80024E9C, 0x80024FC4,
    0x80025070,
};
__asm__(".globl func_818D4800\n"
        ".size func_818D4800, 660");
#define BODY_NAME func_818D4844
#else
#define BODY_NAME func_818D4800
#endif

s32 BODY_NAME(void *arg0, void *arg1)
{
    u8 *obj = arg0;
    u8 *input = arg1;
    u8 *global_addr = D_80083160;
    register u32 low_mask ASM_REG("$18") = 0x00FFFFFF;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    DungeonState818D4800 *state =
        *(DungeonState818D4800 **)D_80083160;
    u32 high_mask = 0xFF000000;
    Scratch818D4800 *scratch = (Scratch818D4800 *)0x1F800000;
    register u8 *prim;
    u32 value;
    void *next_obj;
    u8 *initial_next;
    u8 *next_prim;

    ASM_KEEP(high_mask);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP(global_addr);   /* MATCH pin: retail schedule: same instructions, different order without it */

    initial_next = state->next;
    scratch->ot = (u32 *)((u8 *)state + 0xB0);
    scratch->next = initial_next;
    ASM_KEEP(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */

    scratch->x = *(volatile u16 *)(input + 2);
    prim = scratch->next;
    scratch->y = *(u16 *)(input + 6);
    scratch->z = *(u16 *)(input + 0xA);
    scratch->next = prim + 0xC;

    scratch->index = func_80065420(scratch, prim + 8,
        (u8 *)scratch + 0x90, (u8 *)scratch + 0x94);

    if (scratch->index < 0x1E0U) {
        *(u32 *)(prim + 4) = *(u32 *)(obj + 8);

        prim[4] = (prim[4] * *(s16 *)(obj + 0x32)) / 0x100;
        prim[5] = (prim[5] * *(s16 *)(obj + 0x32)) / 0x100;
        prim[6] = (prim[6] * *(s16 *)(obj + 0x32)) / 0x100;

        prim[3] = 2;
        prim[7] = 0x6A;

        *(u32 *)prim = (*(u32 *)prim & high_mask) |
            (scratch->ot[scratch->index] & low_mask);
        {
            register u32 ot_word ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

            ot_word = scratch->ot[scratch->index];
            scratch->ot[scratch->index] = (ot_word & high_mask) |
                ((s32)prim & low_mask);
        }

        prim = scratch->next;
        next_prim = prim + 0xC;
        *(u8 **)((u8 *)scratch + 0x18) = next_prim;
        value = func_80066460(0, 1, 0, 0);
        func_80067F20(prim, 0, 0, value & 0xFFFF, 0);

        *(u32 *)prim = (*(u32 *)prim & high_mask) |
            (scratch->ot[scratch->index] & low_mask);
        prim = (u8 *)((u32)prim & low_mask);
        scratch->ot[scratch->index] =
            (scratch->ot[scratch->index] & high_mask) | (u32)prim;
    }

    next_obj = *(void **)(obj - 8);
    if (next_obj == 0) {
        goto finish;
    }

    obj = (u8 *)next_obj + 0x20;
    input = *(u8 **)((u8 *)next_obj + 8);
    ASM_KEEP(obj);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP(input);   /* MATCH pin: keeps a statement from moving across a call/branch */
#ifdef __mips__
    {
        register void *tail_a0 ASM_REG("$4") = scratch;   /* MATCH pin: retail delay-slot contents depend on it */
        void *tail_a1 = next_obj;

        ASM_TAILSLOT_PIN(tail_a0);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8002409C();
    }
#else
    func_8002409C_args(scratch, next_obj);
#endif

finish:
    (*(DungeonState818D4800 **)global_addr)->next = scratch->next;
    return 0;
}
