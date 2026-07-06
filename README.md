# 3D ASCII Cube

A rotating 3D cube rendered as ASCII characters directly in the terminal, written from scratch in C++ — no graphics libraries, no external dependencies. Just rotation matrices, perspective projection, and ANSI escape codes.

## How it works

The whole pipeline is a few dozen lines of maths and one framebuffer:

- **Rotation.** Every point on the cube's surface is rotated by three angles (`A`, `B`, `C`) around the x, y, and z axes. Rather than storing a matrix type, the composite rotation matrix `Rx(A)·Ry(B)·Rz(C)` is multiplied out by hand and collapsed into three scalar functions (`cX`, `cY`, `cZ`) — each returns one coordinate of the rotated point. No matrix or quaternion classes needed.
- **Projection.** Each rotated 3D point is flattened to 2D with a perspective divide: the point is pushed away from the camera along the depth axis, then its x and y are divided by that depth. Dividing by depth is what creates perspective — points further away shrink, so the near faces render larger than the far ones.
- **Surface sampling.** Each of the six faces is a flat square, so it's drawn by sweeping two coordinates across the face while pinning the third to `±cubeWidth`. This samples the whole surface rather than just the eight corners, so the faces come out solid. Each face uses a different character so you can tell them apart as the cube turns.
- **Rendering.** Characters are written into a 1D framebuffer, then printed row by row. Each frame redraws in place using ANSI escape codes (`\033[2J` to clear, `\033[H` to home the cursor), with a small sleep between frames to pace the animation.

## Build and run

```bash
# macOS (clang)
clang++ -std=c++17 -O2 cube.cpp -o cube

# Linux (gcc) — std::thread needs -pthread
g++ -std=c++17 -O2 -pthread cube.cpp -o cube

./cube        # Ctrl-C to quit
```

Replace `cube.cpp` with your source filename. Use a terminal window at least **160×40** characters — if the render wraps or looks broken, either enlarge the window or shrink the `width` / `height` constants.

## Configuration

All the knobs live as constants near the top of the file:

| Constant | Effect |
|---|---|
| `cubeWidth` | Half-size of the cube |
| `distFromCam` | How far the cube sits from the camera. Larger = smaller and flatter; smaller = closer with stronger perspective |
| `K1` | Zoom / focal length — how many pixels one unit of projected size maps to |
| `A`, `B`, `C` increments | Per-frame rotation speed around each axis. Slightly different values give a natural tumble |
| Loop step (`0.15`) | Surface sampling density — smaller fills faces more densely but costs more per frame |
| `width`, `height` | Canvas size in characters |

## Possible extensions

- **Depth buffering.** A `zbuffer` is scaffolded but not yet used, so faces are drawn in call order rather than by distance — a back face can occasionally paint over a front face. Storing `1 / depth` per pixel and only overwriting when a point is nearer would give proper hidden-surface removal.
- **Shading.** Ramp the character by depth (e.g. `.:-=+*#@`) to fake lighting instead of one glyph per face.
- **Arbitrary axis, colour, runtime resizing.** Spin around a custom axis, add ANSI colour per face, or adjust size on the fly.

## Acknowledgements

The rotation and projection approach was inspired by Code Fiction's `cube.c` ("ASMR Programming — Spinning Cube"). Built from scratch as a learning project.
