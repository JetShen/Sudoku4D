# Sudoku 4D (2D, 3D, 4D) 

A personal attempt to learn a graphical API like OpenGL or Vulkan while also improving my skills in C programming. This project explores the concept of Sudoku in two, three, and four dimensions, introducing new rules and challenges for the higher-dimensional versions.

**Start Date**: 21/01/25 

---

## Basic Rules of Sudoku

Sudoku is a logic-based number-placement puzzle. The objective is to fill a grid with numbers such that:

1. Each row contains all numbers exactly once.
2. Each column contains all numbers exactly once.
3. Each sub-grid (if applicable) contains all numbers exactly once.

These rules apply to 2D Sudoku and extend in different ways for higher dimensions.

---

## Sudoku 3D

In 3D Sudoku, the puzzle expands into a cube format. Instead of a single 2D grid, we have multiple layers stacked together, forming a cube.

### Rules for 3D Sudoku:
1. Each row, column, and layer must contain all numbers exactly once.
2. Each sub-cube (a 3D equivalent of a sub-grid) must also contain all numbers exactly once.

The challenge lies in visualizing and maintaining consistency across three dimensions.

---

## Sudoku 4D

In 4D Sudoku, the concept extends further, adding a fourth dimension represented by a sequence of interconnected 3D cubes. This introduces new complexities and rules.

### Base Rotation Rule:
When you place a number in a position `(x, y, z)` of Cube A:
- This number affects adjacent positions in the other cubes following a rotational pattern.
- For example, placing a `5` at `(1, 1, 1)` in Cube A:
  - In Cube B: The `5` cannot appear in `(1, 1, 2)`, `(1, 2, 1)`, or `(2, 1, 1)`.
  - In Cube C: The restriction rotates again, following a defined pattern.

### Propagation Patterns:
- Restrictions propagate predictably across the cubes.
- Each subsequent cube follows a rotated restriction pattern.
- This creates a "chain" of restrictions that spans the fourth dimension.

### Verification System:
When placing a number, the following must be validated:
1. **3D Sudoku Rules**: The number must obey the standard 3D Sudoku rules within its own cube.
2. **Rotation Constraints**: The number must respect rotational restrictions in adjacent cubes.
3. **4D Chain Rules**: The number must fit the complete chain of restrictions across all cubes in the fourth dimension.


## Dependencias

- **GLFW**: Download version 3.3.8 from [glfw.org](https://www.glfw.org/download.html) and place it in the folder `/lib/glfw/`.
- **GLAD**: Generates GLAD files in [glad.dav1d.de](https://glad.dav1d.de/) and place them in the folder `/lib/glad/`.

---

Feel free to explore the code, report issues, or contribute improvements.
