# Cub3D

Cub3D is a small first-person 3D engine written in C as a group project for the
42 curriculum. Inspired by early raycasting games such as Wolfenstein 3D, it
renders a navigable world from a two-dimensional map using MiniLibX.

The project combines real-time rendering, collision detection, input handling,
configuration parsing, and map validation without relying on a game engine.

## Contributions

- `efittant` — execution: raycasting, rendering, player movement, collision
  detection, keyboard handling, and the game loop
- `nrumpfhu` — parsing: `.cub` file parsing, texture and color configuration,
  map loading, and validation

## Features

- DDA-based raycasting with textured walls
- Different textures for north, south, east, and west walls
- Configurable floor and ceiling colors
- Smooth movement, strafing, and camera rotation
- Collision detection against map walls
- Validation of map boundaries, player placement, textures, and RGB values
- Continuous keyboard input for responsive controls

## Build

The project targets Linux and requires a C compiler, `make`, X11, Xext, and
zlib. On Debian or Ubuntu:

```sh
sudo apt install build-essential libx11-dev libxext-dev zlib1g-dev
```

Build the executable with:

```sh
make
```

## Run

Pass a valid `.cub` scene file to the program:

```sh
./cub3D maps/good.cub
```

Controls:

- `W` / `S` — move forward and backward
- `A` / `D` — strafe left and right
- Left / Right arrows — rotate the camera
- `Esc` — exit

## Assets

The texture artwork used by the project was AI-generated with ChatGPT and then
converted to XPM format for use with MiniLibX. The game engine, rendering code,
movement system, and parser were implemented by the project team.
