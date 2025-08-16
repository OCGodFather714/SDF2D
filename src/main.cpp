#include <QApplication>
#include "AppWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("SDF2D");
    QApplication::setOrganizationName("Stephen D. Farrar II");
    QApplication::setApplicationVersion("0.1.0");

    AppWindow window;
    window.show();

    return app.exec();
}
