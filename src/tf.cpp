#include <iostream>
#include <iterator>
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
        indent();
        show_indent();
        break;
      case '>':
        out_ << "\n";
        dedent();
        show_indent();
        out_ << '>';
        break;
      case ',':
        out_ << ",\n";
        show_indent();
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

  void show_indent() const { out_ << std::string(depth_ * indent_, ' '); }

  void indent() { depth_++; }

  void dedent() {
    depth_--;
    if (depth_ < 0) {
      invalid_input();
    }
  }

  [[noreturn]] void invalid_input() {
    std::cerr << "Input type is not a valid C++ type." << std::endl;
    std::exit(1);
  }
};

int main() {
  std::istream_iterator<char> iter(std::cin);
  std::istream_iterator<char> end;

  formatter f;

  f(iter, end);

  return 0;
}
