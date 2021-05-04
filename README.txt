Code Run and Compiled on 
Ubuntu 20.04.2 LTS 
gcc compiler 
through VSCode


To compile code:
Install vcpkg at

https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=msvc-160

Type the following commands into terminal to Install
mkdir repo
cd repo
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
./vcpkg install curl[tools]
sudo apt-get install libcurl4-openssl-dev
./vcpkg install json-c

These commands should allow you to compile the program after reloading the terminal.
compile + flags:

gcc main.c -lcurl -ljson-c

My compiled executable is attached!

