# supergfxctl-plasmoid

KDE Plasma plasmoid for [supergfxctl](https://gitlab.com/asus-linux/supergfxctl)  
Built as a C++/QML Plasmoid

## Features

- [x] Graphics mode switching
- [x] dGPU power indication
- [x] Dynamic plasmoid logo, tooltip
- [x] Filter available switches
- [x] Display dbus error message
- [x] Revert change

## Screenshot

<img src="https://gitlab.com/jhyub/supergfxctl-plasmoid/-/raw/master/screenshots/v1.0.0.png" alt="v1.0.0.png" width="300">

## Installation
### Arch User Repository
[plasma5-applets-supergfxctl](https://aur.archlinux.org/packages/plasma5-applets-supergfxctl)
### Fedora Copr [![Copr build status](https://copr.fedorainfracloud.org/coprs/jhyub/supergfxctl-plasmoid/package/supergfxctl-plasmoid/status_image/last_build.png)](https://copr.fedorainfracloud.org/coprs/jhyub/supergfxctl-plasmoid/package/supergfxctl-plasmoid/)
```shell
dnf copr enable jhyub/supergfxctl-plasmoid
dnf install supergfxctl-plasmoid
```
### Build yourself

```shell
git clone https://gitlab.com/Jhyub/supergfxctl-plasmoid
cd supergfxctl-plasmoid
git checkout [LATEST VERSION TAG HERE]
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make
sudo make install # or any other elevation tool
```

## Copyright Notice
Some files under ./icons/status are from or derived from [asusctl-gex](https://gitlab.com/asus-linux/asusctl-gex), which is distributed under the Mozilla Public License 2.0.
The following is an exhaustive list of files.  
```
supergfxctl-plasmoid-dgpu-active.svg
supergfxctl-plasmoid-dgpu-off.svg
supergfxctl-plasmoid-dgpu-suspended.svg
supergfxctl-plasmoid-gpu-copute.svg
supergfxctl-plasmoid-gpu-compute-active.svg
supergfxctl-plasmoid-gpu-dedicated.svg
supergfxctl-plasmoid-gpu-dedicated-active.svg
supergfxctl-plasmoid-gpu-egpu.svg
supergfxctl-plasmoid-gpu-egpu-active.svg
supergfxctl-plasmoid-gpu-hybrid.svg
supergfxctl-plasmoid-gpu-hybrid-active.svg
supergfxctl-plasmoid-gpu-integrated.svg
supergfxctl-plasmoid-gpu-integrated-active.svg
supergfxctl-plasmoid-gpu-vfio.svg
supergfxctl-plasmoid-gpu-vfio-active.svg
```
