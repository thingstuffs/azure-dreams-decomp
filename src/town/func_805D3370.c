#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

extern void func_8001749C(void) __attribute__((noreturn));
extern s32 func_800191E8();
extern M2C_UNK D_8001A20C;
extern M2C_UNK D_8001A2E7;
extern M2C_UNK D_8001A348;
extern M2C_UNK D_8001A526;
extern M2C_UNK D_8001A5E8;
extern M2C_UNK D_8001A685;
extern M2C_UNK D_8001A8BC;
extern M2C_UNK D_8001A91D;




M2C_UNK *func_805D3370(s32 arg0, s32 arg1, s32 arg2) {
    M2C_UNK *var_v1;
    s32 status;

    var_v1 = NULL;
    if (arg2 != 0x1B) {
        goto case_2c;
    }
    do {  register u32 page ASM_REG("$2");  register M2C_UNK *tail_result ASM_REG("$3");  status = func_800191E8(arg0);  if (status == -0x30) {  page = 0x80020000;   goto case_1_success;  }  status = func_800191E8();   if (status != -0x38) {  goto case_1_other;  }  ASM_SCHED_BARRIER();  page = 0x80020000;   case_1_success:  tail_result = (M2C_UNK *)(page - (0x56E3));  ASM_TAILSLOT_PIN(tail_result);  func_8001749C();  } while (0);
case_1_other:
    do {  register u32 page ASM_REG("$2");  register M2C_UNK *tail_result ASM_REG("$3");  ASM_SCHED_BARRIER();  page = 0x80020000;  ASM_KEEP(page);  tail_result = (M2C_UNK *)(page - (0x5744));  ASM_TAILSLOT_PIN(tail_result);  func_8001749C();  } while (0);

case_2c:
    if (arg2 != 0x2C) {
        goto case_31;
    }
    do {  register u32 page ASM_REG("$2");  register M2C_UNK *tail_result ASM_REG("$3");  status = func_800191E8(arg0);  if (status == -0x30) {  page = 0x80020000;   goto case_2_success;  }  status = func_800191E8();   if (status != -0x38) {  goto case_2_other;  }  ASM_SCHED_BARRIER();  page = 0x80020000;   case_2_success:  tail_result = (M2C_UNK *)(page - (0x5D19));  ASM_TAILSLOT_PIN(tail_result);  func_8001749C();  } while (0);
case_2_other:
    do {  register u32 page ASM_REG("$2");  register M2C_UNK *tail_result ASM_REG("$3");  ASM_SCHED_BARRIER();  page = 0x80020000;  ASM_KEEP(page);  tail_result = (M2C_UNK *)(page - (0x5DF4));  ASM_TAILSLOT_PIN(tail_result);  func_8001749C();  } while (0);

case_31:
    if (arg2 != 0x31) {
        goto case_34;
    }
    do {  register u32 page ASM_REG("$2");  register M2C_UNK *tail_result ASM_REG("$3");  status = func_800191E8(arg0);  if (status == -0x30) {  page = 0x80020000;   goto case_3_success;  }  status = func_800191E8();   if (status != -0x38) {  goto case_3_other;  }  ASM_SCHED_BARRIER();  page = 0x80020000;   case_3_success:  tail_result = (M2C_UNK *)(page - (0x5ADA));  ASM_TAILSLOT_PIN(tail_result);  func_8001749C();  } while (0);
case_3_other:
    do {  register u32 page ASM_REG("$2");  register M2C_UNK *tail_result ASM_REG("$3");  ASM_SCHED_BARRIER();  page = 0x80020000;  ASM_KEEP(page);  tail_result = (M2C_UNK *)(page - (0x5CB8));  ASM_TAILSLOT_PIN(tail_result);  func_8001749C();  } while (0);

case_34:
    if (arg2 != 0x34) {
        goto done;
    }
    status = func_800191E8(arg0);
    if (status != -0x30) {
        status = func_800191E8();
        if (status != -0x38) {
            goto case_4_other;
        }
    }
    do {  register u32 page ASM_REG("$2");  register M2C_UNK *tail_result ASM_REG("$3");  page = 0x80020000;  ASM_KEEP(page);  tail_result = (M2C_UNK *)(page - (0x597B));  ASM_TAILSLOT_PIN(tail_result);  func_8001749C();  } while (0);
case_4_other:
    var_v1 = &D_8001A5E8;

done:
    return var_v1;
}
