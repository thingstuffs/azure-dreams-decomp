#include "common.h"

typedef void (*Callback)(void);

extern u8 D_80083498[];

extern u8 *func_8003FD64(s32 kind, void *data);
extern void func_8004491C(void *object, Callback callback);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *object, s32 arg1, s32 arg2);
extern void func_800A9C18(void *object, void *arg1, void *arg2, s32 arg3);
extern void func_800AA36C(void *object, void *arg1, void *arg2, void *arg3);

extern void func_80045340(void);
extern void func_8014CE5C(void);
extern void func_80150510(void);
extern void func_80150538(void);
extern void func_8014CA58(void);

void *func_8014C854(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 v_s2 = arg0;
    u8 *v_s0 = 0;
    register s32 v_s5 ASM_REG("$21") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    long v_s1;
    long v_s4;
    u8 *v_s3;
    u8 *v_s6;
    register s32 v_s7 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 alloc_kind;
    register u8 *alloc_data ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u32 callback_page;
    u32 flags0;
    u32 flags1;
    u32 masked;
    s32 random;

    alloc_kind = 0x112;
    ASM_KEEP_NV(alloc_kind);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    alloc_data = D_80083498;
    v_s1 = arg3;
    v_s4 = arg2;
    ASM_KEEP_DEP_NV(v_s4, alloc_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    v_s3 = func_8003FD64(alloc_kind, alloc_data);
    v_s7 = v_s2;
    if (v_s3 != 0) {
        v_s0 = v_s3 + 0x20;
        ASM_KEEP_NV(v_s0);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        *(u8 *)(v_s0 + 0x13) = 0x1C;
        func_8004491C(v_s3, func_80045340);

        v_s6 = *(u8 **)(v_s3 + 8);
        *(s16 *)(v_s6 + 0xA) = v_s1;
        v_s1 = (long)*(u8 **)(v_s3 + 0xC);
        *(u8 *)((u8 *)v_s1 + 0x25) = v_s4;
        v_s4 = (long)v_s0;
        *(u8 *)((u8 *)v_s1 + 0x24) = v_s5;

    if ((v_s2 & 3) == 1) {
        *(Callback *)(v_s0 + 0x8C) = func_8014CE5C;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        flags0 = *(u32 *)(v_s0 + 0x14);
        flags1 = *(u32 *)(v_s0 + 0x1C);
        flags0 |= 0x6000;
        flags1 |= 0x6000;
        *(u32 *)(v_s0 + 0x14) = flags0;
        *(u32 *)(v_s0 + 0x1C) = flags1;
        *(Callback *)((u8 *)v_s1 + 0x2C) = func_80150510;
    } else if ((v_s2 & 3) >= 2) {
        *(Callback *)(v_s0 + 0x8C) = func_8014CE5C;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        flags0 = *(u32 *)(v_s0 + 0x14);
        flags1 = *(u32 *)(v_s0 + 0x1C);
        flags0 |= 0x2000;
        flags1 |= 0x2000;
        *(u32 *)(v_s0 + 0x14) = flags0;
        *(u32 *)(v_s0 + 0x1C) = flags1;
        *(Callback *)((u8 *)v_s1 + 0x2C) = func_80150510;
    } else {
        masked = v_s2 & -4;
        if ((s16)masked == 0) {
            if ((*(u32 *)(v_s0 + 0x14) & 0x200) == 0) {
                if ((func_800A6D30() & 1) != 0) {
                    random = func_800A6D30();
                    func_800A48F0(v_s0, 1, (random & 0x3F) | 0x20);
                    *(Callback *)((u8 *)v_s1 + 0x2C) = func_80150538;
                }
            }
#ifdef NON_MATCHING
            *(Callback *)((u8 *)v_s4 + 0x8C) = func_8014CE5C;
#else
            callback_page = 0x80150000;
            ASM_KEEP_NV(callback_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            callback_page -= 0x31A4;
            *(Callback *)((u8 *)v_s4 + 0x8C) = (Callback)callback_page;
#endif
        } else {
#ifdef NON_MATCHING
            *(Callback *)(v_s0 + 0x8C) = func_8014CE5C;
#else
            callback_page = 0x80150000;
            ASM_KEEP_NV(callback_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            callback_page -= 0x31A4;
            *(Callback *)(v_s0 + 0x8C) = (Callback)callback_page;
#endif
        }
        *(Callback *)((u8 *)v_s1 + 0x2C) = func_80150510;
    }

    *(Callback *)(v_s3 + 0x10) = func_8014CA58;
    func_800A9C18(v_s3, v_s6, (u8 *)v_s1, (s16)v_s7);

        *(u8 *)((u8 *)v_s4 + 0x9A) = 0xFF;
        *(s8 *)((u8 *)v_s4 + 0x9C) = -1;
        func_800AA36C((u8 *)v_s4, v_s6, (u8 *)v_s1, v_s0);
    }
    return v_s0;
}
