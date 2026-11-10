#include <QApplication>
#include <QMainWindow>
#include <QTabWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle(
        "Conversational Dynamics Engine"
    );

    window.resize(1200, 800);

    auto *tabs = new QTabWidget(&window);

    auto createPanel = [](const QString& title) {
        auto *panel = new QWidget();
        auto *layout = new QVBoxLayout(panel);

        auto *label = new QLabel(title);
        label->setAlignment(Qt::AlignCenter);

        layout->addWidget(label);

        return panel;
    };

    tabs->addTab(
        createPanel("Dialogue Stream"),
        "Stream"
    );

    tabs->addTab(
        createPanel("Ontology and Referents"),
        "Ontology"
    );

    tabs->addTab(
        createPanel("Relationships"),
        "Relationships"
    );

    tabs->addTab(
        createPanel("Prediction Engine"),
        "Predictions"
    );

    tabs->addTab(
        createPanel("Statistical Analysis"),
        "Statistics"
    );

    window.setCentralWidget(tabs);
    window.show();

    return app.exec();
}