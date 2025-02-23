/*
 * Copyright (c) 2020, the SerenityOS developers.
 * Copyright (c) 2023, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/NonnullRefPtr.h>
#include <AK/StringView.h>
#include <AK/Types.h>
#include <LibJS/SourceCode.h>

namespace JS {

struct Position {
    size_t line { 0 };
    size_t column { 0 };
    size_t offset { 0 };
};

struct SourceRange {
    [[nodiscard]] bool contains(Position const& position) const { return position.offset <= end.offset && position.offset >= start.offset; }

    NonnullRefPtr<SourceCode const> code;
    Position start;
    Position end;

    DeprecatedString filename() const;
};

struct UnrealizedSourceRange {
    [[nodiscard]] SourceRange realize() const
    {
        VERIFY(source_code);
        return source_code->range_from_offsets(start_offset, end_offset);
    }

    RefPtr<SourceCode const> source_code;
    u32 start_offset { 0 };
    u32 end_offset { 0 };
};

}
