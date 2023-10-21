echo -e "\033[7mclean\033[0m"
rm -rf *.o
rm -rf *.a

echo -e "\033[7mcreate xetwl lib\033[0m"
g++ -std=c++11 -c xetwl.cpp -o xetwl.o
ar rcs xetwl.a xetwl.o

echo -e "\033[7mcopy files\033[0m"
sudo mkdir -p /usr/local/lib/xe/ && sudo cp xetwl.a /usr/local/lib/xe/libxetw.a
sudo mkdir -p /usr/local/include/xe/ && sudo cp xetwl.h /usr/local/include/xe/
