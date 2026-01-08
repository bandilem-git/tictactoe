#include <raylib.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#define RAYGUI_IMPLEMENTATION
using namespace std;

bool isInbox(int w, int h){
    if(GetMouseX()>0 && GetMouseY()> 0){
        if(GetMouseX()< w && GetMouseY() < h){
            return true;
        }
        return false;
    }
    return false;
}

int main(){
    // window constants
    const int w = 800;
    const int h = 800;
    const char* title = "Tic-Tac-Toe";
    
    InitWindow(w,h,title);
    SetTargetFPS(60);

    //decision variables
    bool mustDraw = false;
    
    //vertical lines starting x
    const int vertLine_1 = w * (0.35);
    const int vertLine_2 = vertLine_1 + w/4;

    // line constants int arr[2] = {start, end}
    const int vertLineHeight[2] = {h/6, h-vertLine_1/2} ;

    //horizontal lines starting x
    const int horizLine_1_x_start = vertLineHeight[0];
    const int horizLine_1_y_start = vertLine_1;
    const int horizLine_1_x_end = vertLineHeight[1];
    const int horizLine_1_y_end = vertLine_1;
    
    const int horizLine_2_x_start = vertLineHeight[0];
    const int horizLine_2_y_start = vertLine_2;
    const int horizLine_2_x_end = vertLineHeight[1];
    const int horizLine_2_y_end = vertLine_2;
    
    //Color of lines
    const Color lineColor = BLACK;

    //set vline vectors 
    const Vector2 vLine1_startPos ={(float)vertLine_1,(float)vertLineHeight[0]};
    const Vector2 vLine1_endPos ={(float)vertLine_1,(float)vertLineHeight[1]};
    const Vector2 vLine2_startPos ={(float)vertLine_2,(float)vertLineHeight[0]};
    const Vector2 vLine2_endPos ={(float)vertLine_2,(float)vertLineHeight[1]};

    //set hline vectors Width
    const Vector2 hLine1_startPos ={(float)horizLine_1_x_start,(float)horizLine_1_y_start,};
    const Vector2 hLine1_endPos ={(float)horizLine_1_x_end,(float)horizLine_1_y_start};
    const Vector2 hLine2_startPos ={(float)horizLine_2_x_start,(float)horizLine_2_y_start};
    const Vector2 hLine2_endPos ={(float)horizLine_2_x_end,(float)horizLine_2_y_end};

    //line width
    const float line_width = 20.0f;
    int player = 0;

    //player +position logic
    //turn player position
    vector<pair<char,Vector2>> playerMoves;

    char** twoDimArr = new char*[3];
    for(int i = 0; i < 3; i++){
        twoDimArr[i] = new char[3];
    }
    for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
        twoDimArr[i][j] = '\0';


    while (!WindowShouldClose()){   
        BeginDrawing();

        ClearBackground(RAYWHITE);
       for (auto& x : playerMoves) {
        char sym[2] = { x.first, '\0' };
        DrawText(sym, (int)x.second.x, (int)x.second.y, 50, BLACK);
        }

        const char* mousePosText = TextFormat("Mouse: %i, %i", GetMouseX(), GetMouseY());
        DrawText(mousePosText, 10, 10, 20, DARKGRAY);
        //Vertical lines {int startintX, int startintY}
        DrawLineEx(vLine1_startPos,vLine1_endPos,line_width,lineColor);
        DrawLineEx(vLine2_startPos,vLine2_endPos,line_width,lineColor);

        //Horizontal lines 
        DrawLineEx(hLine1_startPos,hLine1_endPos,line_width,lineColor);
        DrawLineEx(hLine2_startPos,hLine2_endPos,line_width,lineColor);

        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        Vector2 currentMouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isInbox(w, h)) {
            char playerSymbol = (player == 0) ? 'X' : 'O';
            Vector2 location = {(float)mouseX, (float)mouseY };


            cout << "Mouse x: " << mouseX << endl;
            cout << "Mouse y: " << mouseY << endl;

            //find  top row 
            
            bool canplace = true;

            if(mouseY <= horizLine_1_y_start){
                if(mouseX <= vLine1_startPos.x){
                    if(twoDimArr[0][0] == '\0')
                        twoDimArr[0][0] = playerSymbol;
                    else{
                        canplace = false;
                    }
                }
                else if(mouseX >= vLine2_startPos.x){
                    if(twoDimArr[0][2] == '\0')
                        twoDimArr[0][2] = playerSymbol;
                    else{
                        canplace = false;
                    }
                }
                else{
                    if(twoDimArr[0][1] == '\0')
                        twoDimArr[0][1] = playerSymbol;
                    else{
                        canplace = false;
                    }
                }
            }
            else if(mouseY > hLine1_startPos.y && mouseY <= hLine2_startPos.y){
                //goes up going down
               if(mouseX <= vLine1_startPos.x){
                    if(twoDimArr[1][0] == '\0')
                        twoDimArr[1][0] = playerSymbol;
                    else{
                        canplace = false;
                    }
                }
                else if(mouseX >= vLine2_startPos.x){
                    if(twoDimArr[1][2] == '\0')
                        twoDimArr[1][2] = playerSymbol;
                    else{
                        canplace = false;
                    }
                }
                else{
                    if(twoDimArr[1][1] == '\0')
                        twoDimArr[1][1] = playerSymbol;
                    else{
                        canplace = false;
                    }
                }
            }
            else{
                //goes up going down
               if(mouseX <= vLine1_startPos.x){
                    if(twoDimArr[2][0] == '\0')
                        twoDimArr[2][0] = playerSymbol;
                    else{
                        canplace = false;
                    }
                }
                else if(mouseX >= vLine2_startPos.x){
                    if(twoDimArr[2][2] == '\0')
                        twoDimArr[2][2] = playerSymbol;
                    else{
                        canplace = false;
                    }
                }
                else{
                    if(twoDimArr[2][1] == '\0')
                        twoDimArr[2][1] = playerSymbol;
                    else{
                        canplace = false;
                    }
                }
            }
                for(int i = 0,count = 1; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        cout << count<< ":"<< twoDimArr[i][j] << "\t";
                        if(count %3 == 0){
                            cout << endl;
                        }
                        count++;
                    }  
                }

            
            playerMoves.push_back({ playerSymbol, location });

                        

            player = (player == 0) ? 1 : 0;
        }
       
        EndDrawing();
    }
    CloseWindow();


    for(int i = 0; i < 3; i++){
        delete[] twoDimArr[i];
    }
    delete[] twoDimArr;

    return 0;
}
