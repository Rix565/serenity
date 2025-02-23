/*
 * Copyright (c) 2022, Sam Atkins <atkinssj@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Array.h>
#include <AK/String.h>
#include <LibCards/Card.h>
#include <LibGfx/Bitmap.h>
#include <LibGfx/Color.h>

namespace Cards {

class CardPainter {
public:
    static CardPainter& the();

    NonnullRefPtr<Gfx::Bitmap> card_front(Suit, Rank);
    NonnullRefPtr<Gfx::Bitmap> card_back();
    NonnullRefPtr<Gfx::Bitmap> card_front_inverted(Suit, Rank);
    NonnullRefPtr<Gfx::Bitmap> card_back_inverted();
    NonnullRefPtr<Gfx::Bitmap> card_front_highlighted(Suit, Rank);

    void set_background_image_path(StringView path);
    void set_background_color(Color);

private:
    CardPainter();
    NonnullRefPtr<Gfx::Bitmap> create_card_bitmap();
    void paint_card_front(Gfx::Bitmap&, Suit, Rank);
    void paint_card_back(Gfx::Bitmap&);
    void paint_inverted_card(Gfx::Bitmap& bitmap, Gfx::Bitmap const& source_to_invert);
    void paint_highlighted_card(Gfx::Bitmap& bitmap, Gfx::Bitmap const& source_to_highlight);

    Array<Array<RefPtr<Gfx::Bitmap>, to_underlying(Rank::__Count)>, to_underlying(Suit::__Count)> m_cards;
    Array<Array<RefPtr<Gfx::Bitmap>, to_underlying(Rank::__Count)>, to_underlying(Suit::__Count)> m_cards_inverted;
    Array<Array<RefPtr<Gfx::Bitmap>, to_underlying(Rank::__Count)>, to_underlying(Suit::__Count)> m_cards_highlighted;
    RefPtr<Gfx::Bitmap> m_card_back;
    RefPtr<Gfx::Bitmap> m_card_back_inverted;

    String m_background_image_path;
    Color m_background_color;
};

}
