# Reading the source

Choose a game feature, follow its callbacks, and resolve a row ID whenever an
old address name leads to a missing file. These guides describe the source at
snapshot `f4f4ed991`; each feature example links to its implementation.

| Guide | Start here for |
| --- | --- |
| [SLUS](slus.md) | Resident executable, initialization, CD commands and sound |
| [Engine](engine.md) | Object lists, scripts, graphics, resources and frame updates |
| [MAIN](main.md) | The MAIN container and remaining card-server source |
| [Frontend](frontend.md) | Card screens and settings |
| [Town](town.md) | Buildings, dialogue, people, shops and minigames |
| [Dungeon](dungeon.md) | Floor generation, actor turns, player actions and monster callbacks |
| [Movie / OVMOVIE](movie.md) | Scene movie requests, display lifecycle and MDEC services |
| [Event scripts](script.md) | Dialogue, choices, flags and story logic: the script byte format, every opcode and the numbered calls into game code |

## Game mechanics

The [mechanics guide](mechanics/README.md) explains combat, levels and MP,
familiars, items, floor generation, monster decisions and town systems from
the C, with formulas, verification notes and links to original bugs. It
distinguishes checked behavior from inference and incomplete data catalogs.

## Find a function

From the repository root, without a disc:

```sh
python3 tools/source_layout.py path town/func_8008D54C
python3 tools/source_layout.py ids src/town/scene/copy_words_backward_from_offset.c
python3 tools/source_layout.py --root . check
```

The first command resolves a stable row ID to its current editable file; the
second finds rows associated with that file. The implementation is
[`row_relative` / `row_ids_for_paths`](../../tools/gate/source_layout.py).
Use the [source-layout reference](../SOURCE_LAYOUT.md) for merged TUs and
inlined member extents. The generated container indexes
([SLUS](../../src/slus/INDEX.md), [MAIN](../../src/main/INDEX.md),
[town](../../src/town/INDEX.md), [dungeon](../../src/dungeon/INDEX.md),
[OVMOVIE](../../src/ovmovie/INDEX.md)) list row recipes and locations.

For a known symbol, search its feature folder and owning headers, for example:

```sh
rg --max-filesize 4M -n 'allocate_list_node' src/engine/node include/engine/node.h
```

Start reading at
[`allocate_list_node`](../../src/engine/node/allocate_list_node.c), then
[`run_active_node_callbacks`](../../src/engine/node/run_active_node_callbacks.c):
allocation explains the node/payload layout, and callback execution shows why
one object update receives body, position and sprite arguments. For scene
changes, start at
[`load_scene_resource_group`](../../src/engine/scene/load_scene_resource_group.c)
and follow `Control_CD` and the resource descriptors before interpreting an
address as a particular overlay.

## Counts and identities

A **row** is a registered function or data extent; a **TU** is a compiler input;
a **placement** links a home's source into another image. These relationships
are represented by [row records](../../ledger/rows.jsonl),
[source layout](../../ledger/layout.jsonl),
[inline extents](../../ledger/layout_inline.jsonl), and
[link lists](../LINK_LISTS.md). A source folder is not a disc container.

The README's source census uses
[`tools/readability/score.py`](../../tools/readability/score.py), schema
`readability-v1`. It reads every physical `.c`/`.h` file under `src/` once,
including local headers, static helpers, K&R definitions and both sides of
conditional compilation, without expanding includes or multiplying placements.
At snapshot `f4f4ed991` it finds 6,257 files (6,255 C files and 2 headers) and
8,252 function definitions. Of those, 8,117 (98.4%) have names other than
address placeholders: identifiers matching
`(?:func_|w_|sub_)[0-9A-Fa-f]{8}(?:_.*)?` in full are excluded. This measures
spelling, not recovered original names or reviewed gameplay meanings.

[Readability methodology](../READABILITY.md) describes the scanner and weighted
source-debt metrics; its generated tables carry their own baseline label.
[STATUS.md](../../STATUS.md) instead counts registered rows and image bytes.
Neither a source definition nor a readability score is a byte-proof receipt.

## Naming and ownership

The following summarizes [decisions 61, 73, 74 and 75](../evidence/r97_decisions.md);
the decision record is authoritative, and held source may still use older forms.

- **61 — names and folders:** use short English `snake_case` function names,
  without a binary prefix; keep proven original developer spellings. Names
  must be unique within a link. Shared types belong under `include/`, grouped
  by concept; evidence determines placement. A readable name describes what
  the code proves, rather than asserting an uncertain game role.
- **73 — object records:** use `ObjectPosition`, `ActorRecord` and
  `PlayerRecord` from [shared/entity.h](../../include/shared/entity.h).
  `ActorRecord` is the 0xBC-byte actor body; `PlayerRecord` has that prefix
  plus a player tail, 0x12C bytes in total. Actor +0x24/+0x25 is fractional
  and integer **MP**, with `max_mp` at +0x66, used by familiars/monsters;
  the player has none. `EntityRec` is a legacy view for held users, not the
  type to add to new code. Retyping must follow the entire proven type flow.
- **74 — declarations:** prototypes belong in the owning folder header,
  `include/<subsystem>/<feature>.h`, and change with their definitions.
  Include the caller's and callee's owning headers. Shared record headers
  carry types; `include/sdk/` contains project stand-ins for SDK declarations.
  Data declarations belong with their owning folder, or in per-image data
  headers for imports. Byte-sensitive exceptions remain recorded holds.
- **75 — shared code:** matching relinked copies become link-list placements
  of one home file, including across containers. Read the home implementation
  for behavior and the placement records for each image's addresses and proof.
  A folder or a repeated address alone does not establish shared ownership.

## Loading and proof

The code-side route is dispatch entry → resource-group read or movie setup →
file commands → callbacks. See
[`load_scene_resource_group`](../../src/engine/scene/load_scene_resource_group.c),
[`load_dispatch_entry_files`](../../src/engine/resource/load_dispatch_entry_files.c)
and [`run_dispatch_entry_callbacks`](../../src/engine/resource/run_dispatch_entry_callbacks.c).
The guides describe individual branches of this route; they do not infer
runtime exclusivity from build layouts. [BUILD.md](../BUILD.md) explains actual
load/file images versus diagnostic recipe and placement images, imported gaps,
and the current `make` / `make check` proof. Certificates are retired from the
landing requirement (decision 71).

Check every local link in the public entry pages and these guides with:

```sh
python3 tools/docs/check_links.py
python3 -m unittest discover -s tools/docs -p 'test_*.py'
```

The checker resolves paths, Markdown anchors and source-line fragments without
the network or disc. Pass explicit Markdown files/directories to widen its
scope; historical evidence is not scanned by default.
