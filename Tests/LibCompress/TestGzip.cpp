/*
 * Copyright (c) 2020-2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibTest/TestCase.h>

#include <AK/Array.h>
#include <AK/Random.h>
#include <LibCompress/Gzip.h>

TEST_CASE(gzip_decompress_simple)
{
    Array<u8, 33> const compressed {
        0x1f, 0x8b, 0x08, 0x00, 0x77, 0xff, 0x47, 0x5f, 0x02, 0xff, 0x2b, 0xcf,
        0x2f, 0x4a, 0x31, 0x54, 0x48, 0x4c, 0x4a, 0x56, 0x28, 0x07, 0xb2, 0x8c,
        0x00, 0xc2, 0x1d, 0x22, 0x15, 0x0f, 0x00, 0x00, 0x00
    };

    const u8 uncompressed[] = "word1 abc word2";

    auto const decompressed = Compress::GzipDecompressor::decompress_all(compressed);
    EXPECT(decompressed.value().bytes() == (ReadonlyBytes { uncompressed, sizeof(uncompressed) - 1 }));
}

TEST_CASE(gzip_decompress_multiple_members)
{
    Array<u8, 52> const compressed {
        0x1f, 0x8b, 0x08, 0x00, 0xe0, 0x03, 0x48, 0x5f, 0x02, 0xff, 0x4b, 0x4c,
        0x4a, 0x4e, 0x4c, 0x4a, 0x06, 0x00, 0x4c, 0x99, 0x6e, 0x72, 0x06, 0x00,
        0x00, 0x00, 0x1f, 0x8b, 0x08, 0x00, 0xe0, 0x03, 0x48, 0x5f, 0x02, 0xff,
        0x4b, 0x4c, 0x4a, 0x4e, 0x4c, 0x4a, 0x06, 0x00, 0x4c, 0x99, 0x6e, 0x72,
        0x06, 0x00, 0x00, 0x00
    };

    const u8 uncompressed[] = "abcabcabcabc";

    auto const decompressed = Compress::GzipDecompressor::decompress_all(compressed);
    EXPECT(decompressed.value().bytes() == (ReadonlyBytes { uncompressed, sizeof(uncompressed) - 1 }));
}

TEST_CASE(gzip_decompress_zeroes)
{
    Array<u8, 161> const compressed {
        0x1f, 0x8b, 0x08, 0x00, 0x6e, 0x7a, 0x4b, 0x5f, 0x02, 0xff, 0xed, 0xc1,
        0x31, 0x01, 0x00, 0x00, 0x00, 0xc2, 0xa0, 0xf5, 0x4f, 0xed, 0x61, 0x0d,
        0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6e, 0xcd, 0xcd, 0xe8,
        0x7e, 0x00, 0x00, 0x02, 0x00
    };

    Array<u8, 128 * 1024> const uncompressed = { 0 };

    auto const decompressed = Compress::GzipDecompressor::decompress_all(compressed);
    EXPECT(uncompressed == decompressed.value().bytes());
}

TEST_CASE(gzip_decompress_repeat_around_buffer)
{
    Array<u8, 70> const compressed {
        0x1f, 0x8b, 0x08, 0x00, 0xc6, 0x74, 0x53, 0x5f, 0x02, 0xff, 0xed, 0xc1,
        0x01, 0x0d, 0x00, 0x00, 0x0c, 0x02, 0xa0, 0xdb, 0xbf, 0xf4, 0x37, 0x6b,
        0x08, 0x24, 0xdb, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xca,
        0xb8, 0x07, 0xcd, 0xe5, 0x38, 0xfa, 0x00, 0x80, 0x00, 0x00
    };

    Array<u8, 0x8000> uncompressed;
    uncompressed.span().slice(0x0000, 0x0100).fill(1);
    uncompressed.span().slice(0x0100, 0x7e00).fill(0);
    uncompressed.span().slice(0x7f00, 0x0100).fill(1);

    auto const decompressed = Compress::GzipDecompressor::decompress_all(compressed);
    EXPECT(uncompressed == decompressed.value().bytes());
}

TEST_CASE(gzip_round_trip)
{
    auto original = ByteBuffer::create_uninitialized(1024).release_value();
    fill_with_random(original);
    auto compressed = TRY_OR_FAIL(Compress::GzipCompressor::compress_all(original));
    auto uncompressed = TRY_OR_FAIL(Compress::GzipDecompressor::decompress_all(compressed));
    EXPECT(uncompressed == original);
}

TEST_CASE(gzip_truncated_uncompressed_block)
{
    Array<u8, 38> const compressed {
        0x1F, 0x8B, 0x08, 0x13, 0x5D, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x85, 0x1C,
        0x1C, 0xFF, 0xDB, 0xFB, 0xFF, 0xDB
    };

    auto const decompressed_or_error = Compress::GzipDecompressor::decompress_all(compressed);
    EXPECT(decompressed_or_error.is_error());
}
