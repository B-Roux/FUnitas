# FList

A dynamically allocated list template that allows for convenient editing, access and implementation. Loosely based on Python lists.

## General Notes

* if a name begins with a dash (ex. `_export_array()`) then it is for internal use and not meant to be used by the caller.
* If a name ends with a dash (ex. `start_`) then it is fine to use, but was named differently for a reason not important to the caller.

## Getting Started

How to initialize an FArray:

* Create an empty FList: `auto foo = FList<Bar>()`
* From a dynamically allocated array: `auto foo = FList<Bar>(my_bar_array, my_bar_array_length)`<sup>1</sup>
* From an existing FList (deep copy): `auto foo = FList<Bar>(my_bar)`

How to add data to an FList:

* Individual datum: `foo.append(bmy_ar)`<sup>2</sup>
* From a dynamically allocated array: `foo._integrate_array(my_bar_array, my_bar_array_length)`<sup>1</sup>
* From an existing FList: `foo.append(my_bar_FList)`

How to get data from an FList:

* Individual datum by index: `foo[i]`
* Range of data by index: `foo[FRange(start_index, end_index)` -- note that an FRange(i,j) refers to indices i, i+1, ..., j-1
* Logically: `foo[my_bool_FList]` -- will return all foo[i] where my_bool_FList[i] == true
* As a dynamically allocated array: `foo._export_array()`<sup>3</sup>

Defined operators:

* Basic conditionals (<, >, <=, >=, ==, !=): `foo > bar` -- will return an FList<bool> with true where foo > bar and false where not
* Basic conditionals with individual operands: `foo > 5` -- will return an FList<bool> with true where foo > 5 and false where not
* Indexing (subscript): see section above
* Assignment (=): `foo = bar` -- will delete and free the contents of foo and obtain a deep copy of bar
* Stream insertion (<<): `std::cout << foo << std::endl` -- will insert foo into the string into the cout stream, in the format "[ firstItem, secondItem, ..., lastItem]"
  
Other useful tools:
  
* `foo.length()` will return the total length of the list
* if `DEBUG_MODE` is defined, then `foo.print_structure()` will print a more detailed view of the internal structurem, including data block granularity. This will only work for the top-level FList, nested FLists will print normally.

## Footnotes

1. Meant for internal use. Be aware that the array is not copied, and the FList must become responsible for the allocation. Incorrect use may lead to memory leaks or read access violations.
2. Adding individual items may slow the performance of subsequent operations. If many individual items need to be added, consider making a temporary FList to store them before appending that FList to the main one. (Appending an FList automatically reallocates it into a contiguous data block for efficiency.)
3. Meant for internal use. Be aware that the array is newly created, and that the caller must become responsible for the allocation. Incorrect use may lead to memory leaks or read access violations. Use in conjunction with the foo.length() method.
