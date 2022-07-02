IMPORTANT NOTE: This project is currently on hold. Maybe not over, but I need to make sure it's actually a design that is worth pursuing. It's also not a project I am currently spending time on. Maybe again some day.

---

# FList

An list implementation loosely based on Python lists for C++. As such, many "Pythonic" conventions were adopted in this implementation (with some necessary changes).

## Initializing an FList

There are two ways to initialize FLists: with assignment and by explicitly calling the constructor. While you *can* use either, using assignment is much neater, clearer, and Pythonic. They do the same thing at the end of the day,

* Empty: `FList<int> foo = {}` or `FList<int> foo = FList<int>()`
* Explicit Value: `FList<int> foo = {1, 2, 3}` or `FList<int> foo = FList<int>({1, 2, 3})`
* Copy: `FList<int> foo = bar` or `FList<int> foo = FList<int>(bar)`

## Adding Values

New values can be added to an FList with the `foo.append()` function. Appended values are stored in a linked list until they are integrated into a contiguous block with `foo.defragment()`. Adding all values of the array with `append()` will lead to O(n) access times, while `defragment()`-ing the array will guarantee O(1) access times.

* Single Values: `foo.append(1)`
* Multiple Values from an FList: `foo.append(bar)`
* Multiple Explicit Values: `foo.append({1, 2, 3}`

## Accessing Values

* Single Value: `foo[0]`
* Index Range: `foo[FRange(0, 100)]` (indexes 0 through 99)
* Index Range (with 'by'): `foo[FRange(0, 100, 2)]` every second element (make negative to reverse the output) (indexes 0 through 99)
* Logically: `foo[bar]` (where `bar` is an `FList<bool>` of length `foo.length()`)

## Modifying Values

* Single Values: `foo[0] = 1` this uses default `T` assignment.
* Remapping: `bar.map(my_map_fn)` where `my_map_fn` takes one `T` argument and returns a `T`, this function will modify each record in-place (guaranteed O(n)).
* Mutating: `FList<bool> foo = bar.for_each(my_mut_fn)` - this works like remapping, except `my_mut_fn` can return any datatype (not just `T`) and a new FList is returned as opposed to being modified in-place.

## Comparing Values

Us the built-in comparison function to generate a new `FList<bool>` containing the element-wise comparisons:

```C++
auto baz = foo.compare(greater_than, bar)
```

You can use this in conjunction with logical indexing to write very concise code, ex.
```C++
auto baz = foo[foo.compare(greater_than, bar)];
```
This snippet assigns all values of `foo` that are greater than `bar` to `baz`.
