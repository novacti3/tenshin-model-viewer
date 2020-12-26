# Tenshin Model Viewer
Tenshin is a program which lets you view a model of your choosing as closely as it'd look on a PS1.

## Features
- Affine texture mapping (WIP)
- Gourard shading (WIP)
- Forward rendering (WIP)

## Supported formats
- OBJ
- GLTF (WIP)

## Cloning
```bash
git clone --recursive https://github.com/novacti3/tenshin-model-viewer "Tenshin"
```

## Build
Requires CMake 3.15 and above (this might change) and a compiler with C++17 support.

Run the `build-release.sh` or `build-debug.sh` based on the configuration you want to build (WIP). The executable will be located in `bin/(config)`