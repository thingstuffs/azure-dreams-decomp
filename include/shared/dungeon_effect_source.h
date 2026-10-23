#ifndef SHARED_DUNGEON_EFFECT_SOURCE_H
#define SHARED_DUNGEON_EFFECT_SOURCE_H

/* Callers pass this byte address to func_8003A7C4 (or its banked alias)
 * at index zero. They do not establish the data layout or allocation extent. */
extern unsigned char positioned_effect_source[];

#endif
