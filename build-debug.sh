#-------------------------------------------------
# 		builds project in debug configuration
#-------------------------------------------------
./premake/premake5 gmake2
make config=debug
./bin/Debug-Platformer/Platformer