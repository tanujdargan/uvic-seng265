# Lab 9, directory `C`: to dos for `Circle` class

1. Copy over your `B/geometry.txt` into this directory.

2. Create a `circle` class.
    * instance variable: `center` (i.e., a `Point` instance)
    * instance variable: `radius`
    * Write a an appropriate constructor based on what you
      learn from the `test_geometry.text` doctest.
    * Note that this doctest builds on from the previous one
      from task/directory `B`.

Note that `Circle` (like `Point`) is meant **to be immutable**. This
means that any method which modifies attributes must result in a new
instance of `Circle` being created.

3. Add a `__repr__` method
    * Use doctest contents to determine what this should be.

4. Add `area` method
    * no parameters
    * behavior: compute area of circle using an appropriate
      formula (and import the `math` module if that will help).

5. Add `perimeter` method
    * no parameters
    * behavior: compute perimeter of circle using an appropriate
      formula (and import that `math` module if that will help).

6.  Add `translate` method
    * parameters: `dx` and `dy`
    * behavior: creates and returns a new `circle` instance whose
      center is at the point obtained by modifying the centre
      of the original object by `dx` and `dy`.
