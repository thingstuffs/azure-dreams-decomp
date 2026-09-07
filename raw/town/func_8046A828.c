#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
typedef s32 Callback(s32);

extern void func_80019730(void);
extern s8 func_8001A4F0(void);
extern s32 func_8001A58C(s32);
extern void *func_8001B6E4(s32);
extern void *func_8001B6F8();
extern void func_8001E5F0(s32);

extern void *D_80016000;
extern s32 D_8001601C;
extern u8 D_80017774[];
extern u8 D_8001914C[];
extern u8 *D_8001E950;

void *func_8001B828(s32 arg0, void *arg1, s32 arg2) {
    register s32 value ASM_REG("$2");
    u8 stored_value;
    s32 result;
    void *obj;
    void *final_obj;
    void *ret;

    if (arg2 == 0) {
        func_8001E5F0(0x402);
        obj = D_8001E950;
        result = func_8001A58C(FIELD(obj, u8, 4));
        if (result == 0) {
            obj = D_80016000;
            obj = FIELD(obj, void *, 0x20);
            result = (*(Callback **)((u8 *)obj + 0x2D4))(0);
            if (result != 2) {
                return D_8001914C;
            }
            stored_value = func_8001A4F0();
            D_8001E950[4] = stored_value;
        }
        final_obj = D_8001E950;
        value = FIELD(final_obj, u8, 4);
        ASM_KEEP(final_obj);
        ASM_KEEP(value);
        if (value != 0) {
            return func_8001B6E4(value);
        }
        return D_8001914C;
    }
    if (arg2 == 1) {
        func_80019730();
        return func_8001B6F8(arg0, arg1, 1);
    }
    if (arg2 == 5) {
        return D_80017774;
    }
    if (arg2 == 4) {
        goto mode_4;
    }
    ret = func_8001B6F8(arg0, arg1);
    goto done;
mode_4:
    ret = &D_8001601C;
done:
    return ret;
}

/* MECHANISM: The ordered if-chain and explicit result merge reproduce the 0x20 s0/s1/ra frame
   and recover every apparent 0x8001B948 call as a local epilogue edge.  A guarded v0 byte
   live range restores the missing call-slot move; scope-splitting its v1 pointer closes coloring. */
