# math_equations

Сlasses for calculating simple arithmetic expressions. The `Expression` class is a node of the computation tree and has three heirs: `Val`, `Add`, and `Mul`. 

```
Expression const* val = new Add(new Val(10), new Val(20));

assert(printToString(val), "(10 + 20)");


Expression* sum = new Add(new Val(20), new Val(30));
Expression const* mul = new Mul(new Val(10), sum);

assert(printToString(mul), "10 * (20 + 30)");
```

The `Var` class is also implemented, a variable that is a descendant of `Expression` and has a constructor from `std::string` (variable name). The class `Context`, is designed to store the values of named variables. This class has methods for exposing and retrieving variable values, as well as for checking if they are exposed.  An object of this class gets the `eval` method of the `expression` class in order to calculate the value of the expression given the context. 

```
Expression* sum = new Add(new Val(2), new Var("x"));
Expression* mul = new Mul(sum, new Var("x"));

assert(printToString(mul), "(2 + x) * x");

Context ctx;
ctx.setVar("x", 10);

assert(mul->eval(ctx), 120);
```

Additionally added to `Expression` is the `simplified` method, which takes the context and returns a new `Expression`:

```
(1 + 2 * x).simplified({x = 2}) => 5
(1 + 2 * x).simplified({}) => 1 + 2 * x
(x + 2 * y).simplified({x = 2, y = 5}) => 12
(x * 2 + y * 3).simplified({x = 3}) => 6 + y * 3
(x * 2 + y * x).simplified({y = -5}) => x * 2 - 5 * x
```