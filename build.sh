echo -e "\033[7mclean\033[0m"
rm -rf *.o
rm -rf *.a

echo -e "\033[7mcreate xetws lib\033[0m"
g++ -std=c++11 -c xetws.cpp -o xetws.o
ar rcs xetws.a xetws.o

echo -e "\033[7mcopy to /lib/xe\033[0m"
sudo mkdir -p /lib/xe && sudo cp xetws.a /lib/xe/
