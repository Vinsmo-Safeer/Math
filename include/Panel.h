#ifndef MATH_PANEL_H
#define MATH_PANEL_H

#include <iostream>
#include "RenderWindow.h"
#include "MouseHandler.h"
#include "DataProxy.h"
#include "Rect.h"

class Panel {

private:

    RenderWindow& window;
    DataProxy& dataProxy;

    int barWidth = 10;
    int wholeWidth = 0; // whole width include the size bar.
    int panelWidth = 0;

    bool draggingBar = false;

    Rect DeleteButton = Rect(0, 0, 0, 0);

public:
    Panel(RenderWindow& p_window, DataProxy& p_dataProxy);
    void setPanelWidth(int width);
    void reload();
    void buttonHandler();
    void draw();
    void update();

    void handleEvents();
    void cleanUp();

};

#endif //MATH_PANEL_H
