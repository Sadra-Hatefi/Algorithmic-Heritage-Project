## Correctness of bitonic sort

In this section, we will prove the correctness of bitonic sort.

We first need to prove the following proposition.

### Proposition

Let $A$ be a bitonic sequence of $2n$ elements. Let

$$
L=(\ell_1,\ell_2,\ldots,\ell_n),\qquad
H=(h_1,h_2,\ldots,h_n),
$$

where

$$
\ell_i = \min(a_i, a_{n+i})
$$

and

$$
h_i = \max(a_i, a_{n+i}).
$$

Then:

1. $L$ and $H$ are bitonic sequences.
2. $\max(L) \leq \min(H)$, i.e. every element of $L$ is smaller than or equal to every element of $H$.

### Proof

Since $A$ is bitonic, we can , if necessary, reverse its order so that it has the following form (This does not affect the proposition as reversing A reverses L and H and the reverse of a bitonic sequence is bitonic. Futhermore, it does not change the minimum or maximum of L and H, and hence the second part of the proposition is not affected):

$$
a_1 \leq a_2 \leq \cdots \leq a_j
\geq a_{} \geq \cdots \geq a_{}
$$

for some $j$ satisfying:

$$
n < j \leq 2n.
$$

#### Case 1: $a_n \leq a_{2n}$

Since the sequence is increasing up to position $j$, and $n < j$, we have:

$$
a_i \leq a_n, \qquad 1 \leq i \leq n.
$$

Furthermore, since all the elements from $j$ to $2n-1$ are greater than or equal to $a_{2n}$, and $a_n \leq a_{2n}$, we have:

$$
a_i \leq a_n \leq a_{n+i}
$$

for every $1 \leq i \leq n$.

Consequently,

$$
\ell_i = a_i
$$

and

$$
h_i = a_{n+i}.
$$

Thus,

$$
L = [a_1, a_2, \ldots, a_n]
$$

and

$$
H = [a_{n+1}, a_{n+2}, \ldots, a_{2n}].
$$

$L$ is a monotonically increasing sequence and hence it is bitonic. $H$ is also bitonic as it contains the element at position $j$, which is the maximum, increasing before $a_j$ and decreasing afterwards.

Finally,

$$
\max(L) = a_n
$$

and, as $a_n \leq a_{i+n}$,

$$
\min(H) \geq a_n.
$$

Therefore,

$$
\boxed{\max(L) \leq \min(H)}
$$

Both properties hold in this case.

#### Case 2: $a_n > a_{2n}$

We now consider the situation where the last element of the sequence is smaller than the element at position $n$.

Since the sequence increases up to position $j$ and decreases afterwards and $j > n$, the sequence

$$
a_{j-n}, a_{j-n+1}, \ldots, a_n
$$

is monotonically increasing, while

$$
a_j, a_{j+1}, \ldots, a_{2n}
$$

is monotonically decreasing.

Furthermore:

$$
a_{j-n} \leq a_j
$$

as $j$ is the maximum, and

$$
a_n > a_{2n}.
$$

by assumption

Consequently, there must exist an index $k$, with $j \leq k < 2n$, such that:

$$
\boxed{a_{k-n} \leq a_k}
$$

but:

$$
\boxed{a_{k-n+1} > a_{k+1}}.
$$

Intuitively, we are comparing elements at a distance of $n$, and since $a_n > a_{2n}$, there must be a point, which we denote by $k$, where the elements at an earlier position change from being smaller than the corresponding elements at a later position to being greater.

For $1 \leq i \leq k-n$, as the sequence is monotonically increasing, we have:

$$
a_i \leq a_{n+i}.
$$

For $k-n < i \leq n$, as the sequence is monotonically decreasing, we have:

$$
a_i > a_{n+i}.
$$

Therefore, the elements of $L$ and $H$ can be expressed as:

$$
L = [a_1, \ldots, a_{k-n}, a_{k+1}, \ldots, a_{2n}]
$$

and

$$
H = [a_{k-n+1}, \ldots, a_n, a_{n+1}, \ldots, a_k].
$$

Now we prove that both sequences are bitonic.

For $L$, we observe that:

- The sequence $a_1, \ldots, a_{k-n}$ is monotonically increasing.
- The sequence $a_{k+1}, \ldots, a_{2n}$ is monotonically decreasing.

Their concatenation is therefore bitonic.

For $H$, observe that:

- The sequence $a_{k-n+1}, \ldots, a_n$ is monotonically increasing.
- The sequence $a_{n+1}, \ldots, a_k$ increases up to position $j$ and then decreases.
- Also, $a_n \leq a_{n+1}$, since the original sequence is increasing up to position $j$ and $j > n$.

Therefore, $H$ is also bitonic.

Finally, we prove that every element of $L$ is smaller than or equal to every element of $H$.

From the structures, the maximum of $L$ must be one of the elements at the boundary between its increasing and decreasing parts:

$$
\max(L) = \max(a_{k-n}, a_{k+1}).
$$

