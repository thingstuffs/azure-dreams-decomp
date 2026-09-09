#include "common.h"

extern s32 func_8001628C();
extern s32 func_80017E98(s32, s32);
extern s32 func_80019880();
extern s32 func_80019A04();
extern s32 func_80019ABC();
extern s32 func_8001A7F8();
extern s32 D_8001A954;
extern s32 D_8001B1F8;
extern s32 D_8001B63C;
extern s32 D_800211DC;

/* Selects a response from the table, applying the threshold override and fallback. */
s32 func_80016730(s32 object, s32 check_value, s32 selection) {
    register void *response_table ASM_REG("$19");
    s32 response;

    if (func_80017E98(object, check_value) != 0) {
        s32 address_page;

        address_page = (s32)0x80020000;
        ASM_KEEP(address_page);
        return address_page - 0x49C4;
    }
    {
        register s32 address_page ASM_REG("$2");

        ASM_CLOBBER("$2");
        address_page = (s32)0x80020000;
        ASM_KEEP(address_page);
        response_table = (void *)(address_page - 0x56AC);
    }
    response = func_80019ABC(response_table, &D_8001B1F8, object, selection);
    if (func_8001A7F8() >= 10) {
        register void *call_table ASM_REG("$4");
        s32 address_page;

        call_table = response_table;
        ASM_KEEP(call_table);
        func_80019880(call_table);
        address_page = (s32)0x80020000;
        ASM_KEEP(address_page);
        response = address_page + 0x11DC;
    }
    if (func_80019A04(response_table, object, selection) != 0) {
        response = func_8001628C(object, check_value, selection);
    }
    return response;
}
