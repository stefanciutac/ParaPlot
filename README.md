# ParaPlot Documentation - v0.0.1 (Pre-release)
## Description
ParaPlot is a parametric data visualisation library that allows for real-time variable adjustment and animation macros. [WIP: NO STABLE RELEASE YET]

**NOTE: As this is far from a stable release, if you wish to try ParaPlot for yourself, I would recommend you compile and run the example project as-is; there is a significant risk that following the documentation below to create custom interactive plots may simply not work. Please let me know of any bugs (or errors in the documentation) you encounter if you do decide to follow the documentation below anyway.**

## TL;DR
- Implement your function/algorithm/simulation in `evaluate_point` in `System.cpp`
- Declare and initialise an instance of `Plot` in `main.cpp`, by calling the constructor defined in `Plot.h`
- Call `plot_graph()` in `main.cpp`
- Compile and run
## Dependencies/Prerequisites
- `raylib.h`
- a `c++` compiler
- `CMake` (at least version 4.2)
## Defining a Plot
To create a plot, first open the file named `System.cpp`. This file contains the implementation of both relevant methods of the `System` class: the constructor `Plot` and the system definition `evaluate_point`—the third implementation, `evaluate_points`, is just a wrapper.

You will notice that there is a comment and some example code in the otherwise empty `evaluate_point` that says, "your code goes here". Delete this code (or, if you so wish, comment it out) and write the implementation of your function or algorithm in its place. The return type of `evaluate_points` is `std::vector<Point>`: a vector of instances of the `Point` struct.

The `Point` struct definition can be found, predictably, in `Structs.h`. If opening `Structs.h` is too much effort for you, the definition of `Point` is as follows:

```cpp
struct Point
{
    std::vector<double> dims;  // dimensions
};
```

Although `Point` can store objects of arbitrary dimensionality, only two of these may be plotted at once.

## Initialising a Plot
A single instance of the `Plot` class should be initialised in `main`, by calling the constructor—the definition of which is in `Plot.h`, as well as here:
```cpp
Plot(const std::vector<Variable>& variables);
```
The struct `Variable` is defined in `Structs.h` and below:
```cpp
struct Variable
{
    double value;
    double lbound;  // lower bound, inclusive
    double ubound;  // upper bound, exclusive
    std::string name;
    Color colour;
};
```
Scroll to the bottom of https://www.raylib.com/cheatsheet/cheatsheet.html (Raylib documentation) or look below for the definition of `Color`:
```cpp
// Color, 4 components, R8G8B8A8 (32bit)
typedef struct Color {
    unsigned char r;        // Color red value
    unsigned char g;        // Color green value
    unsigned char b;        // Color blue value
    unsigned char a;        // Color alpha value
} Color;
```

### `std::vector<Variable> variables`
The `Variable`s you pass to the constructor in `main` are used to initialise the instance of `System` in `Plot`, so the `std::vector<Variable> variables` can be accessed from `evaluate_point` as a member variable of `System`. Make sure that the **y-coordinate variable goes last** (so it is the final element of the vector passed to the constructor).

### `int x_index`
This is the index of the variable that is to be on the x-axis. There is no y_index, because, once again, the y-coordinate variable must go last.

### `double step`
This is the size of the increments into which the x-axis is subdivided, in the same unit as your x-variable; the function you have implemented (`evaluate_point`) will be called for every multiple of `step`, between the `lbound` (lower bound) and `ubound` (upper bound) of the variable in `variables` at index `x_index`.

### `int window_width`
The width (horizontal length, in pixels) of the ParaPlot window. Window resizing during runtime has not been implemented as of now.

### `int window_height`
The height (vertical length, in pixels) of the ParaPlot window. Window resizing during runtime has not been implemented as of now.

### `int fps`
The FPS at which the ParaPlot window will run; the number of frames that will be rendered each second.

### `double x_grid_interval`
The interval, in the same unit as the x-axis variable, along the x-axis, at which vertical grid lines and ticks will be rendered; one vertical grid line and tick will be rendered at each multiple of `x_grid_interval` along the x-axis.

### `double y_grid_interval`
The interval, in the same unit as the y-axis variable, along the y-axis, at which horizontal grid lines and ticks will be rendered; one horizontal grid line and tick will be rendered at each multiple of `y_grid_interval` along the y-axis.

**NOTE: More comprehensive documentation will be published in due course, and this documentation will be updated along when a change to the codebase necessitates it.**