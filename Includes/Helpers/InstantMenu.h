#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include <concepts>
#include <functional>
#include <CTRPluginFramework.hpp>

/*

InstantMenu menu{ "", { "a", "b", "c" } };



*/

namespace CTRPluginFramework {
  template <class T, std::string(*conv_fn)(T) = nullptr>
  class InstantMenuImpl {
    std::string title;
    std::vector<T> const& items;

    bool is_open;
    long index;
    long ret;

    static constexpr int edge = 16;
    static constexpr bool is_top = true;

    static constexpr int menu_draw_x = edge;
    static constexpr int menu_draw_y = edge;
    static constexpr int menu_width = (is_top ? 400 : 320) - edge * 2;
    static constexpr int menu_height = 240 - edge * 2;

    static constexpr int item_height = 14;
    static constexpr int item_draw_count = menu_height / item_height - 1;

  public:
    InstantMenuImpl(std::string const& title = "")
      : title(title),
        is_open(false),
        index(0)
    {
    }

    InstantMenuImpl(std::string const& title, std::vector<T> const& items)
      : title(title),
        items(items),
        is_open(false),
        index(0)
    {
    }

    void draw(Screen const& screen) {
      auto const& background_color = Color::Black;

      // background
      screen.DrawRect(menu_draw_x, menu_draw_y, menu_width, menu_height, background_color);

      // draw title
      screen.Draw(title, menu_draw_x + 2, menu_draw_y + 2);
      screen.DrawRect(menu_draw_x + 2, menu_draw_y + 2, (title.length() + 2) * 9, 1, Color::White);

      // draw items
      {
        long begin = std::max<long>(0, index - (item_draw_count - 2));
        long end = std::min<long>(items.size(), begin + item_draw_count);
        long dy = menu_draw_y + item_height + 2;

        for( ; begin < end; begin++, dy += item_height ) {
          if constexpr( conv_fn == nullptr ) {
            if( index == begin ) {
              screen.Draw(items[begin], menu_draw_x + 2, dy, Color::White, Color::Blue);
            }
            else {
              screen.Draw(items[begin], menu_draw_x + 2, dy);
            }
          }
          else {
            if( index == begin ) {
              screen.Draw(conv_fn(items[begin]), menu_draw_x + 2, dy, Color::White, Color::Blue);
            }
            else {
              screen.Draw(conv_fn(items[begin]), menu_draw_x + 2, dy);
            }
          }
        }
      }
    }

    void control() {
      static int tick = -1;
      static constexpr int tickmax = 60;

      u32 keys = Controller::GetKeysDown();

      if( keys ) {
        tick++;

        if( tick == 0 || tick == tickmax ) {
          if( keys & Key::DPadUp ) index = std::max<long>(0, index - 1);
          if( keys & Key::DPadDown ) index = std::min<long>(items.size() - 1, index + 1);
        }

        if( tick >= tickmax ) tick = 0;
      }
      else {
        tick = -1;
      }

      if( keys & Key::A ) {
        is_open = false;
        ret = index;
      }
      else if( keys & Key::B ) {
        is_open = false;
        ret = -1;
      }
    }

    long open() {
      is_open = true;

      Process::Pause();
      auto const& screen = OSD::GetTopScreen();

      while( is_open ) {
        Controller::Update();

        draw(screen);
        control();

        OSD::SwapBuffers();
        Sleep(Milliseconds(16));
      }

      Process::Play();

      return ret;
    }



  };

  using InstantMenu = InstantMenuImpl<std::string>;
  using InstantMenu_Int = InstantMenuImpl<int, std::to_string>;
}