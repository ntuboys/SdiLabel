# C++ Labelling Program
## Build instructions
### Windows
#### Install Qt
Download [Qt](https://www.qt.io/download-open-source/) installer

During installation select:

Qt -> Qt5.9 -> MingW 5.3.0 32bit
  
Qt -> Tools -> MingW 5.3.0
#### Install CMake
Download [CMake](https://cmake.org/download/) installer

During installation select "Add CMake to the system PATH for all users"
#### Install OpenCV
Download [OpenCV](https://sourceforge.net/projects/opencvlibrary/) installer (make note of where you installed it)
#### Build OpenCV
Add the directory containing MingW ([QtDIR]\Tools\mingw530_32\bin) to your [systems path variable](https://lmgtfy.com/?q=how+to+add+to+path+windows)

Open CMake GUI

In the source code field enter: [OpenCV dir]\sources

In the build field enter where you want OpenCV to be built

Click configure and wait

Enter the following settings:

Specify the generator for this project: MinGW Makefiles

Specify native compilers, next

Compilers C: [QtDIR]\Tools\mingw530_32\bin\gcc.exe

Compilers C++: [QtDIR]\Tools\mingw530_32\bin\g++.exe

Finish

Check the box [X]WITH_QT

Check the box [X]WITH_OPENGL

set Qt5_DIR to [QtDIR]\5.9\mingw53_32\lib\cmake\Qt5

Uncheck the box []ENABLE_PRECOMPILED_HEADERS

Then click configure again

Set QT_MAKE_EXECUTABLE to [QtDIR]\5.9\mingw53_32\bin\qmake.exe

Set Qt5Concurrent_DIR to [QtDIR]\5.9\mingw53_32\lib\cmake\Qt5Concurrent

Set Qt5Core_DIR to [QtDIR]\5.9\mingw53_32\lib\cmake\Qt5Core

Set Qt5Gui_DIR to [QtDIR]\5.9\mingw53_32\lib\cmake\Qt5Gui

Set Qt5Test_DIR to [QtDIR]\5.9\mingw53_32\lib\cmake\Qt5Test

Set Qt5Widgets_DIR to [QtDIR]\5.9\mingw53_32\lib\cmake\Qt5Widgets

Set Qt5OpenGL_DIR to [QtDIR]\5.9\mingw53_32\lib\cmake\Qt5OpenGL

Set CMAKE_BUILD_TYPE to Release 

Set OPENCV_VS_VERSIONINFO_SKIP=1

Then click configure again Then click generate

Go to directory where you built OpenCV

Open terminal

run "mingw32-make -j x" where x is the number of threads your CPU has

run "mingw32-make install"

Add the directory containing OpenCV ([OpenCV build dir]\install\x86\mingw\bin) to your [systems path variable](https://lmgtfy.com/?q=how+to+add+to+path+windows)
#### Build Labels
Edit the win32 section in the SDI.pro file to match your directories

Open terminal in the project directory

Run qmake

Run mingw32-make

Cd to release forlder

run "windeployqt SDI.exe"

Copy libopencv_calib3d430.dll, libopencv_calib3d430.dll, libopencv_features2d430.dll, libopencv_highgui430.dll, libopencv_imgcodecs430.dll, libopencv_imgproc430.dll from the OpenCV folder to the current folder
### Linux
Todo
