#ifndef SHARED_DUNGEON_ACTOR_CALLBACKS_H
#define SHARED_DUNGEON_ACTOR_CALLBACKS_H
/* Code address formerly misdeclared as D_8008ACDC. The defining dungeon
 * function has four pointer parameters and returns void. Callers assign its
 * address to the actor callback word at +0x8C. Pointee types remain unknown. */
void func_8008ACDC(void *, void *, void *, void *);
#endif
