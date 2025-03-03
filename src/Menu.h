#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "TextureManager.h"

class Menu {
private:
    SDL_Renderer* renderer;
    bool isActive; // Trạng thái menu (hiển thị hay không)
    // Các tài nguyên khác của menu, ví dụ: texture cho nút bấm
    // Ví dụ: SDL_Texture* startButton
    TTF_Font* font;
    std::string selectedMusicPath = "";
	std::string selectedChartPath = "";
	std::string selectedImagePath = "";
    int currentSongIndex;
public:
    Menu(SDL_Renderer* renderer);
    ~Menu();

    void init(); // Khởi tạo các tài nguyên riêng của menu (nếu cần)
    void handleEvents(); // Xử lý input (như nhấn nút Start)
    void update(); // Cập nhật logic của menu
    void render(); // Vẽ menu lên màn hình
    bool isMenuActive() const; // Kiểm tra xem menu đang hiển thị không
    void clean(); // Giải phóng tài nguyên
    std::string getSelectedMusicPath() const { return selectedMusicPath; }
    std::string getSelectedChartPath() const { return selectedChartPath; }
    std::string getSelectedImagePath() const { return selectedImagePath; }
};

#endif