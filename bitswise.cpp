// 1)
// Some mathematical properties of bitwise operations:
// (Whenever there is a bitwise mathematical relation given in q, use these to simplify it)
// src -> https://codeforces.com/blog/entry/94470

// a|b = a⊕b + a&b
// a⊕(a&b) = (a|b)⊕b
// b⊕(a&b) = (a|b)⊕a
// (a&b)⊕(a|b) = a⊕b

// Addition:
// a+b = a|b + a&b
// a+b = a⊕b + 2(a&b)

// Subtraction:
// a-b = (a⊕(a&b))-((a|b)⊕a)
// a-b = ((a|b)⊕b)-((a|b)⊕a)
// a-b = (a⊕(a&b))-(b⊕(a&b))
// a-b = ((a|b)⊕b)-(b⊕(a&b))


// 2)
