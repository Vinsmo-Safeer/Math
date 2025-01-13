#ifndef MATH_DELETEVECTORBUTTON_H
#define MATH_DELETEVECTORBUTTON_H

#include <iostream>
#include <string>
#include "PanelButtons.h"
#include "DataProxy.h"
#include "RenderWindow.h"

class DeleteVectorButton : public PanelButtons {
public:
    DeleteVectorButton(DataProxy& p_dataProxy, RenderWindow&p_window);

    void update(int mouseX, int mouseY) override;

private:
    RenderWindow& window;
    DataProxy& dataProxy;
};

#endif //MATH_DELETEVECTORBUTTON_H
