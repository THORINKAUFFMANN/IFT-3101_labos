# OpenGL Circle Application

This project is a simple OpenGL application that creates a window and draws a circle using OpenGL commands. It serves as a basic example of using OpenGL for rendering graphics in a C++ application.

## Project Structure

```
opengl-circle-app
├── src
│   ├── main.cpp         # Entry point of the application
│   ├── ellipse.cpp     # Implementation of the Ellipse class
│   ├── ellipse.h       # Declaration of the Ellipse class
│   └── window.h         # Declaration of the Window class
├── CMakeLists.txt       # CMake configuration file
└── README.md            # Project documentation
```

## Requirements

- C++11 or higher
- OpenGL
- GLFW (for window management)
- GLEW (for managing OpenGL extensions)

## Building the Project

1. Clone the repository or download the project files.
2. Navigate to the project directory:
   ```
   cd opengl-circle-app
   ```
3. Create a build directory:
   ```
   mkdir build
   cd build
   ```
4. Run CMake to configure the project:
   ```
   cmake ..
   ```
5. Build the project:
   ```
   make
   ```

## Running the Application

After building the project, you can run the application with the following command:

```
./opengl-circle-app
```

This will open a window and render a circle in the center of the screen.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.