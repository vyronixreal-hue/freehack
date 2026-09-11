# FreeHack starter project

## Build

1. Install/configure the Geode SDK and CLI.
2. Open a terminal in this folder.
3. Run `geode build`.
4. Install the generated `.geode` package if it was not auto-installed.

The current project targets the Geode v5.10.1 and Geometry Dash 2.2081. If your Geometry Dash/Geode setup is a different version, change the `gd.win` entry in `mod.json` to the exact version you are developing against.

## What is implemented

This first build is a real Geode mod project with:
- FreeHack branding
- a FreeHack button on the main menu
- a large dark multi-column interface inspired by the supplied screenshot
- grouped feature names
- clickable visual toggles
- close button
- project metadata/about/changelog

## Next implementation pass

The UI is deliberately separated from gameplay hooks. Individual entries such as FPS, practice helpers, replay tools, editor tools, cosmetic toggles, and other utilities can then be wired to actual Geometry Dash APIs one by one.


## Producing the actual `.geode` file

A `.geode` file is a compiled mod package, not just a renamed source ZIP. Geode's official documentation says to run `geode build`; the resulting `.geode` package is produced in the build folder. This project also contains `.github/workflows/build.yml` for building it with Geode's official GitHub build action.
