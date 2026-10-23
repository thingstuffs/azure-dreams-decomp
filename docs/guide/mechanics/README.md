# Game mechanics from the code

[Source guide](../README.md) · [Dungeon folders](../dungeon.md) · [Town folders](../town.md)

These pages explain the C at source baseline `f4f4ed991`. They describe the
implemented rules, including original bugs. Verification means static reading
of the linked functions; it does not mean emulator testing or recovered design
intent. Short names follow the shared headers. Unknown fields keep their code
offsets, and deductions beyond a branch or formula are labeled **inferred**.

| Mechanic | What is covered |
| --- | --- |
| [Combat and status](combat.md) | Hit checks, damage, elements, critical rolls, four status slots |
| [Levels, EXP and MP](leveling.md) | Generated EXP curve, rewards, stat growth, spell levels, MP accounting |
| [Familiars](familiars.md) | Eggs, heating, fusion selection, spells, talents, evolution |
| [Items](items.md) | Kinds, effect handlers, identification, curses and floor rarity |
| [Dungeon generation](dungeon-generation.md) | Rooms, corridors, floor resources, spawning and traps |
| [Monster decisions](monsters.md) | Shared action selection and species-specific branches |
| [Town mechanics](town.md) | Prices, building eligibility and event selection |

The record distinction matters throughout: an
[`ActorRecord`](../../../include/shared/entity.h) contains stats and action
state; an `ObjectPosition` contains world coordinates. Actor +0x24/+0x25 is
8.8 **MP**, with maximum MP at +0x66. The player's `PlayerRecord` extends the
actor prefix and has no familiar MP resource. Sprite tile coordinates occupy
different records even when their offsets happen to be the same.

Integer formulas preserve C rounding: `trunc(a/b)` rounds toward zero;
`a >> k` is the signed right shift used by the target code. Formulas stated
for ordinary positive stats do not imply that overflowing byte/halfword
intermediates saturate. The linked [bug catalog](../../BUGS.md) records those
exceptions. Table-selection code establishes how external resource data is
used; it does not by itself establish a complete floor-by-floor bestiary,
item catalog, price list or event walkthrough.
