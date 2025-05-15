# Software Engineer (C++) – Technical Task – Artifex Mundi

## TestGame
TestGame is a simple clone of the iconic Flappy Bird.
Your mission? Navigate a brave little bird through an endless series of pipes without crashing into anything. The goal is to stay airborne for as long as possible, avoiding the ground, ceiling, and pipes. One wrong move—and it's game over.

### 🛠️ The Task
Our humble little game has a few… quirks that need fixing. Here’s what’s currently broken:
* The game doesn’t compile out of the box.
* Points stop adding up after the first obstacle.
* For some reason, the bird flies straight through the floor. That’s not ideal.
* The bird animation is choppy and not smooth.
* Pipes mysteriously disappear after a while.
* Unlike the original, the bird doesn’t rotate when it moves.

But wait—there’s more!
Our game designer came by with some exciting feature requests:
* Collectible Coins – Randomly scattered between obstacles, but always placed so that players actually have a fair chance to grab them.
* Varied Pipe Spacing – Right now all pipes are evenly spaced on the X-axis. That’s boring. Let’s spice it up with some randomness.
* New Obstacle Type – A special pipe composed of three segments with two gaps for the bird to pass through. This obstacle should appear randomly, with a maximum probability of 20%.
Choose ONE feature, You like the most, and add it into the game.

### 🚀 What You’re Starting With
* A basic game skeleton written using SDL 3
* CMake build scripts
* Starter graphics and assets

### 📦 Submission
Please send us a .zip file containing all source code and graphic assets. We should be able to build it on a Windows machine without jumping through too many hoops.
If you have any thoughts, challenges, or notes you'd like to share, feel free to include them in a separate README_reviewers.md file.

Good luck—and have fun!


## Solution is based on SDL3 App From Source Minimal Example
This is a minimal example for building and using SDL3, SDL_Mixer, SDL_Image, and SDL_ttf_ from source 
using C++ and CMake. It also demonstrates setting up things like macOS/iOS
bundles.
 

### Building And Running
Are you a complete beginner? If so, read [this](https://github.com/Ravbug/sdl3-sample/wiki/Setting-up-your-computer)!
Otherwise, install CMake and your favorite compiler, and follow the commands below:
```sh
# You need to clone with submodules, otherwise SDL will not download.
git clone https://github.com/Ravbug/sdl3-sample --depth=1 --recurse-submodules
cd sdl3-sample
cmake -S . -B build
```
You can also use an init script inside [`config/`](config/). Then open the IDE project inside `build/` 
(If you had CMake generate one) and run!


## Updating SDL
Just update the submodule:
```sh
cd SDL
git pull
cd ..

cd SDL_ttf
git pull
```
You don't need to use a submodule, you can also copy the source in directly. This
repository uses a submodule to keep its size to a minimum.
