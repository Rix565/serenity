/*
 * Copyright (c) 2020, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/CSS/StyleProperties.h>
#include <LibWeb/CSS/StyleValues/IdentifierStyleValue.h>
#include <LibWeb/HTML/HTMLDivElement.h>

namespace Web::HTML {

HTMLDivElement::HTMLDivElement(DOM::Document& document, DOM::QualifiedName qualified_name)
    : HTMLElement(document, move(qualified_name))
{
}

HTMLDivElement::~HTMLDivElement() = default;

// https://html.spec.whatwg.org/multipage/rendering.html#flow-content-3
void HTMLDivElement::apply_presentational_hints(CSS::StyleProperties& style) const
{
    for_each_attribute([&](auto& name, auto& value) {
        if (name.equals_ignoring_ascii_case("align"sv)) {
            if (value.equals_ignoring_ascii_case("left"sv))
                style.set_property(CSS::PropertyID::TextAlign, CSS::IdentifierStyleValue::create(CSS::ValueID::LibwebLeft).release_value_but_fixme_should_propagate_errors());
            else if (value.equals_ignoring_ascii_case("right"sv))
                style.set_property(CSS::PropertyID::TextAlign, CSS::IdentifierStyleValue::create(CSS::ValueID::LibwebRight).release_value_but_fixme_should_propagate_errors());
            else if (value.equals_ignoring_ascii_case("center"sv))
                style.set_property(CSS::PropertyID::TextAlign, CSS::IdentifierStyleValue::create(CSS::ValueID::LibwebCenter).release_value_but_fixme_should_propagate_errors());
            else if (value.equals_ignoring_ascii_case("justify"sv))
                style.set_property(CSS::PropertyID::TextAlign, CSS::IdentifierStyleValue::create(CSS::ValueID::Justify).release_value_but_fixme_should_propagate_errors());
        }
    });
}

JS::ThrowCompletionOr<void> HTMLDivElement::initialize(JS::Realm& realm)
{
    MUST_OR_THROW_OOM(Base::initialize(realm));
    set_prototype(&Bindings::ensure_web_prototype<Bindings::HTMLDivElementPrototype>(realm, "HTMLDivElement"));

    return {};
}

}
