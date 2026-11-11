
#include "MainWindow.h"

#include <QTabWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      tabs(new QTabWidget(this))
{
    setWindowTitle("Conversational Dynamics Engine");
    resize(1200, 800);

    setupTabs();

    setCentralWidget(tabs);
}

QWidget *MainWindow::createPanel(const QString &title)
{
    auto *panel = new QWidget(this);
    auto *layout = new QVBoxLayout(panel);

    auto *label = new QLabel(title, panel);
    label->setAlignment(Qt::AlignCenter);

    layout->addWidget(label);

    return panel;
}

void MainWindow::setupTabs()
{
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
}
