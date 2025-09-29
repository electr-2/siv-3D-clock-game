#include <Siv3D.hpp>

void Main() {
  // ウィンドウの設定
  Window::SetTitle(U"Simple Game");
  Window::Resize(800, 600);

  // 背景色の設定
  Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
  const Font fontMSDF{FontMethod::MSDF, 48};
  bool clicked = false;
  enum GameState { Waiting, Success, Late, Early };
  GameState state = Waiting;
  bool running = true;
  Stopwatch sw;
  sw.start();
  // メインループ
  while (System::Update()) {
    if (state == Early) {
      fontMSDF(U"判断が早い").drawAt(Scene::Center(), Palette::Black);
      continue;
    }
    if (state == Late) {
      fontMSDF(U"判断が遅い").drawAt(Scene::Center(), Palette::Black);
      continue;
    }

    if (state == Success) {
      fontMSDF(U"成功").drawAt(Scene::Center(), Palette::Black);
      continue;
    }

    if (MouseL.down()) {
      if (sw < 2.9s) {
        state = Early;
      }
      if (2.9s < sw && sw < 3.1s) {
        state = Success;
      }
      if (3.1s < sw) {
        state = Late;
      }
    }
    fontMSDF(U"3秒を狙ってクリック！").drawAt(Scene::Center(), Palette::Black);
  }
}