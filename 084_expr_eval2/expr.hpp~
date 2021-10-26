#include <cstdlib>
#include <iostream>
#include <sstream>
//#include <string>

class Expression {
 public:
  //toString
  virtual std::string toString() const = 0;
  //evaluate the expression
  virtual long evaluate() const = 0;
  //destructor
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 protected:
  long value;

 public:
  //build up a constructor
  NumExpression(long val) : value(val) {}
  //evalue the expression
  virtual long evaluate() const { return value; }
  //toString
  virtual std::string toString() const {
    std::ostringstream os;
    os << value;
    //std::string res = std::to_string(value);
    return os.str();
  }
  //destructor
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 protected:
  Expression * left;
  Expression * right;

 public:
  //constructor
  PlusExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  //evalute
  virtual long evaluate() const { return left->evaluate() + right->evaluate(); }
  //toString
  virtual std::string toString() const {
    std::string res = "(" + left->toString() + " + " + right->toString() + ")";
    return res;
  }

  //destructor
  virtual ~PlusExpression() {
    delete left;
    delete right;
  }
};
