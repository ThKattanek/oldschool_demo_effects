# Oldschool Demo Effects
## This is a compilation of old demo effects with sdl2 in a single application.

### [Latest windows version here](https://github.com/ThKattanek/oldschool_demo_effects/releases/latest)

original sdl version -> http://demo-effects.sourceforge.net

### All implemented effects
* Plasma
* Blob
* Fire
* Bob
* Copperbars

### Using Libraries
* sdl2
* sdl2_ttf
* sdl2_image

### Build and installation under linux
```bash
git clone https://github.com/ThKattanek/oldschool_demo_effects.git
cd oldschool_demo_effects
git checkout 0.2.0
mkdir build
cd build
qmake .. PREFIX="/usr/local"
make -j8
sudo make install
```

## Screenshots
![Screenshot Plasma](screenshots/plasma.png)
![Screenshot Blob](screenshots/blob.png)
![Screenshot Fire](screenshots/fire.png)
![Screenshot Bob](screenshots/bob.png)
![Screenshot Copperbars](screenshots/copperbars.png)
