#!/bin/bash

mkdir build
cd build

#qmake ../snomcontrol.pro CONFIG+=release
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr ..
make -j

make DESTDIR=appdir install

wget -c "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage" && chmod a+x linuxdeployqt*.AppImage

./linuxdeployqt*.AppImage ./appdir/usr/share/applications/*.desktop -bundle-non-qt-libs -no-strip
./linuxdeployqt*.AppImage ./appdir/usr/share/applications/*.desktop -appimage -no-strip

#find ./appdir -executable -type f -exec ldd {} \; | grep " => /usr" | cut -d " " -f 2-3 | sort | uniq
#ls -la

mv snomcontrol*.AppImage ../

cd -

echo ##########################################################################
