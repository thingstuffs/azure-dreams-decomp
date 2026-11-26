"""Check scene, movie, sprite and sound reads against the disc tables."""

import os
import struct
from pathlib import Path

from tools.build.retail_spans import FILES
from tools.decoded.lz import decode
from tools.gate.disc_slice import Disc

SCENE = 'scene_resource_read'
MOVIE = 'movie_overlay_read'
INDEXED_SPRITES = 'indexed_sprite_bundle_read'
TOWN_TEXTURES = 'town_texture_read'
TOWN_CHARACTERS = 'town_character_resource_read'
TOWN_CHUNKS = 'town_map_chunk_read'
TOWN_SETUP = 'town_setup_resource_read'
TOWN_DEFAULT_SCENE = 'town_default_scene_read'
FLOOR_IMAGES = 'dungeon_floor_image_read'
FLOOR_LAYOUTS = 'dungeon_floor_layout_read'
FLOOR_CHUNKS = 'dungeon_floor_chunk_read'
FLOOR_SPAWNS = 'dungeon_floor_spawn_table_read'
FLOOR_MODULE_READ = 'dungeon_floor_module_read'
FLOOR_CATEGORIES = (FLOOR_IMAGES, FLOOR_LAYOUTS, FLOOR_CHUNKS)
EFFECT_BANK = 'sound_effect_bank_read'
SOUND_SET = 'sound_set_read'
SOUND_STREAM = 'sound_stream_read'
AUDIO_CATEGORIES = (EFFECT_BANK, SOUND_SET, SOUND_STREAM)
CATEGORIES = {SCENE, MOVIE, INDEXED_SPRITES, TOWN_TEXTURES, TOWN_CHARACTERS, TOWN_CHUNKS, TOWN_SETUP,
              TOWN_DEFAULT_SCENE, FLOOR_SPAWNS, FLOOR_MODULE_READ, *FLOOR_CATEGORIES, *AUDIO_CATEGORIES}
INDEXED_SPRITE_CONTAINERS = ('dungeon', 'town', 'town')
VOLUMES = {'main': 'MAIN/MAIN.BIN', 'town': 'TOWN/TOWN.BIN',
           'dungeon': 'DUNGEON/DUNGEON.BIN', 'ovmovie': 'OVMOVIE.BIN'}
SECTOR_BYTES = 2048
TOWN_ENGINE_DELTA = 0x8007D760
TOWN_RESOURCE_CATALOG = 0x800CF838
TOWN_MAP_VARIANTS = (0x800d2fb4, 67 * 32)
TOWN_CHUNK_TABLES = (0x800d1bfc, 0x800d20cc - 0x800d1bfc)
TOWN_SETUP_DESCRIPTORS = (
    # setup_town_scene reads two resident and two Town engine descriptors.
    ('slus', 0x80080ea0, 'town'),
    ('slus', 0x80080e28, 'main'),
    ('town', 0x800d1d54, 'town'),
    ('town', 0x800d1e7c, 'town'),
    # queue_town_movie_and_load_resources reads the two movie setup assets.
    ('slus', 0x80080ed0, 'town'),
    ('slus', 0x80080ed8, 'town'),
)
FLOOR_MODULE = (0x2a3000, 19 * SECTOR_BYTES)
FLOOR_MODULE_BASE = 0x80016000
FLOOR_MODULE_DESCRIPTOR = 0xf9c6c
FLOOR_TRACKS = 0x8001f62c - FLOOR_MODULE_BASE
CHUNK_BYTES = 16 * SECTOR_BYTES
CHUNK_OUTPUT_LIMITS = {FLOOR_CHUNKS: 0x80200000 - 0x800f0000,
                       TOWN_CHUNKS: 0x80200000 - 0x8012f004}


