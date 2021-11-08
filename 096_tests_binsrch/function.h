#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
template<typename R, typename A>
class Function {
 public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};

class CountedIntFn : public Function<int, int> {
 protected:
  //record the number of invocations we can do
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  //initialization
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}

  //
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

//sin function
class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

//sin function
class NegSquareFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -(arg + 1) * (arg + 1); }
};

class LinearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg - 2.5; }
};

class SegFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) {
    if (arg >= 0) {
      return arg + 1;
    }
    else {
      return arg - 1;
    }
  }
};

class ConstFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -1; }
};

#endif
