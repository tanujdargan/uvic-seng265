# Lab 9, directory `B`: to dos for `Point` class

Note that `Point` is meant **to be immutable**. This means that any
method which modifies attributes must result in a new instance
of `Point` being created.

1. Add `delta_x` method
    * parameter: `d`
    * behavior: create and return a new point with instance attributes
      of `x + d` and `y`

2. Add `delta_y` method
    * parameter: `d`
    * behavior: create and return a new point with instance attributes
      of `x` and `y + d`

3.  Add `translate` method
    * parameters: `dx` and `dy`
    * behavior: create and return a new point with instance attributes
      of `x + dx` and `y + dy`
