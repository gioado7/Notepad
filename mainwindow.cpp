#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

// constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("AdoNotepad");
    setWindowIcon(QIcon(":/resources/img/icons8-notepad-80.png"));
    this->setCentralWidget(ui->textEdit);
}

// destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// triggers...

void MainWindow::on_actionNew_triggered() {
    file_path = "";
    ui -> textEdit -> setText("");
}

void MainWindow::on_actionCut_triggered() {
    ui -> textEdit -> cut();
}


void MainWindow::on_actionCopy_triggered() {
    ui -> textEdit -> copy();
}


void MainWindow::on_actionPaste_triggered() {
    ui -> textEdit -> paste();
}


void MainWindow::on_actionRedo_triggered() {
    ui -> textEdit -> redo();
}


void MainWindow::on_actionUndo_triggered() {
    ui -> textEdit -> undo();
}

void MainWindow::on_actionOpen_triggered() {
    QString name = QFileDialog::getOpenFileName(this, "Open File");
    QFile file(name);

    if (!file.open(QFile::ReadOnly | QFile::Text)) { // with flags
        QMessageBox::warning(this, "..", "File not opened");
        return;
    }

    QTextStream in(&file); // input
    QString text = in.readAll(); // read text
    ui -> textEdit -> setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered() {
    QFile file(file_path);

    if (!file.open(QFile::WriteOnly | QFile::Text)) { // with flags
        QMessageBox::warning(this, "..", "File not opened");
        return;
    }

    QTextStream out(&file); // input
    QString text = ui -> textEdit -> toPlainText(); // read text from area
    out << text; // write output
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_As_triggered() {
    QString name = QFileDialog::getSaveFileName(this, "Open file");
    QFile file(name);

    file_path = name;

    if (!file.open(QFile::WriteOnly | QFile::Text)) { // with flags
        QMessageBox::warning(this, "..", "File not opened");
        return;
    }

    QTextStream out(&file); // input
    QString text = ui -> textEdit -> toPlainText(); // read text from area
    out << text; // write output
    file.flush();
    file.close();
}

void MainWindow::on_actionAbout_Me_triggered() {
    QString text = "I'm George, author of this app!";

    QMessageBox messageBox("About Me",  // ignore depricated
                           text,
                           QMessageBox::Information,
                           QMessageBox::Yes | QMessageBox::Default,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);

    QPixmap exportSuccess(":/resources/img/icons8-notepad-80.png");
    messageBox.setIconPixmap(exportSuccess);
    messageBox.exec();
}
