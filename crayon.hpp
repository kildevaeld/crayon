#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
namespace crayon {

#define ESCAPE "\u001b["
#define MODIFIER "m"

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

  Text(Style style, const std::string &text) : m_text(text) {
    m_styles.push_back(style);
  }

  Text(Text &&other)
      : m_styles(other.m_styles), m_text(std::move(other.m_text)) {}

  Text &operator=(Text &&other) {
    if (&other != this) {
      m_text.swap(other.m_text);
      m_styles.swap(other.m_styles);
    }
    return *this;
  }

  operator std::string() const { return str(); }

  std::string str() const {
    std::stringstream stream;
    int i = 0;
    int l = m_styles.size();

    for (; i < l; i++) {
      stream << ESCAPE << m_styles[i] << MODIFIER;
    }
    stream << m_text;
    while (i >= 0) {
      stream << ESCAPE << m_styles[i--] << MODIFIER;
    }
    return stream.str();
  }

  Text &style(Style style) {
    m_styles.push_back(style);
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &stream, const Text &text) {
    stream << text.str();
    return stream;
  }

private:
  int get_closer(Style style) const {
    if (style > 0 && style <= 9)
      return style + 20;
    if ((style >= 30 && style <= 37) || style == 90)
      return 39;
    if (style >= 40 && style <= 47)
      return 49;
    return 0;
  }
  std::vector<Style> m_styles;
  std::string m_text;
};

Text style(Style style, const std::string &txt) { return Text(style, txt); }

namespace fg {
Text red(const std::string &txt) { return std::move(Text(Red, txt)); }
Text green(const std::string &txt) { return std::move(Text(Green, txt)); }
Text yellow(const std::string &txt) { return std::move(Text(Yellow, txt)); }
Text blue(const std::string &txt) { return std::move(Text(Blue, txt)); }
Text megenta(const std::string &txt) { return std::move(Text(Megenta, txt)); }
Text cyan(const std::string &txt) { return std::move(Text(Cyan, txt)); }
Text white(const std::string &txt) { return std::move(Text(White, txt)); }
Text gray(const std::string &txt) { return std::move(Text(Gray, txt)); }
}

namespace bg {
Text red(const std::string &txt) { return Text(BgRed, txt); }
Text green(const std::string &txt) { return Text(BgGreen, txt); }
Text yellow(const std::string &txt) { return Text(BgYellow, txt); }
Text blue(const std::string &txt) { return Text(BgBlue, txt); }
Text megenta(const std::string &txt) { return Text(BgMegenta, txt); }
Text cyan(const std::string &txt) { return Text(BgCyan, txt); }
Text white(const std::string &txt) { return Text(BgWhite, txt); }
}
}