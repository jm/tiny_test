# TinyTest — A small, single-header testing framework

During my classwork for a C++ class, I found writing little test programs annoying and ugly, so I wrote this little testing framework to use.  My instructor called it overkill, but it made them much easier to write and prettier to my eyes.  Plus, I got to play with some cool C++11 features.

## How does it work?

The code is simple, so go dive right in!  If you want to know how to use it, simply look at `example.cpp`.  Run `make` to get a small test program that will show you the test run output: 

    Starting suite: Money
    ....FF

    Failures
    ----------------
    - Money -> Failure
    - Money -> Failure with message -> Cents ain't right

    ----------------
    Results: 4 tests, 4 assertions, 2 failures, 0 errors
    ----------------

The output is somewhat similar to Ruby's test runner.