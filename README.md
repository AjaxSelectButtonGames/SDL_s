# SDL_s

SDL_s is a small scale scripting language for rapidly building UI for games in SDL2, it's sole purpse is for educational reasons while it could be used for production based products keep in mind that this is a WIP project and will be updated as much as possible. 

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

SDL_s was designed to be a rapid prototype UI design without having to change game/program code while using SDL2. 

## Features

- [Features]
- [Button Calls]
- [Text box calls]
- [Label calls]
- [Function design calls]

## Installation
Currently you can clone this repository to test and compile it based on your needs or run the demo make sure to change where SDL.h and all it's dependant libraries are found you will need 

SDL2
SDL_ttf
SDL_Image

Make sure if you are using the demo you make a script in notepad or another text editor called 1.sdl_s an place it in a folder in the directory called scripts/ or it will not work. 

## License
This project is licensed under the MIT License 

## Usage 
```
main start 
{
     // can define a variable such as BUTTON, LABLE, TEXTBOX or can call a function(not fully implemented yet but WIP)
}

```

The script has to have a main start or the code will not work, each line that is not the call of a function or main start MUST end in a ; spacing must be taken when using the LEFT_PARN and the RIGHT_PARN ( ) if this not being done you will end in a error and the code will not work. 

While mouse clicks are being called they are currently not being called to anything yet so this will cause a crash as of right now. 

Function declartion 
```
function functionname
{
     // can define a variable such as BUTTON, LABLE, TEXTBOX
}
```

main start and function must start and end with a { } without them the parser will not completely parse the script and errors can be run into. 

## Contributing
If you want to contribute to this project feel free to fork it and make your additions or changes. 

-If you find any issues or bugs please report them to me either here in Github, discord or my email tivoilos@hotmail.com 

**If you don't like how I coded this please feel free to code a scripting language on your own and make it better(I say this with all love no hate but things can always be better and unless we learn and help each other we will never get better)** =)
