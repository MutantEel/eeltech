Eel Tech
===

Eel tech is a component based framework for creating games. Eel Tech is targeting OS X, Linux and Windows operating systems however right now only OS X has projnect files and support. Once the base of the Framework is complete Linux (Makefile) and Windows (VS) projects will be created.


### Current Features
- Component Based Architecure (Artemis) with added support for serialization to Json.
- Windowing System (glfw)
- Input System (glfw) mouse, keyboard and joystick/gamepad
- Comprehensive math library (glm)
- Basic graphics data types, Shaders, vbo, vao, textures (SOIL) etc
- Basic file system that handles loading file from multiple root paths and archive files (physfs)


### Compiling
Eel Tech consists of multiple library and repositories. I've seperated out each library into it's own repository so you will need to clone the following repositories into the same folder
- Artemis-cpp ( https://github.com/MutantEel/Artemis-Cpp )
- glfw-eeltech ( https://github.com/MutantEel/glfw-eeltech )
- glew-eeltech ( https://github.com/MutantEel/glew-eeltech )
- glm-eeltech ( https://github.com/MutantEel/glm-eeltech )
- soil-eeltech ( https://github.com/MutantEel/soil-eeltech )
- physfs-eeltech ( https://github.com/MutantEel/physfs-eeltech )
- eeltech ( https://github.com/MutantEel/eeltech )

The console commands would be:

```Shell
mkdir eeltech
cd eeltech
git clone git@github.com:MutantEel/Artemis-Cpp.git
git clone git@github.com:MutantEel/glfw-eeltech.git
git clone git@github.com:MutantEel/glew-eeltech.git
git clone git@github.com:MutantEel/glm-eeltech.git
git clone git@github.com:MutantEel/soil-eeltech.git
git clone git@github.com:MutantEel/physfs-eeltech.git
git clone git@github.com:MutantEel/eeltech.git
```

The main eeltech project is located in:
eeltech/projects/mac/EelTech.xcodeproj

and the test/demo project is in:
eeltech/projects/mac/EelTechTest.xcodeproj


### License

Copyright (c) 2013, Mutant Eel
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Mutant Eel nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MUTANT EEL BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
