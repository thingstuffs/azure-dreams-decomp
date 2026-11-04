# L4 fan-out measurement

`fanout.tsv` joins the live object recipes to the schema-2 cache manifests and
compares each object's prior and landing input hashes in the last three landing
event ranges. The shared cache was read only. `dependent_objects` counts live
recipes whose make prerequisites or cached compiler include walk names the
path. 1,598 live recipes have no retained manifest, so their make prerequisites
provide the count; compiler-only includes for those recipes are unknown.

The 9,506 ACCURACY 108 events are the schema-2 migration. For 9,256, the old
schema's manifest is unavailable in `v2`, so its per-file cause is `NA`. The
ACCURACY 109 and 110 columns compare retained schema-2 manifests and are
complete for their 5,861 and 4,220 misses. Causes overlap: a row can be counted
under more than one changed input.

| Input | Live dependents | Recompiled in 109 | Recompiled in 110 |
| --- | ---: | ---: | ---: |
| `include/shared/town_object.h` | 5,551 | 5,453 | 3 |
| `include/dungeon/effect/screen.h` | 2,941 | 2,797 | 14 |
| `include/dungeon/effect.h` | 2,951 | 2,796 | 9 |
| `include/dungeon/item.h` | 2,368 | 2,244 | 12 |
| `include/dungeon/monster/dragon.h` | 836 | 0 | 836 |
| `src/dungeon/monster/dragon/spawn_mode_dependent_object.c` | 835 | 0 | 835 |
| `include/dungeon/effect/motion.h` | 763 | 758 | 0 |
| `include/dungeon/monster/zu.h` | 742 | 0 | 732 |
| `include/slus.h` | 574 | 0 | 504 |

The dragon source is the owner translation unit for 835 projected `.member`
recipes. For example, `build/obj/8c68acbfd3d1d32905c3022e.o` is compiled
from `build/.state/enumerate/func_8016AA7C.member/func_809C9228.c`, but its
recipe records `src/dungeon/monster/dragon/spawn_mode_dependent_object.c` as
the projection owner and make prerequisite. `project_compile_source()`
re-derives the member from that owner immediately before compiling. Removing
the owner prerequisite alone would permit a stale object when a member body
changes. A safe narrowing would give each member a content-stable generated
source target, regenerate it from the owner before make evaluates objects, and
make the object depend on that target. That graph change needs the cold,
edited-owner, restored and byte-verification proof requested for L1; it was
not made here.

Plan for the ten largest header hubs by observed 109–110 recompiles:

1. `shared/town_object.h`: isolate the `TownObjectRecord` layout and the smaller `PersonDescriptor` type; use forward declarations in consumers that only carry pointers.
2. `dungeon/effect/screen.h`: separate screen effect body layouts, GPU packet dependencies and callback declarations.
3. `dungeon/effect.h`: move source-linked fade types and motion effect imports into narrower consumer headers.
4. `dungeon/item.h`: separate item body layouts, sprite state dependencies and item declarations.
5. `dungeon/monster/dragon.h`: separate the dragon-specific layouts, global frame data and common actor imports.
6. `dungeon/effect/motion.h`: split motion body layouts from the `particle_effect_active` extern and callback declarations.
7. `dungeon/monster/zu.h`: keep zu-specific frame externs and body layout apart from general dungeon actor imports.
8. `slus.h`: separate broad runtime externs and subsystem prototypes into the existing subsystem headers where consumers can include only the needed declarations.
9. `town/person.h`: isolate the large frame-data extern group and person setup types.
10. `town/scene/flags.h`: split flag definitions from record imports used by only a subset of consumers.

These are migration candidates, not validated source changes. For each split,
measure identifier use before editing, migrate consumers, then compare make
dependency lists, generated recipes, objects and images. A declaration-use
projection can reduce unnecessary recompiles without changing source layout,
but must first pass L1's cache verification proof.
