# Freedom Nostalgia

A game I sometimes hack on in my free time.

# Changes

I document the past, planned and working changes here.

## Currently working on

- [ ] completing an ECS
- [ ] a general map system
- [ ] a proper render queue
- [ ] simplifying the control system

## Planing to change

- making the control system more abstact
- adding multiple languages
- …

## Last changes

These are only the changes from the latest commit. For more information regarding the progess of this project see the [commits](https://https://github.com/davidpkj/freedom-nostalgia/commits/main) on this repository.

- Add: gamepad support (technically, not yet usable)
- Add: dedicated control system
- Add: first textures

# Downloading

This game is not yet up for download. If you are on a Linux based system however, you can build it from source like this:

Clone this repository:
```bash
git clone https://github.com/davidpkj/freedom-nostalgia
```

Create and enter a build directory:
```bash
cd freedom-nostalgia
mkdir build
cd build
```

Finally make the project:
```bash
cmake .. && make -j$(nproc)
```
