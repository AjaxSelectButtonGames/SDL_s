#include "Parser.h"
#include <sstream>
#include <iostream>
#include <algorithm>

// Parse the script and create AST
AST_Script Parser::ParseScript(const std::string& script) {
    AST_Script ast;

    // Create stringstream from script
    std::stringstream ss(script);
    std::string line;
    int lineNumber = 0;

    // Read each line from the script
    while (std::getline(ss, line)) {
        lineNumber++;

        // Skip empty lines and comments
        if (line.empty() || line.find("//") == 0) {
            continue;
        }

        // Ignore leading whitespace
        size_t start = line.find_first_not_of(" \t");
        if (start != std::string::npos) {
            line = line.substr(start);
        }

        // Check if line defines a UI element
        if (line.find("var") == 0) {
            std::cout << "Parsing line " << lineNumber << ": " << line << std::endl;
            ParseElementDeclaration(line, ast);
        }
        else {
            std::cerr << "Error: Line " << lineNumber << " does not define a UI element." << std::endl;
        }
    }

    std::cout << "Script parsing complete." << std::endl;

    return ast;
}





// C++
void Parser::ParseElementDeclaration(const std::string& line, AST_Script& ast) {
    // Extract UI element type and parameters from line
    std::string varKeyword, type;
    int x = -1, y = -1, width = -1, height = -1; // Initialize to -1 to indicate they haven't been set
    std::string text;

    // Parse line to extract type and parameters
    std::stringstream line_ss(line);
    line_ss >> varKeyword; // Read the var keyword

    // Read the type and opening parenthesis as a single string
    std::string typeAndParenthesis;
    line_ss >> typeAndParenthesis;

    // Split the type and opening parenthesis
    size_t pos = typeAndParenthesis.find('(');
    if (pos != std::string::npos) {
        type = typeAndParenthesis.substr(0, pos);
    }
    else {
        std::cerr << "Error: Invalid syntax on line." << std::endl;
        return;
    }

    // Convert type to uppercase
    std::transform(type.begin(), type.end(), type.begin(), ::toupper);

    // Ignore the opening parenthesis
    line_ss.ignore();

    // Read parameters
    if (type == "BUTTON" || type == "TEXTBOX" || type == "LABEL") {
        if (!(line_ss >> x)) {
            std::cerr << "Error: Failed to read 'x' value on line." << std::endl;
            return;
        }
        line_ss.ignore(); // skip comma
        if (!(line_ss >> y)) {
            std::cerr << "Error: Failed to read 'y' value on line." << std::endl;
            return;
        }
        line_ss.ignore(); // skip comma
        if (!(line_ss >> width)) {
            std::cerr << "Error: Failed to read 'width' value on line." << std::endl;
            return;
        }
        line_ss.ignore(); // skip comma
        if (!(line_ss >> height)) {
            std::cerr << "Error: Failed to read 'height' value on line." << std::endl;
            return;
        }
        if (type == "LABEL") {
            line_ss.ignore(); // skip space
            char nextChar = line_ss.peek();
            if (nextChar != '\"') {
                std::cerr << "Error: Text parameter for LABEL is not enclosed in double quotes." << std::endl;
                return;
            }
            std::string temp;
            std::getline(line_ss, temp);
            size_t startPos = temp.find('\"') + 1;
            size_t endPos = temp.rfind('\"');
            if (startPos == std::string::npos || endPos == std::string::npos || startPos >= endPos) {
                std::cerr << "Error: Text parameter for LABEL is not properly enclosed in double quotes." << std::endl;
                return;
            }

            const size_t maxTextLength = 100;
            if (endPos - startPos > maxTextLength) {
				std::cerr << "Error: Text parameter for LABEL exceeds maximum length of " << maxTextLength << " characters." << std::endl;
				return;
			}
            text = temp.substr(startPos, endPos - startPos);
        }

        // Create AST node for UI element
        AST_UIElement element;
        element.type = (type == "BUTTON") ? UIElementType::BUTTON :
            (type == "LABEL") ? UIElementType::LABEL : // Ensure "LABEL" is handled here
            (type == "TEXTBOX") ? UIElementType::TEXTBOX :
            UIElementType::BUTTON; // Default to button if type is unrecognized
        element.x = x;
        element.y = y;
        element.width = width;
        element.height = height;
        element.text = text;

        // Add UI element to AST
        ast.elements.push_back(element);

        // Print parsed UI element
        std::cout << "Parsed UI Element: Type=" << type << ", X=" << x << ", Y=" << y
            << ", Width=" << width << ", Height=" << height << ", Text=\"" << text << "\"" << std::endl;
    }
    else {
        std::cerr << "Error: Invalid UI element type '" << type << "' on line." << std::endl;
        return;
    }
}










