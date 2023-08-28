/*
 * Copyright (c) 2020, Linus Groh <linusg@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibJS/Runtime/NativeFunction.h>

namespace JS {

class ArrayBufferConstructor final : public NativeFunction {
    JS_OBJECT(ArrayBufferConstructor, NativeFunction);

public:
    virtual void initialize(Realm&) override;
    virtual ~ArrayBufferConstructor() override = default;

    virtual ThrowCompletionOr<Value> call() override;
    virtual ThrowCompletionOr<NonnullGCPtr<Object>> construct(FunctionObject& new_target) override;

private:
    explicit ArrayBufferConstructor(Realm&);

    virtual bool has_constructor() const override { return true; }

    JS_DECLARE_NATIVE_FUNCTION(is_view);

    JS_DECLARE_NATIVE_FUNCTION(symbol_species_getter);
};

}
