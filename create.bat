mkdir build
cd build

mkdir vs2015
cd vs2015
cmake -G "Visual Studio 14 2015" ..\..
cd ..

mkdir ninja
cd ninja
cmake -G "Ninja" ..\..
cd ..

cd ..



