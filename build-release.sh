#-------------------------------------------------
# 		builds project in release configuration
#-------------------------------------------------
./premake/premake5 gmake2
make config=release
./bin/Release-Platformer/Platformer