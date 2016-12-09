#include <iostream>

#include "tiny_test.h"

class Money {
public:
  int dollars, cents;

  Money() { this->dollars = 0; this->cents = 0; };
  Money(int d, int c):dollars(d),cents(c) {};
};

int main() {
  Suite("Money", []() {
    Test("Default constructor", []() {
      Money m = Money();

      assert(m.dollars == 0);
      assert(m.cents == 0);
    });

    Test("Integer constructor", []() {
      Money m = Money(20, 19);

      assert(m.dollars == 20);
      assert(m.cents == 19);
    });

    Test("Failure", [] () {
      Money m = Money(3, 77);

      assert(m.dollars == 19);
    });

    Test("Failure with message", [] () {
      Money m = Money(3, 77);

      assert((m.cents == 20), "Cents ain't right");
    });
  });

  return 0;
}