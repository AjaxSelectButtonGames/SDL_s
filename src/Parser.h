#pragma once
#ifndef PARSER_H
#define PARSER_H

#include "Syntax.h"
#include <string>
#include <vector>

// AST node for UI elements
struct AST_UIElement {
    UIElementType type;
    int x;
    int y;
    int width;
    int height;
    std::string text;
};

// AST node for a script
struct AST_Script {
    std::vector<AST_UIElement> elements;

   
};

// Parser class
class Parser {
public:
    // Parse the script and create AST
    static AST_Script ParseScript(const std::string& script);
private:
    // Helper function to parse each line of the script
    
    static void ParseElementDeclaration(const std::string& line, AST_Script& ast);
};

#endif
