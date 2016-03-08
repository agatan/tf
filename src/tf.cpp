#include <iostream>
#include <string>

class formatter {
public:
  formatter(std::ostream &out = std::cout, int indent = 4) noexcept
      : out_(out),
        depth_(0),
        indent_(indent) {}
  ~formatter() = default;

  template <typename Iter> void operator()(Iter iter, Iter const end) {
    while (iter != end) {
      switch (*iter) {
      case '<':
        out_ << "<\n";
        depth_++;
        indent();
        break;
      case '>':
        out_ << "\n";
        depth_--;
        indent();
        out_ << '>';
        break;
      case ',':
        out_ << ",\n";
        indent();
        break;
      case ' ':
      case '\t':
      case '\n':
      case '\r':
        break;
      default:
        out_ << *iter;
        break;
      }
      iter++;
    }
    out_ << "\n";
  }

  void operator()(std::string const &src) { (*this)(src.cbegin(), src.cend()); }

private:
  std::ostream &out_;
  int depth_;
  int indent_;

  void indent() const { out_ << std::string(depth_ * indent_, ' '); }
};

int main() {
  std::string src;
  std::string line;
  while (std::getline(std::cin, line)) {
    src += line + '\n';
  }

  formatter f;

  f(src);

  return 0;
}
