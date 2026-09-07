#include "common.h"

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

extern s32 func_8008D344();
extern s32 func_8008D368();
extern s32 func_80098864(u8 *, s32);
extern s32 func_80098B38();
extern s32 func_800990FC();
extern s32 func_80099194();
extern s32 func_80099290();
extern s32 func_80099368();
extern s32 func_8009955C();
extern s32 func_800997FC();
extern s32 func_800998C0();
extern s32 func_80099978();
extern s32 func_800A5720();
extern s32 func_800A5F38();
extern s32 func_800A6480();
extern s32 func_800AD6FC();
extern s32 func_800BF004();
extern s32 func_800BF034();
extern s32 func_800BF050();
extern s32 func_800BF050_alias(void) __asm__("func_800BF050");

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u8 D_8008936C[];
extern u8 D_80089370[];
extern u8 D_800DD158[];
extern u16 D_800DDE84[];
extern u8 D_800E118C[];
extern u8 D_800E11AB[];
extern u8 D_800E11D7[];
extern u8 *D_800E3D7C[];

s32 func_800BEDEC(u32 arg0, u8 *arg1, s16 arg2, s32 arg3) {
    register u8 *base ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    register u32 object ASM_REG("$16") = arg0;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 chain ASM_REG("$17");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *other;
    register s32 temp ASM_REG("$19");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u8 *item ASM_REG("$20") = arg1;   /* MATCH pin: retail callee-saved set / frame layout depends on it */

    ASM_KEEP_NV(object);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP_NV(item);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    if (arg2 == 0xD) {
        func_80098864(item, arg3);
        return func_800BF050();
    }

    base = D_800E3D7C[0];
    if ((u8 *)object == base) {
        u8 flags;
        s32 result;

        ASM_KEEP(base);   /* MATCH pin: retail register colouring depends on it */
        *(u8 **)(base + 0x110) = item;
        func_8008D344(base, D_80083780, D_80082E80, base);
        flags = item[3];
        ASM_KEEP(flags);   /* MATCH pin: retail delay-slot fill depends on it */
        result = 0;
        ASM_KEEP(result);   /* MATCH pin: load-bearing for the whole function shape */
        item[3] = flags & 0xDF;
        return func_800BF050_alias();
    }

    if (object <= 0x9FFFFFFF) {
        func_800A6480(object, item, arg2);
        if (func_800AD6FC(object, D_800DDE84[*(u8 *)(object + 0x13)] & 3, 0) == 0) {
            func_800A5F38(object, item);
            func_800BF050();
            return 1;
        }
        D_80083460.fieldA--;
        func_80098B38(item);
        return 1;
    }

    other = *(u8 **)(base + 0x50);
    if (other != 0) {
        if (!(item[3] & 0x20)) {
            u8 flags;
            register s32 result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

            *(s32 *)(base + 0x114) = 0x802020;
            func_8008D368(base, D_80083780, D_80082E80, D_800DD158, 0);
            flags = item[3];
            ASM_KEEP(flags);   /* MATCH pin: retail delay-slot fill depends on it */
            result = 0;
            ASM_KEEP(result);   /* MATCH pin: load-bearing for the whole function shape */
            item[3] = flags | 0x20;
            return func_800BF050();
        }

        if (!(other[3] & 0x40)) {
            s32 next;
            s32 old_arg;

            temp = func_800990FC();
            ASM_KEEP(temp);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            chain = func_8009955C(other, temp);
            if (*(s8 *)(other + 2) < 0x63) {
                other[2] = other[2] + 1;
            }
            chain = func_80099978(func_80099194(D_800E118C, chain));
            next = func_80099194(D_8008936C, chain);
            object = chain - 2;
            chain = next;
            next = func_80099368(other, chain);
            old_arg = chain;
            chain = next;
            func_800998C0(object, old_arg);
            return func_800BF004(D_80089370, chain);
        }

        temp = func_800990FC();
        {
            s32 message_value;
            u8 *message_base;
            register s32 message_arg ASM_REG("$5");   /* MATCH pin: retail delay-slot fill depends on it */

            message_value = func_80099368(other, temp);
            message_base = D_800E11AB;
            ASM_KEEP(message_base);   /* MATCH pin: retail schedule: same instructions, different order without it */
            message_arg = message_value;
            ASM_KEEP(message_arg);   /* MATCH pin: retail delay-slot fill depends on it */
            func_80099290(func_80099194(message_base, message_arg));
        }
        func_800A5720(temp);
        {
            u32 page = 0x80080000;

            ASM_PAGEBASE_PIN(page);   /* MATCH pin: retail delay-slot contents depend on it */
            return func_800BF034();
        }
    }

    func_800997FC(D_800E11D7, arg3, arg2);
    D_80083460.fieldA--;
    func_80098B38(item);
    return 1;
}
