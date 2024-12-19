#include "Tree.h"
#include <string>
#include <fstream>
#include <cmath>

#include "raylib.h"


void readFile(Tree<std::string>& tree) {
    std::ifstream file("words.txt");
    std::string line;
    while (std::getline(file, line)) {
        tree.addEl(line);
    }
    file.close();
}


void drawTree(Node<std::string>* node, float x, float y, float offset, Camera2D camera, char inputChar) {
    if (node == nullptr)
        return;

    Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
    std::string tempString = node->data.substr(0, 5);
    Vector2 circlePosition = {x + 25.f, y + 10.f};
    Vector2 nextCirclePosition1 = {x - offset + 25.f, y + 100 + 10.f};
    Vector2 nextCirclePosition2 = {x + offset + 25.f, y + 100 + 10.f};
    float circleRadius = 40;
    if (CheckCollisionPointCircle(mousePosition, circlePosition, circleRadius)) {
        DrawText(node->data.c_str(), static_cast<int>(camera.target.x + 5), static_cast<int>(camera.target.y), 40, BLACK);
    }
    auto color = GREEN;
    if (tempString[0] == inputChar) {
        color = RED;
    }

    if (node->left != nullptr) {
        DrawLineEx(Vector2(circlePosition.x, circlePosition.y),  Vector2(nextCirclePosition1.x, nextCirclePosition1.y), 3, BLACK);
        drawTree(node->left, x - offset, y + 100, offset / 1.3f, camera, inputChar);
    }

    if (node->right != nullptr) {
        DrawLineEx(Vector2(circlePosition.x, circlePosition.y),  Vector2(nextCirclePosition2.x, nextCirclePosition2.y), 3, BLACK);
        drawTree(node->right, x + offset, y + 100, offset / 1.3f, camera, inputChar);
    }
    DrawCircle((int)circlePosition.x, (int)circlePosition.y, circleRadius, color);
    DrawText(tempString.c_str(), (int)x, (int)y, 20, BLACK);
}

int countSymbolEqual(Node<std::string>* node, char symbol) {
    int ans = 0;
    std::queue<Node<std::string>*> q;
    Node<std::string>* cur = node;
    q.push(cur);
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        if (cur->left != nullptr) {
            q.push(cur->left);
        }
        if (cur->right != nullptr) {
            q.push(cur->right);
        }
        if (cur->data[0] == symbol) {
            ans++;
        }
    }

    return ans;
}

void searchInFile(char inputChar, int count) {
    std::string line;
    std::ifstream file("words.txt");
    while (count) {
        std::getline(file, line);
        if (line[0] == inputChar) {
            count--;
        }
    }
}

void searchInTree(Node<std::string>* cur, char inputChar, int &count) {
    if (cur->left == nullptr && cur->right == nullptr) {
        if (count <= 0) {
            return;
        }
    }

    if (cur->data[0] == inputChar) {
        count--;
    }

    if (count <= 0) {
        return;
    }

    if (cur->left != nullptr && inputChar <= cur->data[0]) {
        searchInTree(cur->left, inputChar, count);
    }
    if (cur->right != nullptr && inputChar >= cur->data[0]) {
        searchInTree(cur->right, inputChar, count);
    }
}


int main() {
    const int width = 4098, height = 2024;
    InitWindow(width, height, "BinarySearchTree");
    Tree<std::string> tree;
    readFile(tree);

    Camera2D camera = {};
    camera.target = (Vector2){width / 2 - width / 4 + 50, -10.0f};
    camera.offset = (Vector2){0, 0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    char inputChar = '\0';
    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) camera.target.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) camera.target.x -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) camera.target.y += 2.0f;
        if (IsKeyDown(KEY_UP)) camera.target.y -= 2.0f;

        if (GetMouseWheelMove() > 0) camera.zoom += 0.05f;
        if (GetMouseWheelMove() < 0) camera.zoom -= 0.05f;

        int key = GetCharPressed();
        if (key > 0 && key >= 32 && key <= 125) {
            inputChar = (char)key;
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);
        int number = countSymbolEqual(tree.getRoot(), inputChar);
        std::string temp = "Char: ";
        temp += inputChar;
        std::string temp2 = "Count of nodes: ";
        temp2 += std::to_string(number);
        double timeFileSrch = 0;
        if (number != 0) {
            timeFileSrch = GetTime();
            searchInFile(inputChar, number);
            timeFileSrch = GetTime() - timeFileSrch;
        }
        std::string fileSearch = "Time of search in file: ";
        fileSearch += std::to_string(timeFileSrch);
        double timeTreeSrch = 0;
        if (number != 0) {
            timeTreeSrch = GetTime();
            int tempNumber = number;
            searchInTree(tree.getRoot(), inputChar, tempNumber);
            timeTreeSrch = GetTime() - timeTreeSrch;
        }
        std::string treeSearch = "Time of search in tree: ";
        treeSearch += std::to_string(timeTreeSrch);
        BeginMode2D(camera);
        drawTree(tree.getRoot(), width / 2 - 20, 20.0f, 600.0f, camera, inputChar);
        EndMode2D();
        DrawText(treeSearch.c_str(), static_cast<int>(camera.offset.x + 10),
            static_cast<int>(camera.offset.y + height / 3 + 150), 30, BLACK);
        DrawText(fileSearch.c_str(), static_cast<int>(camera.offset.x + 10),
            static_cast<int>(camera.offset.y + height / 3 + 200), 30, BLACK);
        DrawText(temp2.c_str(), static_cast<int>(camera.offset.x + 10),
            static_cast<int>(camera.offset.y + height / 3 + 250), 30, BLACK);
        DrawText(temp.c_str(), static_cast<int>(camera.offset.x + 10),
            static_cast<int>(camera.offset.y + height / 3 + 300), 40, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

