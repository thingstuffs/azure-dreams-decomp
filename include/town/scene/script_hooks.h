#ifndef INCLUDE_TOWN_SCENE_SCRIPT_HOOKS_H
#define INCLUDE_TOWN_SCENE_SCRIPT_HOOKS_H

#include "common.h"

void noop_scene_script_call(void);

/* Return words consumed by script variable v15. */
s32 apply_stored_value_1792_c(void);
s32 invoke_status_handler_with_code_780(void);
s32 invoke_status_handler_with_code_1470(void);
s32 store_result_calling(void);
s32 update_result_1(void);
s32 register_command_records(void);
s32 prepare_and_register_entry_buffer(void);
void *bind_scene_pointer(void);
void *mcard_func_set(void);
s32 scr_func_koya_tamago_pal_ld(void);

#endif
