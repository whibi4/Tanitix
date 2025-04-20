
# Tanitix

**Tanitix** is a lightweight simulation tool written in C++ that allows users to draw and animate items using physics-based forces. It uses **GTK** for rendering graphics and includes a custom, easy-to-use syntax for defining simulation elements.

## Features

- 🧲 Physics-based force simulation  
- ✏️ Custom drawing of items (shapes, objects, etc.)  
- 🧩 Simple scripting syntax for defining simulation components  
- 🖼️ GTK-based rendering for smooth visuals  
- ⚙️ Written entirely in C++ for performance and control

## Getting Started

### Prerequisites
- C++17 or later
- GTK 3 (or compatible version)

### Building the Project

Clone the repository and run the following commands:

```bash
make
```

This will:

1. Create a `build` directory (if it doesn’t exist)
2. Run CMake to configure the project
3. Build the executable

### Running Tanitix

After building, you can run the app with:

```bash
make run
```

> ⚠️ Note: Tanitix forces the `GDK_BACKEND` to `x11` when launching. This is to avoid compatibility issues on some systems with Wayland.

### Cleaning the Build

To clean all generated build files:

```bash
make clean
```

## Project Structure

```
.
├── src/           # Source files for Tanitix
├── build/         # Auto-generated build folder (ignored in version control)
├── Makefile       # Simple build script
└── README.md      # Project documentation
```

## Contributing

Contributions are welcome! If you'd like to improve the physics, extend the syntax, or fix bugs, feel free to fork the repo and open a pull request.


## Author

Crafted with ❤️ by Mohamed Ouhibi
