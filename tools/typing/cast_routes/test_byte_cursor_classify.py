#!/usr/bin/env python3
"""Unit tests for byte_cursor_classify.py (pure functions; no build, no code map)."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent))
import byte_cursor_classify as B  # noqa: E402


def row(**kw):
    base = dict(cast_text='', variable_offset='False', chain_offset='0', chain_base_type='void *', _base='p',
                ast_sub='')
    base.update(kw)
    return base


class Advancement(unittest.TestCase):
    def test_constant_step(self):
        self.assertEqual(B.advancement('{ p += 0x18; p++; }', 'p'), ('const', 0x18))

    def test_reassigned_arithmetic(self):
        self.assertEqual(B.advancement('{ p = (u8 *)p + 12; }', 'p'), ('const', 12))

    def test_data_step(self):
        self.assertEqual(B.advancement('{ p += p[1] + 2; }', 'p')[0], 'data')

    def test_list_walk_is_not_an_advance(self):
        self.assertEqual(B.advancement('{ p = *(void **)((u8 *)p + 4); }', 'p'), ('', None))
        self.assertEqual(B.advancement('{ p = p->next; }', 'p'), ('', None))

    def test_member_compound_is_not_an_advance(self):
        self.assertEqual(B.advancement('{ p[0x11] -= 1; q->p += 2; }', 'p'), ('', None))


class Classify(unittest.TestCase):
    def test_data_driven_offset(self):
        r = row(cast_text='(Cmd *)((u8 *)cmd + cmd->next)', variable_offset='True', _base='cmd')
        self.assertEqual(B.classify(r, dict(base_kind='struct', base_decl='local'), '', None)[0], 'stream_reader')

    def test_record_walk_inside_step(self):
        r = row(cast_text='(s16 *)((u8 *)packet + 0x10)', chain_offset='16', _base='packet')
        self.assertEqual(B.classify(r, dict(base_kind='void', base_decl='local'), 'const', 24),
                         ('record_walk', 'constant_step_24'))

    def test_access_beyond_step_is_a_record_access(self):
        r = row(cast_text='(s32 *)(entity + 0x18)', chain_offset='24', chain_base_type='u8 *', _base='entity')
        self.assertEqual(B.classify(r, dict(base_kind='byte', base_decl='local'), 'const', 3)[0], 'untyped_record')

    def test_typed_member_and_gap(self):
        r = row(cast_text='(s16 *)((u8 *)actor + 0xB8)', chain_offset='184', chain_base_type='ActorRecord *')
        self.assertEqual(B.classify(r, dict(base_kind='struct', sub='addr_member'), '', None)[0], 'typed_member')
        self.assertEqual(B.classify(r, dict(base_kind='struct', sub='width_differs'), '', None)[0], 'layout_gap')

    def test_array_stride(self):
        r = row(cast_text='(s16 *)((u8 *)dir_step_x + (dir << 1))', variable_offset='True', _base='dir_step_x')
        self.assertEqual(B.classify(r, dict(base_kind='global', base_decl='global'), '', None),
                         ('array_stride', 'global_table'))
        r = row(cast_text='(u32 *)(values + (i * 4) + 0x48)', variable_offset='True', chain_base_type='u8 *',
                _base='values')
        self.assertEqual(B.classify(r, dict(base_kind='byte', base_decl='param:0'), '', None),
                         ('array_stride', 'scaled_index'))

    def test_untyped_and_global_record(self):
        r = row(cast_text='(u16 *)((u8 *)object + 0x3E)', chain_offset='62')
        self.assertEqual(B.classify(r, dict(base_kind='void', base_decl='param:0'), '', None),
                         ('untyped_record', 'void_param'))
        r = row(cast_text='(void **)((u8 *)D_80010000 + 0x6000)', chain_offset='24576')
        self.assertEqual(B.classify(r, dict(base_kind='global', base_decl='global'), '', None)[0], 'global_record')


class Helpers(unittest.TestCase):
    def test_base_name(self):
        self.assertEqual(B.base_name(dict(cast_text='(u16 *)((u8 *)object + 0x3E)'), {}), 'object')
        self.assertEqual(B.base_name(dict(cast_text='(s16 *)(w + 18)'), {}), 'w')
        self.assertEqual(B.base_name(dict(cast_text='(s16 *)(x)'), dict(base_expr='a->b')), 'a->b')

    def test_alias_source(self):
        body = 'void f(ActorRecord *body) { u8 *entity; entity = (u8 *)body; x = *(s32 *)(entity + 0x18); }'
        self.assertEqual(B.alias_source(body, 'entity'), ('body', 'param'))
        body = 'void f(void) { void *o; o = NODE_BODY(node); }'
        self.assertEqual(B.alias_source(body, 'o')[1], 'node_body')
        body = 'void f(void) { void *o; o = *(void **)((u8 *)q + 4); }'
        self.assertEqual(B.alias_source(body, 'o')[1], 'load')

    def test_candidates(self):
        index = {(0, 2): {'A', 'B'}, (2, 2): {'A', 'B'}, (4, 4): {'A'}}
        info = {'A': (8, False), 'B': (8, False)}
        self.assertEqual(B.candidates([(0, 2), (2, 2), (4, 4)], index, info), ['A'])
        self.assertEqual(B.candidates([(0, 2), (2, 2)], index, info), [])   # too few accesses

    def test_domain(self):
        self.assertEqual(B.domain_of('src/engine/script/opcode_52_set_immediate.c', 'opcode_52'), 'script')
        self.assertEqual(B.domain_of('src/dungeon/effect/x.c', 'draw_textured_quad'), 'gpu_packet')


if __name__ == '__main__':
    unittest.main()