def scene_sector_count(initial_count, tail):
    """The scene loader reads pairs of bulk chunks, then the descriptor tail."""
    bulk = max(0, initial_count - 0x200)
    return ((bulk + 0x1ff) // 0x200) * 0x200 + tail


def packed_chunk_reads(packed, lba, count):
    sectors = packed >> 23
    if packed & 0x7fffff or not 0 < sectors <= 16 or not count:
        raise ValueError('chunk descriptor differs from the packed-resource reader')
    yield lba, sectors
    # Later reads use complete sixteen-sector chunks at a fixed stride.
    if count > 1:
        yield lba + 16, (count - 1) * 16


def floor_transfers(categories, module, read, transfer):
    """Follow the tables consumed by build_dungeon_floor and load_dungeon_layout."""
    if module is None or len(module) != FLOOR_MODULE[1]:
        raise ValueError('Dungeon floor catalog lies outside its loaded module')
    tracks = list(struct.iter_unpack('<5B', module[FLOOR_TRACKS:FLOOR_TRACKS + 50]))
    results = {}

    def descriptor(address):
        if FLOOR_MODULE_BASE <= address <= FLOOR_MODULE_BASE + len(module) - 8 and address % 4 == 0:
            return struct.unpack_from('<II', module, address - FLOOR_MODULE_BASE)
        return read(address), read(address + 4)

    def add(category, index, lba, sectors):
        extent = transfer(lba, sectors)
        if extent[0] != 'dungeon':
            raise ValueError('Dungeon floor read names a different disc container')
        results[category, index] = extent

    track_images = {track[3] for track in tracks}
    if FLOOR_IMAGES in categories and any(index >= 3 for index in track_images):
        raise ValueError('Dungeon floor track image index lies outside its resource table')
    selections = {
        FLOOR_IMAGES: (0x8001f588, 27, set(range(3, 27)) | track_images),
        FLOOR_LAYOUTS: (0x8001f604, 10, {track[1] - 1 for track in tracks if track[1]}),
    }
    for category, (table, count, indices) in selections.items():
        if category not in categories:
            continue
        if any(not 0 <= index < count for index in indices):
            raise ValueError('Dungeon floor track index lies outside its resource table')
        seen = set()
        for index in sorted(indices):
            address, = struct.unpack_from('<I', module, table - FLOOR_MODULE_BASE + index * 4)
            packed, lba = descriptor(address)
            if packed & 0x7fffff:
                raise ValueError('Dungeon floor image or layout does not read to scratch')
            if (packed, lba) not in seen:
                add(category, index, lba, packed >> 23)
                seen.add((packed, lba))

    if FLOOR_CHUNKS in categories:
        for kind in sorted({0x29} | {track[0] for track in tracks}):
            if not 0x29 <= kind <= 0x2b:
                raise ValueError('Dungeon floor track kind lies outside its chunk table')
            layout = read(0x8006e7f0 + kind * 4)
            packed, lba = descriptor(read(layout))
            count = read(layout + 4) & 0xffff
            for part, (first, sectors) in enumerate(packed_chunk_reads(packed, lba, count)):
                add(FLOOR_CHUNKS, kind * 2 + part, first, sectors)
    return results


def town_chunk_transfers(town, read, transfer):
    start, size = TOWN_MAP_VARIANTS
    if town is None or start + size - TOWN_ENGINE_DELTA > len(town):
        raise ValueError('Town map variants lie outside their loaded image')
    catalog = TOWN_CHUNK_TABLES[0]
    end = catalog + TOWN_CHUNK_TABLES[1]

    def read_town(address, fmt):
        if address % 4 or not catalog <= address <= end - struct.calcsize(fmt):
            raise ValueError('Town map chunk table pointer lies outside its catalog')
        return struct.unpack_from(fmt, town, address - TOWN_ENGINE_DELTA)

    # initialize_building_scene_assets skips the special kind at the end of
    # the Town table. initialize_building_graphics also requests kind zero.
    kinds = set(town[start - TOWN_ENGINE_DELTA:start + size - TOWN_ENGINE_DELTA:32]) | {0}
    result, seen = {}, set()
    for kind in sorted(kinds - {0x29}):
        if not 0 <= kind < 0x29:
            raise ValueError('Town map variant has an invalid chunk kind')
        layout = read(0x8006e7f0 + kind * 4)
        descriptor, count = read_town(layout, '<IH')
        packed, lba = read_town(descriptor, '<II')
        key = packed, lba, count
        if key in seen:
            continue
        seen.add(key)
        for part, (first, sectors) in enumerate(packed_chunk_reads(packed, lba, count)):
            extent = transfer(first, sectors)
            if extent[0] != 'town':
                raise ValueError('Town map chunk read names a different disc container')
            result[TOWN_CHUNKS, kind * 2 + part] = extent
    return result


def transfer_table(executable, volumes, categories, town=None, floor_module=None, *, floor_descriptors=None):
    if not executable.startswith(b'PS-X EXE') or len(executable) < 0x800:
        raise ValueError('invalid executable header for resource reads')
    base, length = struct.unpack_from('<II', executable, 0x18)
    if not 0 < length <= len(executable) - 0x800:
        raise ValueError('invalid executable load extent for resource reads')

    def read(address, fmt='<I'):
        if address % 4 or not base <= address <= base + length - 4:
            raise ValueError('resource table pointer lies outside the executable')
        return struct.unpack_from(fmt, executable, address - base + 0x800)[0]

    def transfer(lba, sectors):
        size = sectors * SECTOR_BYTES
        hits = []
        for family, (first, length) in volumes.items():
            offset = (lba - first) * SECTOR_BYTES
            if 0 <= offset < offset + size <= length:
                hits.append((family, offset, size))
        if len(hits) != 1:
            raise ValueError('resource read lies outside a single disc container')
        return hits[0]

    result = {}
    if SCENE in categories:
        # load_scene_resource_group handles types 1–3 with the two tables.
        for group in (1, 2, 3):
            count = read(0x8006ce6c + 4 * group, '<i')
            descriptor = read(0x8006ce44 + 8 * group + 4)
            sectors = scene_sector_count(count, read(descriptor) >> 23)
            result[SCENE, group] = transfer(read(descriptor + 4), sectors)
    if MOVIE in categories:
        # load_movie_overlay_once reads the first resource_read_descriptors entry.
        movie = transfer(read(0x80080c54), read(0x80080c50) >> 23)
        if movie[0] != 'ovmovie':
            raise ValueError('movie overlay descriptor names a different disc container')
        result[MOVIE, 0] = movie
    if INDEXED_SPRITES in categories:
        # The three bundle wrappers call load_indexed_sprite_bundle with
        # indices 0, 1 and 2. Each table entry pairs a CD descriptor with
        # the resource address subsequently used by the upload and relocator.
        for group, container in enumerate(INDEXED_SPRITE_CONTAINERS):
            entry = 0x80071210 + group * 8
            descriptor, destination = read(entry), read(entry + 4)
            packed = read(descriptor)
            extent = transfer(read(descriptor + 4), packed >> 23)
            if extent[0] != container or (0x80000000 | (packed & 0x7fffff)) != destination:
                raise ValueError('indexed sprite descriptor differs from its consumer')
            result[INDEXED_SPRITES, group] = extent
    if TOWN_TEXTURES in categories:
        # load_scene_texture_and_data and load_variant_texture_set queue
        # these descriptor records, then process the image commands at their
        # shared destination. The menu code read is a separate descriptor.
        for index, descriptor in enumerate(range(0x80080bac, 0x80080c1c, 8)):
            packed = read(descriptor)
            extent = transfer(read(descriptor + 4), packed >> 23)
            if extent[0] != 'town' or (packed & 0x7fffff) != 0x20000:
                raise ValueError('Town texture descriptor differs from its consumer')
            result[TOWN_TEXTURES, index] = extent
    if TOWN_CHARACTERS in categories:
        # load_reserved_slot_resources passes the Town catalog's character
        # descriptors to file_load_com. Several of the IDs alias one descriptor.
        start = TOWN_RESOURCE_CATALOG - TOWN_ENGINE_DELTA
        if town is None or len(town) < start + 14 * 4:
            raise ValueError('Town character resource catalog lies outside the Town container')
        seen = set()
        for character in range(1, 14):
            descriptor, = struct.unpack_from('<I', town, start + character * 4)
            if descriptor in seen:
                continue
            seen.add(descriptor)
            packed = read(descriptor)
            extent = transfer(read(descriptor + 4), packed >> 23)
            if extent[0] != 'town' or packed & 0x7fffff:
                raise ValueError('Town character descriptor differs from its consumer')
            result[TOWN_CHARACTERS, character] = extent
    if categories.intersection(FLOOR_CATEGORIES):
        result.update(floor_transfers(categories, floor_module, read, transfer))
    if FLOOR_MODULE_READ in categories:
        if floor_descriptors is None or len(floor_descriptors) != 16:
            raise ValueError('missing Dungeon floor module descriptors')
        # The two floor reload callers each pass one descriptor to Control_CD.
        for group, (packed, lba) in enumerate(struct.iter_unpack('<II', floor_descriptors)):
            extent = transfer(lba, packed >> 23)
            if extent[0] != 'dungeon' or (0x80000000 | (packed & 0x7fffff)) != FLOOR_MODULE_BASE:
                raise ValueError('Dungeon floor module descriptor has the wrong destination')
            result[FLOOR_MODULE_READ, group] = extent
    if TOWN_CHUNKS in categories:
        result.update(town_chunk_transfers(town, read, transfer))
    if TOWN_SETUP in categories:
        for index, (owner, address, family) in enumerate(TOWN_SETUP_DESCRIPTORS):
            if owner == 'town':
                offset = address - TOWN_ENGINE_DELTA
                if town is None or offset + 8 > len(town):
                    raise ValueError('Town setup descriptor lies outside its loaded image')
                packed, lba = struct.unpack_from('<II', town, offset)
            else:
                packed, lba = read(address), read(address + 4)
            extent = transfer(lba, packed >> 23)
            if extent[0] != family or packed & 0x7fffff:
                raise ValueError('Town setup descriptor differs from its consumer')
            result[TOWN_SETUP, index] = extent
    if TOWN_DEFAULT_SCENE in categories:
        # change_map selects this resident descriptor outside scene selector 12.
        packed, lba = read(0x800812f8), read(0x800812fc)
        extent = transfer(lba, packed >> 23)
        if extent[0] != 'town' or packed & 0x7fffff != 0x16000:
            raise ValueError('Town default scene descriptor differs from its consumer')
        result[TOWN_DEFAULT_SCENE, 0] = extent
    if FLOOR_SPAWNS in categories:
        # Ordinary floors start at one. setup_dungeon_floor_encounters skips
        # load_floor_spawn_tables from floor forty onward.
        for floor in range(1, 40):
            extent = transfer(0x3f5e + floor, 1)
            if extent[0] != 'dungeon':
                raise ValueError('Dungeon spawn table read names a different disc container')
            result[FLOOR_SPAWNS, floor] = extent
    if EFFECT_BANK in categories:
        # audio_load_sound_effect_bank submits both reads of each bank.
        # Each record pairs a read to scratch with a read to a fixed destination.
        for index, address in enumerate(range(0x8006e61c, 0x8006e6f4, 12)):
            if not 1 <= (read(address) & 0xffff) <= 3:
                raise ValueError('sound effect bank has an invalid channel slot')
            for part, scratch in enumerate((True, False), 1):
                descriptor = read(address + part * 4)
                packed = read(descriptor)
                if (packed & 0x7fffff == 0) != scratch:
                    raise ValueError('sound effect bank descriptor has the wrong destination mode')
                result[EFFECT_BANK, 2 * index + part - 1] = transfer(read(descriptor + 4), packed >> 23)
    if SOUND_SET in categories:
        # load_sound_set reads one pair per sound mode.
        for index, address in enumerate(range(0x8006e6f4, 0x8006e704, 4)):
            descriptor = read(address)
            packed = read(descriptor)
            if (packed & 0x7fffff == 0) != (index % 2 == 0):
                raise ValueError('sound set descriptor has the wrong destination mode')
            result[SOUND_SET, index] = transfer(read(descriptor + 4), packed >> 23)
    if SOUND_STREAM in categories:
        # select_sound_stream replaces only the destination before submitting a read.
        for index, address in enumerate(range(0x8006e704, 0x8006e7b4, 4)):
            descriptor = read(address)
            result[SOUND_STREAM, index] = transfer(read(descriptor + 4), read(descriptor) >> 23)
    return result


def verify_records(records, executable, volumes, town=None, floor_module=None, *, floor_descriptors=None):
    categories = {row['category'] for row in records}
    expected = transfer_table(executable, volumes, categories, town, floor_module,
                              floor_descriptors=floor_descriptors)
    actual = {(row['category'], row['group']): (row['container'], row['foff'], row['size'])
              for row in records}
    if len(actual) != len(records) or actual != expected:
        raise ValueError('coverage records disagree with the executable resource read tables')
    return actual


def check_sprite_bundle_payload(data):
    """Bound the VRAM row the bundle loader uploads before relocation."""
    if len(data) < 0x28:
        raise ValueError('indexed sprite payload is missing its header')
    offset, width_blocks = struct.unpack_from('<ii', data, 0x1c)
    if not 0x28 <= offset < offset + width_blocks * 32 <= len(data):
        raise ValueError('indexed sprite upload row lies outside the disc read')


def check_chunk_payload(data, remaining):
    """Decode each separately transferred chunk within the remaining RAM."""
    for offset in range(0, len(data), CHUNK_BYTES):
        decoded, _ = decode(data[offset:offset + CHUNK_BYTES], remaining)
        if not decoded:
            raise ValueError('packed resource chunk decodes to an empty buffer')
        remaining -= len(decoded)
    return remaining


def checked_ranges(root, disc_root, records, executable, containers):
    if not records:
        return {}
    disc_path = Path(os.environ.get('AZURE_CLEAN_DISC') or root / 'bin/Azure Dreams.bin')
    ranges = {}
    with Disc(disc_path) as disc:
        volumes = {family: disc.locate(name) for family, name in VOLUMES.items()}
        if any(size != containers[family][0] for family, (_, size) in volumes.items()):
            raise ValueError('resource disc directory differs from the registered containers')
        categories = {row['category'] for row in records}

        def checked_slice(family, start, size):
            name = VOLUMES[family]
            with (disc_root / FILES[name]).open('rb') as extracted:
                extracted.seek(start)
                data = extracted.read(size)
            if disc.slice(name, start, size) != data:
                raise ValueError(f'{family}: resource read differs from the extracted disc bytes')
            return data

        town = floor_module = floor_descriptors = None
        if categories.intersection({TOWN_CHARACTERS, TOWN_CHUNKS, TOWN_SETUP}):
            town = (disc_root / FILES[VOLUMES['town']]).read_bytes()
            town_tables = []
            if TOWN_CHARACTERS in categories:
                town_tables.append((TOWN_RESOURCE_CATALOG, 14 * 4))
            if TOWN_CHUNKS in categories:
                town_tables.extend((TOWN_MAP_VARIANTS, TOWN_CHUNK_TABLES))
            if TOWN_SETUP in categories:
                town_tables.extend((address, 8) for owner, address, _ in TOWN_SETUP_DESCRIPTORS if owner == 'town')
            for address, size in town_tables:
                offset = address - TOWN_ENGINE_DELTA
                if disc.slice(VOLUMES['town'], offset, size) != town[offset:offset + size]:
                    raise ValueError('Town resource catalog differs from the extracted disc bytes')
        if categories.intersection((*FLOOR_CATEGORIES, FLOOR_MODULE_READ)):
            floor_descriptors = checked_slice('dungeon', FLOOR_MODULE_DESCRIPTOR, 16)
        if categories.intersection(FLOOR_CATEGORIES):
            packed, lba = struct.unpack_from('<II', floor_descriptors)
            first, _ = volumes['dungeon']
            module = ((lba - first) * SECTOR_BYTES, (packed >> 23) * SECTOR_BYTES)
            if module != FLOOR_MODULE or 0x80000000 | (packed & 0x7fffff) != FLOOR_MODULE_BASE:
                raise ValueError('Dungeon floor module descriptor differs from its catalog placement')
            floor_module = checked_slice('dungeon', *module)
        chunk_space = {}
        for (category, group), (family, start, size) in sorted(verify_records(
                records, executable, volumes, town, floor_module, floor_descriptors=floor_descriptors).items()):
            data = checked_slice(family, start, size)
            if category == INDEXED_SPRITES:
                check_sprite_bundle_payload(data)
            if category in CHUNK_OUTPUT_LIMITS:
                key = category, group // 2
                remaining = chunk_space.get(key, CHUNK_OUTPUT_LIMITS[category])
                chunk_space[key] = check_chunk_payload(data, remaining)
            ranges.setdefault(family, {}).setdefault(category, []).append([start, start + size])
    return ranges
