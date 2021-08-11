# FList

An list implementation loosely based on Python lists for C++. As such, many "Pythonic" conventions were adopted in this implementation (with some necessary changes).

## Initializing an FList

There are two ways to initialize FLists: with assignment and by explicitly calling the constructor. While you *can* use either, using assignment is much neater, clearer, and Pythonic. They do the same thing at the end of the day,

* Empty: `FList<int> foo = {};` or `FList<int> foo = FList<int>();`
* Explicit Value: `FList<int> foo = {1, 2, 3};` or `FList<int> foo = FList<int>({1, 2, 3});`
* Copy: `FList<int> foo = bar;` or `FList<int> foo = FList<int>(bar);`

## Accessing Values

* Single Value: `foo[0]`
* Index Range: `foo[FRange(0, 3)]` (indexes 0 through 2)
* Logically: `foo[bar]` (where `bar` is an `FList<bool>` of length `foo.length()`)

## Modifying Values

* Single Values: `foo[0] = 1` this uses default `T` assignment.
* Remapping: `bar.map(my_map_fn)` where `my_map_fn` takes one `T` argument and returns a `T`, this function will modify each record in-place (guaranteed O(n)).
* Mutating: `FList<bool> foo = bar.mutate(my_mut_fn)` - this works like remapping, except `my_mut_fn` can return any datatype (not just `T`) and a new FList is returned as opposed to being modified in-place.

## Comparing Values

FLists support all common comparisons (<, >, <=, >=, !=, ==) for both comparing two FLists element-wise, and comparing an FList to a single `T` value. The result of such a comparison is an `FList<bool>` that contains either true or false for each test.
