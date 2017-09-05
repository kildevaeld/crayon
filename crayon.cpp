#include "crayon.hpp"

#define ESCAPE "\u001b["
#define MODIFIER "m"

namespace crayon {

namespace fg {

Text red(const std::string &txt) { return std::move(Text(Red, txt)); }

Text green(const std::string &txt) { return std::move(Text(Green, txt)); }

Text yellow(const std::string &txt) { return std::move(Text(Yellow, txt)); }

Text blue(const std::string &txt) { return std::move(Text(Blue, txt)); }

Text megenta(const std::string &txt) { return std::move(Text(Megenta, txt)); }

Text cyan(const std::string &txt) { return std::move(Text(Cyan, txt)); }

Text white(const std::string &txt) { return std::move(Text(White, txt)); }

Text gray(const std::string &txt) { return std::move(Text(Gray, txt)); }

Text reset() { return std::move(Text(Reset, ""));}

} // namespace fg

namespace bg {

Text red(const std::string &txt) { return Text(BgRed, txt); }

Text green(const std::string &txt) { return Text(BgGreen, txt); }

Text yellow(const std::string &txt) { return Text(BgYellow, txt); }

Text blue(const std::string &txt) { return Text(BgBlue, txt); }

Text megenta(const std::string &txt) { return Text(BgMegenta, txt); }

Text cyan(const std::string &txt) { return Text(BgCyan, txt); }

Text white(const std::string &txt) { return Text(BgWhite, txt); }

} // namespace bg

Text::Text(Style style, const std::string &text) : m_text(text) {
  m_styles.push_back(style);
}

Text::Text(Text &&other)
    : m_styles(other.m_styles), m_text(std::move(other.m_text)) {}

Text &Text::operator=(Text &&other) {
  if (&other != this) {
    m_text.swap(other.m_text);
    m_styles.swap(other.m_styles);
  }
  return *this;
}

Text::operator std::string() const { return str(); }

std::string Text::str() const {
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

Text &Text::style(Style style) {
  m_styles.push_back(style);
  return *this;
}

void Text::append(const std::string &str) { m_text.append(str); }



int Text::get_closer(Style style) const {
  if (style > 0 && style <= 9)
    return style + 20;
  if ((style >= 30 && style <= 37) || style == 90)
    return 39;
  if (style >= 40 && style <= 47)
    return 49;
  return 0;
}

Text style(Style style, const std::string &txt) { return Text(style, txt); }


std::ostream &operator<<(std::ostream &stream, const Text &text) {
    stream << text.str();
    return stream;
  }
  
  Text &operator<<(Text &text, const std::string &str) {
    text.append(str);
    return text;
  }

} // namespace crayon


