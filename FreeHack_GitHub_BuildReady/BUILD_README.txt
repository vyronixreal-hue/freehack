FREEHACK — ACTUAL BUILD FIX

The error "Unable to find platform binary under the name freehack.mod.dll"
happens because a source project was being installed as if it were a compiled
Geode package. A real Windows .geode must contain the compiled Windows binary.

This package is ready to build through GitHub Actions.

1. Create a new GitHub repository.
2. Upload ALL files/folders from this package to the repository.
3. Open the repository's Actions tab.
4. Select "Build FreeHack".
5. Choose "Run workflow".
6. When it finishes, open the workflow run and download the
   "FreeHack-Windows" artifact.
7. The downloaded .geode is the one to install in Geometry Dash.

Do NOT rename the source ZIP to .geode. That does not compile the DLL.

Your original source files are preserved.
