#include "syntax.h"

UIElement* Button(int x, int y, int width, int height) {
    UIElement* button = new UIElement;
    button->type = UIElementType::BUTTON;
    button->rect = { x, y, width, height };
    button->texture = nullptr; // You may initialize the texture here if needed
    return button;
}

UIElement* Label(int x, int y, int width, int height, const std::string& text) {
    UIElement* label = new UIElement;
    label->type = UIElementType::LABEL;
    label->rect = { x, y, width, height}; // Width and height will be set when rendering
    label->texture = nullptr; // You may initialize the texture here if needed
    label->text = text;
    return label;
}

UIElement* TextBox(int x, int y, int width, int height) {
    UIElement* textbox = new UIElement;
    textbox->type = UIElementType::TEXTBOX;
    textbox->rect = { x, y, width, height };
    textbox->texture = nullptr; // You may initialize the texture here if needed
    return textbox;
}

// Function to handle events
void HandleEvents(SDL_Event event, UIElement** elements, int numElements) {
    // Iterate through UI elements and handle events
    for (int i = 0; i < numElements; ++i) {
        UIElement* element = elements[i];
        if (element == nullptr) {
            continue;
        }
        // Check for mouse click event
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;
            // Check if mouse click is within element's rectangle
            if (mouseX >= element->rect.x && mouseX <= (element->rect.x + element->rect.w) &&
                mouseY >= element->rect.y && mouseY <= (element->rect.y + element->rect.h)) {
                // Call onClick function if defined
                if (element->onClick != nullptr) {
                    element->onClick();
                    //render simple SDL box to show that a element has been clicked
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Element Clicked", "Element has been clicked", NULL);
                }
            }
        }
    }
}
