# supergfxctl-plasmoid 
KDE Plasma plasmoid for [supergfxctl](https://gitlab.com/asus-linux/supergfxctl)  
Built as a C++/QML Plasmoid
## Installation 
### Build yourself 
```shell
git clone https://gitlab.com/Jhyub/supergfxctl-plasmoid
cd supergfxctl-plasmoid
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make
sudo make install # or any other elevation tool
```
## Copyright Notice
Some files under ./icons/status and ./src/package/contents/images are from [asusctl-gex](https://gitlab.com/asus-linux/asusctl-gex), which is distributed under the Mozilla Public License 2.0.  
The following is an exhaustive list of files.  
```
dgpu-active.svg
dgpu-off.svg
dgpu-suspended.svg
supergfxctl-plasmoid-gpu-copute.svg
supergfxctl-plasmoid-gpu-compute-active.svg
supergfxctl-plasmoid-gpu-egpu.svg
supergfxctl-plasmoid-gpu-egpu-active.svg
supergfxctl-plasmoid-gpu-hybrid.svg
supergfxctl-plasmoid-gpu-hybrid-active.svg
supergfxctl-plasmoid-gpu-integrated.svg
supergfxctl-plasmoid-gpu-integrated-active.svg
supergfxctl-plasmoid-gpu-nvidia.svg
supergfxctl-plasmoid-gpu-nvidia-active.svg
supergfxctl-plasmoid-gpu-vfio.svg
supergfxctl-plasmoid-gpu-vfio-active.svg
```