and the minimum of $H$ must be one of the two elements at either end of the sequence:

$$
\min(H) = \min(a_{k-n+1}, a_k).
$$

Please recall that we established:

$$
a_{k-n}\leq a_k
$$

and

$$
a_{k-n+1}>a_{k+1}.
$$

Moreover, since the original sequence is increasing before position $j$ and decreasing afterwards:

$$
a_{k-n}\leq a_{k-n+1}
$$

and

$$
a_{k+1}\leq a_k.
$$

Combining these inequalities, we obtain:

$$
\max(a_{k-n},a_{k+1})
\leq
\min(a_k,a_{k-n+1}).
$$

Therefore:

$$
\boxed{\max(L)\leq\min(H)}
$$

Both properties hold in this case as well.

#### Conclusion

Since the two possible cases cover all possibilities for the relationship between $a_n$ and $a_{2n}$, we have established that:

$$
\boxed{L\text{ and }H\text{ are bitonic sequences}}
$$

and

$$
\boxed{\max(L)\leq\min(H)}.
$$

This completes the proof. $\square$


## Correctness of the bitonic merger

Now we need to prove the correctness of the bitonic merger; this can be done by mathematical induction.

### Proof of the correctness of the bitonic merger

In the following proof, we use another interpretation of the bitonic merger which is viewing it as a recursive procedure. Given a bitonic sequence of length $x$, we first compare elements at a distance of $x/2$, placing the smaller elements in the first half and the larger elements in the second half (for ascending order). This produces two smaller subsequences which by our proposition, are bitonic. The same procedure is then recursively applied to each subsequence until each subsequence contains only one element. (Please note that we are not splitting the sequence at each step, we are just viewing the subsequences within that sequence, so there is no need for a concatenation step.)

We want to prove that the bitonic merger correctly sorts any bitonic sequence of length $n=2^p$ in ascending order. We prove this for sorting in ascending order, the proof for the descending order is analogous.

We use mathematical induction on $p$.

#### Base case

Consider a bitonic sequence containing only one element:

$$
A=[a_1]
$$

Since the sequence contains only one element, it is already sorted. Therefore, the bitonic merger is correct for $n=1$.

#### Inductive hypothesis

Assume that the bitonic merger correctly sorts every bitonic sequence containing $2^{p-1}$ elements.

#### Inductive step

We now consider a bitonic sequence $A$ containing $2^p$ elements.

The first stage of the bitonic merger consists of comparing elements at a distance of $n/2$, where $n=2^p$. This produces two subsequences:

$$
L=[\min(a_1,a_{n/2+1}),\ldots,
\min(a_{n/2},a_n)]
$$

$$
H=[\max(a_1,a_{n/2+1}),\ldots,
\max(a_{n/2},a_n)]
$$

According to the proposition proved previously, these two subsequences have the following properties:

1. Both $L$ and $H$ are bitonic sequences.
2. Every element of $L$ is smaller than or equal to every element of $H$, meaning that:

   $$
   \max(L)\leq\min(H)
   $$

Both subsequences are bitonic and contain $2^{p-1}$ elements, by the inductive hypothesis, the bitonic merger correctly sorts the subsequences into ascending order.

We consequently obtain:

$$
L_{\text{sorted}}=[l_1,l_2,\ldots,l_{n/2}]
$$

and

$$
H_{\text{sorted}}=[h_1,h_2,\ldots,h_{n/2}]
$$

Furthermore, since every element of $L$ is smaller than or equal to every element of $H$, sorting the two subsequences does not change this property. Thus:

$$
l_{n/2}\leq h_1
$$

Since both subsequences are individually sorted, and the largest element of $L_{\text{sorted}}$ is smaller than or equal to the smallest element of $H_{\text{sorted}}$, $A$ being their concatenation is also sorted:

$$
\boxed{
A = [l_1,\ldots,l_{n/2},h_1,\ldots,h_{n/2}]
}
$$

Therefore, the bitonic merger correctly sorts a bitonic sequence containing $2^p$ elements, provided that it correctly sorts bitonic sequences containing $2^{p-1}$ elements.

Hence, the bitonic merger correctly sorts every bitonic sequence whose length is a power of two by mathematical induction. $\square$



### Connection to the complete bitonic sort algorithm

After establishing the correctness of the bitonic merger, we can prove the correctness of the complete bitonic sort algorithm.

1. Initially, the algorithm creates sorted sequences of length 2 using ascending or descending comparators.
2. Two adjacent sorted sequences are combined, with one reversed, to form a bitonic sequence.
3. The bitonic merger correctly sorts this sequence, as established by the preceding proof.
4. Consequently, the resulting sequence is sorted and contains all the elements of the original two sequences.
5. Repeating this process produces increasingly larger sorted sequences until the entire input is sorted.

Thus, since every bitonic merging operation is correct, and the algorithm repeatedly applies these operations to combine sorted sequences, the complete bitonic sort algorithm correctly sorts any input sequence whose length is a power of two.