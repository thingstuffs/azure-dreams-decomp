#include "common.h"

extern void card_boot_build_save_description(void *, s32);
extern void initialize_text_editor_context(void *, s32);
void initialize_save_description(void *owner, s32 value) { card_boot_build_save_description(owner, value); initialize_text_editor_context(owner, value); }
