"""Synthetic checks for diagnostic image entry witnesses."""
import hashlib
import struct
import unittest

from tools.diagnostic_code import LOAD_METHOD, checked_spans, span


class DiagnosticWitnessTests(unittest.TestCase):
    def setUp(self):
        self.data = bytearray(128)
        self.base = 0x80400000
        self.call = 12
        self.entry = 48
        struct.pack_into('<I', self.data, self.call,
                         (3 << 26) | ((self.base + self.entry) & 0x0fffffff) >> 2)
        struct.pack_into('<I', self.data, self.entry + 8, (31 << 21) | 8)
        self.image = dict(schema='azure-clean.instance-load-region.v1', method=LOAD_METHOD,
                          container='main', foff=0, size=len(self.data),
                          base=self.base, delta=self.base)
        self.seal_image()
        self.caller = dict(id='main/func_sample', func='func_sample', container='main', foff=8, size=32)
        self.record = dict(container='main', foff=self.entry, size=16, image_foff=0,
                           call_foff=self.call, caller=self.caller['id'])

    def seal_image(self):
        self.image['image_sha256'] = hashlib.sha256(self.data).hexdigest()

    def check(self, record=None):
        return span(record or self.record, self.image, self.caller, self.data)

    def test_registered_direct_call_confirms_only_its_actual_destination(self):
        self.assertEqual(self.check(), [48, 64])
        with self.assertRaisesRegex(ValueError, 'does not target'):
            self.check(dict(self.record, foff=52))
        with self.assertRaisesRegex(ValueError, 'outside its registered or checked caller'):
            self.check(dict(self.record, call_foff=84))

    def test_direct_calls_can_extend_an_anchored_chain(self):
        struct.pack_into('<I', self.data, 52, (3 << 26) | ((self.base + 80) & 0x0fffffff) >> 2)
        struct.pack_into('<I', self.data, 88, (31 << 21) | 8)
        self.seal_image()
        target = dict(container='main', image_foff=0, foff=80, size=16, caller_foff=48, call_foff=52)
        images = {('main', 0): self.image}
        registry = {self.caller['id']: self.caller}
        self.assertEqual(list(checked_spans([target, self.record], images, registry, self.data)),
                         [[48, 64], [80, 96]])
        with self.assertRaisesRegex(ValueError, 'has no registered anchor'):
            checked_spans([target], images, registry, self.data)
        with self.assertRaisesRegex(ValueError, 'outside its registered or checked caller'):
            checked_spans([self.record, dict(target, call_foff=68)], images, registry, self.data)

    def test_change_in_body_without_changing_witnesses_fails(self):
        self.data[self.entry] ^= 1
        with self.assertRaisesRegex(ValueError, 'placement record'):
            self.check()

    def test_callback_slot_has_the_right_consumer_and_entry(self):
        table = 96
        reader = [16, 20]
        base = self.base + table
        struct.pack_into('<II', self.data, reader[0], (15 << 26) | (3 << 16) | (base >> 16),
                         (9 << 26) | (3 << 21) | (3 << 16) | (base & 0xffff))
        struct.pack_into('<II', self.data, table, 0, self.base + self.entry)
        self.seal_image()
        record = dict(self.record, table_foff=table, entry_foff=table+4, table_reader=reader)
        del record['call_foff']
        self.assertEqual(self.check(record), [48, 64])
        with self.assertRaisesRegex(ValueError, 'callback table'):
            self.check(dict(record, table_foff=table+4))
        with self.assertRaisesRegex(ValueError, 'does not target'):
            self.check(dict(record, entry_foff=table))

    def test_jump_uses_the_address_constructed_by_the_wrapper(self):
        target = self.base + self.entry
        struct.pack_into('<III', self.data, 16, (15 << 26) | (3 << 16) | (target >> 16),
                         (9 << 26) | (3 << 21) | (4 << 16) | (target & 0xffff),
                         (4 << 21) | 8)
        self.seal_image()
        record = dict(self.record, jump_foff=24)
        del record['call_foff']
        self.assertEqual(self.check(record), [48, 64])
        struct.pack_into('<I', self.data, 24, (3 << 21) | 8)
        self.seal_image()
        with self.assertRaisesRegex(ValueError, 'does not jump'):
            self.check(record)


if __name__ == '__main__':
    unittest.main()
