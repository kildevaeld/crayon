#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
namespace crayon {

enum Style {
  Reset = 0,
  Bold,
  Dim,
  Italic,
  Underline,
  Inverse = 7,
  Hidden,
  Strikethrough,

  Black = 30,
  Red,
  Green,
  Yellow,
  Blue,
  Megenta,
  Cyan,
  White,

  Gray = 90,
  BgBlack = 40,
  BgRed,
  BgGreen,
  BgYellow,
  BgBlue,
  BgMegenta,
  BgCyan,
  BgWhite
};

struct Text {

  Text(Style style, const std::string &text);

  Text(Text &&other);

  Text &operator=(Text &&other);

  operator std::string() const;

  std::string str() const;

  Text &style(Style style);

  void append(const std::string &str);

  friend std::ostream &operator<<(std::ostream &stream, const Text &text);

  friend Text &operator<<(Text &text, const std::string &str);

private:
  int get_closer(Style style) const;
  std::vector<Style> m_styles;
  std::string m_text;
};

Text style(Style style, const std::string &txt);

namespace fg {
Text red(const std::string &txt = "");
Text green(const std::string &txt = "");
Text yellow(const std::string &txt = "");
Text blue(const std::string &txt = "");
Text megenta(const std::string &txt = "");
Text cyan(const std::string &txt = "");
Text white(const std::string &txt = "");
Text gray(const std::string &txt = "");
Text reset();
}

namespace bg {
Text red(const std::string &txt);
Text green(const std::string &txt);
Text yellow(const std::string &txt);
Text blue(const std::string &txt);
Text megenta(const std::string &txt);
Text cyan(const std::string &txt);
Text white(const std::string &txt);
}
}
