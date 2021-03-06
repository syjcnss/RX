グラフィックス、GUI Widgets フレームワーク
=========

## 概要

2D、3D 描画、GUI Widgets、画像ファイルローダーなど、グラフィックス関係の操作を行うもの。
   
## プロジェクト・リスト
|ファイル名|機能|
|---|---|
|afont.hpp|ASCII フォントクラス|
|font6x12.hpp|6x12 ASCII フォントクラス|
|font6x12.cpp|6x12 ASCII フォントリソース|
|font8x16.hpp|8x16 ASCII フォントクラス|
|font8x16.cpp|8x16 ASCII フォントリソース|
|kfont.hpp|漢字フォントクラス|
|kfont16.cpp|16x16 漢字フォントリソース|
|font.hpp|フォント|
|color.hpp|カラー定義|
|color.cpp|カラー定義リソース|
|graphics.hpp|2D 描画クラス|
|monograph.hpp|2D ビットマップ描画クラス|
|filer.hpp|ファイル選択クラス|
|root_menu.hpp|ルートメニュークラス|
|dialog.hpp|ダイアログクラス|
|term.hpp|ターミナルクラス|
|img.hpp|イメージ定義クラス|
|img_in.hpp|画像定義|
|pixel.hpp|ピクセル定義|
|bmp_in.hpp|BMP ファイルローダー|
|jpeg_in.hpp|JPEG ファイルローダー|
|png_in.hpp|PNG ローダー|
|picojpeg.h|picojpeg ヘッダー|
|picojpeg.c|picojpeg ソースコード|
|picojpeg_in.hpp|picoJPEG ローダー|
|scaling.hpp|スケーリングパイプクラス|
|glmatrix.hpp|OpenGL マトリックスクラス|
|tgl.hpp|TinyGL(OpenGL) クラス|
|widget_director.hpp|Widget ディレクター|
|widget.hpp|Widget ウィジェット基本クラス|
|group.hpp|Widget グループ|
|frame.hpp|Widget フレーム|
|button.hpp|Widget ボタン|
|check.hpp|Widget チェックボックス|
|radio.hpp|Widget ラジオボタン|
|slider.hpp|Widget スライダー|
|menu.hpp|Widget メニュー|
|spinbox.hpp|Widget スピンボックス|
   
---

## 画像ローダー

- BMP, PNG, JPEG 画像のロードと展開
- 「展開」を行うファンクタをテンプレートで指定する構成（省メモリ）
- 「スケーリング」クラスを経由する事で、拡大、縮小が可能

## 簡易ダイアログ

- 単独で、ダイアログを表示する事が出来る。
- メッセージを表示し、タッチで消える、簡単なポリシー

## GUI Widget 概要

- タッチパネルと、グラフィックス画面を使った GUI フレームワーク
- テンプレートを使う事で、記憶割り当てを使わないシンプルな構造
- ソフトウェアー、及びハードウェアーレンダリングに適応出来る構成
- 記憶割り当てを利用しない、スタテック構造（テンプレートパラメーターでサイズ指定）
- リソースの消費を抑えた設計




---
   
License
---

MIT
