# Grineut factory code-only placements

The three live entries at dungeon offsets A9D054, AA3054 and AA9054 have complete 468-byte factory bodies. The new typed home at A9D054 uses ObjectNodeHeader, ObjectPosition, SpriteFrameState and an ActorRecord union view for opaque callback fields. The other two entries reuse that home through address relocations. Every complete section matches the retail interval, including the final return delay slot; no instruction bits are masked or replaced.

The existing Grineut factory remains in its prefix/table-owning translation unit. That larger owner cannot serve as a 468-byte placement under the size-equality rule. Its source, tables and allocation are retained. These observed slots receive one independent code-only home and two shared placements, adding 1,404 bytes of C ownership. Their owning folder header declares spawn_grineut.

The delivered continuation map records source and complete-section hashes, exact bounds and address bindings. Runtime entry alone does not identify a placement. Full image proof must confirm that the new code contributes to each registered bank; imported gaps are never credited as C.
