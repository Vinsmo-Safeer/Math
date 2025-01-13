#ifndef MATH_CONNECTVECTORBUTTON_H
#define MATH_CONNECTVECTORBUTTON_H

#include "DataProxy.h"
#include "RenderWindow.h"
#include "PanelButtons.h"

class ConnectVectorButton : public PanelButtons {
public:
    ConnectVectorButton(DataProxy& p_dataProxy, RenderWindow&p_window);

    void update(int mouseX, int mouseY) override;

private:
    DataProxy& dataProxy;
    RenderWindow& window;
};

#endif //MATH_CONNECTVECTORBUTTON_H
