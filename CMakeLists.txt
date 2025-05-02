cmake_minimum_required(VERSION 3.10)
project(drum)

set(CMAKE_CXX_STANDARD 17)

# Đường dẫn thư viện SDL2, SDL2_mixer, SDL2_image
set(SDL2_DIR "D:/rhygame/drum/libs/SDL2")
set(SDL2_MIXER_DIR "D:/rhygame/drum/libs/SDL2_mixer")
set(SDL2_IMAGE_DIR "D:/rhygame/drum/libs/SDL2_image")
set(SDL2_TTF_DIR "D:/rhygame/drum/libs/SDL2_image")

# Thêm include path
include_directories(
    D:/rhygame/drum/libs/SDL2/include
    D:/rhygame/drum/libs/SDL2_image/include
    D:/rhygame/drum/libs/SDL2_mixer/include
    D:/rhygame/drum/libs/SDL2_ttf/include
)

# Thêm thư mục chứa file .lib
link_directories(
    D:/rhygame/drum/libs/SDL2/lib/x64
    D:/rhygame/drum/libs/SDL2_mixer/lib/x64
    D:/rhygame/drum/libs/SDL2_image/lib/x64
)

# Thêm các file nguồn

add_executable(drum src/main.cpp
    src/Game.cpp src/Game.h
    src/InputHandler.cpp src/InputHandler.h
    src/TextureManager.cpp src/TextureManager.h
    src/Note.cpp src/Note.h
    src/SoundManager.cpp src/SoundManager.h src/Menu.h src/Menu.cpp src/AfterGame.h src/AfterGame.cpp 
    src/ParticleSystem.h src/ParticleSystem.cpp "src/Song.h")
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/InputHandler.cpp
    src/TextureManager.cpp
    src/Note.cpp
    src/SoundManager.cpp
    src/Menu.cpp
    src/AferGame.cpp
    src/ParticleSystem.cpp# Đảm bảo file này có mặt!
)

# Liên kết thư viện
target_link_libraries(drum 
    D:/rhygame/drum/libs/SDL2/lib/x64/SDL2.lib
    D:/rhygame/drum/libs/SDL2/lib/x64/SDL2main.lib
    D:/rhygame/drum/libs/SDL2_mixer/lib/x64/SDL2_mixer.lib
    D:/rhygame/drum/libs/SDL2_image/lib/x64/SDL2_image.lib
    D:/rhygame/drum/libs/SDL2_ttf/lib/x64/SDL2_ttf.lib
)
