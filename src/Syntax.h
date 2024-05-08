#pragma once
#ifndef SYNTAX_H
#define SYNTAX_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string> // Include for std::string
#include <vector>
// UI Element types
enum class UIElementType {
	BUTTON,
	LABEL,
	TEXTBOX
};


// UI Element struct
struct UIElement {
    UIElementType type;
    SDL_Rect rect;
    SDL_Texture* texture;
    std::string text;
    void (*onClick)(void);

   

    // Getters for UIElement properties
    int getX() const { return rect.x; }
    int getY() const { return rect.y; }
    int getWidth() const { return rect.w; }
    int getHeight() const { return rect.h; }
};

// Function to create a button
UIElement* Button(int x, int y, int width, int height);

// Function to create a label
UIElement* Label(int x, int y, int width, int height, const std::string& text);

// Function to create a textbox
UIElement* TextBox(int x, int y, int width, int height);

// Function to handle events
void HandleEvents(SDL_Event event, UIElement** elements, int numElements);


#endif