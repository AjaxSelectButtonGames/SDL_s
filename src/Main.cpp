#include "parser.h"
#include "Syntax.h"
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow("SDL_S Script Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600, SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create an SDL renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    //Init SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        return 1;
    }

    // Load a font
    TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", 24); // Replace with your font path and size
    if (font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }



    // Load the script
    std::string sdlScript;
    std::ifstream scriptFile("scripts/1.sdl_s");
    if (scriptFile.is_open()) {
        std::string line;
        while (std::getline(scriptFile, line)) {
            sdlScript += line;
            sdlScript += '\n'; // Add newline character to preserve line breaks
        }
        std::cout << "Loading the script" << std::endl;
        scriptFile.close();
    }
    else {
        std::cerr << "Failed to open SDL_S script file." << std::endl;
        return 1; // Exit the program if the script file cannot be opened
    }

    // Parse the script
    Parser parser;
    AST_Script ast = parser.ParseScript(sdlScript);
    std::cout << "Parsing the script from Main call " << std::endl;
    // Create the UI elements
    std::vector<UIElement*> uiElements;
    for (const AST_UIElement& astElement : ast.elements) {
        UIElement* uiElement = nullptr;
        switch (astElement.type) {
        case UIElementType::BUTTON:
            uiElement = Button(astElement.x, astElement.y, astElement.width, astElement.height);
            std::cout << "Creating button at: " << astElement.x << ", " << astElement.y << std::endl;
            break;
        case UIElementType::LABEL:
            uiElement = Label(astElement.x, astElement.y,astElement.width, astElement.height,  astElement.text);
            std::cout << "Creating label at: " << astElement.x << ", " << astElement.y << std::endl;
            break;
        case UIElementType::TEXTBOX:
            uiElement = TextBox(astElement.x, astElement.y, astElement.width, astElement.height);
            std::cout << "Creating textbox at: " << astElement.x << ", " << astElement.y << std::endl;
            break;
        }
        if (uiElement != nullptr) {
            uiElements.push_back(uiElement);
        }
    }

    // Event loop
    bool quit = false;
    while (!quit) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            HandleEvents(event, uiElements.data(), uiElements.size());
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render UI elements
      
        for (UIElement* element : uiElements) {
            // Set the color based on the type of the UI element
            switch (element->type) {
            case UIElementType::BUTTON:
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for buttons
                break;
            case UIElementType::LABEL:
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for labels
                SDL_Color textColor = { 255, 255, 255, 255 }; // White text

                // Create a surface from the text
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, element->text.c_str(), textColor);
                if (textSurface == nullptr) {
                    std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
                    continue;
                }

                // Convert the surface to a texture
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture == nullptr) {
                    std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
                    SDL_FreeSurface(textSurface);
                    continue;
                }

                // Render the texture
                SDL_Rect textRect = { element->getX(), element->getY(), textSurface->w, textSurface->h };
                SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

                // Cleanup
                SDL_DestroyTexture(textTexture);
                SDL_FreeSurface(textSurface);

            }
                break;
            case UIElementType::TEXTBOX:
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for textboxes
                break;
            }

            // Render the UI element as a rectangle
            SDL_RenderFillRect(renderer, &element->rect);
        }


        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    for (UIElement* element : uiElements) {
       TTF_CloseFont(font);
       TTF_Quit();
		delete element;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
