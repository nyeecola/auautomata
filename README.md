# Auautomata
A basic Conway's game of life implemented in C++ using FLTK for cross-platform GUI.

### To compile on GNU/Linux:
- Download and install FLTK
- Then, from the root directory of the project, run:

    ```
    make
    ```

### To compile on Windows:
- Download and compile FLTK (requires Visual Studio 2005 or above) and make sure the includes are located on `c:\FLTK\FL\` and the fltk.lib file is on `c:\fltk\lib\fltk.lib`
    
    Also, make sure you compile FLTK with the /MT option. (Otherwise, change the /MT option in the build.bat file to /MDd or whatever you used.)
- Then, from the root directory of the project, run:

    ```
    build
    ```
