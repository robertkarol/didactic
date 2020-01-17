# Expressions Evaluation

## Expressions representation
### Mathematical representation
What is an expression? Well, matematicians and [Wikipedia](https://en.wikipedia.org/wiki/Expression_(mathematics)) would say:
> In mathematics, an expression or mathematical expression is a finite combination of symbols that is well-formed according to rules that depend on the context. Mathematical symbols can designate numbers (constants), variables, operations, functions, brackets, punctuation, and grouping to help determine order of operations, and other aspects of logical syntax.

In a more [siplified math](https://www.mathsisfun.com/definitions/expression.html) language and with less things to worry about, it can be defined as:
> Numbers, symbols and operators (such as + and ×) grouped together that show the value of something.

Greater, huh? Now back to computers...
### Computer science representation
Well, let's see an example, not just story telling:

![expression](https://www5a.wolframalpha.com/Calculate/MSP/MSP38911c1d583ahcd0b9cd0000387acbfdc7g5biai?MSPStoreType=image/gif&s=21)

Computers don't like this, so we'll translate it for it: `(1+1)*13+10/2`

Is this enough? Not really. Computers just do `01010111001111` until it gets the value (31 here). So, here come the programming languages to help. A programming language is capable of translating such expression into a pretty abstractization of `01010111001111`, called [assembly language](https://en.wikipedia.org/wiki/Assembly_language) and directly mapped to binary representation. We'll study this in C++, so we'll call this process *compilation*.

Now comes the question: *How does the compiler handle this `(1+1)*13+10/2`?*. Briefly and beyond the scope of this lesson, it uses the [reversed polish notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation) for its algorithm. It has many advantages, but it's not our goal for now.

So let's focus on what we want to do and what do we need for that. In this thing that we called *expression*, as we learned in priamry school, we can spot some key aspects that will lead to the solution we want for now: we see some operators (`+`, `/`, `*`), some operands (`1`, `13`, `10`, `2`) and some paranthesis. Each operator has an *arity* (how many operators it requires) and a *priority* (who gets evaluated first). Here we have only binary operators and among them `*` and `/` have higher priority than `+`. Unless there are parathesis, which get evaluated prior to respecting these priorities. Operators of the same priority gen evaluated by "who's the first".

This being told, the step by step evaluation of `(1+1)*13+10/2` would be:

(1+1)\*13+10/2 -> 2\*13+10/2 -> 26+10/2 -> 26+5 -> 31

## Indirect recursion
We already know that if we have a function 

```
void func1()
{
  /*
  do whatever
  */
  func1();
}
```

Then the fact that `func1` calls itself within its body is making us characterize `func1` as *recursive function*. We already know many useful usage, like Fibonacci, Backtracking, Divide and Conquer an so on. But what if we have

```
void func1()
{
  /*
  do whatever
  */
  func2();
}

void func2()
{
  /*
  do whatever
  */
  func1();
}
```

This can't be classified as recursion based on the definition we knew. So, we'll extend the previous definition and state that what we called recursion it's actually, *direct recursion* (because func1 directly calles itself). Let's continue with this "weird" code. We see that there is a "ping-pong" game between them, ecah passing the control to each other. This is called *indirect rescursion*. That's because `func1` passes the control to `func2`, which passes it back to `func1`. So, here we have a recursion, but with the help of an intermediate.

## Algorithm for evaluating an expression using indirect recursion
First things first, we must keep in mind that arithmetic expressions are __not the only expressions that can be evaluated with this technique__. So, I'll state a general algorithm that can be used as a start template for any problem of this kind, with examples for the arithmetic ones. A trivial assumption will be made: operators have an arity of at least 1. Each processing will consume characters corresponding to their purpose.

A general algorithm would be:
1. Identify all the operators that may be in the expression. Let's call it the *set of operators*.
2. Separate the set of operators into subsets based on priority. Each subset will have a priority between 1 and N, where N is the number of subsets we created, 1 is the highest priority and N is the lowest priority.
3. For each subset, create a function. Continuously look for the operators in the subset and try to aquire the operands. For each operator having a priotity of K (K > 1), operands will be results of calling the function having the priority K-1. The number of calls will correspond with the arity of the operator.
4. Create a top level function called `evaluate` that will call the lowest priority function and will return the result.
5. Identify the possible domain of representation for the operand. Create a function that is responsible of "extracting" an operand for us. Let's call it `value`.
6. Create a function that will abstractize the value extraction, called `operand`. If there are paranthesis allowed in the expression, handle this case here. If there is an opening paranthesis is found, call the top level evaluation function.
7. The the highest priority function will call the `operand` function instead of calling a higher priority function, as explained in step 3.

For arithmetic expression calculation, it will pe particulary like this:
- Separate the set of operators into 2 subsets `{+, -}` and `{*, /}` and create 2 functions: `ADD_SUBSTRACT` and `MULTIPLY_DIVIDE`
- Since all are binary operators having an operand to the right and the other to the left.  
- In `ADD_SUBSTRACT` we'll call `MULTIPLY_DIVIDE` to "hand over" the evaluation and use it's result as the left operand. We'll continuously look for either `+` or `-` as long we find one, consume it (a.k.a "move" the pointer to escape it), get the right operand by calling `MULTIPLY_DIVIDE` and compute the result. The continuous look-up is required for cases such `1+2+3` (chained operations).
- Define the top level function `evaluate` that will call `ADD_SUBSTRACT` and return its result.
- Define the `value` function that will get the first number in the current state of expression.
- Define the `operand` function that will check if the current character in the expression is a `(`. If so, if will consume it and call `evaluate` to get the result of the inner expression, consume the remaining `)` and return the result.
- In `MULTIPLY_DIVIDE` we proceed in a way similar to `ADD_SUBSTRACT`. The difference is that in this case, this is the highest priority function, so that it will have to call `operand` function the way we used to call this function in `ADD_SUBSTRACT`.
- Read an expression and call `evaluate` on it. 

A source implementing the solution explained can be found [here](https://github.com/robertkarol/didactic/blob/master/Expressions%20Evaluation%20-%20Indirect%20Recursion/EvalExpr.cpp)

## Link to problems
