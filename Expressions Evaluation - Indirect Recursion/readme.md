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

## Link to problems
