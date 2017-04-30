#include "MainWindow.h"

//constructors
MainWindow::MainWindow()
{
  m_ui = new Ui_MainWindow();
  m_ui->setupUi(this);
}
MainWindow::~MainWindow()
{
  delete m_ui;
}
