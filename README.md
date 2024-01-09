# easy_compiler

This is a toy exercise for practising compilation techniques.

Current support:
* Lexical Analysis

## Get Started
``` bash
mkdir build && cd build
cmake ..
make -j
```

## Test Cases
Todo

## Characteristic
### Front-end Language

1. **No need** to concern the type systems, e.g. it only has two types, numbers (floating-point) and strings.
2. Define a variable by the `let` keyword, which cannot be assigned twice, like functional language. E.g. `let x = 10`, `let str = "hi"`.
3. the lifetime of a variable is defined by `{` and `}`. **Release immediately after leaving the lifetime**, that is, the life cycle of the variable is not allowed to span `}`. 
4. Functions are defined by the `def` keyword. **Function parameters and return values do not specify parameter types**, so **function overloading** and other features related to function parameter types are not supported.
5. ……

### Optimization
Todo

## Docs
Todo
